
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


