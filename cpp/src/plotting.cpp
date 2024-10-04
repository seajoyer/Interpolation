#include "plotting.h"
#include <fstream>
#include <iostream>

const std::string PLOTS_DIR = "plots/";

void plotResults(const std::vector<double>& x_nodes, const std::vector<double>& y_nodes,
                 const std::vector<double>& x_values, const std::vector<double>& y_values,
                 const std::vector<double>& x_extra_values, const std::vector<double>& y_extra_values_original,
                 const std::vector<double>& y_extra_values_interpolated, const std::string& xrange,
                 const std::string& yrange, const std::string& title) {

    std::ofstream dataFile(PLOTS_DIR + "data/" + title + ".txt");
    for (size_t i = 0; i < x_nodes.size(); ++i) {
        dataFile << x_nodes[i] << " " << y_nodes[i] << std::endl;
    }
    dataFile << std::endl << std::endl;
    for (size_t i = 0; i < x_values.size(); ++i) {
        dataFile << x_values[i] << " " << y_values[i] << std::endl;
    }
    dataFile << std::endl << std::endl;
    for (size_t i = 0; i < x_extra_values.size(); ++i) {
        dataFile << x_extra_values[i] << " " << y_extra_values_original[i] << std::endl;
    }
    dataFile << std::endl << std::endl;
    for (size_t i = 0; i < x_extra_values.size(); ++i) {
        dataFile << x_extra_values[i] << " " << y_extra_values_interpolated[i] << std::endl;
    }
    dataFile.close();

    std::ofstream scriptFile(PLOTS_DIR + "data/" + title + ".gp");
    scriptFile << "set terminal png size 1200,900\n"
               << "set output '" + PLOTS_DIR + "images/" + title + ".png'\n"
               << "set xlabel 'x'\n"
               << "set ylabel 'y'\n"
               << "set grid\n";
    if (title != "")
        scriptFile << "set title '" << title << "'\n";
    if (xrange != "")
        scriptFile << "set xrange " + xrange + "\n";
    if (yrange != "")
        scriptFile << "set yrange " + yrange + "\n";
    scriptFile
        << "plot '" + PLOTS_DIR + "data/" + title +
               ".txt' index 0 with points lc 'black' ps 3 title 'Interpolation nodes', "
        << "'' index 1 with points lc 'magenta' ps 3 title 'Interpolation values', "
        << "'' index 2 with lines lw 3 lc 'black' title 'Original function', "
        << "'' index 3 with lines lw 3 lc 'magenta' title 'Lagrange "
           "Interpolation'\n"
        << "set output\n";
    scriptFile.close();

    std::cout << "Data and script files created." << std::endl;
}
