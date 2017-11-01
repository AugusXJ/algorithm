#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
给定1元，3元，5元三种硬币
使用动态规划解决给定金额所需的最少硬币
*/
class DynamicProgramming
{
public:
	int minNum(vector<int> &coin,int money);
};

int DynamicProgramming::minNum(vector<int> &coin, int money)
{
	int minNum(int money);
	{
		int min = money;
		vector<int> num(money + 1);
		for (int i = 0; i < num.size(); i++) num[i] = i;
		num[0] = 0;
		for (int i = 1; i < money+1; i++)
		{
			for (int j = 0; j < coin.size(); j++)
			{
				if (i >= coin[j] && num[i - coin[j]] + 1 < num[i])
					num[i] = num[i - coin[j]] + 1;
			}
		}
		return *num.rbegin();
	}
}

int main()
{
	DynamicProgramming DP;
	vector<int> coin = { 1,3,5 };
	int money;
	cout << "Please import the money: ";
	while (cin >> money)
	{
		cout << DP.minNum(coin,money) << endl;
		cout << "Please import the money: ";
	}
	system("pause");
}