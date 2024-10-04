import numpy as np

def chebyshev_nodes(a, b, N):
    """
    Calculate Chebyshev nodes on the interval [a, b].

    Parameters:
        a (float): Left boundary of the interpolation interval.
        b (float): Right boundary of the interpolation interval.
        N (int): Number of interpolation nodes.

    Returns:
        array-like: Chebyshev nodes on the interval [a, b].
    """
    k = np.arange(N)
    x_chebyshev = 0.5 * (a + b) + 0.5 * (b - a) * np.cos((2 * k + 1) / (2 * N) * np.pi)
    return x_chebyshev

def lagrange_interpolation(x, x_nodes, y_nodes):
    """
    Lagrange interpolation polynomial.

    Parameters:
        x (array-like): Points at which to evaluate the interpolation.
        x_nodes (array-like): Interpolation nodes (x-coordinates).
        y_nodes (array-like): Function values at interpolation nodes.

    Returns:
        array-like: Interpolated values at the points x.
    """
    L = np.zeros_like(x, dtype=float)
    N = len(x_nodes)
    for i in range(N):
        term = y_nodes[i]
        for j in range(N):
            if i != j:
                term *= (x - x_nodes[j]) / (x_nodes[i] - x_nodes[j])
        L += term
    return L
