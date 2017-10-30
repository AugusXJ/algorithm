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

	void insert(const T &x);												//插入一个元素
	void erase(const T &x);													//删除一个元素
	int contains(const T &x);												//返回元素x所属的层数
	const T findMin() { return findMin(root)->element; }					//查找最小元素值
	const T findMax() { return findMax(root)->element; }					//查找最大元素值
	void getFloors() const { return floors; }								//返回层数
	void printTree() const;
private:
	class BinaryNode														//节点嵌套类
	{
	public:
		T element;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode(const T& theelement,BinaryNode *lt,BinaryNode *rt)
			:element(theelement),left(lt),right(rt){}
	};
	BinaryNode *root;														//根节点
	size_t floors;
	void insert(const T &x, BinaryNode *&t,size_t f);
	int contains(const T &x, BinaryNode *&t, size_t f);
	void erase(const T &x, BinaryNode *&t, size_t f);
	BinaryNode* findMin(BinaryNode *t = root) const;						//查找t节点的子节点的最小节点
	BinaryNode* findMax(BinaryNode *t = root) const;						//查找t节点的子节点的最大节点
	void makeEmpty(BinaryNode *t);
	BinaryNode* clone(BinaryNode *t) const;
	void printTree(BinaryNode *t) const;
};

/*
输入：A（vector数据数组）rootIndex（根节点所在索引，默认为0）
功能：根据数组构造二叉查找树
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
功能：往查找二叉树中插入元素x
输入：x（待插入元素）
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
功能：在查找二叉树中删除元素x
输入：x（待删除元素）
*/
template <typename T>
void BinarySearchTree<T>::erase(const T &x)
{
	erase(x, root, 1);
}

/*
功能：查找元素x在查找二叉树中的层数
输入：x（待查找元素）
输出：元素所在层数
*/
template <typename T>
int BinarySearchTree <T>::contains(const T &x)
{
	return contains(x, root, 1);
}

/*
功能：可视化输出树（未完善）
*/
template<typename T>
inline void BinarySearchTree<T>::printTree() const
{
	cout << "层次遍历" << endl;
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

//------------------------------------------私有类工具函数-------------------------------------------

/*
输入：x（插入的值） t（节点） f(当前所在层数）
功能：若t处为空指针，在t处插入，否则根据二叉查找树的性质递归
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
		std::cout << "插入出错：二叉查找树中已含有该数" << endl;
}

/*
输入：x（待删除元素） t（当前所在节点） f（当前所在层数）
功能：查询是否在当前节点，若是则删除，否在根据二叉树性质往下搜索
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
	else if (t->left != nullptr && t->right != nullptr)		//找到元素时，分成2个孩子和1个孩子两种情况
	{
		t->element = findMin(t->right)->element;
		erase(t->element, t->right, f + 1);
	}
	else
	{
		BinaryNode *oldnode = t;
		t = (t->left == nullptr) ? t->right : t->left;
		if (oldnode == root)								//若删除的是根节点，改变根节点
			root = t;
		delete oldnode; oldnode = nullptr;
		floors = min(floors, --f);
	}
}



/*
输入：x（待查询元素） t（当前所在节点） f（当前所在层数）
功能：查询x是否在当前节点，若不是根据查找二叉树性质往下搜索
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
功能：查找t节点的子节点的最小节点
输入：t（查找节点，默认为根节点）
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
查找t节点的子节点的最大节点
输入：t（查找节点，默认为根节点）
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
功能：删除节点t及其孩子节点
输入：t（待删除节点）
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


