#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED
void fillArrayWithRandomValues(int arr[], int size, int min, int max);
int* reallocateArray(int* arr, int newSize);
int* generateSizesArray(int minSize, int maxSize, int numSizes);
void movingAverageSmoothing(double* data, int dataSize, int windowSize) ;
double benchmarkSort(void (*sortFunc)(int[], int), int arr[], int arrSize);
void benchmarkSortingFunctions(double** results,void (*sortingFunctions[])(int[], int), int numSortFunctions, int arrSize, int numSizes, int currentSizeIndex);



#endif // HELPER_H_INCLUDED
