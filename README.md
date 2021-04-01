# Leetcode

**教学**

[代码随想录Github](https://github.com/youngyangyang04/leetcode-master)　　[代码随想录Wechat](https://mp.weixin.qq.com/s/weyitJcVHBgFtSc19cbPdw)

[labuladong 的算法小抄Github](https://github.com/labuladong/fucking-algorithm)　　[labuladong 的算法小抄Wechat](https://mp.weixin.qq.com/s/AWsL7G89RtaHyHjRPNJENA)　　[labuladong 的算法小抄Gitbook](https://labuladong.gitee.io/algo/)

[力扣加加 - lucifer](https://github.com/azl397985856/leetcode)　　[力扣加加 - 社区](https://leetcode-solution-leetcode-pp.gitbook.io/leetcode-solution/)

[进阶石](https://github.com/acm-clan/algorithm-stone)

**题解+教学**

[李威威](https://liweiwei1419.gitee.io/leetcode-algo/)

[liuchuo](https://github.com/liuchuo/LeetCode)

**模板**

[负雪明烛模板](https://blog.csdn.net/fuxuemingzhu/article/details/101900729)

[AlgoWiki模板](https://ojeveryday.github.io/AlgoWiki/#/?id=algowiki)

**英语**

[specialized-vocabulary](https://github.com/liuchuo/specialized-vocabulary)

**残酷**

[LeetCode打卡和竞赛微信群](https://wisdompeak.github.io/lc-score-board/rules.html)

做好Medium，没必要死扣Hard。LeetCode上很多Easy的题目看似简单，实则想要写出Perfect的代码并非易事。多思考如何优化Easy，Medium的解法实际上比花精力解Hard题更能提高自己。

```shell
git config --global http.proxy 127.0.0.1:1080
//然后开全局代理push/pull
```

## TIPS/TRICKS

|  技巧  |
|  :----:  |
|if (root != NULL)　而不是　if (root)|
|int size;   double asum;<br>vec.push_back(double(asum/size)); 　而不是　vec.push_back(asum/size);|
|-2^31~2^31-1 对应 INT_MIN 和 INT_MAX|
| (p && !q) &#124;&#124; (!p && q)  = (!p &#124;&#124; !q)　两者状态不同时为true　其中!q代表q为空 |
| size在for之前取值，防止for循环中size大小改变|
|tostring()　stoi()|
|如果需要遍历整棵树，递归函数就不能有返回值。<br>如果需要遍历某一条固定路线，不要求遍历整棵树，递归函数就一定要有返回值！<br>两种写法注意选择 <br>if(递归函数(left)) return;　　　if(递归函数(right)) return;<br>left = 递归函数(left);　　 　　  right = 递归函数(right);|
|反中序过程就是从最右侧往最左侧运行|
|复杂函数放在private会减少执行用时，减少内存消耗|
|数组构造二叉树，不要定义新的数组，通过索引在原数组上操作。|
|如果让空节点进入递归，就不加if<br>如果不让空节点进递归，就加if限制，终止条件也相应调整|
||
||
|剪枝,可以放在递归函数头部,也可以放在调用函数前(即上一层)|
|回溯递归是一一对应的，有一个递归，就要有一个回溯|
|回溯隐藏，直接在给函数传参时加计算，函数执行完，不改变原值|
|自底向上=后序遍历=天然的回溯过程|
||
||
||
||
||
||



---
## 1. 题表

|  题目  |知识点|技巧|
|  :----  |:----:|:----:|
|[94. Binary Tree Inorder Traversal](Tree/94+inorderTraversal.cpp) |中序 R| 注意放private|
|[144. Binary Tree Preorder Traversal](Tree/144+preorderTraversal.cpp) |先序 R| |
|[145. Binary Tree Postorder Traversal](Tree/145+postorderTraversal.cpp) |后序 R| |
|[105. Construct Binary Tree from Preorder and Inorder Traversal](Tree/105+buildTree.cpp) | 先序 中序 R|索引确定|
|[106. Construct Binary Tree from Inorder and Postorder Traversal](Tree/106+buildTree.cpp)   |中序 后序 R |索引确定|
|[114. Flatten Binary Tree to Linked List](Tree/144+preorderTraversal.cpp)   | 后序 R |注意指针连接|
|[116. Populating Next Right Pointers in Each Node](Tree/116+connect.cpp)*   | 先序 R|考虑到特殊情况即可|
|[222. Count Complete Tree Nodes](Tree/222+countNodes_Rec.cpp)*  | 完全二叉树 | 利用其性质减少计算|
|[226. Invert Binary Tree](Tree/226+invertTree_Rec.cpp)*   | 先序 R | 跟交换数字一样|
|[297. Serialize and Deserialize Binary Tree](Tree/297+serialize.cpp) | 序列化<br>反序列化 |  出入队列搜索树 <br>to_string()<br>stoi() |
|[652. Find Duplicate Subtrees](Tree/652+findDuplicateSubtrees.cpp) |后序 R  | 巧用map<br>注意输出格式|
|[654. Maximum Binary Tree](Tree/654+constructMaximumBinaryTree.cpp)* |前序 R  |注意索引 注意返回值|
|[102. Binary Tree Level Order Traversal](Tree/102+levelOrder.cpp)   | 层序 自顶向下| Q|
|[107. Binary Tree Level Order Traversal II](Tree/107+levelOrderBottom.cpp)   | 层序 自底向上|reverse|
|[199. Binary Tree Right Side View](Tree/199+rightSideView.cpp)   | 层序 ||
|[637. Average of Levels in Binary Tree](Tree/637+averageOfLevels.cpp)   |层序  |强制类型转换|
|[429. N-ary Tree Level Order Traversal](Tree/429+levelOrder.cpp)   |层序 N叉树 |换汤不换药|
|[515. Find Largest Value in Each Tree Row](Tree/515+largestValues.cpp)   |层序  | INT_MIN|
|[116. Populating Next Right Pointers in Each Node](Tree/116+connect_Queue.cpp)   | 层序 |R Q |
|[117. Populating Next Right Pointers in Each Node II](Tree/117+connect.cpp)   | 层序 | 与116一样|
|[589. N-ary Tree Preorder Traversal](Tree/589+preorder_Rec.cpp)*   | N叉树 | R S|
|[590. N-ary Tree Postorder Traversal](Tree/590+postorder_Rec.cpp)*   | N叉树 | R S|
|[101. Symmetric Tree](Tree/101+isSymmetric_Rec.cpp)*   | 思考题 |R Q S|
|[104. Maximum Depth of Binary Tree](Tree/104+maxDepth_Rec.cpp)*   |思考题 |R Q BFS|
|[559. Maximum Depth of N-ary Tree](Tree/559+maxDepth_Rec.cpp)*   |  |R /Q BFS|
|[111. Minimum Depth of Binary Tree](Tree/111+minDepth_Rec.cpp)*  |  |R /Q BFS|
|[110. Balanced Binary Tree](Tree/110+isBalanced.cpp)*:(  | 回溯 ||
|[257. Binary Tree Paths](Tree/257+binaryTreePaths_Rec+Back.cpp):)   | 回溯 | to_string()|
|[404. Sum of Left Leaves](Tree/404+sumOfLeftLeaves.cpp):(   |后序  |R|
|[513. Find Bottom Left Tree Value](Tree/513+findBottomLeftValue_Queue_BFS.cpp)*:(   |回溯  |R Q BFS|
|[112. Path Sum](Tree/112+hasPathSum.cpp):(   | 回溯 |R|
|[113. Path Sum II](Tree/113+pathSum.cpp)   | 回溯|R |
|[617. Merge Two Binary Trees](Tree/617+mergeTrees_Rec.cpp)*   |  |递归|
|[700. Search in a Binary Search Tree](Tree/700+searchBST.cpp)   |  |R|
|[98. Validate Binary Search Tree](Tree/98+isValidBST.cpp):(   |  |R 利用平衡二叉树性质|
|[530. Minimum Absolute Difference in BST](Tree/530+getMinimumDifference.cpp)*   |  |R|
|[501. Find Mode in Binary Search Tree](Tree/501+findMode.cpp)*   |  |R Template|
|[236. Lowest Common Ancestor of a Binary Tree](Tree/236+lowestCommonAncestor.cpp)   | 回溯 |R|
|[450. Delete Node in a BST](Tree/450+deleteNode.cpp)   |BST右子树最左侧的节点的值与其兄弟左子树的值最接近  |R|
|[669. Trim a Binary Search Tree](Tree/669+trimBST.cpp):(   |  |R|
|[108. Convert Sorted Array to Binary Search Tree](Tree/108+sortedArrayToBST_B_Rec.cpp)   | 二分 分治 |R|
|[538. Convert BST to Greater Tree](Tree/538+convertBST_Rec.cpp)   | 反中序 ||
|[100. Same Tree](Tree/100+isSameTree.cpp)   |  |递归|
|   |  ||

> 题号前*表示有多种解法， :(表示:(     　　:)表示:)
> 
> R代表Recursion，Q代表Queue，S代表Stack，DFS代表深度优先遍历，BFS代表广度优先遍历


|  题目  |知识点|技巧|
|  :----  |:----:|:----:|
|[203. Remove Linked List Elements](Linked_list/203+removeElements.cpp)|链表删除节点|虚拟头结点|
|[707. Design Linked List](Linked_list/707+MyLinkedList.cpp)   | 链表设计 |关键是确定待操作节点的先驱节点位置|
|   |  ||
|   |  ||
|   |  ||
|   |  ||


---
## 2. 专题

### 2.1. [树](Tree/README.md)
- 二叉树定义
- 二叉树遍历（递归/迭代）



---

## 3. C++标准模板库([STL](https://github.com/DuanYaQi/leetcode/blob/master/STL.md))介绍
- vector
- set
- string
- map
- queue
- stack
- pair
- algorithm

---

## 4. 分类
### 4.1. 刷题顺序
**基础篇（30 天）**

基础永远是最重要的，先把最最基础的这些搞熟，磨刀不误砍柴工。

- 数组，队列，栈
- 链表
- 树与递归
- 哈希表
- 双指针

**思想篇（30 天）**

这些思想是投资回报率极高的，强烈推荐每一个小的专题花一定的时间掌握。
- 二分
- 滑动窗口
- 搜索（BFS，DFS，回溯）
- 动态规划

**提高篇（31 天）**

这部分收益没那么明显，并且往往需要一定的技术积累。出现的频率相对而言比较低。但是有的题目需要你使用这些技巧。又或者可以使用这些技巧可以实现「降维打击」。
- 贪心
- 分治
- 位运算
- KMP & RK
- 并查集
- 前缀树
- 线段树
- 堆

-----

### 4.2. 分类1

**算法**

- 基础技巧：分治、二分、贪心
- 排序算法：快速排序、归并排序、计数排序
- 搜索算法：回溯、递归、深度优先遍历，广度优先遍历，二叉搜索树等
- 图论：最短路径、最小生成树
- 动态规划：背包问题、最长子序列

**数据结构**

- 数组与链表：单 / 双向链表
- 栈与队列
- 哈希表
- 堆：最大堆 / 最小堆
- 树与图：最近公共祖先、并查集
- 字符串：前缀树（字典树）/ 后缀树

**操作系统**

- 内存管理
- 线程处理
- 文件系统
- 网络

---
### 4.3. 分类2

•考察数据结构，比如链表、栈、队列、哈希表、图、Trie、二叉树等

•考察基础算法，比如深度优先、广度优先、二分查找、递归等

•考察基本算法思想：递归、分治、回溯搜索、贪心、动态规划等

---
### 4.4. 难度分类3
- Easy：常规字符串操作、常规数组操作、简单数据结构。
- Medium：数组操作、滑动窗口、哈希表、二分、搜索（bfs、dfs）、常规DP、单调栈、二叉树相关、排序算法、前缀树、堆、并查集等
- Hard：DP（背包相关、概率DP、简单数论算法、数位DP、记忆化搜索）、简单图算法（最短路、最小生成树）、数据结构实现、字符串算法（后缀数组、回文相关）

----
### 4.5. 模式分类4
1. Pattern: Sliding window，滑动窗口模式
2. Pattern: two points, 双指针类型
3. Pattern: Fast & Slow pointers, 快慢指针类型
4. Pattern: Merge Intervals，区间合并模式
5. Pattern: Cyclic Sort，循环排序
6. Pattern: In-place Reversal of a LinkedList，原地链表翻转模式
7. Pattern: Tree Breadth First Search，树上的BFS模式
8. Pattern: Tree Depth First Search，树上的DFS模式
9. Pattern: Two Heaps，双堆类型
10. Pattern: Subsets，子集类型，一般都是使用多重DFS
11. Pattern: Modified Binary Search，改造过的二分
12. Pattern: Top ‘K’ Elements，前K个系列模式
13. Pattern: K-way merge，多路归并类型模式
14. Pattern: 0/1 Knapsack (Dynamic Programming)，0/1背包类型
    1.  0/1 Knapsack, 0/1背包
    2.  Unbounded Knapsack，无限背包
    3.  Fibonacci Numbers，斐波那契数列
    4.  Palindromic Subsequence，回文子系列
    5.  Longest Common Substring，最长子字符串系列
15. Pattern: Topological Sort (Graph)，拓扑排序模式
    

[Class1-Grokking the Coding Interview: Patterns for Coding Questions](https://www.educative.io/courses/grokking-the-coding-interview)

[Class2-Grokking Dynamic Programming Patterns for Coding Interviews](https://www.educative.io/courses/grokking-dynamic-programming-patterns-for-coding-interviews)

----
## 5. 数据结构

### 5.1. 存储方式

只有两种：**数组**（顺序存储）和**链表**（链式存储）。

「**队列**」、「**栈**」这两种数据结构既可以使用链表也可以使用数组实现。用数组实现，就要处理扩容缩容的问题；用链表实现，没有这个问题，但需要更多的内存空间存储节点指针。

「**图**」的两种表示方法，邻接表就是链表，邻接矩阵就是二维数组。邻接矩阵判断连通性迅速，并可以进行矩阵运算解决一些问题，但是如果图比较稀疏的话很耗费空间。邻接表比较节省空间，但是很多操作的效率上肯定比不过邻接矩阵。

「**散列表**」就是通过散列函数把键映射到一个大数组里。而且对于解决散列冲突的方法，拉链法需要链表特性，操作简单，但需要额外的空间存储指针；线性探查法就需要数组特性，以便连续寻址，不需要指针的存储空间，但操作稍微复杂些。

「**树**」，用数组实现就是「**堆**」，因为「堆」是一个完全二叉树，用数组存储不需要节点指针，操作也比较简单；用链表实现就是很常见的那种「树」，因为不一定是完全二叉树，所以不适合用数组存储。为此，在这种链表「树」结构之上，又衍生出各种巧妙的设计，比如二叉搜索树、AVL 树、红黑树、区间树、B 树等等，以应对不同的问题。

综上，数据结构种类很多，甚至你也可以发明自己的数据结构，但是底层存储无非数组或者链表，**二者的优缺点如下**：

**数组**由于是紧凑**连续**存储,可以随机访问，通过索引快速找到对应元素，而且相对节约存储空间。但正因为连续存储，内存空间必须一次性分配够，所以说数组如果要扩容，需要重新分配一块更大的空间，再把数据全部复制过去，时间复杂度 O(N)；而且你如果想在数组中间进行插入和删除，每次必须搬移后面的所有数据以保持连续，时间复杂度 O(N)。

**链表**因为元素不连续，而是靠指针指向下一个元素的位置，所以不存在数组的扩容问题；如果知道某一元素的前驱和后驱，操作指针即可删除该元素或者插入新元素，时间复杂度 O(1)。但是正因为存储空间不连续，你无法根据一个索引算出对应元素的地址，所以不能随机访问；而且由于每个元素必须存储指向前后元素位置的指针，会消耗相对更多的**储存空间**。



刷题，就是在锻炼你的眼力，看你能不能**看穿问题表象**揪出相应的解法框架。

比如说，让你求解一个迷宫，你要把这个问题层层抽象：迷宫 -> 图的遍历 -> N 叉树的遍历 -> 二叉树的遍历。然后让框架指导你写具体的解法。

---

### 5.2. 基本操作

对于任何数据结构，其基本操作无非遍历 + 访问，再具体一点就是：增删查改。

**数据结构种类很多，但它们存在的目的都是在不同的应用场景，尽可能高效地增删查改**。这也就是数据结构的使命。

如何遍历 + 访问？我们仍然从最高层来看，各种数据结构的遍历 + 访问无非两种形式：线性的和非线性的。

线性就是 for/while 迭代为代表，非线性就是递归为代表。再具体一步，无非以下几种框架：

数组遍历框架，典型的**线性**迭代结构：

```c++
void traverse(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
        // 迭代访问 arr[i]
    }
}
```

链表遍历框架，兼具**迭代**和**递归**结构：

```c++
/* 基本的单链表节点 */
class ListNode {
    int val;
    ListNode next;
}

void traverse(ListNode head) {
    for (ListNode p = head; p != null; p = p.next) {
        // 迭代访问 p.val
    }
}

void traverse(ListNode head) {
    // 递归访问 head.val
    traverse(head.next);
}
```

二叉树遍历框架，典型的**非线性递归**遍历结构：

```c++
/* 基本的二叉树节点 */
class TreeNode {
    int val;
    TreeNode left, right;
}

void traverse(TreeNode root) {
    traverse(root.left);
    traverse(root.right);
}
```

二叉树框架可以扩展为 N 叉树的遍历框架：

```c++
/* 基本的 N 叉树节点 */
class TreeNode {
    int val;
    TreeNode[] children;
}

void traverse(TreeNode root) {
    for (TreeNode child : root.children)
        traverse(child);
}
```

N 叉树的遍历又可以扩展为图的遍历，因为图就是好几 N 叉棵树的结合体。图可能出现环？这个很好办，用个布尔数组 visited 做标记就行了。

**所谓框架，就是套路。不管增删查改，这些代码都是永远无法脱离的结构，你可以把这个结构作为大纲，根据具体问题在框架上添加代码就行了，下面会具体举例**。

---

### 5.3. 刷题建议

**先刷二叉树，先刷二叉树，先刷二叉树**！**二叉树是最容易培养框架思维的，而且大部分算法技巧，本质上都是树的遍历问题**。

**只要涉及递归的问题，都是树的问题**。


数据结构的基本存储方式就是链式和顺序两种，基本操作就是增删查改，遍历方式无非迭代和递归。

刷算法题建议从「**树**」分类开始刷，结合框架思维，把这几十道题刷完，对于树结构的理解应该就到位了。这时候去看**回溯、动规、分治**等算法专题，对思路的理解可能会更加深刻一些。







---

## 6. Big O

目前分析算法主要从「**时间**」和「**空间**」两个维度来进行分析。时间维度顾名思义就是算法需要**消耗的时间**，「时间复杂度」是常用的分析单位。空间维度代表算法需要占用的**内存空间**，我们通常用「空间复杂度」来分析。

分析算法的效率主要从「**时间复杂度**」和「**空间复杂度**」来分析。这两个复杂度反映的是，随着问题量级的增大，时间和空间**增长的趋势**。很多时候我们两者不可兼得，有时候要用**时间换空间**，或者**空间换时间**。



---

### 6.1. 时间复杂度

`T(n)` 表示算法的**渐进时间复杂度**，`f(n)​` 表示代码**执行次数**，​`O()​` 表示**正比关系**。

```c++
for (int i = 1; i <= n; i++) {
    x++;
}

i <= n 	执行n+1次 最后还要再判断一次
i++		执行n次
x++;	执行n次
i = 1	执行1次
共3N+2次
```

`O(3N+2) = O(N)` 

关心的是**输入不断增长时程序的表现如何**，当N很大时，就是**最坏情况下的性能**，因此只需要**关注高阶项**，**忽略低阶项**。



```c++
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
    	x++;
    }
}
```

时间复杂度为 `O(N^2)​`



```c++
for (int i = 1; i <= n; i++) {
    x++;
}
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
    	x++;
    }
}
```

时间复杂度为 `O(N+N^2)=O(N^2)​`



---

### 6.2. 常用时间复杂度量级

横轴为问题的量级，纵轴为时间复杂度

![37b5a1516b172f9c8456d1574a0446b5.png](assets/37b5a1516b172f9c8456d1574a0446b5.png)



![Image result for time complexity chart](assets/big-o-running-time-complexity.png)

- **常数**阶O(1)
- **对数**阶O(logN)



- **线性**阶O(n)
- **线性对数/超线性**阶O(nlogN)



- 平方阶O(n²)
- 立方阶O(n³)
- **K次方/多项式**阶O(n^k)
- **指数**阶(2^n)
- **阶乘**O(n!)



上面的时间复杂从上到下复杂度越来越大，也意味着执行效率越来越低。

![1616323325038](assets/1616323325038.png)



---

#### 6.2.1. 常数阶O(1)

只要没有**循环**或**递归**等复杂逻辑，无论代码执行多少行，代码复杂度都为O(1)，如下：

```c++
int x = 0;
int y = 1;
int temp = x;
x = y;
y = temp;
```

上述代码在执行的时候，所消耗的**时间不会随着特定变量的增长而增长**，即使有几万行这样的代码，我们都可以用O(1)来表示它的时间复杂度。



#### 6.2.2. 线性阶O(n)

```c++
for (int i = 1; i <= n; i++) {
    x++;
}
```

在这段代码中，for循环会执行n遍，因此**计算消耗的时间是随着n的变化而变化**，因此这类代码都可以用O(n)来表示其时间复杂度。



#### 6.2.3. 对数阶O(logN)

```c++
int i = 1;
while(i < n) {
    i = i * 2;
}
```

在上面的循环中，每次 i 都会被乘以2，也意味着每次 i 都离 n 更进一步。那需要多少次循环 i 才能等于或大于 n 呢，也就是求解 $2 ^ k = n$，答案 $k=log_{2}N$ 。 取最高次项，且去掉最高此项的系数，所有进一步简化为 $k=logN$

也就是说循环 $k=logN$ 次之后，i 会大于等于n，这段代码就结束了。所以此代码的复杂度为：`O(logN)`。



#### 6.2.4. 线性对数阶O(nlogN)

线性对数阶O(nlogN)很好理解，也就是将复杂度为O(logN)的代码循环n遍：

```c++
for(int i = 0; i <= n: i++) {
    int x = 1;
    while(x < n) {
        x = x * 2;
    }
}
```

因为每次循环的复杂度为 `O(logN)`，所以 `n * logN = O(nlogN)`



#### 6.2.5. 平方阶O(n²)

```c++
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        x++;
    }
}

```

O(n²)的本质就是 `n * n`，如果我们将内层的循环次数改为m，复杂度就变为 `n * m = O(nm)`。

关于一些更高的阶级比如 `O(n³)` 或者 `O(n^k)`，我们可以参考 `O(n²)` 来理解即可，`O(n³)` 相当于三层循环，以此类推。



### 6.2.6. 指数阶O(2^n)

```c++
int f (int n) {
    if (n == 1) return 1;
    else return f(n-1) + f(n-1);
}
```

`O(2^N-1) = O(2^N)`

---



除了「大O表示法」还有其他「平均时间复杂度」、「均摊时间复杂度」、「最坏时间复杂度」、「最好时间复杂度」等等分析指数，但是最常用的依然是「大O表示法」，表示最差情况。



---

### 6.3. 空间复杂度

「空间复杂度」也不是用来计算程序具体占用的空间。随着问题量级的变大，程序需要分配的内存空间也可能会变得更多，而「空间复杂度」反映的则是**内存空间增长的趋势**。

比较常用的空间复杂度有：O(1)、O(n)、O(n²)。用 S(n) 来定义「空间复杂度」。



#### 6.3.1. O(1)空间复杂度

如果算法执行所需要的临时空间**不随着某个变量 n 的大小而变化**，此算法空间复杂度为一个**常量**，可表示为 O(1)：

```c++
int x = 0;
int y = 0;
x++;
y++;
```

其中x, y所分配的空间**不随着处理数据量变化**，因此「空间复杂度」为 O(1)



#### 6.3.2. O(n)空间复杂度

以下的代码给长度为n的数组赋值：

```c++
int[] newArray = new int[n];
for (int i = 0; i < n; i++) {
    newArray[i] = i;
}
```

在这段代码中，我们创建了一个长度为 n 的数组，然后在循环中为其中的元素赋值。因此，这段代码的「空间复杂度」**取决于 newArray 的长度**，也就是 n，所以 S(n) = O(n)。



如果newArray是个二维数组，则空间复杂度为O(n²)





![e85d4af103548c1f4d7729b6cf63607b.png](assets/e85d4af103548c1f4d7729b6cf63607b.png)

