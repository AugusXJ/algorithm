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
| Heap Sort | \\(O(nlog_2n)\\) | \\(O(nlog_2n)\\) | unstable | \\(O(1)\\) |
| Quick Sort | \\(O(nlog_2n)\\) | \\(O(n^2)\\) | unstable | \\(O(log2n)-O(n)\\) |
## Contents

### INSERTION_SORT
插入排序：插入排序的原理就是每一轮确定几个排序好的元素，第一轮确定前两个数（一个数的时候本身就是有序的），第二轮确定三个数的排序，一次类推，当n-1轮之后就完成了数组的排序。

### SELECTION_SORT
选择排序：选择排序的原理就是每轮确定一个最大的数，然后与队列前段的元素交换一下。第一轮时，在N个元素中找最大的，把这个数与A[0]进行交换，第二轮从A[1]~A[n-1]中找最大的，然后与A[1]交换，第k轮从A[k-1]~A[n-1]中找最大的，然后与A[k-1]进行交换，当k=N时排序完成。
 
### MERGE_SORT
归并排序：归并排序的思想是将排序数组分解成小数组并对有序小数组进行排序，对于小数组递归该操作，如果小数组足够小（1个元素或2个元素）就很容易进行排序了。假设一个N=4的数组A，排序数组A就相当于排序A[0]~A[1]和A[1]~A[2]两个子数组，两个元素的子数组通过比较大小即可排序，接着只要合并两个有序数组就完成排序了。

### BUBLE_SORT
冒泡排序也是一种交换排序，从尾元素开始不断与前一个元素进行交换，以此达到有序。第一轮时从最后一个元素开始往前走，碰到更小的就交换，那么等到它走到第一个元素A[0]时就是最小的啦，第二轮就走到A[1]停止就好了（因为A[0]是最小的），此时A[0]A[1]是两个最小的元素。

## HEAP_SORT
堆排序：将队列放入二叉树结果中，并使用最大堆的性质进行排序。
**第一轮**：将A[0]~A[N-1]放入堆中，建立最大堆，此时A[0]就是最大的，将其与A[N-1]进行交换。
**第二轮**：将A[0]~A[N-2]放入堆中，建立最大堆，此时A[0]就是最大的，将其与A[N-2]进行交换。此时A[N-1]是最大的元素，A[N-2]是第二大的元素。
**第N轮**：此时就只剩下A[0]了，自然是最大的，那么排序就完成了，数组从最后一位到第一位是不断减小的，那从前到后就是不断增加的。

## QUICK_SORT
快速排序:使用递归的思想，每一次确定一个基数，并确保小于基数的值在左边，大于基数的值在右边。然后对小于基数的子数组进行快速排序，大于基数的子数组进行快速排序。
