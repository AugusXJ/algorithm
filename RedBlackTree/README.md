# 红黑树
------------------

## Descritpion
实现红黑树的C++构造，具有增加删除，赋值，维护红色树的性质等操作。 
红黑树性质：
(1) 每个节点或者是黑色，或者是红色。
(2) 根节点是黑色。
(3) 每个叶子节点是黑色。 [注意：这里叶子节点，是指为空的叶子节点！]
(4) 如果一个节点是红色的，则它的子节点必须是黑色的。
(5) 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点

###插入&&删除
可参考[http://www.cnblogs.com/skywang12345/p/3245399.html](http://www.cnblogs.com/skywang12345/p/3245399.html)

代码：[RedBlackTree.h](RedBlackTree.h)

## Contents 
- RBTree类
- 构造函数
	- `RBTree()`
	> 默认构造函数
	- `RBTree(std::vector<T> &A, size_t rootIndex = 0)`
	> 输入：A（vector数据数组）rootIndex（根节点所在索引，默认为0）
	功能：根据数组构造红黑树
	- `RBTree(const RBTree *rhs)`
	> 拷贝构造函数
- 析构函数
	- `~RBTree()`
	> 析构函数
- 重载操作符
	- `const RBTree operator=(const RBTree *rhs)`
	> 重载赋值运算符
- 功能函数
	- `void insert(const T &x)`
	> 功能：往红黑树中插入元素x
	输入：x（待插入元素）

	- `void erase(const T &x)`
	> 功能：在红黑树中删除元素x
	输入：x（待删除元素）

	- `bool contains(const T &x)`
	> 功能：查找元素x是否在树中
	输入：x（待查找元素）
	输出：true（存在）false（不存在）

	- `void printTree() const`
	 > 功能：可视化输出树（未完善）
- 私有函数见代码，均有详细注释，红黑树重点是处理插入和删除时的维护红黑树性质。
	