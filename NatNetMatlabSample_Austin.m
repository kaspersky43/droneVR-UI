
% Optitrack Matlab / NatNet Sample
% 
%  Requirements:
%   - OptiTrack Motive 1.5 or later
%   - OptiTrack NatNet 2.5 or later
%   - Matlab R2013
%

function NatNetMatlabSample()

    display('NatNet Sample Begin')
    
    global frameRate;
    lastFrameTime = -1.0;
    lastFrameID = -1.0;
    usePollingLoop = false;         % approach 1 : poll for mocap data in a tight loop using GetLastFrameOfData
    usePollingTimer = false;        % approach 2 : poll using a Matlab timer callback ( better for UI based apps )
    useFrameReadyEvent = true;      % approach 3 : use event callback from NatNet (no polling)
    useUI = true;

    persistent arr;
    % Open figure
    if(useUI)
        %figure() defines the biggest frame of the entire UI
        hFigure = figure('Name','OptiTrack NatNet Matlab Sample','NumberTitle','off');
    end

    try
        % Add NatNet .NET assembly so that Matlab can access its methods, delegates, etc.
        % Note : The NatNetML.DLL assembly depends on NatNet.dll, so make sure they
        % are both in the same folder and/or path if you move them.
        display('[NatNet] Creating Client.')
		curDir = pwd;
		mainDir = fileparts(fileparts(curDir));
		dllPath = fullfile(mainDir,'lib','x64','NatNetML.dll');
        assemblyInfo = NET.addAssembly(dllPath);

        % Create an instance of a NatNet client
        theClient = NatNetML.NatNetClientML(0); % Input = iConnectionType: 0 = Multicast, 1 = Unicast
        %NatNetClientML : instance allows an application to connect to a
        %server app 
        version = theClient.NatNetVersion();
        fprintf( '[NatNet] Client Version : %d.%d.%d.%d\n', version(1), version(2), version(3), version(4) );

        % Connect to an OptiTrack server (e.g. Motive)
        display('[NatNet] Connecting to OptiTrack Server.')
        
		% Connect to another computer's stream.
        %LocalIP = char('10.0.1.1'); % Enter your local IP address
        %ServerIP = char('10.0.1.200'); % Enter the server's IP address
        %flg = theClient.Initialize(LocalIP, ServerIP); % Flg = returnCode: 0 = Success
		
        % Connect to a local stream.
        HostIP = char('127.0.0.1');
        flg = theClient.Initialize(HostIP, HostIP); % Flg = returnCode: 0 = Success
        
		if (flg == 0)
            display('[NatNet] Initialization Succeeded')
        else
            display('[NatNet] Initialization Failed')
        end
        
        % print out a list of the active tracking Models in Motive
        GetDataDescriptions(theClient)
        
        % Test - send command/request to Motive
        [byteArray, retCode] = theClient.SendMessageAndWait('FrameRate');
        if(retCode ==0) %if sendmessagesandwait works normally
            byteArray = uint8(byteArray);
            frameRate = typecast(byteArray,'single');
        end
        
        % get the mocap data
        if(usePollingTimer)
            % approach 2 : poll using a Matlab timer callback ( better for UI based apps )
            framePerSecond = 200;   % timer frequency
            TimerData = timer('TimerFcn', {@TimerCallback,theClient},'Period',1/framePerSecond,'ExecutionMode','fixedRate','BusyMode','drop');
            start(TimerData);
            % wait until figure is closed
            uiwait(hFigure);
        else
            if(usePollingLoop)
                % approach 1 : get data by polling - just grab 5 secs worth of data in a tight loop
                for idx = 1 : 1000   
                   % Note: sleep() accepts [mSecs] duration, but does not process any events.
                   % pause() processes events, but resolution on windows can be at worst 15 msecs
                   java.lang.Thread.sleep(5);  

                    % Poll for latest frame instead of using event callback
                    data = theClient.GetLastFrameOfData();
                    frameTime = data.fLatency; %fLatency is the latency 
                    frameID = data.iFrame; %iFrame is the host defined frame number
                    if(frameTime ~= lastFrameTime)
                        fprintf('FrameTime: %0.3f\tFrameID: %5d\n',frameTime, frameID);
                        lastFrameTime = frameTime;
                        lastFrameID = frameID;
                    else
                        display('Duplicate frame');
                    end
                 end
            else
                % approach 3 : get data by event handler (no polling)
                % Add NatNet FrameReady event handler
                ls = addlistener(theClient,'OnFrameReady2',@(src,event)FrameReadyCallback(src,event));
                display('[NatNet] FrameReady Listener added.');
                % wait until figure is closed
                uiwait(hFigure);
            end
        end

    catch err
        display(err);
    end

    % cleanup
    if(usePollingTimer)
        stop(TimerData);
        delete(TimerData);
    end
    theClient.Uninitialize();
    if(useFrameReadyEvent)
        if(~isempty(ls))
            delete(ls);
        end
    end
    clear functions;

    display('NatNet Sample End')
    
