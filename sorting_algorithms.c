#include "sorting_algorithms.h"

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//merge sort :
void merge(int arr[], int tempArray[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Copy data to temp arrays tempL[] and tempR[]
    int* tempL = (int*)malloc(n1 * sizeof(int));
    int* tempR = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        tempL[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        tempR[j] = arr[middle + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (tempL[i] <= tempR[j]) {
            arr[k] = tempL[i];
            i++;
        } else {
            arr[k] = tempR[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of tempL[], if any
    while (i < n1) {
        arr[k] = tempL[i];
        i++;
        k++;
    }

    // Copy the remaining elements of tempR[], if any
    while (j < n2) {
        arr[k] = tempR[j];
        j++;
        k++;
    }

    free(tempL);
    free(tempR);
}

void mergeSortRecursive(int arr[], int tempArray[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSortRecursive(arr, tempArray, left, middle);
        mergeSortRecursive(arr, tempArray, middle + 1, right);
        merge(arr, tempArray, left, middle, right);
    }
}

void mergeSort(int arr[], int n) {
    int* tempArray = (int*)malloc(n * sizeof(int));
    mergeSortRecursive(arr, tempArray, 0, n - 1);
    free(tempArray);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortRecursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    quickSortRecursive(arr, 0, n - 1);
}

