#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

/*
�����ʵ��
*/
template <typename T>
class RBTree
{
public:
	RBTree() :root(nullptr) {}
	RBTree(std::vector<T> &A, size_t rootIndex = 0);
	RBTree(const RBTree *rhs) { clone(rhs.root); }
	~RBTree() { makeEmpty(root); }

	const RBTree operator=(const RBTree *rhs);

	void insert(const T &x);												//����һ��Ԫ��
	void erase(const T &x);													//ɾ��һ��Ԫ��
	bool contains(const T &x);												//����Ԫ��x�����Ĳ���
	const T findMin() { return findMin(root)->element; }					//������СԪ��ֵ
	const T findMax() { return findMax(root)->element; }					//�������Ԫ��ֵ
	void printTree() const;
private:
	class RBNode														//�ڵ�Ƕ����
	{
	public:
		T element;
		RBNode *left;
		RBNode *right;
		RBNode *father;
		int color;				//��(0) ��(1)
		RBNode(const T& theelement,RBNode *lt,RBNode *rt,int c = 0)
			:element(theelement), left(lt), right(rt), color(c) {
			father = nullptr;
		}
	};
	RBNode *root;														//���ڵ�
	RBNode* insert(const T &x, RBNode *&t);
	void insert_maintenance(RBNode *t);
	bool contains(const T &x, RBNode *&t);
	void erase(const T &x, RBNode *&t);
	void erase_maintenance(RBNode *t);
	RBNode* findMin(RBNode *t = root) const;						//����t�ڵ���ӽڵ����С�ڵ�
	RBNode* findMax(RBNode *t = root) const;						//����t�ڵ���ӽڵ�����ڵ�
	void makeEmpty(RBNode *t);
	RBNode* clone(RBNode *t) const;
	void printTree(RBNode *t) const;
	void RightRotate(RBNode *& k2);
	void LeftRotate(RBNode *& k2);
};

/*
���룺A��vector�������飩rootIndex�����ڵ�����������Ĭ��Ϊ0��
���ܣ��������鹹����������
*/
template <typename T>
inline RBTree<T>::RBTree(std::vector<T> &A, size_t rootIndex)
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
inline const RBTree<T> RBTree<T>::operator=(const RBTree * rhs)
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
void RBTree<T>::insert(const T &x)
{
	if (root == nullptr)
	{
		root = new RBNode(x, nullptr, nullptr,1);
	}
	else
	{
		RBNode* n = insert(x, root);
		insert_maintenance(n);					//����ڵ�֮��ά�����������
		
	}
	root->color = 1;
		
}

/*
���ܣ��ڲ��Ҷ�������ɾ��Ԫ��x
���룺x����ɾ��Ԫ�أ�
*/
template <typename T>
void RBTree<T>::erase(const T &x)
{
	erase(x, root);
}

/*
���ܣ�����Ԫ��x�ڲ��Ҷ������еĲ���
���룺x��������Ԫ�أ�
�����Ԫ�����ڲ���
*/
template <typename T>
bool RBTree <T>::contains(const T &x)
{
	return contains(x, root);
}

