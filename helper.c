#include <time.h>
#include "helper.h"
// Function to benchmark a sorting function
double benchmarkSort(void (*sortFunc)(int[], int), int arr[], int arrSize)
{
    clock_t start = clock();
    sortFunc(arr, arrSize);
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
// Function to benchmark multiple sorting functions using the same input data
void benchmarkSortingFunctions(double** results,void (*sortingFunctions[])(int[], int), int numSortFunctions, int arrSize, int numSizes, int currentSizeIndex)
{



    int* arr = (int*)malloc(arrSize * sizeof(int));

    for (int i = 0; i < numSortFunctions; i++)
    {
        fillArrayWithRandomValues(arr, arrSize, 1, 10000);

        results[i][currentSizeIndex] = benchmarkSort(sortingFunctions[i], arr, arrSize);
    }

    free(arr);


}
void fillArrayWithRandomValues(int arr[], int size, int min, int max) {
    if (size <= 0) {
        return; // No need to fill an empty array
    }

    // Seed the random number generator with the current time
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = (rand() % (max - min + 1)) + min;
    }
}

int* reallocateArray(int* arr, int newSize) {
    int* newArray = realloc(arr, newSize * sizeof(int));

    if (newArray == NULL) {
        // realloc failed, handle the error (e.g., return NULL or exit)
        return NULL;
    }

    return newArray;
}

int* generateSizesArray(int minSize, int maxSize, int numSizes) {
    int* sizes = (int*)malloc(numSizes * sizeof(int));

    if (sizes == NULL) {
        // Handle memory allocation error
        return NULL;
    }

    // Calculate the step size to evenly distribute sizes between min and max
    int step = (maxSize - minSize) / (numSizes - 1);

    for (int i = 0; i < numSizes; i++) {
        sizes[i] = minSize + i * step;
    }

    return sizes;
}

//

// Function to apply a simple moving average (MA) smoothing to data
void movingAverageSmoothing(double* data, int dataSize, int windowSize) {
    if (windowSize < 1 || windowSize > dataSize) {
        printf( "Invalid window size.\n");
        return;
    }

    double* smoothedData = (double*)malloc(dataSize * sizeof(double));

    for (int i = 0; i < dataSize; i++) {
        double sum = 0.0;
        int count = 0;

        for (int j = i - windowSize + 1; j <= i; j++) {
            if (j >= 0) {
                sum += data[j];
                count++;
            }
        }

        smoothedData[i] = sum / count;
    }

    // Copy the smoothed data back to the original array
    for (int i = 0; i < dataSize; i++) {
        data[i] = smoothedData[i];
    }

    free(smoothedData);
}




