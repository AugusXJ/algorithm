#pragma once
#include <vector>
#include <algorithm>
//--------------------------------------------------------------------------------------------------
/*
插入排序
功能：实现从小到大的插入排序
输入：A（待排序数组）
*/
template<typename T>
void INSERTION_SORT(std::vector<T> &A)
{
	for (size_t i = 1; i < A.size(); i++)
	{
		T key = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > key)
		{
			A[j + 1] = A[j];			//往后移一位
			j--;
		}
		A[j + 1] = key;					//每一轮完成i个数据的排序
	}
}
//--------------------------------------------------------------------------------------------------
/*
选择排序
功能：实现从小到大的选择排序
输入：A（待排序数组）
*/
template <typename T>
void SELECTION_SORT(std::vector<T> &A)
{
	for (size_t i = 0; i < A.size(); i++)
	{
		T index = i;
		for (size_t j = i + 1; j < A.size(); j++)
		{
			if (A[j] < A[index])
			{
				index = j;
			}
		}
		swap(A[i], A[index]);
	}
}
//--------------------------------------------------------------------------------------------------
/*
归并排序
功能：实现从小到大的归并排序
输入：A（待排序数组) p(待排序数组首元素索引) r(待排序数组尾元素索引)
*/
template <typename T>
void MERGE_SORT(std::vector<T> &A, size_t p, size_t r)
{
	if (p < r)
	{
		size_t q = (p + r) / 2;
		MERGE_SORT(A, p, q);
		MERGE_SORT(A, q + 1, r);
		MERGE(A, p, q, r);
	}
}

/*
归并排序工具函数
功能：对两个有序数组进行合并并排序
输入：A（待合并后数组) p(待排序数组1首元素索引) q(待排序数组1尾元素索引) r(待排序数组2尾元素索引)
*/
template <typename T>
void MERGE(std::vector<T> &A, size_t p, size_t q, size_t r)
{
	std::vector<T> L(A.begin() + p, A.begin() + q + 1);
	std::vector<T> R(A.begin() + q + 1, A.begin() + r + 1);
	//copy(A.begin() + p, A.begin() + q+1);
	//std::vector<T> R = copy(A.begin() + q + 1, A.begin() + r + 1);
	size_t i = 0, j = 0;
	for (size_t k = p; k != r; k++)
	{
		if (j==R.size() || L[i] < R[j])
			A[k] = L[i++];
		else
			A[k] = R[j++];
	}
}
//--------------------------------------------------------------------------------------------------
/*
冒泡排序
功能：实现从小到大的归并排序
输入：A（待排序数组）
*/
template <typename T> 
void BUBLE_SORT(std::vector<T> &A)
{
	size_t N = A.size();
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = N - 1; j > i; j--)
		{
			if (A[j] < A[j - 1])
				swap(A[j], A[j - 1]);
		}
	}
}
//--------------------------------------------------------------------------------------------------
/*
调整堆
输入：A（待排序数组） i（索引） size（堆的大小）
功能：维护最小堆A在i处的最小堆性质
复杂度：O(lgn)
*/
template <typename T>
void ADJUST_HEAP(std::vector<T> &A, size_t i, size_t size)
{
	size_t lchild = 2 * i;
	size_t rchild = 2 * i + 1;
	size_t largest = i;
	if (lchild<=size && A[lchild]>A[largest])
		largest = lchild;
	if (rchild<=size && A[rchild]>A[largest])
		largest = rchild;
	if (largest != i)
	{
		swap(A[i], A[largest]);
		ADJUST_HEAP(A, largest, size);
	}

}

/*
建堆
输入：A（待排序数组） size（堆的大小）
功能：建立大顶堆
复杂度：O(nlgn)
*/
template <typename T>
void BULID_HEAP(std::vector<T> &A, size_t size)
{
	size_t N = A.size();
	for (size_t i = N / 2; i != 0; i--)
	{
		ADJUST_HEAP(A, i,size);
	}
}

/*
堆排序
功能：实现从小到大的堆排序
输入：A(待排序数组)
复杂度：O(nlgn)
*/
template <typename T>
void HEAP_SORT(std::vector<T> &A)
{
	if (A.size() <= 1)
		return;
	size_t N = A.size();
	A.insert(A.begin(), 0);				//数组A是从0开始的，堆是从1开始的，在数组A首位置插个不用的元素
	BULID_HEAP(A,N);
	for (size_t i = N; i > 1; i--)		//由于每次把最小的数放到最后，结果A是从大到小排列的
	{
		swap(A[i], A[1]);
		ADJUST_HEAP(A, 1, i-1);
	}
	A.erase(A.begin());
}
//--------------------------------------------------------------------------------------------------
/*
快速排序工具函数
功能：定义一个基数（一般为首元素），实现该基数左边元素的值小于该基数的值，右边的大于。
输入：A（带排序数组） p（带排序数组首元素） r（带排序数组尾元素）
输出：基数的索引
*/
template <typename T>
const size_t PARTITION(std::vector<T> &A, size_t p, size_t r)
{
	T basic = A[p];
	size_t i = p, j = r;
	while (i < j)
	{
		while (j > i && A[j] >= basic) j--;
		while (i<j && A[i]<=basic) i++;
		swap(A[i], A[j]);
	}
	swap(A[p], A[i]);
	return i;
}


/*
快速排序
功能：实现从小到大的快速排序
输入：A（带排序数组） p（排序数组首元素） r（排序数组尾元素(A.size()-1)）
*/
template <typename T>
void QUICK_SORT(std::vector<T> &A, size_t p, size_t r)
{
	if (p < r)
	{
		size_t q = PARTITION(A, p, r);
		QUICK_SORT(A, p, q - 1);
		QUICK_SORT(A, q + 1, r);
	}
}
//--------------------------------------------------------------------------------------------------