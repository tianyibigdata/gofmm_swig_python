# "test.py"

import tools
import numpy as np

# Construct a 3x3 SPD matrix
spdMatrix = np.array([[2, -1, 0], [-1, 2, -1], [0, -1, 2]], dtype=np.double)

# load the numpy matrix into the tree container
treeSpd = tools.load_denseSPD_from_console(spdMatrix)

# run gofmm + accuracy
tools.launchhelper_denseSPD(treeSpd, "parameters_numpy_console.txt")
