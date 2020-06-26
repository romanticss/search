rm -rf build
rm -r bin
mkdir build
mkdir bin
cd build
cmake ..
make
mv invert_search ../bin
