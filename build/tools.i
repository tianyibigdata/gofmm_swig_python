// "tools.i"
%module tools


// Must include these two lib files before .cpp so that .cpp can see
// the types
%include "stdint.i" // Included to use uint64_t
%include <std_string.i>  // Included to use std::string


/* Initialize the swig and c++ interface: can only be done once */
%{
  #define SWIG_FILE_WITH_INIT
  #include "../example/test_gofmm.cpp"
%}


/* Use numpy array: this section must be placed before .cpp include */
%include "numpy.i"
%init %{
  import_array();
%}

// Typemap: the order and names of the parameteres must match exactly
// the function args in the cpp file. `\` is the line separator
%apply (double* IN_ARRAY2, int DIM1, int DIM2 ) \
      {(double* numpyArr, int row_numpyArr, int col_numpyArr)}


/* Typically in the end */
%include "../example/test_gofmm.h"

