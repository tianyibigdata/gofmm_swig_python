# `Memo`
I'll try to document what I did specifically on a daily basis in this file,
such as what problems I ran into, my relevant thoughts and what tasks
I finished.

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
