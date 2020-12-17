cp tools.i build/
cd build
swig -o toolswrap.cpp -c++ -python tools.i
# Create a wrapper file for tools
g++ -o tools_wrap.os -c -I/usr/include/python3.5m -I../gofmm/ -I../include/ -I../frame/ -I ../frame/base/ -I../frame/containers/ toolswrap.cpp -fPIC
# Create a shared library. Note: we must link the lapack and blas libs
# at run time together with hmlp in order to construct a python-portable
# _tools.so
g++ -O3 -fopenmp -m64 -fPIC -D_POSIX_C_SOURCE=200112L -fprofile-arcs -ftest-coverage -fPIC -DUSE_BLAS -mavx -std=c++11  -lpthread -fopenmp -lm -L/usr/local/lib/ -lopenblas tools_wrap.os  -o _tools.so -shared  -Wl,-rpath,./build: libhmlp.so -Wl,-rpath,./build: libhmlp.so -Wl,-rpath,/usr/local/lib -lblas -Wl,-rpath,/usr/local/lib -llapack

