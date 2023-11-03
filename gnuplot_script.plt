set grid;
set xrange[0:1000000];
set yrange[0:3];
set key box;
set multiplot; 
set size 1,1;
set origin 0.0,0.0;
plot 'data.txt' u 1:2 title ' quickSort' w lp lt rgb 'red' lw 2 axes x1y1 ,  'data.txt' u 1:3 title 'mergeSort' w lp lt rgb 'green' lw 2 axes x1y1 ,  'data.txt' u 1:4 title 'insertionSort' w lp lt rgb 'blue' lw 2 axes x1y1 , 'data.txt' u 1:5 title 'bubbleSort' w lp lt rgb 'black' lw 2 axes x1y1 , 'data.txt' u 1:6 title 'selectionSort' w lp lt rgb 'yellow' lw 2 axes x1y1 ; 
unset multiplot; 
