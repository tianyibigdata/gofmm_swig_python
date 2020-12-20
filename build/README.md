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

/home/getianyi/Documents/Master/Fall_2020/MasterThesis/tobiasPackage/docker4datafold/dockerTest_gcc/files_4_jupyterLab

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

compile:

$ sudo docker build --network=host -f ../dockerfiles/Dockerfile_test-gcc_gofmm-python-jupyterlab:shared    --tag=test-gcc:gofmm-python-jupyterlab-shared .
$ sudo python3.7 start-docker4gofmm.py -d /home/getianyi/work/datafold-testFork

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
