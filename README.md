# AiDrivers Sensor Diagnosis

## Installation

Clone this repo 
```
cd ~catkin_ws/src
git clone git@github.com:Ahmad-Drak/aid.git
```


Prerequisites (kinetic):
```bash
sudo apt install python-blist python-pygraph python-psutil python-scipy
sudo apt-get install ros-kinetic-rostest ros-kinetic-roslint
sudo apt-get install ros-kinetic-ackermann-msgs
```

Note: Some further dependencies might be needed during build time \
Note2: Protobuf is *NOT* needed at this time 28-06-2019. It breaks the build.
```
#We might need protobuf library for serilization of data
sudo apt install autoconf automake libtool curl make g++ unzip -y
git clone https://github.com/google/protobuf.git
cd protobuf
git submodule update --init --recursive
./autogen.sh
./configure
make #maybe use make -j8 if possible since its slow
make check
sudo make install
sudo ldconfig
#
#
#TODO: Might need these specific libraries instead
#sudo apt-get install protobuf-compiler libprotobuf-dev libprotoc-dev python-proto
```

Build
```
cd ~catkin_ws
catkin_make
```
