# errorAnalysis_gofmm.py
import tools
import numpy as np
from math import sqrt
from sklearn.datasets import make_spd_matrix

# Include all files in the python folder in the search path for import
import sys
sys.path.insert(1, '../python')
from generate_SPD_from_KDE import generateSPD_fromKDE


class gofmm_mulCalculator():
    """This is a child class of the rse_calculator. It speciflizes in
    calculating the rse of matrix multiplication."""
    def __init__(self, executable, n, m, k, s, nrhs, stol, budget,
                 distance, matrixtype, kerneltype, spdMatrix,
                 weight):
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

        # Construct a fix spd matrix and load it into SPDMATRIX_DENSE structure
        self.denseSpd = tools.load_denseSPD_from_console(self.spdMatrix)

        self.weight = np.float32(weight)  # from input

        # Construct a dummy w vector and load it into DATA structure
        self.wData = tools.load_matrix_from_console(self.weight)
        self.lenMul = self.spdSize * self.nrhs

    def matvec(self):
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

    # Construct K and w. Note: dtype is double
    # spdMatrix = make_spd_matrix(spdSize)
    spdMatrix = generateSPD_fromKDE(spdSize)
    w = np.ones((spdSize, nrhs))  # User defined, here w is a dummy vector
    lambda0 = 5.0  # regularization parameter

    rseCalculatorMul = gofmm_mulCalculator(executable, spdSize, m,
                                           k, s, nrhs, stol, budget,
                                           distance, matrixtype,
                                           kerneltype, spdMatrix,
                                           w)
    
    return rseCalculatorMul.matvec()


if __name__ == "__main__":
    mul = main()

    print(mul)
