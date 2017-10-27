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

	void insert(const T &x);												//插入一个元素
	void erase(const T &x);													//删除一个元素
	bool contains(const T &x);												//返回元素x所属的层数
	const T findMin() { return findMin(root)->element; }					//查找最小元素值
	const T findMax() { return findMax(root)->element; }					//查找最大元素值
	void printTree() const;
private:
	class AvlNode														//节点嵌套类
	{
	public:
		T element;
		AvlNode *left;
		AvlNode *right;
		int height;
		AvlNode(const T& theelement,AvlNode *lt,AvlNode *rt,int h=0)
			:element(theelement),left(lt),right(rt),height(h){}
	};
	AvlNode *root;														//根节点
	void insert(const T &x, AvlNode *&t);
	bool contains(const T &x, AvlNode *&t);
	void erase(const T &x, AvlNode *&t);
	AvlNode* findMin(AvlNode *t = root) const;						//查找t节点的子节点的最小节点
	AvlNode* findMax(AvlNode *t = root) const;						//查找t节点的子节点的最大节点
	void makeEmpty(AvlNode *t);
	AvlNode* clone(AvlNode *t) const;
	void printTree(AvlNode *t) const;
	int height(AvlNode *t) const { return t == nullptr ? -1 : t->height; }	//返回节点t的高度，没有孩子节点为0
	void rotateWithLeftChild(AvlNode *& k2);
	void rotateWithRightChild(AvlNode *& k2);
	void doubleWithLeftChild(AvlNode *& k3);
	void doubleWithRightChild(AvlNode *& k3);
};

/*
输入：A（vector数据数组）rootIndex（根节点所在索引，默认为0）
功能：根据数组构造二叉查找树
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
功能：往查找二叉树中插入元素x
输入：x（待插入元素）
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
功能：在查找二叉树中删除元素x
输入：x（待删除元素）
*/
template <typename T>
void AvlTree<T>::erase(const T &x)
{
	erase(x, root);
}

/*
功能：查找元素x在查找二叉树中的层数
输入：x（待查找元素）
输出：元素所在层数
*/
template <typename T>
bool AvlTree <T>::contains(const T &x)
{
	return contains(x, root);
}

/*
功能：可视化输出树（未完善）
*/
template<typename T>
inline void AvlTree<T>::printTree() const
{
	cout << "先序遍历" << endl;
	printTree(root);
}

//------------------------------------------私有类工具函数-------------------------------------------

/*
输入：x（插入的值） t（节点） 
功能：若t处为空指针，在t处插入，否则根据二叉查找树的性质递归
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
			if (x < t->left->element)						//插在左孩子的左边（外部）
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
			if(x>t->right->element)							//插在右孩子的右边（外部）
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
	}
	else
		std::cout << "插入出错：二叉查找树中已含有该数" << endl;
	t->height = max(height(t->left), height(t->right)) + 1;
}

/*
输入：x（待删除元素） t（当前所在节点）
功能：查询是否在当前节点，若是则删除，否在根据二叉树性质往下搜索
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
		
	else if (t->left != nullptr && t->right != nullptr)		//找到元素时，分成2个孩子和1个孩子两种情况
	{
		t->element = findMin(t->right)->element;
		erase(t->element, t->right);
	}
	else
	{
		AvlNode *oldnode = t;
		t = (t->left == nullptr) ? t->right : t->left;
		if (oldnode == root)								//若删除的是根节点，改变根节点
			root = t;
		delete oldnode; oldnode = nullptr;
	}
}



/*
输入：x（待查询元素） t（当前所在节点）
功能：查询x是否在当前节点，若不是根据查找二叉树性质往下搜索
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
功能：查找t节点的子节点的最小节点
输入：t（查找节点，默认为根节点）
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
查找t节点的子节点的最大节点
输入：t（查找节点，默认为根节点）
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
功能：删除节点t及其孩子节点
输入：t（待删除节点）
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
功能：克隆节点t，返回新节点
输入：t（被克隆节点）
*/
template<typename T>
inline typename AvlTree<T>::AvlNode * AvlTree<T>::clone(AvlNode * t) const
{
	if (t == nullptr)
		return nullptr;
	return new AvlNode(t->element, clone(t->left), clone(t->right));
}


/*
功能：输出节点t并以先序遍历输出子树
输入：t（待输出节点）
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
功能：平衡二叉树单旋转（左孩子的左子树过长，顺时针）
输入：k3（不平衡节点）
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
功能：单旋转（右孩子的右子树过长，逆时针）
输入：k2（不平衡节点）
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
功能：平衡二叉树双旋转（左孩子的右子树过长，右-左单旋转）
输入：k3（非平衡节点）
*/
template<typename T>
inline void AvlTree<T>::doubleWithLeftChild(AvlNode *& k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

/*
功能：双旋转（右孩子的左子树过长，左-右单旋转）
*/
template<typename T>
inline void AvlTree<T>::doubleWithRightChild(AvlNode *& k3)
{
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}


