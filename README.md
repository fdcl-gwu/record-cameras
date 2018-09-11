# Record-Cameras

This is a simple GUI for recording inputs from different cameras.

## Contents
1. [Dependencies](#dependencies)
2. [Building](#building)
3. [Configuring](#configuring)

## Dependencies

### CMake
On Linux:
```
sudo apt-get install build-essential pkg-config cmake
```

On Mac:
```
brew install cmake
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null
```


### Glade
Glade is used for the GUI. On Linux:
```
sudo apt-get install glade libgtkmm-3.0-dev
```

On Mac (with [Homebrew](https://brew.sh/) installed)
```
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null
brew install gtkmm3
brew install glade
```

### OpenCV

You can install the standalone ArUco library by downloading the source files which can be found in the above website and building and installing them.
But it is highly recommended to install ArUco library packed in OpenCV library.
The instruction below are for installing OpenCV with ArUco library.

You can install OpenCV using the master branch of their repository, **OR** using the submodules added to this repository.
Building and installing OpenCV with the provided submodules guarantees that the other codes on this repository works without issues.
So it is recommended to install from the submodules.


#### Installing v3.4.2 (recommended)
```
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

git submodule update --init
cd libraries/opencv
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
make -j4  # if you have more/less cores on your computer, substitute 4 with the number of cores
          # use command "nproc" to find the number fo cores
sudo make install
```


#### Installing the Latest
```
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

# if you need a specific version, you should checkout to that version on
# both repositories before executing the below commands

mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
make -j4  # if you have more cores on your computer, substitute 4 with the number of cores
          # use command "nproc" to find the number fo cores
sudo make install
```


## Building

Make sure you install all the dependencies, and execute the below commands.
```
cd record-cameras
mkdir build && cd build
cmake ../
make
```


## Configuring

After building, you can make a shortcut so that the GUI can be open easily from somewhere else.
1. Copy the `Record Cameras.desktop` file to place where you want to make a shortcut.
1. Open the `Record Cameras.desktop` and edit `Exec` and `Icon` paths to match yours based on where you cloned the files
1. Make this copied file an executable: `sudo chmod +x Record\ Cameras.desktop`
1. Now, if you double click the file, it should open the GUI.
