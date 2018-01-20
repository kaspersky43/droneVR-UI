hudps = dsp.UDPSender('RemoteIPPort', 63846);
bytesSent = 0;
bytesReceived = 0;
dataLength = 128;

%dataSent = uint8(255*rand(1,dataLength));
%dataSent = unicode2native('1.2 3.4 5.0')
%bytesSent = bytesSent + dataLength;
%step(hudps, dataSent);

fprintf('Bytes sent:     %d\n', bytesSent);
z = 140.0
for i = 0:10
    x = num2str(30.0);

    y = num2str(-140.0);

    zStr = num2str(z);
    temp = [x, ' ', y, ' ', zStr]
    

    dataSent = unicode2native(temp);
    bytesSent = bytesSent + dataLength;
    step(hudps, dataSent);
    z = z + 30;
    pause(2)
end