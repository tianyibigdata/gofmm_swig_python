# errorAnalysis_gofmm.py
import tools
import numpy as np
from math import sqrt
from sklearn.datasets import make_spd_matrix

# Include all files in the python folder in the search path for import
import sys
sys.path.insert(1, '../python')
from generate_SPD_from_KDE import generateSPD_fromKDE

class rse_calculator():
    """Calculate the relative standard errors based on different inputn
    of parameters, eg, nrhs, stol..."""
    def __init__(self, executable, n, m, k, s, nrhs, stol, budget,
                 distance, matrixtype, kerneltype, spdMatrix):
        self.executable = executable
        self.spdSize = n  # from setup file
        self.m = m
        self.k = k
        self.s = s
        self.nrhs = nrhs
        self.stol = stol
        self.budget = budget
        self.distance = distance
        self.matrixtype = matrixtype
        self.kerneltype = kerneltype

        self.spdMatrix = np.float32(spdMatrix)  # from input

        """Class routines that are called in the constructor"""
        self.check_matrixShape()  # Check matrix shape

        # Construct a fix spd matrix and load it into SPDMATRIX_DENSE structure
        self.denseSpd = tools.load_denseSPD_from_console(self.spdMatrix)

    def check_matrixShape(self):
        """Abort if the shape of the input matrix doesnt match the one
        in the setup file. This is a preliminary check before we carry
        on any matrix operation.
        """
        if (self.spdMatrix.shape != (self.spdSize, self.spdSize)):
            raise ValueError("The shape of the input matrix-vector K doesn't match the one in the setup file\n")

    def modify_parameter(self, paraIdx, paraVal):
        """Modify a gofmm parameter according to parameter index and its value.

        @paraIdx[int]: each index corresponds to a parameter in the file.
        Please check the mapping in the file `build/README.md`

        @paraVal[int]: value of this parameter

        @ret: parameters as object fields will be modified
        """
        # # # Modify the specific parameter. If either s or m is modified,
        # # # we must modify the other so that s = m
        # # if (paraIdx == 2 or paraIdx == 4):
        # #     parameters[((2 | 4) ^ paraIdx)] = str(paraVal) + '\n'
        # parameters[paraIdx] = str(paraVal) + '\n'

        if (paraIdx == 0):
            self.executable = paraVal
        elif (paraIdx == 1):
            self.spdSize = paraVal
        elif (paraIdx == 2):
            self.m = paraVal
        elif (paraIdx == 3):
            self.k = paraVal
        elif (paraIdx == 4):
            self.s = paraVal
        elif (paraIdx == 5):
            self.nrhs = paraVal
        elif (paraIdx == 6):
            self.stol = paraVal
        elif (paraIdx == 7):
            self.budget = paraVal
        elif (paraIdx == 8):
            self.distance = paraVal
        elif (paraIdx == 9):
            self.matrixtype = paraVal
        elif (paraIdx == 10):
            self.kerneltype = paraVal
        else:
            raise ValueError("The requested parameter index is invalid as it is not equal to any integer from 0 to 10 \n")

    def compute_rse(self, matExp, matThe):
        """Compute the relative standard error of the experimental matrix
        gofmm against the benchmark, matThe.

        @matExp[numpy.ndarray]: experimental result

        @matThe[numpy.ndarray]: theoretical result

        @ret: relative std error (unit: in percent)
        """
        return np.linalg.norm(matExp - matThe) / sqrt(np.sum(matThe ** 2)) * 100