/*
���ܣ����ӻ��������δ���ƣ�
*/
template<typename T>
inline void RBTree<T>::printTree() const
{
	cout << "��α���" << endl;
	vector<RBNode*> queue;
	queue.push_back(root);
	int flag = 1;
	while (flag == 1)
	{
		flag = 0;
		vector<RBNode*> temp;
		for (auto n : queue)
		{
			if (n != nullptr)
			{
				flag = 1;
				cout << n->element << "("<<n->color<<") ";
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
���룺x�������ֵ�� t���ڵ㣩 
���ܣ���t��Ϊ��ָ�룬��t�����룬������ݶ�������������ʵݹ�
*/
template <typename T>
inline typename RBTree<T>::RBNode * RBTree<T>::insert(const T &x, RBNode *&t)
{
	RBNode* temp = nullptr;
	if (t == nullptr)
	{
		t = new RBNode(x, nullptr, nullptr, 0);
		temp = t;
		return t;
	}
	else if (x < t->element)
	{
		temp = insert(x, t->left);
		t->left->father = t;
	}
	else if (x > t->element)
	{
		temp = insert(x, t->right);
		t->right->father = t;
	}
	else
		throw runtime_error("�������������������Ѻ��и���");
	return temp;
}

template<typename T>
inline void RBTree<T>::insert_maintenance(RBNode * t)
{
	if (t == root)
		return;
	RBNode *father = t->father;
	if (father == root || father->color == 1)
		return;
	else
	{
		RBNode* grandfather = father->father;
		RBNode* uncle = grandfather->left == father ? grandfather->right : grandfather->left;
		if (father->color == 0 && uncle != nullptr && uncle->color == 0)
		{
			father->color = 1;			//������->�ڣ�
			uncle->color = 1;			//�壨��->�ڣ�
			grandfather->color = 0;		//�游����->�죩
			insert_maintenance(grandfather);
		}
		else if (father->color == 0 && (uncle == nullptr||uncle->color == 1) && t == father->right)
		{
			father->color = 1;
			grandfather->color = 0;
			LeftRotate(grandfather);
		}
		else if (father->color == 0 && (uncle == nullptr||uncle->color == 1) && t == father->left)
		{
			father->color = 1;
			grandfather->color = 0;
			RightRotate(grandfather);
		}
	}

}

/*
���룺x����ɾ��Ԫ�أ� t����ǰ���ڽڵ㣩
���ܣ���ѯ�Ƿ��ڵ�ǰ�ڵ㣬������ɾ�������ڸ��ݶ�����������������
*/
template<typename T>
inline void RBTree<T>::erase(const T & x, RBNode *& t)
{
	if (t == nullptr)
		return;
	if (x < t->element)
	{
		erase(x, t->left);
	}
	else if (x > t->element)
	{
		erase(x, t->right);
	}
	else if (t->left != nullptr && t->right != nullptr)		//�ҵ�Ԫ��ʱ���ֳ�2�����Ӻ�1�������������
	{
		t->element = findMin(t->right)->element;
		erase(t->element, t->right);
	}
	else
	{
		RBNode *oldnode = t;
		erase_maintenance(t);
		t = (t->left == nullptr) ? t->right : t->left;
		if (oldnode == root)								//��ɾ�����Ǹ��ڵ㣬�ı���ڵ�
			root = t;
		delete oldnode; oldnode = nullptr;
	}
}

/*
���ܣ�ɾ��������ά�����������
���룺t����ɾ��Ԫ��,��ʱt���ֻ��һ�����ӣ�
*/
template<typename T>
inline void RBTree<T>::erase_maintenance(RBNode * t)
{
	if (t->left != nullptr || t->right != nullptr)	//���t��һ�����ӣ�����Ҫ����		
	{
		RBNode* n = t->left == nullptr ? t->right : t->left;
		n->color = t->color;
		return;
	}
	else if (t->color == 0 || t==root)
		return;
	else
	{
		RBNode* father = t->father;
		RBNode* brother = father->left == t ? father->right : father->left;
		if (t->color == 1 && brother->color == 0)
		{
			brother->color = 1;
			father->color = 0;
			LeftRotate(father);
			erase_maintenance(brother);
		}
		if (t->color == 1 && (brother == nullptr||brother->color == 1 && (brother->left == nullptr||brother->left->color == 1)
			&& (brother->right == nullptr||brother->right->color == 1)))			//��xΪ�ڣ��ֵ�Ϊ�ڣ��ֵܵĺ��Ӿ�Ϊ��
		{
			brother->color = 0;
			erase_maintenance(father);
		}
		if (t->color == 1 && brother->color == 1 && brother->left->color == 0 && brother->right->color == 1)
		{
			brother->left->color = 1;
			brother->color = 0;
			RBNode* temp = brother;
			RightRotate(brother);
			erase_maintenance(temp);
		}
		if (t->color == 1 && brother->color == 1 && brother->right->color == 0)
		{
			brother->color = father->color;
			father->color = 1;
			brother->right->color = 1;
			LeftRotate(father);
			return;
		}
	}
}

/*
���룺x������ѯԪ�أ� t����ǰ���ڽڵ㣩
���ܣ���ѯx�Ƿ��ڵ�ǰ�ڵ㣬�����Ǹ��ݲ��Ҷ�����������������
*/
template<typename T>
inline bool RBTree<T>::contains(const T & x, RBNode *& t)
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
inline typename RBTree<T>::RBNode * RBTree<T>::findMin(RBNode * t) const
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
inline typename RBTree<T>::RBNode * RBTree<T>::findMax(RBNode * t) const
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
inline void RBTree<T>::makeEmpty(RBNode * t)
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
inline typename RBTree<T>::RBNode * RBTree<T>::clone(RBNode * t) const
{
	if (t == nullptr)
		return nullptr;
	return new RBNode(t->element, clone(t->left), clone(t->right));
}


/*
���ܣ�����ڵ�t������������������
���룺t��������ڵ㣩
*/
template<typename T>
inline void RBTree<T>::printTree(RBNode * t) const
{
	if (t != nullptr)
	{
		std::cout << t->element<<endl;
		printTree(t->left);
		printTree(t->right);
	}
}

/*
���ܣ����������ת��������
���룺k2����ƽ��ڵ㣩
*/
template<typename T>
inline void RBTree<T>::RightRotate(RBNode *& k2)
{
	RBNode *k1 = k2->left;
	if (root == k2)
		root = k1;
	k2->left = k1->right;
	if(k1->right!=nullptr)
		k1->right->father = k2;
	k1->father = k2->father;
	k1->right = k2;
	k2->father = k1;
	k2 = k1;
}

/*
���ܣ�����ת��������
���룺k2����ƽ��ڵ㣩
*/
template<typename T>
inline void RBTree<T>::LeftRotate(RBNode *& k2)
{
	RBNode *k1 = k2->right;
	if (root == k2)
		root = k1;
	k2->right = k1->left;
	if(k1->left!=nullptr)
		k1->left->father = k2;
	k1->father = k2->father;
	k1->left = k2;
	k2->father = k1;
	k2 = k1;
}


