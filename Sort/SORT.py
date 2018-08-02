# 插入排序
def insert_sort(A):
    for i in range(1, len(A)):
        j = i - 1
        key = A[i]
        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j -= 1
        A[j+1] = key


# 冒泡排序
def bubble_sort(A):
    for i in range(len(A)):
        for j in range(len(A)-1):
            if A[j] > A[j+1]:
                A[j], A[j+1] = A[j+1], A[j]


# 选择排序
def select_sort(A):
    for i in range(len(A)):
        k = i
        for j in range(i, len(A)):
            if A[j] < A[k]:
                k = j
        A[i], A[k] = A[k], A[i]


# 归并排序
def merge_sort(A, p, r):
    if p < r:
        q = (p + r) // 2
        merge_sort(A, p, q)
        merge_sort(A, q+1, r)
        merge(A, p, q, r)


def merge(A, p, q, r):
    L = A[p:q+1]
    R = A[q+1:r+1]
    L.append(float('inf'))
    R.append(float('inf'))
    i, j = 0, 0
    for k in range(p, r+1):
        if L[i] < R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1




def main():
    A = [1, 2, 3, 4, 2]
    # insert_sort(A)
    # bubble_sort(A)
    # select_sort(A)
    merge_sort(A, 0, len(A)-1)
    print(A)


if __name__ == '__main__':
    main()