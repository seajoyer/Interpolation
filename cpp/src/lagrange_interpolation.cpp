#include "lagrange_interpolation.h"
#include <cmath>

std::vector<double> LagrangeInterpolation::uniformNodes(double a, double b, int n) {
    std::vector<double> nodes(n);
    double h = (b - a) / (n - 1);
    for (int i = 0; i < n; ++i) {
        nodes[i] = a + i * h;
    }
    return nodes;
}

std::vector<double> LagrangeInterpolation::chebyshevNodes(double a, double b, int n) {
    std::vector<double> nodes(n);
    for (int i = 0; i < n; ++i) {
        double t = std::cos((2.0 * i + 1) / (2 * n) * M_PI);
        nodes[i] = (a + b) / 2 + (b - a) / 2 * t;
    }
    return nodes;
}

double LagrangeInterpolation::interpolate(const std::vector<double>& x, const std::vector<double>& y, double x_star) {
    double result = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double term = y[i];
        for (size_t j = 0; j < x.size(); ++j) {
            if (j != i) {
                term *= (x_star - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

std::vector<double> LagrangeInterpolation::interpolateRange(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& x_star) {
    std::vector<double> y_star(x_star.size());
    for (size_t i = 0; i < x_star.size(); ++i) {
        y_star[i] = interpolate(x, y, x_star[i]);
    }
    return y_star;
}
