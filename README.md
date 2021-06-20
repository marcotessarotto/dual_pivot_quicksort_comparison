# comparison of dual pivot quicksort and quicksort algorithms


In 2009, Vladimir Yaroslavskiy published an improvement to the quicksort algorithm, called 'Dual Pivot Quicksort'.
[link to the article](https://web.archive.org/web/20151002230717/http://iaroslavski.narod.ru/quicksort/DualPivotQuicksort.pdf "Vladimir Yaroslavskiy's Dual Pivot Quicksort")


To understand how Dual Pivot Quicksort works, have a look at the Visualization of Dual Pivot Quicksort Partitioning, by B.F. Lyon:
[https://learnforeverlearn.com/yaro_web/](https://learnforeverlearn.com/yaro_web/ "Visualization of Dual Pivot Quicksort Partitioning, by B.F. Lyon")


In 2013, Yaroslavskiy's algorithm was tweaked by Jon Bentley and Joshua Bloch and included as sorting algorithm in Java 7.

***

This program performs some benchmarks between the following algorithms:
- Vladimir Yaroslavskiy's Dual Pivot Quicksort
- quicksort using Hoare partition scheme
- quicksort using Lomuto partition scheme


The Dual Pivot Quicksort implementation used in this program is a translation to C code from the original Java code published by Yaroslavskiy.

This program creates and array of int filled with pseudo-random values, 
and measures the average time each algorithm takes to sort the array.  

sample output:

initializing with pseudo-random values, seed=10001  
average results:  
number of iterations per test= 10  
int array length= 1048576  
dual pivot quick sort                       : dt = 98131122.80 ns/iteration, 98.131 ms/iteration  
quick sort hoare partition scheme   : dt = 127448723.90 ns/iteration, 127.449 ms/iteration  
quick sort lomuto partition scheme : dt = 134373904.80 ns/iteration, 134.374 ms/iteration  


***

Vladimir Yaroslavskiy article published in 2009, with original Java source code: [https://web.archive.org/web/20151002230717/http://iaroslavski.narod.ru/quicksort/DualPivotQuicksort.pdf](https://web.archive.org/web/20151002230717/http://iaroslavski.narod.ru/quicksort/DualPivotQuicksort.pdf)


Tweaked Dual Pivot Quicksort included in the JDK: [https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/DualPivotQuicksort.java](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/DualPivotQuicksort.java)


Sebastian Wild and Markus Nebel's 2013 analysis of Yaroslavskiy's algorithm: [https://arxiv.org/pdf/1310.7409v1.pdf](https://arxiv.org/pdf/1310.7409v1.pdf)


Quicksort Partitioning: Hoare vs. Lomuto [https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto](https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto)

