# Sort
-------

## Description
The implemention of several sorting algorithms for a given array `A` with size `N`. All of my code give an example from small to large.

You can see source code for detail.
code: [click here](sort.h)

The time complexity and spatial complexity of commonly used sorting algorithm.

| Sort        | Best time complexity    |  Worst time complexity  | Stability | Space complexity |
| :--------:   | :-----:   | :----: | :--------:   | :-----: |
| Insertion Sort        | \\(O(n)\\)     |   \\(O(n^2)\\)    | stable | \\(O(1)\\) |
| Selection Sort        | \\(O(n^2)\\)     |   \\(O(n^2)\\)    | unstable | \\(O(1)\\) |
| Merge Sort        | \\(O(nlog_2n)\\)      |   \\(O(nlog_2n)\\)    | stable | \\(O(n)\\) |
| Buble Sort	| \\(O(n^2)\\)	|	\\(O(n^2)\\)	|	stable 	| \\(O(1)\\) |
| Heap Sort | \\(O(nlog_2n)\\ | \\(O(nlog_2n)\\ | unstable | \\(O(1)\\ |

## Contents

### Insertion Sort
Inserting means that a new data is inserted into an ordered array `A` and continues to be ordered. For example, there is a length of `N` disordered array, and the array can be ordered after insert for `N-1` times.
**At the first time**, the first element of the array `A` is considered as an ordered sub-array, the second element of the array `A` insert into this sub-array, and now two elements are ordered.
**At the second time**, the first two elements of the array `A` form an ordered array, the third element of the array `A` insert into this sub-array with two elements, and now three elements are oredered. 
**After N-1 times**, N elements of array `A` are ordered, so the entire insert is completed.

[Chinese explaination](http://www.cnblogs.com/kkun/archive/2011/11/23/2260265.html)

### Selection Sort
 

### Merge Sort

### Buble Sort
