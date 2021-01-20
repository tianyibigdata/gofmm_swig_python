# "test.py"

import tools
import numpy as np

a = np.array([[2, -1, 0], [-1, 2, -1], [0, -1, 2]], dtype=np.double)

b = tools.load_denseSPD_from_console(a)

tools.launchhelper_denseSPD(b, "parameters_numpy_console.txt")
