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
using namespace std;
// using namespace hmlp;

/* Define different spd matrix types */
// Numeric datatype is double since python only accepts double officially
typedef double T;
typedef SPDMatrix<T> SPDMATRIX_DENSE;

SPDMATRIX_DENSE *load_denseSPD(uint64_t height,
                               uint64_t width,
                               const std::string & filename) {
  /* Return a pointer to a newly constructed dense SPD matrix from an
     input data file. */
  SPDMATRIX_DENSE K(height, width, filename);
  return &K;
}


hmlpError_t launchhelper_denseSPD(SPDMATRIX_DENSE *K, char *argv[]) {
  /* Compress and evaluate the input SPD dense matrix.

     @K: a ptr to the matrix data

     @argv: input parameters, eg, ./test_gofmm n m k s ... spdMatrixType
  */
  int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;
  gofmm::CommandLineHelper cmd(argc, argv);

  HANDLE_ERROR(hmlp_init());  // Initialize separate memory space at runtime

  /** random spd initialization */
  

  hmlpError_t temp = gofmm::LaunchHelper(*K, cmd);

  HANDLE_ERROR(hmlp_finalize());
  return temp;
}



int hello_world() {
  cout << "Hello World!"<< endl;
  return 0;
}



hmlp::gofmm::dTree_t* Compress(hmlp::gofmm::dSPDMatrix_t K,
                               double stol,
                               double budget) {
  /* Return a tree node that stores a compressed SPD matrix.

     @return: a tree node with all numeric data type in double

     @K: uncompressed SPD matrix

     @stol: tolerance
  */
  return hmlp::gofmm::Compress<double>(K, stol, budget);
}


// hmlp::Data<double> Evaluate(hmlp::gofmm::dTree_t *tree,
//                             hmlp::Data<double>    *weights) {
//   /* Apply GOFMM on the compressed SPD matrix and return this data object
//    (which is a r value)

//    @return: A newly construct object that is calculated by GOFMM based
//    on a compressed SPD matrix

//    @tree: a ptr to the tree object which stores the compressed SPD matrix
//    with all numeric datatypes being double
  
//    @weights: matrix of skeleton weights
//   */
//   return hmlp::gofmm::Evaluate<hmlp::gofmm::dTree_t, double>(*tree, *weights);
// }


// hmlpError_t call_Launchhelper() {
//   /* Run the "testsuit" case in python */
//   char arg0[] = "./test_gofmm";
//   char arg1[] = "5000";  // n
//   char arg2[] = "64";  // m
//   char arg3[] = "0";  // k
//   char arg4[] = "64";  // s
//   char arg5[] = "512";  // nrhs
//   char arg6[] = "1E-5";  // stol
//   char arg7[] = "0.00";  // budget
//   char arg8[] = "angle";  // distanceType
//   char arg9[] = "testsuit";  // spdMatrixType
//   char arg10[] = "status=0";  // spdMatrixType
//   char* argv[] = {&arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0],
//                   &arg5[0], &arg6[0], &arg7[0], &arg8[0], &arg9[0],
//                   &arg10[0], NULL};
//   int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

//   gofmm::CommandLineHelper cmd(argc, argv);
//   HANDLE_ERROR(hmlp_init());  // Initialize separate memory space at runtime

//   /** random spd initialization */
//   SPDMatrix<double> K(cmd.n, cmd.n);
//   K.randspd(0.0, 1.0);

//   hmlpError_t temp = gofmm::LaunchHelper(K, cmd);

//   HANDLE_ERROR(hmlp_finalize());
//   return temp;
// }



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
      using T = double;
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
}; /** end main() */