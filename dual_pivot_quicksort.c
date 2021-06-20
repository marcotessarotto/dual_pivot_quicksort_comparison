#include <stdio.h>
#include <stdlib.h>

#include "dual_pivot_quicksort.h"

// https://web.archive.org/web/20151002230717/http://iaroslavski.narod.ru/quicksort/DualPivotQuicksort.pdf
// https://arxiv.org/pdf/1310.7409v1.pdf
// https://learnforeverlearn.com/yaro_web/

/*
 * code translated to C from original java code as published by Iaroslavski, article can be found at link below.
 * added #define to skip check on range
 *
 * https://web.archive.org/web/20151002230717/http://iaroslavski.narod.ru/quicksort/DualPivotQuicksort.pdf
 */

#define DIST_SIZE 13
#define TINY_SIZE 17

static void _dual_pivot_quick_sort(int *a, int left, int right) {
	int len = right - left;
	int x;

	if (len < TINY_SIZE) { // insertion sort on tiny array
		for (int i = left + 1; i <= right; i++) {
			for (int j = i; j > left && a[j] < a[j - 1]; j--) {
				x = a[j - 1];
				a[j - 1] = a[j];
				a[j] = x;
			}
		}
		return;
	}
	// median indexes
	int sixth = len / 6;
	int m1 = left + sixth;
	int m2 = m1 + sixth;
	int m3 = m2 + sixth;
	int m4 = m3 + sixth;
	int m5 = m4 + sixth;

	// 5-element sorting network
	if (a[m1] > a[m2]) {
		x = a[m1];
		a[m1] = a[m2];
		a[m2] = x;
	}
	if (a[m4] > a[m5]) {
		x = a[m4];
		a[m4] = a[m5];
		a[m5] = x;
	}
	if (a[m1] > a[m3]) {
		x = a[m1];
		a[m1] = a[m3];
		a[m3] = x;
	}
	if (a[m2] > a[m3]) {
		x = a[m2];
		a[m2] = a[m3];
		a[m3] = x;
	}
	if (a[m1] > a[m4]) {
		x = a[m1];
		a[m1] = a[m4];
		a[m4] = x;
	}
	if (a[m3] > a[m4]) {
		x = a[m3];
		a[m3] = a[m4];
		a[m4] = x;
	}
	if (a[m2] > a[m5]) {
		x = a[m2];
		a[m2] = a[m5];
		a[m5] = x;
	}
	if (a[m2] > a[m3]) {
		x = a[m2];
		a[m2] = a[m3];
		a[m3] = x;
	}
	if (a[m4] > a[m5]) {
		x = a[m4];
		a[m4] = a[m5];
		a[m5] = x;
	}

	// pivots: [ < pivot1 | pivot1 <= && <= pivot2 | > pivot2 ]
	int pivot1 = a[m2];
	int pivot2 = a[m4];
	int diffPivots = pivot1 != pivot2;
	a[m2] = a[left];
	a[m4] = a[right];

	// center part pointers
	int less = left + 1;
	int great = right - 1;

	// sorting
	if (diffPivots) {
		for (int k = less; k <= great; k++) {
			x = a[k];

			if (x < pivot1) {
				a[k] = a[less];
				a[less++] = x;
			} else if (x > pivot2) {
				while (a[great] > pivot2 && k < great) {
					great--;
				}
				a[k] = a[great];
				a[great--] = x;
				x = a[k];

				if (x < pivot1) {
					a[k] = a[less];
					a[less++] = x;
				}
			}
		}
	} else {
		for (int k = less; k <= great; k++) {
			x = a[k];

			if (x == pivot1) {
				continue;
			}
			if (x < pivot1) {
				a[k] = a[less];
				a[less++] = x;
			} else {
				while (a[great] > pivot2 && k < great) {
					great--;
				}
				a[k] = a[great];
				a[great--] = x;
				x = a[k];

				if (x < pivot1) {
					a[k] = a[less];
					a[less++] = x;
				}
			}
		}
	}
	// swap
	a[left] = a[less - 1];
	a[less - 1] = pivot1;

	a[right] = a[great + 1];
	a[great + 1] = pivot2;

	// left and right parts
	_dual_pivot_quick_sort(a, left,	less - 2);
	_dual_pivot_quick_sort(a, great + 2, right);

	// equal elements
	if (great - less > len - DIST_SIZE && diffPivots) {
		for (int k = less; k <= great; k++) {
			x = a[k];

			if (x == pivot1) {
				a[k] = a[less];
				a[less++] = x;
			} else if (x == pivot2) {
				a[k] = a[great];
				a[great--] = x;
				x = a[k];

				if (x == pivot1) {
					a[k] = a[less];
					a[less++] = x;
				}
			}
		}
	}
	// center part
	if (diffPivots) {
		_dual_pivot_quick_sort(a, less, great);
	}
}

static int range_check(int length, int fromIndex, int toIndex) {
	if (fromIndex > toIndex) {
		printf("IllegalArgumentException: fromIndex(%d) >	toIndex(%d)", fromIndex, toIndex);
		return -1;
	}

	if (fromIndex < 0) {
		printf("ArrayIndexOutOfBoundsException: %d", fromIndex);
		return -1;
	}
	if (toIndex > length) {
		printf("ArrayIndexOutOfBoundsException: %d", toIndex);
		return -1;
	}
	return 0;
}

int dual_pivot_quick_sort_part(int *a, int fromIndex, int toIndex, int a_length) {
	if (range_check(a_length, fromIndex, toIndex) != 0)
		return -1;
	_dual_pivot_quick_sort(a, fromIndex, toIndex - 1);

	return 0;
}

void dual_pivot_quick_sort(int * a, int a_length) {
#ifndef SKIP_RANGE_CHECK
	_dual_pivot_quick_sort(a, 0, a_length - 1);
#else
	dual_pivot_quick_sort_part(a, 0, a_length, a_length);
#endif

}
