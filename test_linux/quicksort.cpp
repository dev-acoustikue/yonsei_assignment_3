// written by SukJoon Oh(2018142216)
#include "quicksort.h"

void swap(int* a, int* b) {

	int _t = *a;
	*a = *b;
	*b = _t;	
}

void quicksort(int *arr, size_t len) {

	if (len > 1) {

		int low = 0;
		int high = len - 1;
		int pivot = arr[high]; // pivot

		int i = low; // Index of smaller element

		for (int j = low; j <= high - 1; j++) {
			if (arr[j] <= pivot) {

				swap(&arr[i], &arr[j]);
				i++; // increment index of smaller element
			}
		}

		swap(&arr[i], &arr[high]);

		quicksort(arr, i);
		quicksort(arr + i, len - i);
	}
}

int kthSmallestNaive(int *arr, size_t len, int k) {
	// Fill me!

	quicksort(arr, len);

	if (k - 1 >= 0)
		return arr[k - 1];

	if (k > len) 
		return -1;
}

int kthSmallest(int *arr, size_t len, int k) {
	// Fill me!

	if (k > len)
		return -1;

	if (len > 1) {

		int low = 0;
		int high = len - 1;
		int pivot = arr[high]; // pivot

		int i = low; // Index of smaller element

		for (int j = low; j <= high - 1; j++) {
			if (arr[j] <= pivot) {

				swap(&arr[i], &arr[j]);
				i++; // increment index of smaller element
			}
		}

		swap(&arr[i], &arr[high]);

		if (k == i + 1)
			return arr[i];

		else if (k < i + 1)
			return kthSmallest(arr, i, k);

		else
			return kthSmallest(arr + i + 1, len - i - 1, k - i - 1);
	}
}
