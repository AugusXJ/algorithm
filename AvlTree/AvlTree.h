#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
class AvlTree
{
public:
	AvlTree() :root(nullptr) {}
	AvlTree(std::vector<T> &A, size_t rootIndex = 0);
	AvlTree(const AvlTree *rhs) { clone(rhs.root); }
	~AvlTree() { makeEmpty(root); }

	const AvlTree operator=(const AvlTree *rhs);

	void insert(const T &x);												//����һ��Ԫ��
	void erase(const T &x);													//ɾ��һ��Ԫ��
	bool contains(const T &x);												//����Ԫ��x�����Ĳ���
	const T findMin() { return findMin(root)->element; }					//������СԪ��ֵ
	const T findMax() { return findMax(root)->element; }					//�������Ԫ��ֵ
	void printTree() const;
private:
	class AvlNode														//�ڵ�Ƕ����
	{
	public:
		T element;
		AvlNode *left;
		AvlNode *right;
		int height;
		AvlNode(const T& theelement,AvlNode *lt,AvlNode *rt,int h=0)
			:element(theelement),left(lt),right(rt),height(h){}
	};
	AvlNode *root;														//���ڵ�
	void insert(const T &x, AvlNode *&t);
	bool contains(const T &x, AvlNode *&t);
	void erase(const T &x, AvlNode *&t);
	AvlNode* findMin(AvlNode *t = root) const;						//����t�ڵ���ӽڵ����С�ڵ�
	AvlNode* findMax(AvlNode *t = root) const;						//����t�ڵ���ӽڵ�����ڵ�
	void makeEmpty(AvlNode *t);
	AvlNode* clone(AvlNode *t) const;
	void printTree(AvlNode *t) const;
	int height(AvlNode *t) const { return t == nullptr ? -1 : t->height; }	//���ؽڵ�t�ĸ߶ȣ�û�к��ӽڵ�Ϊ0
	void rotateWithLeftChild(AvlNode *& k2);
	void rotateWithRightChild(AvlNode *& k2);
	void doubleWithLeftChild(AvlNode *& k3);
	void doubleWithRightChild(AvlNode *& k3);
};

