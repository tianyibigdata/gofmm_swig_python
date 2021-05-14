import matplotlib.pyplot as plt
import numpy as np
import scipy.sparse.linalg
import tools  # gofmm shared lib stuff
from scipy.linalg import eig, eigh
from scipy.sparse.linalg import LinearOperator

# NOTE: make sure "path/to/datafold" is in sys.path or PYTHONPATH if not ,!installed
#import datafold.dynfold as dfold
#import datafold.pcfold as pfold
#from datafold.utils.plot import plot_pairwise_eigenvector

random_state = 1

# Create data
n_pts = 128  # 1500
#rng = np.random.default_rng(random_state)
#data = rng.uniform(low=(-2, -1), high=(2, 1), size=(n_pts, 2))
#pcm = pfold.PCManifold(data)
#pcm.optimize_parameters()

#dmap = dfold.DiffusionMaps(
#    kernel=pfold.GaussianKernel(epsilon=pcm.kernel.epsilon),
#    n_eigenpairs=5,
#    dist_kwargs=dict(cut_off=pcm.cut_off),
#)
#dmap.fit(pcm, store_kernel_matrix=True)
#evecs, evals = dmap.eigenvectors_, dmap.eigenvalues_
#plot_pairwise_eigenvector(
#    eigenvectors=dmap.eigenvectors_,
#    n=1,
#    fig_params=dict(figsize=[5, 5]),
#    scatter_params=dict(cmap=plt.cm.Spectral, s=1),
#)



# TODO:
# - tic/toc for timing: total vs. 1x _matvec call etc. (import time from GOFMM?)
# - subprocess calls to GOFMM? <=> writing/reading the matrix, calling GOFMM externally?
class FullMatrix(LinearOperator):
    def __init__(self, matrixA, dtype="float32"):
        self.matrixA = tools.load_denseSPD_from_console(np.float32(matrixA))
        self.shape = matrixA.shape
        self.dtype = np.dtype(dtype)
        self.gofmmCalculator = tools.gofmmTree(executable, spdSize, m, k, s,nrhs,stol,budget,distance,matrixtype,kerneltype,self.matrixA)


    def _matvec(self, x):
        # TODO perform matvec with gofmm
        print(np.array(x.reshape(spdSize,1)).shape)
        print("adfadsfadsf")
        print(spdSize * nrhs)
        xx=np.vstack([x for i in range (nrhs)])
        print(xx.shape)
        print(self.shape)
        print(xx.reshape(spdSize,nrhs).shape)
        a= tools.load_matrix_from_console(np.float32(xx.reshape(spdSize,nrhs)))
        print("test")
        # print(x)
        dir(a)
        print(spdSize * nrhs)
        c = self.gofmmCalculator.mul_denseSPD(a, spdSize * nrhs)
        print("test")
        spdMatrix_mul = np.resize(c,(spdSize, nrhs))
        print(spdMatrix_mul[0])
        print(spdMatrix_mul.shape)
        return spdMatrix_mul



K = np.ones((n_pts,n_pts),dtype=np.float32) #dmap.kernel_matrix_
# print(type(K))
# print(K)
#K = K.todense()
# print(type(K))
# print(K)
K = K.astype("float32")
executable = "./test_gofmm"
spdSize = 128
m = 64
k = 0
s =16
nrhs = 64
stol = 1E-5
budget = 0.00
distance = "angle"
matrixtype = "testsuit"
kerneltype = "gaussian"



kernel_matrix_OP = FullMatrix(K, dtype=np.float32)
# assert(myOp.shape == (4,4))

# ?? inherit from class DmapKernelMethod(BaseEstimator): l. 435  in base.py
# das macht Klasse DiffusionMaps auch.

# symmetric case?
# => directly use
n_eigenpairs = 5
solver_kwargs = {
    "k": n_eigenpairs,
    "which": "LM",
    "v0": np.ones(n_pts),
    "tol": 1e-14,
}
evals_all, evecs_all = eigh(K)
print(evals_all[-n_eigenpairs:])
# assumed output:
# [0.35179151 0.36637801 0.48593941 0.50677673 0.74200987]
# TODO check relevance of l.59-68 in eigsolver.py
evals_large, evecs_large = scipy.sparse.linalg.eigsh(kernel_matrix_OP, **solver_kwargs)
print(evals_large)
# assumed output:
# [0.35179151 0.36637801 0.48593941 0.50677673 0.74200987]
print(np.dot(evecs_large.T, evecs_all[:, -n_eigenpairs:]))
# assumed output:
# [[ 1.  0.  0. -0. -0.]    # may vary (signs)
#  [-0.  1. -0.  0.  0.]
#  [ 0.  0.  1. -0. -0.]
#  [-0.  0. -0. -1.  0.]