class spdMultiplication_rseCalulator(rse_calculator):
    """This is a child class of the rse_calculator. It speciflizes in
    calculating the rse of matrix multiplication."""
    def __init__(self, executable, n, m, k, s, nrhs, stol, budget,
                 distance, matrixtype, kerneltype, spdMatrix,
                 weight):
        # Call the constructor in the parent class (the holder class)
        rse_calculator.__init__(self, executable, n, m, k, s, nrhs,
                                stol, budget,
                                distance, matrixtype, kerneltype, spdMatrix)

        self.weight = np.float32(weight)  # from input

        """Class routines that are called in the constructor"""
        self.check_vectorShape()  # Check the shape of vector w

        # Construct a dummy w vector and load it into DATA structure
        self.wData = tools.load_matrix_from_console(self.weight)
        self.lenMul = self.spdSize * self.nrhs

        # Theoreitcla result of mat-vec multiplication
        self.matvecThe = np.matmul(self.spdMatrix, self.weight)

    def matvec(self):
        """The operation of matrix-vector multiplication. The calculation
        is based on updated instance attributes.

        @ret: multi-dimensional numpy array
        """
        # Initialize a new tree every time a parameter is modified
        # We use this re-initialization method instead of just passing
        # the modified parameter into the object. The reason is
        # we don't know the type of the parameter when we try to
        # pass the parameter in python to the one in c++. C++ needs
        # a clear type (parameters have 3 types, int, float, string)
        gofmmCalculator = tools.gofmmTree(self.executable, self.spdSize,
                                          self.m,
                                          self.k, self.s, self.nrhs,
                                          self.stol, self.budget,
                                          self.distance, self.matrixtype,
                                          self.kerneltype, self.denseSpd)

        # return a 1D array which is a 2D matrix flattened row-wise
        c = gofmmCalculator.mul_denseSPD(self.wData, self.lenMul)
        # resize it to 2D
        spdMatrix_mul = np.resize(c, (self.spdSize, self.nrhs))

        return spdMatrix_mul

    def check_vectorShape(self):
        """Abort if the shape of the input vector doesn't match the one
        in the setup file. This is a preliminary check before we carry
        on any matrix operation.
        """
        if (self.weight.shape != (self.spdSize, self.nrhs)):
            raise ValueError("The shape of the input vecotr w doesn't match the one in the setup file\n")

    def rse_analysis(self, idx, parameterList):
        """ Tune leaf node size and user tolerance to calculate the rse of
        our gofmm multiplication

        @idx: line number of the parameter. Please check the mapping in
        the file `build/README.md`

        @parameterList: a list of parameter value

        @ret: a list of rses wrt to changing parameter
        """
        rseList = []  # holder for rse
        for parameter in parameterList:
            self.modify_parameter(idx, parameter)

            spdMatrix_mul = self.matvec()

            rse = self.compute_rse(spdMatrix_mul, self.matvecThe)
            rseList.append(rse)
        return rseList


class spdInverse_rseCalulator(rse_calculator):
    """This is a child class of the rse_calculator. It specializes at
    calculating the rse of matrix multiplication."""
    def __init__(self, executable, n, m, k, s, nrhs, stol, budget,
                 distance, matrixtype, kerneltype, spdMatrix,
                 lambda0):
        # Call the constructor in the parent class (the holder class)
        rse_calculator.__init__(self, executable, n, m, k, s, nrhs,
                                stol, budget,
                                distance, matrixtype, kerneltype, spdMatrix)

        self.lambda0 = lambda0  # Regularization parameter from user defined

        # Calculate the theoretical inverse of the regularized spd matrix
        self.invThe = np.linalg.inv(self.spdMatrix + lambda0 * np.eye(self.spdSize))

    def inv(self):
        """The operation of matrix inverse. The calculation is based
        on updated instance attributes.

        @ret: multi-dimensional numpy array
        """
        # Initialize a new tree every time a parameter is modified
        # We use this re-initialization method instead of just passing
        # the modified parameter into the object. The reason is
        # we don't know the type of the parameter when we try to
        # pass the parameter in python to the one in c++. C++ needs
        # a clear type (parameters have 3 types, int, float, string)
        len_of_inverseMat = self.spdSize ** 2  # total # of entries in 1D
        gofmmCalculator = tools.gofmmTree(self.executable, self.spdSize,
                                          self.m,
                                          self.k, self.s, self.nrhs,
                                          self.stol, self.budget,
                                          self.distance, self.matrixtype,
                                          self.kerneltype, self.denseSpd)

        # return a 1D array which is a 2D matrix flattened row-wise
        c = gofmmCalculator.invert_denseSPD(self.lambda0, len_of_inverseMat)
        # resize it to 2D
        spdMatrix_inv = np.resize(c, (self.spdSize, self.spdSize))

        return spdMatrix_inv

    def rse_analysis(self, idx, parameterList):
        """ Tune leaf node size and user tolerance to calculate the rse of
        our gofmm inverse

        @idx: line number of the parameter. Please check the mapping in
        the file `build/README.md`

        @parameterList: a list of parameter value

        @ret: a list of rses wrt to changing parameter
        """
        rseList = []  # holder for rse
        for parameter in parameterList:
            self.modify_parameter(idx, parameter)

            spdMatrix_inv = self.inv()
            
            # Calculate the RSEs
            rse = self.compute_rse(spdMatrix_inv, self.invThe)
            rseList.append(rse)
        return rseList


