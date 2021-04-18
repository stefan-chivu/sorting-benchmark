#include  "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

#define ITERATION_NO 25

float shakersort(int* v, int n){
	starton();

	int i,j;
	for (i = 1; i <= n / 2; i++){
		for (j = i - 1; j < n - i; j++){
			if (v[j] > v[j + 1]){
				int aux;
				aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
							
		}
		for (j = n - i - 1; j >= i; j--){
			if (v[j] < v[j - 1]){
				int aux;
				aux = v[j];
				v[j] = v[j - 1];
				v[j - 1] = aux;
			}
				
		}
			
	}

	return startoff();
}

int* generate_array(int n) {
	int* arr;

	if ((arr = (int*)malloc(n * sizeof(int))) == NULL) {
		fprintf(stderr, "\nRANDOM ARRAY ALLOCATION FAILED");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++) {
		arr[i] = rand();
	}

	return arr;
}

int* clone_array(int* source, int n) {
	int* res; 
	
	if ((res = (int*)malloc(n * sizeof(int))) == NULL) {
		fprintf(stderr, "\nRANDOM ARRAY ALLOCATION FAILED");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++) {
		res[i] = source[i];
	}

	return res;
}

void print_array(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("\narr[%2d] = %d", i, arr[i]);
	}
}

float bubblesort(int* arr, int n) {

	starton();

	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j]) {
				int temp;
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	return startoff();
}

void quicksort(int* arr, int first, int last) {
	int i, j, pivot, temp;

	if (first < last) {
		pivot = first;
		i = first;
		j = last;

		while (i < j) {
			while (arr[i] <= arr[pivot] && i < last)
				i++;
			while (arr[j] > arr[pivot])
				j--;
			if (i < j) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}

		temp = arr[pivot];
		arr[pivot] = arr[j];
		arr[j] = temp;
		quicksort(arr, first, j - 1);
		quicksort(arr, j + 1, last);

	}
}

float measure_quicksort_rec(int* arr, int n) {
	starton();
	quicksort(arr, 0, n - 1);
	return startoff();
}

//Library qsort's compare function
int cmpfunc(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

float measure_qsort(int* arr, int n) {
	starton();

	qsort(arr, n, sizeof(int), cmpfunc);

	return startoff();
}

float insertionSort(int arr[], int n){
	starton();

	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}

	return startoff();
}

float selectionSort(int arr[], int n){
	starton();

	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++){
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		int temp;
		temp = arr[min_idx];
		arr[min_idx] = arr[i];
		arr[i] = temp;
	}

	return startoff();
}

void heapify(int* arr, int n, int i) {
	int max = i; //Initialize max as root
	int leftChild = 2 * i + 1;
	int rightChild = 2 * i + 2;

	//If left child is greater than root
	if (leftChild < n && arr[leftChild] > arr[max])
		max = leftChild;

	//If right child is greater than max
	if (rightChild < n && arr[rightChild] > arr[max])
		max = rightChild;

	//If max is not root
	if (max != i) {
		int temp;
		temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;

		//heapify the affected sub-tree recursively
		heapify(arr, n, max);
	}
}

//Main function to perform heap sort
void heapSort(int* arr, int n) {
	//Rearrange array (building heap)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	//Extract elements from heap one by one
	for (int i = n - 1; i >= 0; i--) {
		int temp;
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		//Current root moved to the end

		heapify(arr, i, 0); //calling max heapify on the heap reduced
	}
}

float measure_heap(int* arr, int n) {
	starton();

	heapSort(arr, n);

	return startoff();
}

