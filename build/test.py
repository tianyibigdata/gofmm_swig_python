# "test.py"

import tools
import numpy as np
from sklearn.datasets import make_spd_matrix

##############
# numpy case #
##############
# # Construct a 3x3 SPD matrix
# spdMatrix = np.array([[2, -1, 0], [-1, 2, -1], [0, -1, 2]], dtype=np.double)

# Construct a random n x n numpy spd matrix
spdSize = 10
spdMatrix = make_spd_matrix(spdSize)

# load the numpy matrix into the tree container
treeSpd = tools.load_denseSPD_from_console(spdMatrix)

# run gofmm + accuracy
tools.launchhelper_denseSPD(treeSpd, "parameters_numpy_console.txt")


#################
# testsuit case #
#################
tools.call_Launchhelper("parameters_testsuit.txt")


# ##################
# # dense SPD case #
# ##################
# # Run gofmm on a dense matrix
# # Apply gofmm on a large matrix which is located on a different path. We
# # do this to avoid upload the data onto gitlab
# denseSPD = tools.load_denseSPD(10000, 10000, "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/test.bin")
# tools.launchhelper_denseSPD(denseSPD, "parameters_dense.txt")
