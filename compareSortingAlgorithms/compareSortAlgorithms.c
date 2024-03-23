#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void *Alloc(size_t sz)
{
	extraMemoryAllocated += sz;
	size_t* ret = malloc(sizeof(size_t) + sz);
	*ret = sz;
	printf("Extra memory allocated, size: %ld\n", sz);
	return &ret[1];
}

void DeAlloc(void* ptr)
{
	size_t* pSz = (size_t*)ptr - 1;
	extraMemoryAllocated -= *pSz;
	printf("Extra memory deallocated, size: %ld\n", *pSz);
	free((size_t*)ptr - 1);
}

size_t Size(void* ptr)
{
	return ((size_t*)ptr)[-1];
}
void swap(int* a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void heapify(int arr[], int n, int i){
	int largest = i;
	int left = 2* i +1;
	int right = 2 * i + 2;

	if(left <n && arr[left] > arr[largest]){
		largest = left;
	}
	if(right < n && arr[right] > arr[largest]){
		largest = right;
	}
	if(largest != i){
		swap(&arr[i],&arr[largest]);
	}
	heapify(arr, n, largest);
}
void merge(int pData[],int l, int m, int r){
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1] , R[n2];
	for(int i = 0; i < n1; i++){
		L[i] = pData[l + i];

	}
	for(int j = 0; j< n2; j++){
		R[j] = pData[m + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = l;

	while(i < n1 && j < n2){
		if(L[i] <= R[j]){
			pData[k] = L[i];
			i++;
		} else{
			pData[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < n1){
		pData[k] = L[i];
		i++;
		k++;
	}
	while(j < n2){
		pData[k] = R[j];
		j++;
		k++;
	}
}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int i, int n){
	for(int i = 0; i <= (n/2)-1; i++){
		heapify(arr, n, i);
	}
	for(int j = 0; j <= n - 1;j++){
		swap(arr[0], arr[j]);
		heapify(arr, i ,0);
	}
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r){
	if(l < r){
		int m = l + ( r - 1 ) / 2;

		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);

		merge(pData, l, m, r);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n){
	int i, cur, j;
	for(i = 1; i < n; i++){
		cur = pData[i];
		j = i - 1;

		while (j >= 0 && pData[j] > cur){
			pData[j+1] = pData[j];
			j = j - 1;
		}
		pData[j+1] = cur;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n){
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(pData[j] > pData[j+1]){
				int temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;
		}
	}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n){
	for(int i = 0; i < n - 1; i++){
		int min = i;
		for(int j = i + 1;j < n ; j++){
			if(pData[j] < pData[min]){
				min = j;
			}
		}
		int temp = pData[i];
		pData[i] = pData[min];
		pData[min] = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)Alloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData != NULL) // Check if memory allocation was successful
        {
            for (int i = 0; i < dataSz; i++)
            {
                fscanf(inFile, "%d", &(*ppData)[i]); // Read integers from file into array
            }
        }
        else
        {
            dataSz = 0; // Set data size to 0 if memory allocation failed
        }

        fclose(inFile); // Close the file

	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)Alloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

                printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		DeAlloc(pDataCopy);
		DeAlloc(pDataSrc);
	}
	
}
