#include "lagrange_interpolation.h"
#include "plotting.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

const double LEFT_RANGE_BOUNDARY  = 0.0;
const double RIGHT_RANGE_BOUNDARY = 10.0;
const int NUM_INTERPOLATION_NODES = 5;
const int FUNCTION_EXTRA_POINTS   = 1000;

double f(double x) {
    return std::cos(std::exp(x / 3) / 10);
}

void splitIntervalEvenly(const double a, const double b, size_t n,
                         std::vector<double> *result);

int main() {
    const double a = LEFT_RANGE_BOUNDARY;
    const double b = RIGHT_RANGE_BOUNDARY;
    const int    n = NUM_INTERPOLATION_NODES;

    std::vector<double> x_uniform_nodes   = LagrangeInterpolation::uniformNodes(a, b, n);
    std::vector<double> x_chebyshev_nodes = LagrangeInterpolation::chebyshevNodes(a, b, n);

    std::vector<double> y_uniform_nodes  (n);
    std::vector<double> y_chebyshev_nodes(n);

    std::transform(x_uniform_nodes.begin(), x_uniform_nodes.end(), y_uniform_nodes.begin(), &f);
    std::transform(x_chebyshev_nodes.begin(), x_chebyshev_nodes.end(), y_chebyshev_nodes.begin(), &f);

    std::vector<double> x_uniform_middle_values(n - 1);
    std::vector<double> x_chebyshev_middle_values(n - 1);

    for (int i = 0; i < n - 1; ++i) {
        x_uniform_middle_values[i]   = (x_uniform_nodes[i]   + x_uniform_nodes[i + 1])   / 2;
        x_chebyshev_middle_values[i] = (x_chebyshev_nodes[i] + x_chebyshev_nodes[i + 1]) / 2;
    }

    std::vector<double> y_uniform_middle_values   = LagrangeInterpolation::interpolateRange(x_uniform_nodes, y_uniform_nodes, x_uniform_middle_values);
    std::vector<double> y_chebyshev_middle_values = LagrangeInterpolation::interpolateRange(x_chebyshev_nodes, y_chebyshev_nodes, x_chebyshev_middle_values);

    std::vector<double> x_extra_values(FUNCTION_EXTRA_POINTS);
    splitIntervalEvenly(a, b, FUNCTION_EXTRA_POINTS, &x_extra_values);

    std::vector<double> y_extra_values(FUNCTION_EXTRA_POINTS);
    std::transform(x_extra_values.begin(), x_extra_values.end(), y_extra_values.begin(), &f);

    std::vector<double> y_uniform_extra_values   = LagrangeInterpolation::interpolateRange(x_uniform_nodes, y_uniform_nodes, x_extra_values);
    std::vector<double> y_chebyshev_extra_values = LagrangeInterpolation::interpolateRange(x_chebyshev_nodes, y_chebyshev_nodes, x_extra_values);

    plotResults(x_uniform_nodes, y_uniform_nodes, x_uniform_middle_values, y_uniform_middle_values, x_extra_values, y_extra_values, y_uniform_extra_values, "[0:10]", "[-1:1]", "Uniform Nodes Interpolation");
    plotResults(x_chebyshev_nodes, y_chebyshev_nodes, x_chebyshev_middle_values, y_chebyshev_middle_values, x_extra_values, y_extra_values, y_chebyshev_extra_values, "[0:10]", "[-1:1]", "Chebyshev Nodes Interpolation");

    return 0;
}

void splitIntervalEvenly(const double a, const double b, size_t n,
                         std::vector<double> *result) {
    assert(n == (*result).size() && "! ERROR: Wrong array size");
    double delta = (b - a) / (n - 1);

    (*result).front() = a;
    (*result).back()  = b;

    for (size_t i = 1; i < n - 1; ++i)
        (*result)[i] = (*result)[i - 1] + delta;
}