end

% Test : process data in a Matlab Timer callback
function TimerCallback(obj, event, theClient)

    frameOfData = theClient.GetLastFrameOfData();
    UpdateUI( frameOfData );
    
end

% Test : Process data in a NatNet FrameReady Event listener callback
function FrameReadyCallback(src, event)
    
    frameOfData = event.data;
    %fprintf('Frame %s\n', num2str(frameOfData.iFrame));
    UpdateUI( frameOfData );
    
end

% Update a Matlab Plot with values from a single frame of mocap data
function UpdateUI( frameOfData )

    persistent lastFrameTime;
    persistent lastFrameID;
    persistent hX;
    persistent hY;
    persistent hZ;
    persistent arrayIndex;
    persistent frameVals;
    persistent xVals;
    persistent yVals;
    persistent zVals;
    persistent bufferModulo;

    global frameRate;
    
    % first time - generate an array and a plot
    if isempty(hX)
        % initialize statics
        bufferModulo = 256;
        frameVals = 1:255;
        xVals = zeros([1,255]);
        yVals = zeros([1,255]);
        zVals = zeros([1,255]);
        arrayIndex = 1;
        lastFrameTime = frameOfData.fLatency;
        lastFrameID = frameOfData.iFrame;
       
        % create plot
        hX = plot(frameVals, xVals, 'color', 'r');
        hold on;
        hY = plot(frameVals, yVals, 'color', 'g');
        hZ = plot(frameVals, zVals, 'color', 'b');
        title('Mocap Angle Plot');
        xlabel('Frame number');
        %ylabel('Angle (degrees)');
        %set(gca,'YLim',[-180 180]);    
        ylabel('Angle (degrees)');
        set(gca,'YLim',[-5 5]); 
        set(gca,'XGrid','on','YGrid','on');
    end

    % calculate the frame increment based on mocap frame's timestamp
    % in general this should be monotonically increasing according
    % To the mocap framerate, however frames are not guaranteed delivery
    % so to be accurate we test and report frame drop or duplication
    newFrame = true;
    droppedFrames = false;
    frameTime = frameOfData.fLatency;
    frameID = frameOfData.iFrame;
    calcFrameInc = round( (frameTime - lastFrameTime) * frameRate );
    % clamp it to a circular buffer of 255 frames
    calcFrameInc = 1;
    arrayIndex = mod(arrayIndex + calcFrameInc, bufferModulo);
    %disp(arrayIndex);
    if(arrayIndex==0)
        arrayIndex = 1;
    end
    if(calcFrameInc > 1)
        % debug
        % fprintf('\nDropped Frame(s) : %d\n\tLastTime : %.3f\n\tThisTime : %.3f\n', calcFrameInc-1, lastFrameTime, frameTime);
        droppedFrames = true;
    elseif(calcFrameInc == 0)
        % debug
        % display('Duplicate Frame')      
        newFrame = false;
    end
    
    % debug
    % fprintf('FrameTime: %0.3f\tFrameID: %d\n',frameTime, frameID);
    
    try
        if(newFrame)
            if(frameOfData.RigidBodies.Length() > 0)

                rigidBodyData = frameOfData.RigidBodies(1);

                % Test : Marker Y Position Data
                % angleY = data.LabeledMarkers(1).y;

                % Test : Rigid Body Y Position Data
                % angleY = rigidBodyData.y;

                % Test : Rigid Body 'Yaw'
                % Note : Motive display euler's is X (Pitch), Y (Yaw), Z (Roll), Right-Handed (RHS), Relative Axes
                % so we decode eulers heres to match that.
                q = quaternion( rigidBodyData.qx, rigidBodyData.qy, rigidBodyData.qz, rigidBodyData.qw );
                qRot = quaternion( 0, 0, 0, 1);     % rotate pitch 180 to avoid 180/-180 flip for nicer graphing
                q = mtimes(q, qRot);
                angles = EulerAngles(q,'zyx');
                angleX = -angles(1) * 180.0 / pi;   % must invert due to 180 flip above
                angleY = angles(2) * 180.0 / pi;
                angleZ = -angles(3) * 180.0 / pi;   % must invert due to 180 flip above
                           
                posX = rigidBodyData.x;
                posY = rigidBodyData.y;
                posZ = rigidBodyData.z;
                
                if(droppedFrames)
                    for i = 1 : calcFrameInc
                        fillIndex = arrayIndex - i;
                        if(fillIndex < 1)
                            fillIndex = bufferModulo-(abs(fillIndex)+1);
                        end
                        xVals(fillIndex) = posX;  
                        yVals(fillIndex) = posY;  
                        zVals(fillIndex) = posZ;  
                        %xVals(fillIndex) = angleX;  
                        %yVals(fillIndex) = angleY;  
                        %zVals(fillIndex) = angleZ; 
                    end
                end

                fprintf('Frame %s: X( %s ) Y( %s ) Z( %s )\n', num2str(frameOfData.iFrame), num2str(posX), num2str(posY), num2str(posZ));
                
                % update the array/plot for this frame
                xVals(arrayIndex) = posX;  
                yVals(arrayIndex) = posY;  
                zVals(arrayIndex) = posZ;  
                %xVals(arrayIndex) = angleX;  
                %yVals(arrayIndex) = angleY;  
                %zVals(arrayIndex) = angleZ;
                set(hX, 'YData', xVals);
                set(hY, 'YData', yVals);
                set(hZ, 'YData', zVals);

           end
        end
    catch err
        display(err);
    end
    
    lastFrameTime = frameTime;
    lastFrameID = frameID;

