% Pulls mocap data from connected OptiTrack cameras and sends the data over the network
 function NatNetMatlab()
	LOCAL_IP = '169.254.133.48';
	MASTER_PC_IP = '169.254.26.174';
	MASTER_PC_PORT = 6000;
	PI_ON_DRONE1_IP = '192.168.1.111';
	PI_ON_DRONE1_PORT = 7063;
 
    display('NatNet Sample Begin')
    
    global frameRate; 
    global masterUDPSender;
    global piOnDroneUDPSender;
	
    lastFrameTime = -1.0;
    lastFrameID = -1.0;
    useFrameReadyEvent = true;      % approach 3 : use event callback from NatNet (no polling)

    persistent arr;
    hFigure = figure('Name','OptiTrack NatNet Matlab Sample','NumberTitle','off');

    try
        % Add NatNet .NET assembly so that Matlab can access its methods, delegates, etc.
        % Note : The NatNetML.DLL assembly depends on NatNet.dll, so make sure they
        % are both in the same folder and/or path if you move them.
        display('[NatNet] Creating Client.')
		curDir = pwd;
		mainDir = fileparts(fileparts(curDir));
		dllPath = fullfile(mainDir,'..\OptiTrack\NatNetSDK\lib','x64','NatNetML.dll');
        display(dllPath);
        assemblyInfo = NET.addAssembly(dllPath);

        % Create an instance of a NatNet client
        theClient = NatNetML.NatNetClientML(0); % Input = iConnectionType: 0 = Multicast, 1 = Unicast
        version = theClient.NatNetVersion();
        fprintf( '[NatNet] Client Version : %d.%d.%d.%d\n', version(1), version(2), version(3), version(4) );

        % Connect to an OptiTrack server (e.g. Motive)
        display('[NatNet] Connecting to OptiTrack Server.')
        
        % Connect to a local stream.
        HostIP = char(LOCAL_IP);
        display(HostIP);
        flg = theClient.Initialize(HostIP, HostIP); % Flg = returnCode: 0 = Success
        
		if (flg == 0)
            display('[NatNet] Initialization Succeeded')
        else
            display('[NatNet] Initialization Failed')
        end
        
        % Print out a list of the active tracking Models in Motive
        GetDataDescriptions(theClient)
        
        % Test - send command/request to Motive
        [byteArray, retCode] = theClient.SendMessageAndWait('FrameRate');
        if(retCode ==0)
            byteArray = uint8(byteArray);
            frameRate = typecast(byteArray,'single');
        end
        
        masterUDPSender = dsp.UDPSender('RemoteIPAddress', MASTER_PC_IP , 'RemoteIPPort', MASTER_PC_PORT);
        piOnDroneUDPSender = dsp.UDPSender('RemoteIPAddress', PI_ON_DRONE1_IP , 'RemoteIPPort', PI_ON_DRONE1_PORT);
            
        % Get the mocap data
		display('Using event handler to get mocap data');
		ls = addlistener(theClient,'OnFrameReady2',@(src,event)FrameReadyCallback(src,event));
		display('[NatNet] FrameReady Listener added.');
        uiwait();

    catch err
        display(err);
    end

    % Cleanup
    theClient.Uninitialize();
    if(useFrameReadyEvent)
        if(~isempty(ls))
            delete(ls);
        end
    end
    clear functions;

    display('NatNet Sample End')
end


% Process data in a NatNet FrameReady Event listener callback
function FrameReadyCallback(src, event)
    global masterUDPSender;
    global piOnDroneUDPSender;
	
	frameOfData = event.data;
	
	% Loop through rigid bodies to send positional and rotational data
	if(frameOfData.RigidBodies.Length() > 0)
		dict = containers.Map; % Dictionary maps rigid body ID to JSON string containing pos/rot data
		iter = 1;
		while frameOfData.RigidBodies(iter).ID ~= 0
			rigidBodyData = frameOfData.RigidBodies(iter);
			iter = iter + 1;
						
			posX = rigidBodyData.x;
			posY = rigidBodyData.y;
			posZ = rigidBodyData.z;

			q = quaternion( rigidBodyData.qx, rigidBodyData.qy, rigidBodyData.qz, rigidBodyData.qw );
			qRot = quaternion( 0, 0, 0, 1);     % rotate pitch 180 to avoid 180/-180 flip for nicer graphing
			q = mtimes(q, qRot);
			angles = EulerAngles(q,'zyx');
			angleX = -angles(1) * 180.0 / pi;   % must invert due to 180 flip above
			angleY = angles(2) * 180.0 / pi;
			angleZ = -angles(3) * 180.0 / pi;   % must invert due to 180 flip above

			dict(num2str(rigidBodyData.ID)) = ['{"location":[',num2str(posX), ',', num2str(posY), ',', num2str(posZ), '],"Q":[' , num2str(rigidBodyData.qw), ',', num2str(angleX) ,',', num2str(angleY), ',' num2str(angleZ),']}'];
		end
		
		% Finish up JSON formatting of data before sending 
		piOutputFormat = '{';
		masterOutputFormat = '{';
		dictKeys = keys(dict);
		dictValues = values(dict);
		for k = 1:length(keys(dict));
			if k == length(keys(dict))
				masterOutputFormat = strcat(masterOutputFormat, '"', dictKeys(k), '"', ':', dictValues(k));        
			else
				masterOutputFormat = strcat(masterOutputFormat, '"', dictKeys(k), '"', ':', dictValues(k), ','); 
			end
		end
		masterOutputFormat = strcat(masterOutputFormat, '}');
		piOutputFormat = dictValues(1);
		piDataSent = unicode2native(piOutputFormat{1});
		masterDataSent = unicode2native(masterOutputFormat{1});
		step(masterUDPSender, masterDataSent);
		step(piOnDroneUDPSender, piDataSent);
		
		%display(piOutputFormat);
		%display(masterOutputFormat);
	end
end


% Print out a description of actively tracked models from Motive
function GetDataDescriptions( theClient )

    dataDescriptions = theClient.GetDataDescriptions();
    
    % print out 
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

    for idx = 1 : dataDescriptions.Count
        descriptor = dataDescriptions.Item(idx-1);
        if(descriptor.type == 0)
            fprintf('\n\tMarkerset : %s\t(%d markers)\n', char(descriptor.Name), descriptor.nMarkers);
            markerNames = descriptor.MarkerNames;
            for markerIndex = 1 : descriptor.nMarkers
                name = markerNames(markerIndex);
                fprintf('\t\tMarker : %-20s\t(ID=%d)\n', char(name), markerIndex);             
            end
        elseif(descriptor.type == 1)
            fprintf('\n\tRigid Body : %s\t\t(ID=%d, ParentID=%d)\n', char(descriptor.Name),descriptor.ID,descriptor.parentID);
        elseif(descriptor.type == 2)
            fprintf('\n\tSkeleton : %s\t(%d bones)\n', char(descriptor.Name), descriptor.nRigidBodies);
            %fprintf('\t\tID : %d\n', descriptor.ID);
            rigidBodies = descriptor.RigidBodies;
            for boneIndex = 1 : descriptor.nRigidBodies
                rigidBody = rigidBodies(boneIndex);
                fprintf('\t\tBone : %-20s\t(ID=%d, ParentID=%d)\n', char(rigidBody.Name), rigidBody.ID, rigidBody.parentID);
            end               
        end
    end

end