#pragma once

#include <vector>

class LagrangeInterpolation {
public:
    static std::vector<double> uniformNodes(double a, double b, int n);
    static std::vector<double> chebyshevNodes(double a, double b, int n);
    static double interpolate(const std::vector<double>& x, const std::vector<double>& y, double x_star);
    static std::vector<double> interpolateRange(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& x_star);
};
