# Utils

## Installation

Prerequisites (indigo):
```bash
sudo apt-get install ros-indigo-rostest ros-indigo-roslint
sudo apt-get install ros-indigo-ackermann-msgs     # required for tug_joy
```
Prerequisites (kinetic):
```bash
sudo apt-get install ros-kinetic-rostest ros-kinetic-roslint
sudo apt-get install ros-kinetic-ackermann-msgs     # required for tug_joy
```

If protobuf is needed, also install:
at time of installtion at AiDrivers 28.06.2019, protobuf was not needed, actually it caused errors :)
```bash
sudo apt-get install protobuf-compiler libprotobuf-dev libprotoc-dev python-protobuf
```

