%module tools

// Must include these two lib files before .cpp so that .cpp can see
// the types
%include "stdint.i" // Included to use uint64_t
%include <std_string.i>  // Included to use std::string


%{
#include "../example/test_gofmm.cpp"
%}
%include "../example/test_gofmm.cpp"

