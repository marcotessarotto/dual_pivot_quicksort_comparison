#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/resource.h>

#include "dual_pivot_quicksort.h"
#include "quicksort.h"

// some types of initialization
void init_array1_ordered_desc(int * a, int a_length) {

	printf("initializing with ordered values, descending\n");

	for (int i = 0; i < a_length; i++)
		a[i] = a_length - i - 1;
}

void init_array2_rnd_values(int * a, int a_length, int seed) {

	printf("initializing with pseudo-random values, seed=%d\n", seed);

	srand(seed);

	for (int i = 0; i < a_length; i++)
		a[i] = rand();
}

void init_array3_ordered_ascending(int * a, int a_length) {

	printf("initializing with ordered values, ascending\n");

	for (int i = 0; i < a_length; i++)
		a[i] = i;
}

// duplicate an array
void * memdup(const void * a, size_t size) {
	void * result = malloc(size);
	if (result == NULL)
		return NULL;

	memcpy(result, a, size);

	return result;
}

// create an int array of 'length' elements and fill it with random values, using specified seed
int * rnd_int_array(int length, int seed) {
	int * result = malloc(length * sizeof(int));
	if (result == NULL)
		return NULL;

	srand(seed);

	for (int i = 0; i < length; i++)
		result[i] = rand();

	return result;
}

typedef struct {
	long * dt;
	double average;
} test_results;

test_results do_tests(int * data, int data_length, void (* sort_function)(int *, int), int num_rep, int ** sort_result) {

	test_results result;
	int * work_array = NULL;
	struct timespec ts1, ts2;

	result.dt = malloc(sizeof(long) * num_rep);
	if (result.dt == NULL)
		exit(1);

	// each sort test is repeated num_rep times
	for (int i = 0; i < num_rep; i++) {

		// at each iteration, recreate the array to be sorted, copying values from original test array
		if (work_array != NULL)
			free(work_array);
		work_array = memdup(data, sizeof(int) * data_length);

		if (work_array == NULL)
			exit(1);

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1);

		sort_function(work_array, data_length);

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts2);

		result.dt[i] = ((ts2.tv_sec - ts1.tv_sec) * 1000000000L + ts2.tv_nsec) - ts1.tv_nsec;

	}

	if (sort_result != NULL)
		*sort_result = work_array;
	else
		free(work_array);

	result.average = 0;

	for (int i = 0; i < num_rep; i++) {
		result.average = result.average + (result.dt[i] - result.average) / (i+1);
	}

	return result;
}


int main() {

	int N = 1024*1024;
	int NUMBER_OF_REPETITIONS = 10;
	int RND_SEED = 10001;

	int * test_array;



	test_array = malloc(N * sizeof(int));
	if (test_array == NULL)
		exit(1);

	//init_array1_ordered_desc(test_array, N);
	init_array2_rnd_values(test_array, N, RND_SEED);
	//init_array3_ordered_ascending(test_array, N);

	int * work_array = NULL;
	int * work_array2 = NULL;


	test_results res1 = do_tests(test_array, N, dual_pivot_quick_sort, NUMBER_OF_REPETITIONS, &work_array);

	test_results res2 = do_tests(test_array, N, quick_sort_hoare, NUMBER_OF_REPETITIONS, NULL);

	test_results res3 = do_tests(test_array, N, quick_sort_lomuto, NUMBER_OF_REPETITIONS, &work_array2);

	printf("average results:\n"
			"number of iterations= %d\n"
			"int array length= %d\n", NUMBER_OF_REPETITIONS, N);
	printf("dual pivot quick sort                       : dt = %.2lf ns/iteration, %.3lf ms/iteration\n", res1.average, res1.average / 1000000);
	printf("quick sort hoare partition scheme   : dt = %.2lf ns/iteration, %.3lf ms/iteration\n", res2.average, res2.average / 1000000);
	printf("quick sort lomuto partition scheme : dt = %.2lf ns/iteration, %.3lf ms/iteration\n", res3.average, res3.average / 1000000);


	return 0;
}

