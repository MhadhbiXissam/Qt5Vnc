# Qt5Vnc

## Steps : 
1   - installl Dependecies `bash install_dependecies.sh`: 
```bash
sudo apt update 
sudo apt install -y cmake qtbase5-dev xvfb x11vnc 
```
2   - setup qmake project `bash setup.sh`:   
> download libvncserver and build it locally 
```bash
git clone https://github.com/LibVNC/libvncserver.git
pushd libvncserver
mkdir build
cd build 
cmake ..
cmake --build .
popd 
cp libvncserver/build/libvncserver.so .
cp libvncserver/build/libvncclient.so . 
cp -r libvncserver/build/include/rfb .
cp libvncserver/include/rfb/* rfb/
rm -rf libvncserver 
qmake -project 
```

3   - setup qmake project `bash build.sh`:   
> build the qt5 app 
```bash
qmake qvnc.pro
make clean 
```

3   - setup qmake project `bash build.sh`:   
> build the qt5 app 
```bash
Xvfb :55 & 
x11vnc -display :55 -nopw -rfbport 5800 & 
./qvnc 127.0.0.1 5800 
```