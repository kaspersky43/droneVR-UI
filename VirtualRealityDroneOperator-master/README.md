# VirtualRealityDroneOperator
## Hardware
[Unreal Engine](https://www.unrealengine.com/)  
[Oculus Rift](https://www.oculus.com/rift/)  
[Leap Motion](https://www.leapmotion.com/)  
[Raspberry Pi](https://www.raspberrypi.org/)  
[OptiTrack](http://optitrack.com/)  
[Pixhawk](https://pixhawk.org/)  
[QAV250 Drone](http://www.lumenier.com/products/multirotors/qav250/)  

## Installation
### Drone
  [Setup Raspberry Pi with DroneKit installation](http://ardupilot.org/dev/docs/raspberry-pi-via-mavlink.html)
  Clone repository onto Raspberry Pi  
  Checkout OnboardPiDroneClasses branch  
  Upload Pixhawk [firmware](Pixhawk/px4fmu-v2_lpe.px4) to drone using [QGroundControl](http://qgroundcontrol.com/)  
  SET PARAM:  
  - ATT_EXT_HDG_M to 2 to use motion capture data  
  - LPE_FUSION unselect using barometer  
  - FS_GPS set to 0  
  - GF_ACTION set to 0
  - CBRK_GPSFAIL set to 240024  
  - CBRK_USB_CHK set to 197848  
  - SYS_COMPANION set to 921600  
  
### Master PC
  Clone repository  
  [Install Python 2.7x](https://www.python.org/download/releases/2.7/)  

## Run
### Drone
  SSH into the Raspberry Pi host: pi@192.168.1.111 or 192.168.1.113 password: raspberry
  [Run OnBoard Main: python Main.py](VirtualRealityDroneProject/OnBoardDroneClasses/Main.py)  
### Master PC
  [Run: python Main.py](/VirtualRealityDroneProject/Main.py)  
### Streaming PC
  Setup rigid bodies in Motive (OptiTrack)  
  [Setup data streaming with Master and Oculus Rift PCs](http://wiki.optitrack.com/index.php?title=Data_Streaming_Pane)  
  [Run NatNetMatlabSample.m](NatNet/NatNetMatlabSample_Joey.m)  
### Oculus Rift PC
  Run VR executable  

