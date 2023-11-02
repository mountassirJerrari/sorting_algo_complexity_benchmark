#include <time.h>
#include "helper.h"
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


