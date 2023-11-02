#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting_algorithms.h"
#include "helper.h"

// Function to benchmark a sorting function
double benchmarkSort(void (*sortFunc)(int[], int), int arr[], int arrSize) {
    clock_t start = clock();
    sortFunc(arr, arrSize);
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to benchmark multiple sorting functions using the same input data
void benchmarkSortingFunctions(double** results,void (*sortingFunctions[])(int[], int), int numSortFunctions, int arrSize, int numSizes, int currentSizeIndex) {



    int* arr = (int*)malloc(arrSize * sizeof(int));

    for (int i = 0; i < numSortFunctions; i++) {
            fillArrayWithRandomValues(arr, arrSize, 1, 10000);
        results[i][currentSizeIndex] = benchmarkSort(sortingFunctions[i], arr, arrSize);
    }

    free(arr);


}

int main() {
    int minSize = 10;     // Minimum size
    int maxSize = 50000; // Maximum size
    int numSizes = 10;    // Number of sizes

    int* sizes = generateSizesArray(minSize, maxSize, numSizes);

    if (sizes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Sort functions to benchmark (e.g., bubbleSort, selectionSort, insertionSort)
    void (*sortingFunctions[])(int[], int) = { bubbleSort, selectionSort,insertionSort };
    int numSortFunctions = sizeof(sortingFunctions) / sizeof(sortingFunctions[0]);

    double** benchmarkResults = (double**)malloc(numSortFunctions * sizeof(double*));
    for (int i = 0; i < numSortFunctions; i++) {
        benchmarkResults[i] = (double*)malloc(numSizes * sizeof(double));
    }

    for (int j = 0; j < numSizes; j++) {
         benchmarkSortingFunctions(benchmarkResults,sortingFunctions, numSortFunctions, sizes[j], numSizes, j);
    }

    printf("Benchmark results:\n");

    for (int i = 0; i < numSortFunctions; i++) {
        printf("Sorting Algorithm %d:\n", i + 1);
        for (int j = 0; j < numSizes; j++) {
            printf("Array size: %d, Time taken: %.6f seconds\n", sizes[j], benchmarkResults[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory for benchmark results
    for (int i = 0; i < numSortFunctions; i++) {
        free(benchmarkResults[i]);
    }
    free(benchmarkResults);

    return 0;
}
