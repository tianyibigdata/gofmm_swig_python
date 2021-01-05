#include <iostream>
#include <fstream>  // Use ifstream
#include <vector>
#include <string>


/* Use a binary tree */
#define N_CHILDREN 2


/* Define different spd matrix types */
typedef float T;
typedef SPDMatrix<T> SPDMATRIX_DENSE;

/* Create infrastructure for storing matrix in a tree */
/** Use the geometric-oblivious splitter from the metric ball tree. */
typedef gofmm::centersplit<SPDMATRIX_DENSE, N_CHILDREN, T> SPLITTER;
/** Use the geometric-oblivious splitter from the randomized tree. */
typedef gofmm::randomsplit<SPDMATRIX_DENSE, N_CHILDREN, T> RKDTSPLITTER;
/** Create configuration for all user-define arguments. */
typedef gofmm::Configuration<T> CONFIGURATION;
/** (Optional) provide neighbors, leave uninitialized otherwise. */
typedef Data<pair<T, size_t>> DATA;


class file_to_argv {
  /* A container to store argvs in vector and use destructor to automatically
     free the memory 
  */
 private:
  std::vector<const char*> argv;  // store the parameters

 public:
  /* constructors and destructors */
  file_to_argv();  // default constructor
  explicit file_to_argv(const char* filename);  // single parameter
  ~file_to_argv();

  /* Public methods*/
  void print_argv();  // print out parameters line by line
  std::vector<const char*> return_argv();  // return argv (deep copy)
};

hmlpError_t call_Launchhelper(const char* filename);

hmlpError_t launchhelper_denseSPD(SPDMATRIX_DENSE &K, const char* filename);

SPDMATRIX_DENSE load_denseSPD(uint64_t height,
                              uint64_t width,
                              const std::string &filename);

int hello_world();

hmlp::gofmm::dTree_t* Compress(hmlp::gofmm::dSPDMatrix_t K,
                               double stol,
                               double budget);

hmlp::gofmm::sTree_t* Compress(SPDMATRIX_DENSE &K, DATA NN, SPLITTER splitter,
                               RKDTSPLITTER rkds, CONFIGURATION config);
