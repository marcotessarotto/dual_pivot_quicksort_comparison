#include<stdio.h>

#include "quicksort.h"

static void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto

/* This function takes last element as pivot, places
 the pivot element at its correct position in sorted
 array, and places all smaller (smaller than pivot)
 to left of pivot and all greater elements to right
 of pivot */
/*
 Lomuto-Partition(A, p, r)
 x = A[r]
 i = p - 1
 for j = p to r - 1
 if A[j] <= x
 i = i + 1
 swap( A[i], A[j] )
 swap( A[i + 1], A[r] )
 return i + 1
 */
static int partition_lomuto(int *arr, int low, int high) {
	int pivot = arr[high];    // pivot
	int i = low - 1;  // Index of smaller element

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than or equal to pivot
		if (arr[j] <= pivot) {
			i++;    // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/*
 *Hoare partition scheme:
 algorithm quicksort(A, lo, hi) is
 if lo < hi then
 p := partition(A, lo, hi)
 quicksort(A, lo, p)
 quicksort(A, p + 1, hi)

 algorithm partition(A, lo, hi) is
 pivot := A[ floor((hi + lo) / 2) ]
 i := lo - 1
 j := hi + 1
 loop forever
 do
 i := i + 1
 while A[i] < pivot
 do
 j := j - 1
 while A[j] > pivot
 if i ≥ j then
 return j
 swap A[i] with A[j]
 */
// Hoare partition scheme, in general is more efficient then Lomuto partition scheme
static int partition_hoare(int *A, int lo, int hi) {
	int pivot = A[(hi + lo) / 2];    // pivot
	int i = lo - 1;
	int j = hi + 1;
	while (1) {
		do {
			i++;
		} while (A[i] < pivot);
		do {
			j--;
		} while (A[j] > pivot);

		if (i >= j)
			return j;
		swap(&A[i], &A[j]);
	}

}

void quick_sort_part_hoare(int *arr, int low, int high) {
	if (low < high) {

		int pi = partition_hoare(arr, low, high);

		quick_sort_part_hoare(arr, low, pi);
		quick_sort_part_hoare(arr, pi + 1, high);

	}
}

void quick_sort_part_lomuto(int *arr, int low, int high) {
	if (low < high) {

		int pi = partition_lomuto(arr, low, high);

		quick_sort_part_lomuto(arr, low, pi - 1);
		quick_sort_part_lomuto(arr, pi + 1, high);

	}
}

void quick_sort_hoare(int *arr, int a_length) {
	quick_sort_part_hoare(arr, 0, a_length - 1);
}

void quick_sort_lomuto(int *arr, int a_length) {
	quick_sort_part_lomuto(arr, 0, a_length - 1);
}

