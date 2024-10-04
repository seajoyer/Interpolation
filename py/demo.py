import numpy as np
from lagrange import plot_interpolation

def f(x):
    return np.cos(np.exp(x / 3) / 10)

def main():
    plot_interpolation(f, a=0, b=10, N=5)
    plot_interpolation(f, a=0, b=10, N=5, use_chebyshev=True)

if __name__ == "__main__":
    main()
