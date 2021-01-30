/**
 *  HMLP (High-Performance Machine Learning Primitives)
 *  
 *  Copyright (C) 2014-2018, The University of Texas at Austin
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see the LICENSE file.
 *
 **/  

/** Use GOFMM templates. */
#include <gofmm.hpp>
/** Use dense SPD matrices. */
#include <containers/SPDMatrix.hpp>
/** Use implicit kernel matrices (only coordinates are stored). */
#include <containers/KernelMatrix.hpp>
/** Use implicit matrices. */
#include <containers/VirtualMatrix.hpp>
/** Use implicit Gauss-Newton (multilevel perceptron) matrices. */
#include <containers/MLPGaussNewton.hpp>
/** Use OOC covariance matrices. */
#include <containers/OOCCovMatrix.hpp>
/** Use Gauss Hessian matrices provided by Chao. */
#include <containers/GNHessian.hpp>
/** Use STL and HMLP namespaces. */
#include "test_gofmm.h"
using namespace std;
// using namespace hmlp;

// class file_to_argv {
//   /* A container to store argvs in vector and use destructor to automatically
//      free the memory 
//   */
//  private:
//   std::vector<const char*> argv;  // store the parameters

//  public:
//   /* constructors and destructors */
//   file_to_argv();  // default constructor
//   explicit file_to_argv(const char* filename);  // single parameter
//   ~file_to_argv();

//   /* Public methods*/
//   void print_argv();  // print out parameters line by line
//   std::vector<const char*> return_argv();  // return argv (deep copy)
// };

file_to_argv::file_to_argv() {}  // size 0 vector initialization

file_to_argv::file_to_argv(const char* filename) {
  /* Read file line by line into argv (public field) */

  /* Construct vector string */
  std::string line;
  std::vector<std::string> parameters;
  std::ifstream file(filename);  // read the entire file
  std::string   para;            // parameter <-> each line in file

  // Reading every line in stream and push it into string vector
  while (std::getline(file, para))  // Keep reading in each parameter
    parameters.push_back(para);

  /* Convert vector string to vector char* by pushing */
  for (int i=0; i < parameters.size(); i++)
    argv.push_back(parameters[i].c_str());

  parameters.clear();  // clear the vector
}

file_to_argv::~file_to_argv() {
  argv.clear();  // free the vector
}

void file_to_argv::print_argv() {
  for (auto i = argv.begin(); i != argv.end(); ++i)
    std::cout << *i << '\n';  // print argvs line by line
}

std::vector<const char*> file_to_argv::return_argv() {
  return argv;
}


hmlpError_t call_Launchhelper(const char* filename) {
  /* Construct vector string */
  file_to_argv argvObj(filename);
  gofmm::CommandLineHelper cmd(argvObj.return_argv().size(),
                               argvObj.return_argv());  // avoid deep copy

  HANDLE_ERROR(hmlp_init());  // Initialize separate memory space at runtime

  /** random spd initialization */
  SPDMatrix<double> K(cmd.n, cmd.n);
  K.randspd(0.0, 1.0);

  hmlpError_t temp = gofmm::LaunchHelper(K, cmd);

  HANDLE_ERROR(hmlp_finalize());

  return temp;
}


hmlpError_t launchhelper_denseSPD(SPDMATRIX_DENSE &K, const char* filename) {
  /* Compress and evaluate a SPD dense matrix 

     @K: the compressed SPD matrix

     @filename: the file containing parameters
   */

  // Wrap parameters from filename line by line into argvObj
  file_to_argv argvObj(filename);
  gofmm::CommandLineHelper cmd(argvObj.return_argv().size(),
                               argvObj.return_argv());  // avoid deep copy

  HANDLE_ERROR(hmlp_init());  // Initialize separate memory space at runtime

  hmlpError_t temp = gofmm::LaunchHelper(K, cmd);

  HANDLE_ERROR(hmlp_finalize());

  return temp;
}


SPDMATRIX_DENSE load_denseSPD(uint64_t height,
                              uint64_t width,
                              const std::string &filename) {
  /* Return a newly constructed dense SPD matrix from an input data file. */
  SPDMATRIX_DENSE K(height, width, filename);
  return K;
}


