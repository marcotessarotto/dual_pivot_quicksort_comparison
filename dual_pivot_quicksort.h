#ifndef DUAL_PIVOT_QUICKSORT_H_
#define DUAL_PIVOT_QUICKSORT_H_

#define SKIP_RANGE_CHECK

int dual_pivot_quick_sort_part(int *a, int fromIndex, int toIndex, int a_length);
void dual_pivot_quick_sort(int * a, int a_length);

#endif /* DUAL_PIVOT_QUICKSORT_H_ */
