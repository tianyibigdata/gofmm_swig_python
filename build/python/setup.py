##  
##  HMLP (High-Performance Machine Learning Primitives)
##  
##  Copyright (C) 2014-2017, The University of Texas at Austin
##  
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##  
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
##  GNU General Public License for more details.
##  
##  You should have received a copy of the GNU General Public License
##  along with this program. If not, see the LICENSE file.
##  
  




from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy.distutils.misc_util



# #include directories
inc_dirs = numpy.distutils.misc_util.get_numpy_include_dirs()
inc_dirs = inc_dirs + ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/include']
inc_dirs = inc_dirs + ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/gofmm']
inc_dirs = inc_dirs + ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/frame']
inc_dirs = inc_dirs + ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/frame/base']
inc_dirs = inc_dirs + ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/frame/primitives']
inc_dirs = inc_dirs + ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/frame/containers']
print inc_dirs

# hmlp library directory
lib_dirs = ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/lib']
print lib_dirs





# the c++ extension module
extension_mod_hmlp = Extension( 
  "hmlp", 
  sources = ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/python/hmlp.pyx'],
  language="c++",
  include_dirs = inc_dirs,
  libraries = ['hmlp'],
  library_dirs = lib_dirs,
  runtime_library_dirs = lib_dirs,
  extra_compile_args=['-O3 -fopenmp -arch x86_64 -m64'],
  #extra_compile_args=["-fopenmp", "-O3", "-std=c++11",
  #	"-DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION"],
  extra_link_args=[' -lpthread -fopenmp -lm -L/usr/local/lib/ -lblas -llapack']
)



setup(
  author = 'Chenhan D. Yu',
  author_email = 'chenhan@utexas.edu',
  ext_modules = cythonize([extension_mod_hmlp]) )


# the c++ extension module
extension_mod_gofmm = Extension( 
  "gofmm", 
  sources = ['/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/python/gofmm.pyx'], 
  language="c++",
  include_dirs = inc_dirs,
  libraries = ['hmlp'],
  library_dirs = lib_dirs,
  runtime_library_dirs = lib_dirs,
  extra_compile_args=['-O3 -fopenmp -arch x86_64 -m64'],
  extra_link_args=[' -lpthread -fopenmp -lm -L/usr/local/lib/ -lblas -llapack']
)


setup(
  author = 'Chenhan D. Yu',
  author_email = 'chenhan@cs.utexas.edu',
  ext_modules = cythonize([extension_mod_gofmm]) )
