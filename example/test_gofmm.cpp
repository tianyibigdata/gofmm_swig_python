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


gofmmTree::gofmmTree() {}  // size 0 vector initialization

gofmmTree::gofmmTree(std::string executableName, int n0, int m0, int k0, int s0,
                     int nrhs0, T stol0, T budget0, std::string distanceName,
                     std::string matrixtypeName, std::string kerneltypeName,
                     SPDMATRIX_DENSE K0):
    executable(executableName), n(n0), m(m0), k(k0), s(s0),
    nrhs(nrhs0), stol(stol0), budget(budget0), distance(distanceName),
    matrixtype(matrixtypeName), kerneltype(kerneltypeName) {
  K = K0;  // Initialize SPD matrix
  convert_to_vector();  // Initialize argv
}

void gofmmTree::convert_to_vector() {
  /* Called in the user-defined constructor, this method fills argv
     with  all configuration inputs 
  */
  std::vector<std::string> parameters;

  // Brute-force push all configuration parameters into the vector
  parameters.push_back(executable);
  parameters.push_back(std::to_string(n));
  parameters.push_back(std::to_string(m));
  parameters.push_back(std::to_string(k));
  parameters.push_back(std::to_string(s));
  parameters.push_back(std::to_string(nrhs));
  parameters.push_back(std::to_string(stol));
  parameters.push_back(std::to_string(budget));
  parameters.push_back(distance);
  parameters.push_back(matrixtype);
  parameters.push_back(kerneltype);

  /* Convert vector string to vector char* by pushing */
  for (int i=0; i < parameters.size(); i++)
    argv.push_back(parameters[i].c_str());

  parameters.clear();  // clear the vector
}

void gofmmTree::mul_denseSPD(DATA_s w, double* mul_numpy, int len_mul_numpy) {
  /* Compute the product of a SPD dense matrix K and a vector or matrix
     that is stored in DATA_s

   @w: w is a matrix or vector

   @mul_numpy: K * W

   @len_mul_numpy: length of the 1D array version for the mul numpy

   @ret: the multiplication result  is stored in the variable mul_numpy in place
  */

  gofmm::CommandLineHelper cmd(argv.size(), argv);  // avoid deep copy

  size_t n = cmd.n;  // Size of the SPD
  size_t nrhs = cmd.nrhs;  // col # of w

  // Check if the matrix multiplicatin Kw is viable
  if ((K.row() != n) || (w.row() != n) || (w.col() != nrhs)) {
    std::cerr << "Please check the shape of K and w must match the ones"
              << " specified in the parameter file \n";
    exit(0);
  }

  HANDLE_ERROR(hmlp_init());  // Initialize separate memory space at runtime

  /* Compress K into our gof tree */
  // 1st step: Argument preparation for fitting K into a tree
  /** GOFMM metric ball tree splitter (for the matrix partition). */
  SPLITTER splitter(K, cmd.metric);

  /** Randomized matric tree splitter (for nearest neighbor). */
  RKDTSPLITTER rkdtsplitter(K, cmd.metric);

  /** Create configuration for all user-define arguments. */
  CONFIGURATION config(cmd.metric,
                       cmd.n, cmd.m, cmd.k, cmd.s, cmd.stol,
                       cmd.budget, cmd.secure_accuracy);

  /** (Optional) provide neighbors, leave uninitialized otherwise. */
  Data<pair<T, size_t>> NN;

  /** 2nd step: compress K. */
  auto *tree_ptr = gofmm::Compress(K, NN, splitter, rkdtsplitter, config);

  auto &tree = *tree_ptr;

  /* Construct a random w and compute u = kw.*/
  Data<T> u = Evaluate(tree, w);

  /* Extract the multiplication result from u into mul_numpy */
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < nrhs; j++)
      mul_numpy[j + i * nrhs] = u(i, j);

  /** delete tree_ptr */
  delete tree_ptr;

  HANDLE_ERROR(hmlp_finalize());  
}

void gofmmTree::invert_denseSPD(T lambda,
                                double* inv_numpy,
                                int len_inv_numpy) {
  /* Compute the inverse of a SPD matrix K and output it in the variable 
     inv_numpy 

     @inv_numpy: the inverse of K

     @len_inv_numpy: length of the 1D array version for the inv_numpy

     @ret: the inverse is stored in the variable inv_numpy in place
  */
  gofmm::CommandLineHelper cmd(argv.size(),
                               argv);  // avoid deep copy

  HANDLE_ERROR(hmlp_init());  // Initialize separate memory space at runtime

  /* Compress K into our gof tree */
  // 1st step: Argument preparation for fitting K into a tree
  /** GOFMM metric ball tree splitter (for the matrix partition). */
  SPLITTER splitter(K, cmd.metric);

  /** Randomized matric tree splitter (for nearest neighbor). */
  RKDTSPLITTER rkdtsplitter(K, cmd.metric);

  /** Create configuration for all user-define arguments. */
  CONFIGURATION config(cmd.metric,
                       cmd.n, cmd.m, cmd.k, cmd.s, cmd.stol,
                       cmd.budget, cmd.secure_accuracy);

  /** (Optional) provide neighbors, leave uninitialized otherwise. */
  Data<pair<T, size_t>> NN;

  /** 2nd step: compress K. */
  auto *tree_ptr = gofmm::Compress(K, NN, splitter, rkdtsplitter, config);

  auto &tree = *tree_ptr;

  /* Construct the potential to be n x n identity matrix */
  size_t n = cmd.n;

  // Must change nrhs to be n in the new setup file for inverse
  Data<T> u(n, n);

  // Construct u as an identity matrix. Using 3 loops to enable parallelism
  for (size_t i = 0; i < n; i++)
    for (size_t j = i + 1; j < n; j++)
      u(i, j) = 0;

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < i; j++)
      u(i, j) = 0;

  for (size_t k = 0; k < n; k++)
    u(k, k) = 1;

  // Factorize as preparation
  gofmm::Factorize(tree, lambda);

  /* w = inv( K + lambda * I ) * u where w is weight and u is potential.
     and rhs is u, the potential. Already know K and u. Using Solve to 
     get w, which is stored in rhs.
     Since u is identity martix, w (which overwrites u) will be the inverse
     of w (still need regularization)
  */
  Solve(tree, u);

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      inv_numpy[j + i * n] = u(i, j);

  /** delete tree_ptr */
  delete tree_ptr;

  HANDLE_ERROR(hmlp_finalize());
}


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

hmlpError_t build_cmds(const char* filename) {
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


DATA_s load_matrix_from_console(float* numpyMat,
                                int row_numpyMat,
                                int col_numpyMat) {
  /* Load a numpy matrix into our self-defined DATA container. Mainly
     for loading w into DATA

     @numpyMat: if the input from the console is a numpy row array,
     it'll be first converted to a numpy column arr first in python before
     being processed by this function. This means col_numpyMat is at least
     1.

     @ret: return data in the container DATA_s.
  */
  DATA_s w(row_numpyMat, col_numpyMat);

  for (size_t i = 0; i < row_numpyMat; i++)
    for (size_t j = 0; j < col_numpyMat; j++)
      w(i, j) = numpyMat[j + i * col_numpyMat];
  return w;
}


SPDMATRIX_DENSE load_denseSPD_from_console(float* numpyArr,
                                           int row_numpyArr,
                                           int col_numpyArr) {
  /* Load values of a numpy matrix `numpyArr` into a SPD matrix container
   
   @numpyArr: double pointer of type float

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
