cd /tmp || exit
mkdir cmake-build
cd cmake-build || exit
cmake /app
cmake --build .
./main
