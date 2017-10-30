#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

/*
红黑树实现
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

	void insert(const T &x);												//插入一个元素
	void erase(const T &x);													//删除一个元素
	bool contains(const T &x);												//返回元素x所属的层数
	const T findMin() { return findMin(root)->element; }					//查找最小元素值
	const T findMax() { return findMax(root)->element; }					//查找最大元素值
	void printTree() const;
private:
	class RBNode														//节点嵌套类
	{
	public:
		T element;
		RBNode *left;
		RBNode *right;
		RBNode *father;
		int color;				//红(0) 黑(1)
		RBNode(const T& theelement,RBNode *lt,RBNode *rt,int c = 0)
			:element(theelement), left(lt), right(rt), color(c) {
			father = nullptr;
		}
	};
	RBNode *root;														//根节点
	RBNode* insert(const T &x, RBNode *&t);
	void insert_maintenance(RBNode *t);
	bool contains(const T &x, RBNode *&t);
	void erase(const T &x, RBNode *&t);
	void erase_maintenance(RBNode *t);
	RBNode* findMin(RBNode *t = root) const;						//查找t节点的子节点的最小节点
	RBNode* findMax(RBNode *t = root) const;						//查找t节点的子节点的最大节点
	void makeEmpty(RBNode *t);
	RBNode* clone(RBNode *t) const;
	void printTree(RBNode *t) const;
	void RightRotate(RBNode *& k2);
	void LeftRotate(RBNode *& k2);
};

/*
输入：A（vector数据数组）rootIndex（根节点所在索引，默认为0）
功能：根据数组构造二叉查找树
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
功能：往查找二叉树中插入元素x
输入：x（待插入元素）
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
		insert_maintenance(n);					//插入节点之后维护红黑树性质
		
	}
	root->color = 1;
		
}

/*
功能：在查找二叉树中删除元素x
输入：x（待删除元素）
*/
template <typename T>
void RBTree<T>::erase(const T &x)
{
	erase(x, root);
}

/*
功能：查找元素x在查找二叉树中的层数
输入：x（待查找元素）
输出：元素所在层数
*/
template <typename T>
bool RBTree <T>::contains(const T &x)
{
	return contains(x, root);
}

/*
功能：可视化输出树（未完善）
*/
template<typename T>
inline void RBTree<T>::printTree() const
{
	cout << "层次遍历" << endl;
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

//------------------------------------------私有类工具函数-------------------------------------------

/*
输入：x（插入的值） t（节点） 
功能：若t处为空指针，在t处插入，否则根据二叉查找树的性质递归
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
		throw runtime_error("插入出错：二叉查找树中已含有该数");
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
			father->color = 1;			//父（红->黑）
			uncle->color = 1;			//叔（红->黑）
			grandfather->color = 0;		//祖父（黑->红）
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
输入：x（待删除元素） t（当前所在节点）
功能：查询是否在当前节点，若是则删除，否在根据二叉树性质往下搜索
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
	else if (t->left != nullptr && t->right != nullptr)		//找到元素时，分成2个孩子和1个孩子两种情况
	{
		t->element = findMin(t->right)->element;
		erase(t->element, t->right);
	}
	else
	{
		RBNode *oldnode = t;
		erase_maintenance(t);
		t = (t->left == nullptr) ? t->right : t->left;
		if (oldnode == root)								//若删除的是根节点，改变根节点
			root = t;
		delete oldnode; oldnode = nullptr;
	}
}

/*
功能：删除操作中维护红黑树性质
输入：t（待删除元素,此时t最多只有一个孩子）
*/
template<typename T>
inline void RBTree<T>::erase_maintenance(RBNode * t)
{
	if (t->left != nullptr || t->right != nullptr)	//如果t有一个孩子，则不需要操作		
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
			&& (brother->right == nullptr||brother->right->color == 1)))			//若x为黑，兄弟为黑，兄弟的孩子均为黑
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
输入：x（待查询元素） t（当前所在节点）
功能：查询x是否在当前节点，若不是根据查找二叉树性质往下搜索
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
功能：查找t节点的子节点的最小节点
输入：t（查找节点，默认为根节点）
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
查找t节点的子节点的最大节点
输入：t（查找节点，默认为根节点）
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
功能：删除节点t及其孩子节点
输入：t（待删除节点）
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
功能：克隆节点t，返回新节点
输入：t（被克隆节点）
*/
template<typename T>
inline typename RBTree<T>::RBNode * RBTree<T>::clone(RBNode * t) const
{
	if (t == nullptr)
		return nullptr;
	return new RBNode(t->element, clone(t->left), clone(t->right));
}


/*
功能：输出节点t并以先序遍历输出子树
输入：t（待输出节点）
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
功能：红黑树单旋转（右旋）
输入：k2（不平衡节点）
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
功能：单旋转（左旋）
输入：k2（不平衡节点）
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


