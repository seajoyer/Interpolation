#pragma once

#include <vector>
#include <string>

void plotResults(const std::vector<double>& x_nodes, const std::vector<double>& y_nodes,
                 const std::vector<double>& x_values, const std::vector<double>& y_values,
                 const std::vector<double>& x_extra_values, const std::vector<double>& y_extra_values_original,
                 const std::vector<double>& y_extra_values_interpolated, const std::string& xrange = "",
                 const std::string& yrange = "", const std::string& title = "");