int hello_world() {
  cout << "Hello World!"<< endl;
  return 0;
}


hmlp::gofmm::sTree_t* Compress(SPDMATRIX_DENSE &K, DATA_PAIR NN,
                               SPLITTER splitter, RKDTSPLITTER rkdtsplitter,
                               CONFIGURATION config) {
  /* Return a tree node that stores a compressed SPD matrix.

     @K: uncompressed SPD matrix

     @NN: Number of neighbors

     @config: parameters loaded from the parameter file

     @return: a tree node with all numeric data type in float
  */
  return hmlp::gofmm::Compress( K, NN, splitter, rkdtsplitter, config);
}


DATA_s Evaluate(hmlp::gofmm::sTree_t *tree, DATA_s &weights) {
/* Apply GOFMM on the compressed SPD matrix and return this data object

   @return: A newly construct object that is calculated by GOFMM based
   on a compressed SPD matrix

   @tree: a ptr to the tree object which stores the compressed SPD matrix
   with all numeric datatypes being double
  
   @weights: matrix of skeleton weights
*/
  
  return hmlp::gofmm::Evaluate(*tree, weights);
}


/** @brief Top level driver that reads arguments from the command line. */ 
int main( int argc, char *argv[] ) {
  try {
    /** Parse arguments from the command line. */
    gofmm::CommandLineHelper cmd(argc, argv);
    /** HMLP API call to initialize the runtime */
    HANDLE_ERROR(hmlp_init(&argc, &argv));
    // Print out argc, argv for debugging purposes
    // for (int i = 0; i < argc; i++)
    //   printf("The %d argument is %s\n", i, argv[i]);

    /** Run the matrix file provided by users. */
    if (!cmd.spdmatrix_type.compare("dense")) {
      using T = float;
      /** Dense spd matrix format. */
      SPDMatrix<T> K( cmd.n, cmd.n, cmd.user_matrix_filename );
      gofmm::LaunchHelper( K, cmd );
    }

    /** Run the matrix file provided by users. */
    if ( !cmd.spdmatrix_type.compare( "ooc" ) )
    {
      using T = double;
      /** Dense spd matrix format. */
      OOCSPDMatrix<T> K( cmd.n, cmd.n, cmd.user_matrix_filename );
      gofmm::LaunchHelper( K, cmd );
    }

    /** generate a Gaussian kernel matrix from the coordinates */
    if ( !cmd.spdmatrix_type.compare( "kernel" ) )
    {
      using T = double;
      /** Read the coordinates from the file. */
      Data<T> X( cmd.d, cmd.n, cmd.user_points_filename );
      /** Set the kernel object as Gaussian. */
      kernel_s<T, T> kernel;
      kernel.type = GAUSSIAN;
      if ( !cmd.kernelmatrix_type.compare( "gaussian" ) ) kernel.type = GAUSSIAN;
      if ( !cmd.kernelmatrix_type.compare(  "laplace" ) ) kernel.type = LAPLACE;
      kernel.scal = -0.5 / ( cmd.h * cmd.h );
      /** SPD kernel matrix format (implicitly create). */
      KernelMatrix<T> K( cmd.n, cmd.n, cmd.d, kernel, X );
      gofmm::LaunchHelper( K, cmd );
    }


    /** create a random spd matrix, which is diagonal-dominant */
    if ( !cmd.spdmatrix_type.compare( "testsuit" ) )
    {
      using T = double;
      /** dense spd matrix format */
      SPDMatrix<T> K( cmd.n, cmd.n );
      /** random spd initialization */
      K.randspd( 0.0, 1.0 );
      gofmm::LaunchHelper( K, cmd );
    }


    if ( !cmd.spdmatrix_type.compare( "mlp" ) )
    {
      using T = double;
      /** Read the coordinates from the file. */
      Data<T> X( cmd.d, cmd.n, cmd.user_points_filename );
      /** Multilevel perceptron Gauss-Newton */
      MLPGaussNewton<T> K;
      /** Create an input layer */
      Layer<INPUT, T> layer_input( cmd.d, cmd.n );
      /** Create FC layers */
      Layer<FC, T> layer_fc0( 256, cmd.n, layer_input );
      Layer<FC, T> layer_fc1( 256, cmd.n, layer_fc0 );
      Layer<FC, T> layer_fc2( 256, cmd.n, layer_fc1 );
      /** Insert layers into  */
      K.AppendInputLayer( layer_input );
      K.AppendFCLayer( layer_fc0 );
      K.AppendFCLayer( layer_fc1 );
      K.AppendFCLayer( layer_fc2 );
      /** Feed forward and compute all products */
      K.Update( X );
    }

    if ( !cmd.spdmatrix_type.compare( "cov" ) )
    {
      using T = double;
      OOCCovMatrix<T> K( cmd.n, cmd.d, cmd.nb, cmd.user_points_filename );
      gofmm::LaunchHelper( K, cmd );
    }

    if ( !cmd.spdmatrix_type.compare( "jacobian" ) ) 
    {
      using T = double;
      GNHessian<T> K;
      K.read_jacobian( cmd.user_matrix_filename );
      gofmm::LaunchHelper( K, cmd );
    }


    /** HMLP API call to terminate the runtime */
    HANDLE_ERROR( hmlp_finalize() );
    /** Message Passing Interface */
    //mpi::Finalize();
  }
  catch ( const exception & e )
  {
    cout << e.what() << endl;
    return -1;
  }
  return 0;
} /** end main() */


