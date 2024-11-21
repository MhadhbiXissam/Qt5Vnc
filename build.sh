set -e -x 
qmake PyQvnc.pro && make && make clean 
cp QVncViewer.hpp test/ 
cp QVncViewer.cpp test/ 
pushd test 
qmake Test.pro 
make 
make clean 
popd 