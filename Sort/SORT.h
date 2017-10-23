#pragma once
#include <vector>
#include <algorithm>

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
