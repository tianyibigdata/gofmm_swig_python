# "test.py"

import tools
import numpy as np
from sklearn.datasets import make_spd_matrix

# ##############
# # numpy case #
# ##############
# # # Construct a 3x3 SPD matrix
# # spdMatrix = np.array([[2, -1, 0], [-1, 2, -1], [0, -1, 2]], dtype=np.double)

# # Construct a random n x n numpy spd matrix
# spdSize = 13  # Remmeber to change the parameter file accordingly
# spdMatrix = make_spd_matrix(spdSize)

# # load the numpy matrix into the tree container
# treeSpd = tools.load_denseSPD_from_console(spdMatrix)

# # run gofmm + accuracy
# tools.launchhelper_denseSPD(treeSpd, "parameters_numpy_console.txt")


# #################
# # testsuit case #
# #################
# tools.call_Launchhelper("parameters_testsuit.txt")


# ##################
# # dense SPD case #
# ##################
# # Run gofmm on a dense matrix
# # Apply gofmm on a large matrix which is located on a different path. We
# # do this to avoid upload the data onto gitlab
# denseSPD = tools.load_denseSPD(10000, 10000, "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/test.bin")
# tools.launchhelper_denseSPD(denseSPD, "parameters_dense.txt")


# ##########################################
# # mulplication of two dense SPD matrices #
# ##########################################
# # Construct a random n x n numpy spd matrix
# spdSize = 1000  # Remmeber to change the parameter file accordingly
# spdMatrix = make_spd_matrix(spdSize)
# # Here is a little test for the multiplication
# # spdMatrix = np.array([[2, 6], [6, 20]], dtype=np.double)

# # load the numpy matrix into the tree container
# treeSpd = tools.load_denseSPD_from_console(spdMatrix)

# # Construct a n x n indentity matrix
# # idMatrix = np.identity(spdSize)
# k2_col = 1
# idMatrix = 2 * np.ones((spdSize, k2_col))
# idTree = tools.load_denseSPD_from_console(idMatrix)

# # Do the multiplication
# # lenMatrix = spdSize ** 2  # Length of the 1D array
# lenMatrix = spdSize * k2_col  # Length of the 1D array
# c = tools.mul_denseSPD(treeSpd, idTree, lenMatrix)  # still 1D
# # print("The original SPD matrix is \n", spdMatrix)
# # print("\nThe multiplication result is \n",
# #       np.resize(c, (spdSize, k2_col)))  # Display 1D in 2D


#########################################
# # Inverse of a SPD using gofmm method #
#########################################
# Construct a random n x n numpy spd matrix
spdSize = 10  # Remmeber to change the parameter file accordingly
spdMatrix = make_spd_matrix(spdSize)
spdMatrix = np.float32(spdMatrix)

treeSpd = tools.load_denseSPD_from_console(spdMatrix)

len_of_inverseMat = spdSize ** 2

# return a 1d array which is a 2D matrix flattened row-wise
c = tools.invert_denseSPD(treeSpd,
                          "parameters_inverse.txt",
                          len_of_inverseMat)

# Display 1D in 2D
spdMatrix_inv = np.resize(c, (spdSize, spdSize))

# Dot product of the spd and its inverse
dotProduct = np.linalg.det(np.dot(spdMatrix, spdMatrix_inv))

print("\nThe original SPD matrix is \n", spdMatrix)
print("\nThe inverse is \n", spdMatrix_inv)
print("\nThe determinant of the two is\n", dotProduct)