def main():
    # Configuration parameters
    executable = "./test_gofmm"
    spdSize = 512
    m = 64
    k = 0
    s = 64
    nrhs = 1
    stol = 1E-5
    budget = 0.00
    distance = "angle"
    matrixtype = "testsuit"
    kerneltype = "gaussian"

    # Vary rank and user tolerance
    # Update the 2nd line of the setup file
    rank_idx = 4
    rank = [8, 32, 128, 256, 512, 1024][:2]
    # rank = [8, 32]
    # stol on the 6th line of the setup file
    stol_idx = 6
    stols = [1E-3, 1E-5, 1E-7]

    # Construct K and w. Note: dtype is double
    # spdMatrix = make_spd_matrix(spdSize)
    spdMatrix = generateSPD_fromKDE(spdSize)
    w = np.ones((spdSize, nrhs))  # User defined, here w is a dummy vector
    lambda0 = 5.0  # regularization parameter

    # List to hold the error result
    rseMul_iStol_jLeaf = []
    rseInv_iStol_jLeaf = []

    # """Calculate rses of multiplication due to changing leaf node size"""
    rseCalculatorMul = spdMultiplication_rseCalulator(executable, spdSize, m,
                                                      k, s, nrhs, stol, budget,
                                                      distance, matrixtype,
                                                      kerneltype, spdMatrix,
                                                      w)
    # For every user tolerance, calculate rse for different rank
    for stol in stols:
        rseCalculatorMul.modify_parameter(stol_idx, stol)
        rse = spdMultiplication_rseCalulator.rse_analysis(rseCalculatorMul,
                                                          rank_idx,
                                                          rank)
        rseMul_iStol_jLeaf.append(rse)

    """Calculate rses of inverse due to changing leaf node size"""
    rseCalculatorInv = spdInverse_rseCalulator(executable, spdSize, m,
                                               k, s, nrhs, stol, budget,
                                               distance, matrixtype,
                                               kerneltype, spdMatrix,
                                               lambda0)
    # For every user tolerance, calculate rse for different rank
    for stol in stols:
        rseCalculatorInv.modify_parameter(stol_idx, stol)
        rse = spdInverse_rseCalulator.rse_analysis(rseCalculatorInv,
                                                   rank_idx,
                                                   rank)
        rseInv_iStol_jLeaf.append(rse)

    # row: stol, col: rank
    return np.resize(rseMul_iStol_jLeaf, (len(stols), len(rank))), np.resize(rseInv_iStol_jLeaf, (len(stols), len(rank)))


if __name__ == "__main__":
    # row: stol, col: rank
    rseMul_iStol_jLeaf, rseInv_iStol_jLeaf = main()

    # Print out the errors from two matrix operations: mul + inv
    print("\n")
    print("-----------------------------------------------------------")
    print("RSE of matrix multiplication")
    print("-----------------------------------------------------------")
    print("row: stol, col: rank")
    print(rseMul_iStol_jLeaf)

    print("\n")
    print("-----------------------------------------------------------")
    print("RSE of matrix inverse")
    print("-----------------------------------------------------------")
    print("row: stol, col: rank")
    print(rseInv_iStol_jLeaf)