void benchmark() {
	FILE* results;
	FILE* averages;

	if ((results = fopen("results.csv", "w")) == NULL) {
		fprintf(stderr, "\nOpening of results file failed");
		exit(EXIT_FAILURE);
	}

	if ((averages = fopen("averages.csv", "w")) == NULL) {
		fprintf(stderr, "\nOpening of averages file failed");
		exit(EXIT_FAILURE);
	}

	fprintf(results, "Iteration,Element No.,Algorithm,Time");
	fprintf(averages, "Element No.,Algorithm,Average Time");




	int avg = 0;
	for (int n = 10000; n <= 100000; n += 10000) {

		float bubble_avg, rec_quicksort_avg, shaker_avg, qsort_avg;
		float insertion_avg, selection_avg, heap_avg;

		bubble_avg = rec_quicksort_avg = shaker_avg = qsort_avg = 0;
		insertion_avg = selection_avg = heap_avg = 0;


		printf("\n\nGenerating and sorting %d elements arrays", n);
		for (int i = 0; i < ITERATION_NO; i++) {
			int* original = generate_array(n);
			int* ref = clone_array(original, n);

			printf("\n[%d] - Iteration %d", n, i);
			clock_t iteration_time = clock();

			float quicksort_rec_time = measure_quicksort_rec(ref, n);
			rec_quicksort_avg += quicksort_rec_time;
			fprintf(results, "\n%d,%d,Recursive Quicksort,%f", (i + 1), n, quicksort_rec_time);
			free(ref); 
			
			ref = clone_array(original, n);
			float qsort_time = measure_qsort(ref, n);
			qsort_avg += qsort_time;
			fprintf(results, "\n%d,%d,Library qsort,%f", (i + 1), n, qsort_time);
			free(ref); 
			
			ref = clone_array(original, n);
			float heap_time = measure_heap(ref, n);
			heap_avg += heap_time;
			fprintf(results, "\n%d,%d,Heapsort,%f", (i + 1), n, heap_time);
			free(ref);

			ref = clone_array(original, n);
			float bubble_time = bubblesort(ref, n);
			bubble_avg += bubble_time;
			fprintf(results, "\n%d,%d,Bubblesort,%f", (i + 1), n, bubble_time);
			free(ref);
			
			ref = clone_array(original, n);
			float shaker_time = shakersort(ref, n);
			shaker_avg += shaker_time;
			fprintf(results, "\n%d,%d,Shakersort,%f", (i + 1), n, shaker_time);
			free(ref); 
			
			ref = clone_array(original, n);
			float insertion_time = insertionSort(ref, n);
			insertion_avg += insertion_time;
			fprintf(results, "\n%d,%d,Insertionsort,%f", (i + 1), n, insertion_time);
			free(ref);

			ref = clone_array(original, n);
			float selection_time = selectionSort(ref, n);
			selection_avg += selection_time;
			fprintf(results, "\n%d,%d,Selectionsort,%f", (i + 1), n, selection_time);
			free(ref);

			printf(" - completed in %.2f seconds", (clock() - (float)iteration_time) / CLK_TCK);

			free(original);
		}

		rec_quicksort_avg = rec_quicksort_avg / ITERATION_NO;
		fprintf(averages, "\n%d,Recursive Quicksort,%f", n, rec_quicksort_avg);

		qsort_avg = qsort_avg / ITERATION_NO;
		fprintf(averages, "\n%d,Library qsort,%f", n, qsort_avg); 
		
		heap_avg = heap_avg / ITERATION_NO;
		fprintf(averages, "\n%d,Heapsort,%f", n, heap_avg);

		bubble_avg = bubble_avg / ITERATION_NO;
		fprintf(averages, "\n%d,Bubblesort,%f", n, bubble_avg); 

		shaker_avg = shaker_avg / ITERATION_NO;
		fprintf(averages, "\n%d,Shakersort,%f", n, shaker_avg); 

		insertion_avg = insertion_avg / ITERATION_NO;
		fprintf(averages, "\n%d,Insertionsort,%f", n, insertion_avg);

		selection_avg = selection_avg / ITERATION_NO;
		fprintf(averages, "\n%d,Selectionsort,%f", n, selection_avg);
	}

	fclose(results);
	fclose(averages);
}

int fcpy(FILE* sourceFile, FILE* destFile)
{
	int  count = 0;
	char ch;

	/* Copy file contents character by character. */
	while ((ch = fgetc(sourceFile)) != EOF)
	{
		fputc(ch, destFile);

		/* Increment character copied count */
		count++;
	}

	return count;
}

void main(void){
	char start = 0;

	printf("\nDo you want to start the benchmark?");
	while (start != 'y' && start != 'Y' && start != 'N' && start != 'n') {
		printf("\n\t[Y/N]:");	
		scanf("%c", &start);
		getchar();
	}

	if (start == 'Y' || start == 'y') {
		benchmark();

		FILE* results;
		FILE* results_backup;
		FILE* averages;
		FILE* averages_backup;

		if (((results = fopen("results.csv", "r")) == NULL) || ((results_backup = fopen("results_backup.csv", "w")) == NULL)) {
			fprintf(stderr, "\nOpening of results/backup file failed");
			exit(EXIT_FAILURE);
		}

		if (((averages = fopen("averages.csv", "r")) == NULL) || ((averages_backup = fopen("averages_backup.csv", "w")) == NULL)) {
			fprintf(stderr, "\nOpening of averages/backup file failed");
			exit(EXIT_FAILURE);
		}

		int count;
		count = fcpy(results, results_backup);
		printf("\n\nResults backup created - %d characters copied successfully", count);
		count = fcpy(averages, averages_backup);
		printf("\nAverages backup created - %d characters copied successfully\n", count);

		fclose(results);
		fclose(averages);
		fclose(results_backup);
		fclose(averages_backup);
	}
} 