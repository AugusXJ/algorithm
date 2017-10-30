#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() :root(nullptr), floors(0) {}
	BinarySearchTree(std::vector<T> &A, size_t rootIndex = 0);
	BinarySearchTree(const BinarySearchTree *rhs) { clone(rhs.root); }
	~BinarySearchTree() { makeEmpty(root); }

	const BinarySearchTree operator=(const BinarySearchTree *rhs);

	void insert(const T &x);												//����һ��Ԫ��
	void erase(const T &x);													//ɾ��һ��Ԫ��
	int contains(const T &x);												//����Ԫ��x�����Ĳ���
	const T findMin() { return findMin(root)->element; }					//������СԪ��ֵ
	const T findMax() { return findMax(root)->element; }					//�������Ԫ��ֵ
	void getFloors() const { return floors; }								//���ز���
	void printTree() const;
private:
	class BinaryNode														//�ڵ�Ƕ����
	{
	public:
		T element;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode(const T& theelement,BinaryNode *lt,BinaryNode *rt)
			:element(theelement),left(lt),right(rt){}
	};
	BinaryNode *root;														//���ڵ�
	size_t floors;
	void insert(const T &x, BinaryNode *&t,size_t f);
	int contains(const T &x, BinaryNode *&t, size_t f);
	void erase(const T &x, BinaryNode *&t, size_t f);
	BinaryNode* findMin(BinaryNode *t = root) const;						//����t�ڵ���ӽڵ����С�ڵ�
	BinaryNode* findMax(BinaryNode *t = root) const;						//����t�ڵ���ӽڵ�����ڵ�
	void makeEmpty(BinaryNode *t);
	BinaryNode* clone(BinaryNode *t) const;
	void printTree(BinaryNode *t) const;
};

/*
���룺A��vector�������飩rootIndex�����ڵ�����������Ĭ��Ϊ0��
���ܣ��������鹹����������
*/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(std::vector<T> &A, size_t rootIndex)
{
	floors = 0;
	size_t N = A.size();
	if (N != 0 && rootIndex <N)
	{
		insert(A[rootIndex]);
		for (size_t i = 0; i < N; i++)
		{
			if (i != rootIndex)
				insert(A[i]);
		}
	}
}


template<typename T>
inline const BinarySearchTree<T> BinarySearchTree<T>::operator=(const BinarySearchTree * rhs)
{
	makeEmpty(root);
	clone(rhs.root);
	return *this;
}

/*
���ܣ������Ҷ������в���Ԫ��x
���룺x��������Ԫ�أ�
*/
template <typename T>
void BinarySearchTree<T>::insert(const T &x)
{
	if (root == nullptr)
	{
		root = new BinaryNode(x, nullptr, nullptr);
		floors = 1;
	}
	else
		insert(x, root,1);
}

/*
���ܣ��ڲ��Ҷ�������ɾ��Ԫ��x
���룺x����ɾ��Ԫ�أ�
*/
template <typename T>
void BinarySearchTree<T>::erase(const T &x)
{
	erase(x, root, 1);
}

/*
���ܣ�����Ԫ��x�ڲ��Ҷ������еĲ���
���룺x��������Ԫ�أ�
�����Ԫ�����ڲ���
*/
template <typename T>
int BinarySearchTree <T>::contains(const T &x)
{
	return contains(x, root, 1);
}

/*
���ܣ����ӻ��������δ���ƣ�
*/
template<typename T>
inline void BinarySearchTree<T>::printTree() const
{
	cout << "��α���" << endl;
	vector<BinaryNode*> queue;
	queue.push_back(root);
	int flag = 1;
	while (flag==1)
	{
		flag = 0;
		vector<BinaryNode*> temp;
		for (auto n : queue)
		{
			if (n != nullptr)
			{
				flag = 1;
				cout << n->element << " ";
				if (n->left || n->right != nullptr)
					flag = 1;
				temp.push_back(n->left);
				temp.push_back(n->right);
			}	
			else
			{
				cout << "X" << " ";
				temp.push_back(nullptr); 
				temp.push_back(nullptr);
			}
		}
		cout << endl;
		queue = temp;
	}
}

