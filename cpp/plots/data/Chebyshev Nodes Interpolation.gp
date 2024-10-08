set terminal png size 1200,900
set output 'plots/images/Chebyshev Nodes Interpolation.png'
set xlabel 'x'
set ylabel 'y'
set grid
set key left bottom box
set key font ',24'
set key spacing 1.5
set title 'Chebyshev Nodes Interpolation' font ',24'
set xrange [0:10]
set yrange [-1:1]
plot 'plots/data/Chebyshev Nodes Interpolation.txt' index 0 with points lc 'black' ps 4 title 'Interpolation nodes', '' index 1 with points lc 'magenta' ps 4 title 'Interpolation values', '' index 2 with lines lw 4 lc 'black' title 'Original function', '' index 3 with lines lw 4 lc 'magenta' title 'Lagrange Interpolation'
set output
