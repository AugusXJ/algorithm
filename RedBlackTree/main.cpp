#include <stdlib.h>
#include <vector>
#include "RedBlackTree.h"

using namespace std;

int main()
{
	vector<int> A = { 1,2,3,4,5,6,7,8,9 };
	RBTree<int> bt(A);
	bt.printTree();
	cout << endl;

	bt.erase(4);
	bt.printTree();
	system("pause");
	return 0;
}