# 平衡二叉树
------------------

## Descritpion
350行代码实现了平衡查找树的C++构造，具有增加删除，赋值等操作。 平衡二叉树与二叉查找树类似，但是增加了一个限制：每个节点的左子树和右子数深度之差不能大于，因此在插入与删除操作时候需要使用单旋转和双旋转维护平衡二叉树的性质。

代码：[AvlTree.h](AvlTree.h)

## Contents 
- AvlTree类
- 构造函数
	- `AvlTree()`
	> 默认构造函数
	- `AvlTree(std::vector<T> &A, size_t rootIndex = 0)`
	> 输入：A（vector数据数组）rootIndex（根节点所在索引，默认为0）
	功能：根据数组构造二叉查找树
	- `AvlTree(const BinarySearchTree *rhs)`
	> 拷贝构造函数
- 析构函数
	- `~AvlTree()`
	> 析构函数
- 重载操作符
	- `const AvlTree operator=(const AvlTree *rhs)`
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
- 私有函数
	- `class AvlNode`
	> 节点类，保存节点的元素，左子树，右子树及节点字数的深度。
	
	- 功能函数见代码，都有详细注释。