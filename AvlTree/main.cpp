#include <stdlib.h>
#include <vector>
#include "AvlTree.h"

using namespace std;

int main()
{
	vector<int> A = { 1,2,3,4,5,6,7 };
	AvlTree<int> bt(A);
	bt.printTree();
	cout << bt.contains(4) << endl;
	system("pause");
	return 0;
}