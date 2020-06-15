rm -rf build
rm -r bin
mkdir build
mkdir bin
cd build
cmake ..
make
mv prefix_search ../bin
