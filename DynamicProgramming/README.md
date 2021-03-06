# 动态规划
------------

## 描述
实现了动态规划算法的一个例子，给定一组硬币额度{1,3,5}和一个金额M，确定M最少需要几枚硬币。
首先我们思考一个问题，如何用最少的硬币凑够i元(i<11)？为什么要这么问呢？两个原因：1.当我们遇到一个大问题时，总是习惯把问题的规模变小，这样便于分析讨论。 2.这个规模变小后的问题和原来的问题是同质的，除了规模变小，其它的都是一样的，本质上它还是同一个问题(规模变小后的问题其实是原问题的子问题)。
好了，让我们从最小的i开始吧。当i=0，即我们需要多少个硬币来凑够0元。由于1，3，5都大于0，即没有比0小的币值，因此凑够0元我们最少需要0个硬币。 (这个分析很傻是不是？别着急，这个思路有利于我们理清动态规划究竟在做些什么。) 这时候我们发现用一个标记来表示这句“凑够0元我们最少需要0个硬币。”会比较方便，如果一直用纯文字来表述，不出一会儿你就会觉得很绕了。那么，我们用d(i)=j来表示凑够i元最少需要j个硬币。于是我们已经得到了d(0)=0，表示凑够0元最小需要0个硬币。当i=1时，只有面值为1元的硬币可用，因此我们拿起一个面值为1的硬币，接下来只需要凑够0元即可，而这个是已经知道答案的，即d(0)=0。所以，d(1)=d(1-1)+1=d(0)+1=0+1=1。当i=2时，仍然只有面值为1的硬币可用，于是我拿起一个面值为1的硬币，接下来我只需要再凑够2-1=1元即可(记得要用最小的硬币数量)，而这个答案也已经知道了。所以d(2)=d(2-1)+1=d(1)+1=1+1=2。一直到这里，你都可能会觉得，好无聊，感觉像做小学生的题目似的。因为我们一直都只能操作面值为1的硬币！耐心点，让我们看看i=3时的情况。当i=3时，我们能用的硬币就有两种了：1元的和3元的( 5元的仍然没用，因为你需要凑的数目是3元！5元太多了亲)。既然能用的硬币有两种，我就有两种方案。如果我拿了一个1元的硬币，我的目标就变为了：凑够3-1=2元需要的最少硬币数量。即d(3)=d(3-1)+1=d(2)+1=2+1=3。这个方案说的是，我拿3个1元的硬币；第二种方案是我拿起一个3元的硬币，我的目标就变成：凑够3-3=0元需要的最少硬币数量。即d(3)=d(3-3)+1=d(0)+1=0+1=1. 这个方案说的是，我拿1个3元的硬币。好了，这两种方案哪种更优呢？记得我们可是要用最少的硬币数量来凑够3元的。所以，选择d(3)=1，怎么来的呢？具体是这样得到的：d(3)=min{d(3-1)+1, d(3-3)+1}

代码：[click here](DynamicProgramming.cpp)

动态规划算法实现过程自行百度或谷歌。