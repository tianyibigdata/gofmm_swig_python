#include <iostream>
#include <fstream>  // Use ifstream
#include <vector>
#include <string>


/* Use a binary tree */
#define N_CHILDREN 2


/* Define different spd matrix types */
typedef float T;
typedef SPDMatrix<T> SPDMATRIX_DENSE;
typedef Data<T> DATA_s;
typedef gofmm::CommandLineHelper CommandLineHelper;

/* Create infrastructure for storing matrix in a tree */
/** Use the geometric-oblivious splitter from the metric ball tree. */
typedef gofmm::centersplit<SPDMATRIX_DENSE, N_CHILDREN, T> SPLITTER;
/** Use the geometric-oblivious splitter from the randomized tree. */
typedef gofmm::randomsplit<SPDMATRIX_DENSE, N_CHILDREN, T> RKDTSPLITTER;
/** Create configuration for all user-define arguments. */
typedef gofmm::Configuration<T> CONFIGURATION;
/** (Optional) provide neighbors, leave uninitialized otherwise. */
typedef Data<pair<T, size_t>> DATA_PAIR;


class gofmmTree {
  /* This data structure gofmmTree enables storage of configuration
   parameters needed to execute mainly the following two operations:
   1. Mat-vec multiplication
   2. SPD Inverse 
  */
 private:
  SPDMATRIX_DENSE K;  // SPD Matrix
  std::vector<const char*> argv;  // holder for configuration parameters

  /* Configuration parameters */
  std::string executable;  // ./test_gofmm
  int n;  // problem size
  int m;  // maximum leaf node size
  int k;  // number of neighbors
  int s;  // maximum off-diagonal ranks
  int nrhs;  // number of right hand sides
  T stol;  // user tolerance
  T budget;  // user computation budget [0,1]
  std::string distance;  // distance type (geometry, kernel, angle)
  // spdmatrix type (testsuit, dense, ooc, kernel, userdefine)
  std::string matrixtype;
  std::string kerneltype;  // kernelmatrix type (gaussian, laplace)

 public:
  /* Constructors and destructors*/
  gofmmTree();  // default constructor

  // User-defined constructor: fill the inputs into the object fields above
  gofmmTree(std::string executableName, int n0, int m0, int k0, int s0,
            int nrhs0, T stol0, T budget0, std::string distanceName,
            std::string matrixtypeName, std::string kerneltypeName,
            SPDMATRIX_DENSE K0);

  // Convert all initialized configuration parameters to a vector (argv)
  void convert_to_vector();

  /* Operations: mul + inverse */
  void mul_denseSPD(DATA_s w, double* mul_numpy, int len_mul_numpy);
  void invert_denseSPD(T lambda, double* inv_numpy, int len_inv_numpy);
};


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

SPDMATRIX_DENSE load_denseSPD_from_console(float* numpyArr,
                                           int row_numpyArr,
                                           int col_numpyArr);

DATA_s load_matrix_from_console(float* numpyMat,
                                int row_numpyMat,
                                int col_numpyMat);