end

% Print out a description of actively tracked models from Motive
function GetDataDescriptions( theClient )

    dataDescriptions = theClient.GetDataDescriptions();
    %GetDataDescriptions() requests a list of dataset descriptions of the
    %capture session and saves onto the declared instance of a
    
    % print out 
    % nomination
    fprintf('[NatNet] Tracking Models : %d\n\n', dataDescriptions.Count);
    for idx = 1 : dataDescriptions.Count
        descriptor = dataDescriptions.Item(idx-1);
        if(descriptor.type == 0)
            fprintf('\tMarkerSet \t: ');
            fprintf('%s\n', char(descriptor.Name));
        elseif(descriptor.type == 1)
            fprintf('\tRigid Body \t: ');                
            fprintf('%s\n', char(descriptor.Name));
        elseif(descriptor.type == 2)
            fprintf('\tSkeleton \t: ');               
            fprintf('%s\n', char(descriptor.Name));
        else
            fprintf('\tUnknown data type : ');               
        end
    end

    % indicate the finer detail of the data
    for idx = 1 : dataDescriptions.Count
        descriptor = dataDescriptions.Item(idx-1); %descriptor indicating each object
        if(descriptor.type == 0) % mark all the 
            fprintf('\n\tMarkerset : %s\t(%d markers)\n', char(descriptor.Name), descriptor.nMarkers);
            markerNames = descriptor.MarkerNames;
            for markerIndex = 1 : descriptor.nMarkers
                name = markerNames(markerIndex);
                fprintf('\t\tMarker : %-20s\t(ID=%d)\n', char(name), markerIndex);             
            end
        elseif(descriptor.type == 1) %if the current data description is on the rigidbody
            fprintf('\n\tRigid Body : %s\t\t(ID=%d, ParentID=%d)\n', char(descriptor.Name),descriptor.ID,descriptor.parentID);
        elseif(descriptor.type == 2) %if the current data description is on the skeleton 
            fprintf('\n\tSkeleton : %s\t(%d bones)\n', char(descriptor.Name), descriptor.nRigidBodies);
            %fprintf('\t\tID : %d\n', descriptor.ID);
            rigidBodies = descriptor.RigidBodies;
            for boneIndex = 1 : descriptor.nRigidBodies %nRigidBodies tracking the total number of rigidbody assets both tracked and untracked
%                 rigidBody = rigidBodies(boneIndex);
                fprintf('\t\tBone : %-20s\t(ID=%d, ParentID=%d)\n', char(rigidBody.Name), rigidBody.ID, rigidBody.parentID);
            end               
        end
    end

end



 