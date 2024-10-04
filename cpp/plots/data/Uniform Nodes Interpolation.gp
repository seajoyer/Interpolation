set terminal png size 1200,900
set output 'plots/images/Uniform Nodes Interpolation.png'
set xlabel 'x'
set ylabel 'y'
set grid
set title 'Uniform Nodes Interpolation'
set xrange [0:10]
set yrange [-1:1]
plot 'plots/data/Uniform Nodes Interpolation.txt' index 0 with points lc 'black' ps 3 title 'Interpolation nodes', '' index 1 with points lc 'magenta' ps 3 title 'Interpolation values', '' index 2 with lines lw 3 lc 'black' title 'Original function', '' index 3 with lines lw 3 lc 'magenta' title 'Lagrange Interpolation'
set output
