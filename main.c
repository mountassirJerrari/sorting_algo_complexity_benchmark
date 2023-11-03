#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting_algorithms.h"
#include "helper.h"







// Function to generate Gnuplot scripts
void traceGraphs()
{
    char const *gnuname = "gnuplot_script.plt";
    char const *gnupath = "C:/gnuplot/bin/wgnuplot";
    char command[50000];
    FILE *f_plot = fopen(gnuname,"w");
    if(f_plot != NULL)
    {
        fprintf(f_plot, "set grid;\n");
        fprintf(f_plot, "set xrange[0:1000000];\n");
        fprintf(f_plot, "set yrange[0:3];\n");
        fprintf(f_plot, "set key box;\n");

        fprintf(f_plot, "set multiplot; \n");
        //trace function 1
        fprintf(f_plot, "set size 1,1;\n");
        fprintf(f_plot, "set origin 0.0,0.0;\n");
        fprintf(f_plot, "plot 'data.txt' u 1:2 title ' quickSort' w lp lt rgb 'red' lw 2 axes x1y1 , ");
        fprintf(f_plot, " 'data.txt' u 1:3 title 'mergeSort' w lp lt rgb 'green' lw 2 axes x1y1 , ");
        fprintf(f_plot, " 'data.txt' u 1:4 title 'insertionSort' w lp lt rgb 'blue' lw 2 axes x1y1 ,");
        fprintf(f_plot, " 'data.txt' u 1:5 title 'bubbleSort' w lp lt rgb 'black' lw 2 axes x1y1 ,");
        fprintf(f_plot, " 'data.txt' u 1:6 title 'selectionSort' w lp lt rgb 'yellow' lw 2 axes x1y1 ; \n");

        fprintf(f_plot, "unset multiplot; \n");
        fclose(f_plot);

        sprintf(command,"start %s -persist %s ",gnupath,gnuname);
        system(command);


    }
    else
    {
        printf("ouverture failed");
    }
}



int main()
{

    int minSize = 10;     // Minimum size
    int maxSize = 50000; // Maximum size
    int numSizes = 20;    // Number of sizes

    int windowSize = 10; // Adjust the window size as needed

    int* sizes = generateSizesArray(minSize, maxSize, numSizes);

    if (sizes == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Sort functions to benchmark (e.g., bubbleSort, selectionSort, insertionSort)
    void (*sortingFunctions[])(int[], int) = {  quickSort,mergeSort ,insertionSort, selectionSort ,bubbleSort };
    int numSortFunctions = sizeof(sortingFunctions) / sizeof(sortingFunctions[0]);

    double** benchmarkResults = (double**)malloc(numSortFunctions * sizeof(double*));
    for (int i = 0; i < numSortFunctions; i++)
    {
        benchmarkResults[i] = (double*)malloc(numSizes * sizeof(double));
    }

    for (int j = 0; j < numSizes; j++)
    {
        benchmarkSortingFunctions(benchmarkResults,sortingFunctions, numSortFunctions, sizes[j], numSizes, j);
    }
    //smoothing function :
    for (int i = 0; i < numSortFunctions; i++)
    {
        movingAverageSmoothing(benchmarkResults[i], numSizes, windowSize);
    }

    /* printf("Benchmark results:\n");

     for (int i = 0; i < numSortFunctions; i++)
     {
         printf("Sorting Algorithm %d:\n", i + 1);
         for (int j = 0; j < numSizes; j++)
         {
             printf("Array size: %d, Time taken: %.6f seconds\n", sizes[j], benchmarkResults[i][j]);
         }
         printf("\n");
     }*/


    // Save benchmark results to a data file
    FILE* dataFile = fopen("data.txt", "w");
    if (dataFile == NULL)
    {
        fprintf(stderr, "Failed to create data file.\n");
        return 1;
    }

    // Write data in a format suitable for Gnuplot
    for (int j = 0; j < numSizes; j++)
    {
        fprintf(dataFile, "%d", sizes[j]);
        printf("%d", sizes[j]);
        for (int i = 0; i < numSortFunctions; i++)
        {
            fprintf(dataFile, "\t%.6f", benchmarkResults[i][j]);
            printf(" %.6f", benchmarkResults[i][j]);
        }
        fprintf(dataFile, "\n");
        printf( "\n");

    }

    fclose(dataFile);
    traceGraphs();

    // Free allocated memory for benchmark results
    for (int i = 0; i < numSortFunctions; i++)
    {
        free(benchmarkResults[i]);
    }
    free(benchmarkResults);

    return 0;


    return 0;
}
