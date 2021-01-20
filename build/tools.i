// "tools.i"
%module tools

// Must include these two lib files before .cpp so that .cpp can see
// the types
%include "stdint.i" // Included to use uint64_t
%include <std_string.i>  // Included to use std::string


%{
  #define SWIG_FILE_WITH_INIT
  #include "../example/test_gofmm.cpp"
%}


// Use numpy array
%include "numpy.i"
%init %{
  import_array();
%}


%apply (double* IN_ARRAY2, int DIM1, int DIM2 ) \
      {(double* numpyArr, int row_numpyArr, int col_numpyArr)}

%include "../example/test_gofmm.cpp"

// %include "../example/test_gofmm.h"
