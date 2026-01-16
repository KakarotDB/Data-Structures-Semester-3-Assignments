# Setting the output file type and name
set terminal pngcairo size 800,600
set output 'performance_graph.png'

# Titles and Labels
set title "Naive vs. Divide and Conquer Max-Min"
set xlabel "Array Size (n)"
set ylabel "Number of Comparisons"
set grid

# Legend position
set key left top

# Plot the data
# column 1 is X (Size), column 2 is Naive, column 3 is Recursive
plot "results.dat" using 1:2 with linespoints title "Naive Algorithm", \
     "results.dat" using 1:3 with linespoints title "Divide & Conquer"
