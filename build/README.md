# `../memo`
I'll try to document what I did specifically on a daily basis in this file,
such as what problems I ran into, my relevant thoughts and what tasks
I finished.

# `../questions`
This file documents the questions that I should ask my mentor at our
next meeting.

# `../tools.i`
Notice: whenever we need to change the this file, please change it in
the `hmlp-1` directory not the `build` directory. The reason is that
we'll be running `bash swig.sh` after the change. And `../tools.i` will
replace the `tools.i` in the `build` directory


# `compile_log.txt`
This file records all output from a successful hmlp + gofmm compilation.
If you run into a common problem like "can't link some functions from
the llpack or lblas", please refer to the output of the cmd `source ..`
and `cmake ..` and see where you did wrong.

# `parameters_dense.txt`
This file specifies parameters of running program on a matrix given by
a matrix file. It's used as an input file to c++ functions
NOTICE: please leave no extra space or new line or any such kind!

# `parameters_testsuit.txt`
This file specifies parameters of running program on a randomly computer
generated matrix. It's used as an input file to c++ functions
NOTICE: please leave no extra space or new line or any such kind!

# `parameters_numpy_console.txt`
This file specifies parameters of running program on a user-input
numpy matrix.
NOTICE: please leave no extra space or new line or any such kind!

# `cmds`
Document how to call `gofmm` on random or dense matrix in python

# `swig.sh`
The file that enables to run gofmm in python

# `test.py`
The file to run `numpy` and `gofmm` together


# hmlp + gofmm implementation
1. Download and run blas and lapack as indicated by the website

https://coral.ise.lehigh.edu/jild13/2016/07/27/install-lapack-and-blas-on-linux-based-systems/

2. First check your `set_env.sh` file, do the necessary changes as indicated
by hanyu chen in the official hmlp README.md.

   Some changes I did:
   a. export OPENBLASROOT=false
   b. #export BLISROOT=/usr/lib/openblas-base/
   c. 



   


# GOFMM and SWIG Interface
Go to the directory for the file `gofmm.hpp`

/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/gofmm

Go to the directory for the file `test_gofmm.cpp`

We need to add the following features to the file `test_gofmm.cpp` so 
that the c functions can be imported into python

Call_gofmm(file_path):
	

compress():
	#compress a numpy array

evaluate

invert

compress + evaluate:
https://arxiv.org/pdf/1707.00164.pdf


inverse:
https://mediatum.ub.tum.de/doc/1522878/1522878.pdf

Goal:
https://royalsocietypublishing.org/doi/pdf/10.1098/rspa.2016.0751

# Problem between template and swig
1. Swig can't generate interface codes for a template until it is
instaniated with specific data types. Swig simply ignores the coding 
block.

Our task: instaniate the template in the .i file 
(Eg, put tree node data structure into skeletonize in the .i file)

www.swig.org/Doc3.0/SWIGDocumentation.html#SWIGPlus_nn30

# Run the ./test_gofmm
$ pwd 
......../build/
$ bash bin/run_gofmm_user....sh
modify your test_gofmm.cpp and try to produce the output here in the
python interface


# `hmlp-1/gitadd`
Store all the files that need to be added in git. The git add command to
use 
$ xargs -a gitadd -d '\n' git add


# Parameter setup file
// .exe program name, paraIdx = 0
./test_gofmm
// problem size, paraIdx = 1
n=5000
// maximum leaf node size, paraIdx = 2
m=64
// number of neighbors, paraIdx = 3
k=0
// maximum off-diagonal ranks, paraIdx = 4
s=64
// number of right hand sides, paraIdx = 5
nrhs=512
// user tolerance, paraIdx = 6
stol=1E-5
// user computation budget [0,1], paraIdx = 7
budget=0.00
// distance type (geometry, kernel, angle), paraIdx = 8
distance="angle"
// spdmatrix type (testsuit, dense, ooc, kernel, userdefine), paraIdx = 9
matrixtype="testsuit"
// kernelmatrix type (gaussian, laplace), paraIdx = 10
kerneltype="gaussian"
