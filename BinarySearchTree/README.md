# 二叉查找树
------------------

## Descritpion
250行代码实现了二叉查找树的C++构造，具有增加删除，赋值等操作。 具体原理百度搜一下二叉查找树就有了，这里只给出具体的C++实现。

代码：[BinarySearchTree.h](BinarySearchTree.h)

## Contents
- BinarySearchTree类
- 构造函数
	- `BinarySearchTree()`
	> 默认构造函数
	- `BinarySearchTree(std::vector<T> &A, size_t rootIndex = 0)`
	> 输入：A（vector数据数组）rootIndex（根节点所在索引，默认为0）
	功能：根据数组构造二叉查找树
	- `BinarySearchTree(const BinarySearchTree *rhs)`
	> 拷贝构造函数
- 析构函数
	- `~BinarySearchTree()`
	> 析构函数
- 重载操作符
	- `const BinarySearchTree operator=(const BinarySearchTree *rhs)`
	> 重载赋值运算符
- 功能函数
	- `void insert(const T &x)`
	> 功能：往查找二叉树中插入元素x
	输入：x（待插入元素）

	- `void erase(const T &x)`
	> 功能：在查找二叉树中删除元素x
	输入：x（待删除元素）

	- `int contains(const T &x)`
	> 功能：查找元素x在查找二叉树中的层数
	输入：x（待查找元素）
	输出：元素所在层数

	- `void printTree() const`
	 > 功能：可视化输出树（未完善）