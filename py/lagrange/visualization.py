import numpy as np
import matplotlib.pyplot as plt
from .interpolation import lagrange_interpolation, chebyshev_nodes

def plot_interpolation(func, a, b, N, num_points=1000, use_chebyshev=False):
    """
    Plots the original function and its Lagrange interpolation polynomial.

    Parameters:
        func (callable): The function to interpolate.
        a (float): Left boundary of the interpolation interval.
        b (float): Right boundary of the interpolation interval.
        N (int): Number of interpolation nodes.
        num_points (int): Number of points for smooth plotting.
        use_chebyshev (bool): Whether to use Chebyshev nodes instead of equidistant nodes.
    """
    if use_chebyshev:
        x_nodes = chebyshev_nodes(a, b, N)
    else:
        x_nodes = np.linspace(a, b, N)

    y_nodes = func(x_nodes)

    x_interpolation_values = (x_nodes[:-1] + x_nodes[1:]) / 2
    y_interpolation_values = lagrange_interpolation(x_interpolation_values, x_nodes, y_nodes)

    x_original_func_values = np.linspace(a, b, num_points)
    y_original_func_values = func(x_original_func_values)

    y_extra_interpolation_values = lagrange_interpolation(x_original_func_values, x_nodes, y_nodes)

    plt.plot(x_original_func_values, y_original_func_values, label='Original function', color='white', linewidth=2.5)
    plt.plot(x_original_func_values, y_extra_interpolation_values, label='Lagrange interpolation', color='magenta', linewidth=2.5)
    plt.scatter(x_nodes, y_nodes, label='Interpolation nodes', color='white', s=50)
    plt.scatter(x_interpolation_values, y_interpolation_values, label='Interpolation values', color='magenta', s=50)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.title('Lagrange Interpolation')
    plt.grid(True)
    plt.show()