/*
���룺A��vector�������飩rootIndex�����ڵ�����������Ĭ��Ϊ0��
���ܣ��������鹹����������
*/
template <typename T>
AvlTree<T>::AvlTree(std::vector<T> &A, size_t rootIndex)
{
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
inline const AvlTree<T> AvlTree<T>::operator=(const AvlTree * rhs)
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
void AvlTree<T>::insert(const T &x)
{
	if (root == nullptr)
	{
		root = new AvlNode(x, nullptr, nullptr);
	}
	else
		insert(x, root);
}

/*
���ܣ��ڲ��Ҷ�������ɾ��Ԫ��x
���룺x����ɾ��Ԫ�أ�
*/
template <typename T>
void AvlTree<T>::erase(const T &x)
{
	erase(x, root);
}

/*
���ܣ�����Ԫ��x�ڲ��Ҷ������еĲ���
���룺x��������Ԫ�أ�
�����Ԫ�����ڲ���
*/
template <typename T>
bool AvlTree <T>::contains(const T &x)
{
	return contains(x, root);
}

/*
���ܣ����ӻ��������δ���ƣ�
*/
template<typename T>
inline void AvlTree<T>::printTree() const
{
	cout << "�������" << endl;
	printTree(root);
}

//------------------------------------------˽���๤�ߺ���-------------------------------------------

/*
���룺x�������ֵ�� t���ڵ㣩 
���ܣ���t��Ϊ��ָ�룬��t�����룬������ݶ�������������ʵݹ�
*/
template <typename T>
void AvlTree<T>::insert(const T &x, AvlNode *&t)
{
	if (t == nullptr)
	{
		t = new AvlNode(x, nullptr, nullptr);
	}
	else if (x < t->element)
	{
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2)
		{
			if (x < t->left->element)						//�������ӵ���ߣ��ⲿ��
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
	}
	else if (x > t->element)
	{
		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2)
		{
			if(x>t->right->element)							//�����Һ��ӵ��ұߣ��ⲿ��
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
	}
	else
		std::cout << "�������������������Ѻ��и���" << endl;
	t->height = max(height(t->left), height(t->right)) + 1;
}

/*
���룺x����ɾ��Ԫ�أ� t����ǰ���ڽڵ㣩
���ܣ���ѯ�Ƿ��ڵ�ǰ�ڵ㣬������ɾ�������ڸ��ݶ�����������������
*/
template<typename T>
inline void AvlTree<T>::erase(const T & x, AvlNode *& t)
{
	if (t == nullptr)
		return;
	if (x < t->element)
	{
		erase(x, t->left);
		if (height(t->right) - height(t->left) == 2)
		{
			if (height(t->right->right) < height(t->right->left))
				doubleWithRightChild(t);
			else
				rotateWithRightChild(t);
		}
	}
	else if (x > t->element)
	{
		erase(x, t->right);
		if (height(t->left) - height(t->right) == 2)
		{
			if (height(t->left->left) < height(t->right->right))
				doubleWithRightChild(t);
			else
				rotateWithRightChild(t);
		}
	}
		
	else if (t->left != nullptr && t->right != nullptr)		//�ҵ�Ԫ��ʱ���ֳ�2�����Ӻ�1�������������
	{
		t->element = findMin(t->right)->element;
		erase(t->element, t->right);
	}
	else
	{
		AvlNode *oldnode = t;
		t = (t->left == nullptr) ? t->right : t->left;
		if (oldnode == root)								//��ɾ�����Ǹ��ڵ㣬�ı���ڵ�
			root = t;
		delete oldnode; oldnode = nullptr;
	}
}



/*
���룺x������ѯԪ�أ� t����ǰ���ڽڵ㣩
���ܣ���ѯx�Ƿ��ڵ�ǰ�ڵ㣬�����Ǹ��ݲ��Ҷ�����������������
*/
template<typename T>
inline bool AvlTree<T>::contains(const T & x, AvlNode *& t)
{
	if (t == nullptr)
		return false;
	else if (x < t->element)
		return contains(x, t->left);
	else if (x > t->element)
		return contains(x, t->right);
	else
		return true;
}

/*
���ܣ�����t�ڵ���ӽڵ����С�ڵ�
���룺t�����ҽڵ㣬Ĭ��Ϊ���ڵ㣩
*/
template<typename T>
inline typename AvlTree<T>::AvlNode * AvlTree<T>::findMin(AvlNode * t) const
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
inline typename AvlTree<T>::AvlNode * AvlTree<T>::findMax(AvlNode * t) const
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
inline void AvlTree<T>::makeEmpty(AvlNode * t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}


/*
���ܣ���¡�ڵ�t�������½ڵ�
���룺t������¡�ڵ㣩
*/
template<typename T>
inline typename AvlTree<T>::AvlNode * AvlTree<T>::clone(AvlNode * t) const
{
	if (t == nullptr)
		return nullptr;
	return new AvlNode(t->element, clone(t->left), clone(t->right));
}


/*
���ܣ�����ڵ�t������������������
���룺t��������ڵ㣩
*/
template<typename T>
inline void AvlTree<T>::printTree(AvlNode * t) const
{
	if (t != nullptr)
	{
		std::cout << t->element<<endl;
		printTree(t->left);
		printTree(t->right);
	}
}

/*
���ܣ�ƽ�����������ת�����ӵ�������������˳ʱ�룩
���룺k3����ƽ��ڵ㣩
*/
template<typename T>
inline void AvlTree<T>::rotateWithLeftChild(AvlNode *& k2)
{
	AvlNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

/*
���ܣ�����ת���Һ��ӵ���������������ʱ�룩
���룺k2����ƽ��ڵ㣩
*/
template<typename T>
inline void AvlTree<T>::rotateWithRightChild(AvlNode *& k2)
{
	AvlNode *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->right), k2->height) + 1;
	k2 = k1;
}

/*
���ܣ�ƽ�������˫��ת�����ӵ���������������-����ת��
���룺k3����ƽ��ڵ㣩
*/
template<typename T>
inline void AvlTree<T>::doubleWithLeftChild(AvlNode *& k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

/*
���ܣ�˫��ת���Һ��ӵ���������������-�ҵ���ת��
*/
template<typename T>
inline void AvlTree<T>::doubleWithRightChild(AvlNode *& k3)
{
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}


