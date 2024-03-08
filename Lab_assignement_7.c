#include <stdio.h>

int TotalSwap = 0;

void bubbleSort(int arr[], int swaps[]) {
    int n = 9;
    int i, j, tmp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swaps[arr[j]]++;
                swaps[arr[j + 1]]++;
                TotalSwap++;
            }
        }
    }
}

void selectionSort(int arr[], int swaps[]) {
    int n = 9;
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
            swaps[arr[i]]++;
            swaps[arr[min]]++;
            TotalSwap++;
        }
    }
}

void printSwaps(int arr[], int x, int swaps[]) {
    int n = 9;
    printf("\nArray %d:\n", x);
    for (int i = 0; i < n; i++) {
        printf("%d: # of times %d is swapped\n", arr[i], swaps[arr[i]]);
    }
    printf("Total number of swaps: %d\n", TotalSwap);
}

int main() {
    int x;
    int arr1[] = {97, 16, 45, 63 ,13, 22, 7, 58, 72};
    int arr2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int arr3[] = {97, 16, 45, 63 ,13, 22, 7, 58, 72};
    int arr4[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int swaps1[100] = {0};
    int swaps2[100] = {0};
    int swaps3[100] = {0};
    int swaps4[100] = {0};
   
    bubbleSort(arr1, swaps1);
    printSwaps(arr1, 1, swaps1); 


    TotalSwap = 0;

   
    bubbleSort(arr2, swaps2);
    printSwaps(arr2, 2, swaps2);

  
    TotalSwap = 0;
    
    selectionSort(arr3, swaps3);
    printSwaps(arr3, 1, swaps3);

 
    TotalSwap = 0;

   
    selectionSort(arr4, swaps4);
    printSwaps(arr4, 2, swaps4);

    return 0;
}
