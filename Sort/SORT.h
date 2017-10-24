#pragma once
#include <vector>
#include <algorithm>
//--------------------------------------------------------------------------------------------------
/*
��������
���ܣ�ʵ�ִ�С����Ĳ�������
���룺A�����������飩
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
			A[j + 1] = A[j];			//������һλ
			j--;
		}
		A[j + 1] = key;					//ÿһ�����i�����ݵ�����
	}
}
//--------------------------------------------------------------------------------------------------
/*
ѡ������
���ܣ�ʵ�ִ�С�����ѡ������
���룺A�����������飩
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
�鲢����
���ܣ�ʵ�ִ�С����Ĺ鲢����
���룺A������������) p(������������Ԫ������) r(����������βԪ������)
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
�鲢���򹤾ߺ���
���ܣ�����������������кϲ�������
���룺A�����ϲ�������) p(����������1��Ԫ������) q(����������1βԪ������) r(����������2βԪ������)
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
ð������
���ܣ�ʵ�ִ�С����Ĺ鲢����
���룺A�����������飩
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
������
���룺A�����������飩 i�������� size���ѵĴ�С��
���ܣ�ά����С��A��i������С������
���Ӷȣ�O(lgn)
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
����
���룺A�����������飩 size���ѵĴ�С��
���ܣ������󶥶�
���Ӷȣ�O(nlgn)
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
������
���ܣ�ʵ�ִ�С����Ķ�����
���룺A(����������)
���Ӷȣ�O(nlgn)
*/
template <typename T>
void HEAP_SORT(std::vector<T> &A)
{
	if (A.size() <= 1)
		return;
	size_t N = A.size();
	A.insert(A.begin(), 0);				//����A�Ǵ�0��ʼ�ģ����Ǵ�1��ʼ�ģ�������A��λ�ò�����õ�Ԫ��
	BULID_HEAP(A,N);
	for (size_t i = N; i > 1; i--)		//����ÿ�ΰ���С�����ŵ���󣬽��A�ǴӴ�С���е�
	{
		swap(A[i], A[1]);
		ADJUST_HEAP(A, 1, i-1);
	}
	A.erase(A.begin());
}
//--------------------------------------------------------------------------------------------------
/*
�������򹤾ߺ���
���ܣ�����һ��������һ��Ϊ��Ԫ�أ���ʵ�ָû������Ԫ�ص�ֵС�ڸû�����ֵ���ұߵĴ��ڡ�
���룺A�����������飩 p��������������Ԫ�أ� r������������βԪ�أ�
���������������
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
��������
���ܣ�ʵ�ִ�С����Ŀ�������
���룺A�����������飩 p������������Ԫ�أ� r����������βԪ��(A.size()-1)��
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