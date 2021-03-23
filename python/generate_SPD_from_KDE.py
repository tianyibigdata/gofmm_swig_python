# generate_SPD_from_KDE.py
#!/usr/bin/env python
# coding: utf-8

# ### Generate Samples from the Posterior
# 
# The predictive posterior for Gaussian Process Regression is given by: 
# 
# $$ \boldsymbol{f_{*}} | X, \boldsymbol{f}, X_{*} \sim \mathcal{N} ( \: K(X_{*}, X) K(X,X)^{-1} \boldsymbol{f}, \; K(X_{*}, X_{*} ) - K(X_*, X) K(X,X)^{-1}K(X,X_*) \: )$$
# 
#  where $X_{*}$ contains the input points as columns. The matrix K is computed by using the squared exponential kernel function $ k(\boldsymbol{x_p}, \boldsymbol{x_q} ) = exp(-\frac{1}{2} \left| \boldsymbol{x_p} - \boldsymbol{x_q} \right|^2 ) $ for each combination of input points $ a_{ij} = k(x_i, x_j) $. 
# 
# According to A.2, to sample from a $ x \sim \mathcal{N}(\boldsymbol{m},K) $ with arbitrary mean $\boldsymbol{m}$ and covariance matrix K using a scalar Gaussian generator, we use the follow procedure:
# 
# 1. Compute Cholesk of K i.e. $K = LL^{\intercal}$
# 2. Generate $\boldsymbol{u} \sim \mathcal{N}(\boldsymbol{0}, I)$ by separate calls to scalar Gaussian generator
# 3. $\boldsymbol{x} = \boldsymbol{m} + L \boldsymbol{u} $

import numpy as np
import matplotlib.pyplot as plt

def sq_exp(x,y,length=1.0):
    "x,y: numpy arrays"
    return np.exp (-0.5 * np.linalg.norm( (x-y)/length, ord = 2) ** 2 ) 

def generateSPD_fromKDE(num_test):
    """Generate a SPD matrix using the KDE method.

    @num_test: the shape of the SPD, namely, num_test = row(K) = col(K)

    @ret: a SPD matrix using the KDE method
    """
    x_min = -5
    x_max = 5

    num_train = 10
    epsilon = 1e-6
    l = 1.0

    # evenly spaced training and test points
    training_points = np.linspace(x_min, x_max, num_train)
    test_points = np.linspace(x_min, x_max, num_test)
    function_values = np.sin(training_points)

    # submatrices

    K_x_star_x_star = np.zeros( (num_test, num_test) )

    for i, x_star_1 in enumerate(test_points):
        for j, x_star_2 in enumerate(test_points):
            K_x_star_x_star[i,j] = sq_exp( np.array([x_star_1]), np.array([x_star_2]), l)

    K_x_star_x = np.zeros( (num_test, num_train) )

    for i, x_star in enumerate(test_points):
        for j, x in enumerate(training_points):
            K_x_star_x[i, j] = sq_exp(np.array([x_star]), np.array([x]), l)

    K_x_x = np.zeros(( num_train, num_train)) 

    for i, x in enumerate(training_points):
        for j, y in enumerate(training_points):
            K_x_x[i, j] = sq_exp(np.array([x]), np.array([y]), l)

    K_x_x_star = np.zeros((num_train, num_test))

    for i, x in enumerate(training_points):
        for j, x_star in enumerate(test_points):
            K_x_x_star[i, j] = sq_exp(np.array([x]), np.array([x_star]), l)

    part_mean = np.dot(K_x_star_x, np.linalg.inv(K_x_x + epsilon * np.eye(num_train) ) )
    K = K_x_star_x_star - np.dot( part_mean, (K_x_x_star) ) + epsilon * np.eye(num_test)

    return K
    

# # sample from the posterior distribution

# # 1 cholesky
# chol = np.linalg.cholesky(K)

# # 2 separate samples from gaussian(0,1)
# samples_1 = np.random.standard_normal((num_test,1))
# samples_2 = np.random.standard_normal((num_test,1))

# # 3 compute regression output
# m = np.dot(part_mean, function_values[:, np.newaxis])

# m_1 = (m + np.dot(chol, samples_1)).reshape(-1)
# m_2 = (m + np.dot(chol, samples_2)).reshape(-1)




# plt.plot(test_points, m_1, color="red", label="test sample 1")
# plt.plot(test_points, m_2, color="blue", label="test sample 2")
# plt.scatter(training_points, function_values, color="green", label="training")
# plt.fill_between(test_points, (m_1 - 2 * np.sqrt( np.diag(K) ) ), (m_1 + 2 * np.sqrt (np.diag(K) ) ), alpha=0.5, color="blue", label="95% interval" )
# plt.legend()
# plt.tight_layout()











