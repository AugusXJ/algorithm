#include <stdlib.h>
#include <vector>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
	vector<int> A = { 1,2,3,4,5,6,7 };
	BinarySearchTree<int> bt(A,4);
	bt.erase(3);
	bt.printTree();
	cout << bt.contains(4) << endl;
	system("pause");
	return 0;
}