SPDMATRIX_DENSE load_denseSPD_from_console(double* numpyArr,
                                           int row_numpyArr,
                                           int col_numpyArr) {
  /* Load values of a numpy matrix `numpyArr` into a SPD matrix container
   
   @numpyArr: double pointer of type double

   @row_numpyArr: row of `numpyArr`

   @col_numpyArr: col of `numpyArr`

   @return: copy of a locally created SPD matrix which contains the values
            from `numpyArr`
  */
  SPDMATRIX_DENSE K(row_numpyArr, col_numpyArr);  // container for numpyArr

  // Fill the container
  int index = -1;
  for (int i = 0; i < row_numpyArr; i++)
    for (int j = 0; j < col_numpyArr; j++) {
      index = i * col_numpyArr + j;
      K.data()[index] = numpyArr[index];  // .data()'s type is double*
    }

  return K;
}


void mul_denseSPD(SPDMATRIX_DENSE K1,
                  SPDMATRIX_DENSE K2,
                  double* mul_numpy, int len_mul_numpy) {
  /* Multiply the SPD Matrices from the SPD container and save the result.

     @K1: the SPD container that has the underlying SPD matrix

     @mul_numpy: pointer that points to the result of multiplication of
     the matrix data of K1 and K2

     @len_mul_numpy: length of mul_numpy = row of K1 * col of K2
   */
  // mxk matrix * kxn matrix. Calculate the row and col of two matrices
  size_t row_K1 = K1.row();
  size_t col_K1 = K1.col();
  size_t row_K2 = K2.row();
  size_t col_K2 = K2.col();

  /* Check if the matrix muliplication can be performed */
  // Check the two inputs
  if (col_K1 != row_K2) {
    std::cerr << "Error: dimension of the two input matrices doesn't match!"
              << std::endl;
  }

  if ((row_K1 * col_K2) != len_mul_numpy) {
    std::cerr << "Error: size of the output matrix doesn't match the "
              << "input size m x n!\n"
              << std::endl;
  }

  /* Multiplication: mxk matrix * kxn matrix*/
  int index = -1;
  float* k1 = K1.data();  // Extract matrix data
  float* k2 = K2.data();

  for (size_t i = 0; i < row_K1; i++) {
    for (size_t j = 0; j < col_K2; j++) {
      index = i * col_K2 + j;
      mul_numpy[index] = 0;
      for (size_t k = 0; k < col_K1; k++) {
        mul_numpy[index] += k1[i * col_K1 + k] * k2[k * col_K2 + j];
      }
    }
  }
}