//------------------------------------------˽���๤�ߺ���-------------------------------------------

/*
���룺x�������ֵ�� t���ڵ㣩 f(��ǰ���ڲ�����
���ܣ���t��Ϊ��ָ�룬��t�����룬������ݶ�������������ʵݹ�
*/
template <typename T>
void BinarySearchTree<T>::insert(const T &x, BinaryNode *&t, size_t f)
{
	if (t == nullptr)
	{
		t = new BinaryNode(x, nullptr, nullptr);
		if (f > floors)
			floors = max(floors,f);
	}
	else if (x < t->element)
		insert(x, t->left,f+1);
	else if (x > t->element)
		insert(x, t->right,f+1);
	else
		std::cout << "�������������������Ѻ��и���" << endl;
}

/*
���룺x����ɾ��Ԫ�أ� t����ǰ���ڽڵ㣩 f����ǰ���ڲ�����
���ܣ���ѯ�Ƿ��ڵ�ǰ�ڵ㣬������ɾ�������ڸ��ݶ�����������������
*/
template<typename T>
inline void BinarySearchTree<T>::erase(const T & x, BinaryNode *& t, size_t f)
{
	if (t == nullptr)
		return;
	if (x < t->element)
		erase(x, t->left, f + 1);
	else if (x > t->element)
		erase(x, t->right, f + 1);
	else if (t->left != nullptr && t->right != nullptr)		//�ҵ�Ԫ��ʱ���ֳ�2�����Ӻ�1�������������
	{
		t->element = findMin(t->right)->element;
		erase(t->element, t->right, f + 1);
	}
	else
	{
		BinaryNode *oldnode = t;
		t = (t->left == nullptr) ? t->right : t->left;
		if (oldnode == root)								//��ɾ�����Ǹ��ڵ㣬�ı���ڵ�
			root = t;
		delete oldnode; oldnode = nullptr;
		floors = min(floors, --f);
	}
}



/*
���룺x������ѯԪ�أ� t����ǰ���ڽڵ㣩 f����ǰ���ڲ�����
���ܣ���ѯx�Ƿ��ڵ�ǰ�ڵ㣬�����Ǹ��ݲ��Ҷ�����������������
*/
template<typename T>
inline int BinarySearchTree<T>::contains(const T & x, BinaryNode *& t, size_t f)
{
	if (t == nullptr)
		return 0;
	else if (x < t->element)
		return contains(x, t->left, f + 1);
	else if (x > t->element)
		return contains(x, t->right, f + 1);
	else
		return f;
}

/*
���ܣ�����t�ڵ���ӽڵ����С�ڵ�
���룺t�����ҽڵ㣬Ĭ��Ϊ���ڵ㣩
*/
template<typename T>
inline typename BinarySearchTree<T>::BinaryNode * BinarySearchTree<T>::findMin(BinaryNode * t) const
{
	if (t == nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

/*
����t�ڵ���ӽڵ�����ڵ�
���룺t�����ҽڵ㣬Ĭ��Ϊ���ڵ㣩
*/
template<typename T>
inline typename BinarySearchTree<T>::BinaryNode * BinarySearchTree<T>::findMax(BinaryNode * t) const
{
	if (t == nullptr)
		return nullptr;
	if (t->right == nullptr)
		return t;
	return findMax(t->right);
}
/*
���ܣ�ɾ���ڵ�t���亢�ӽڵ�
���룺t����ɾ���ڵ㣩
*/
template<typename T>
inline void BinarySearchTree<T>::makeEmpty(BinaryNode * t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

template<typename T>
inline typename BinarySearchTree<T>::BinaryNode * BinarySearchTree<T>::clone(BinaryNode * t) const
{
	if (t == nullptr)
		return nullptr;
	return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

template<typename T>
inline void BinarySearchTree<T>::printTree(BinaryNode * t) const
{
	if (t != nullptr)
	{
		std::cout << t->element<<endl;
		printTree(t->left);
		printTree(t->right);
	}
}


