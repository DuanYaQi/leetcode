# Leetcode

**教学**

[力扣加加 - lucifer](https://github.com/azl397985856/leetcode)

[labuladong 的算法小抄](https://github.com/labuladong/fucking-algorithm)

**题解+教学**

[李威威](https://liweiwei1419.gitee.io/leetcode-algo/)

**模板**

[负雪明烛模板](https://blog.csdn.net/fuxuemingzhu/article/details/101900729)

[AlgoWiki模板](https://ojeveryday.github.io/AlgoWiki/#/?id=algowiki)

**残酷**

[LeetCode打卡和竞赛微信群](https://wisdompeak.github.io/lc-score-board/rules.html)

做好Medium，没必要死扣Hard。LeetCode上很多Easy的题目看似简单，实则想要写出Perfect的代码并非易事。多思考如何优化Easy，Medium的解法实际上比花精力解Hard题更能提高自己。

```shell
git config --global http.proxy 127.0.0.1:1080
//然后开全局代理push
```

## Tree

|  题目  |知识点|技巧|
|  :----  |:----:|:----:|
|[94. Binary Tree Inorder Traversal](Tree/94+inorderTraversal.cpp) |中序 递归| 注意放private|
|[144. Binary Tree Inorder Traversal](Tree/144+preorderTraversal.cpp) |先序 递归| |
|[145. Binary Tree Postorder Traversal](Tree/145+postorderTraversal.cpp) |后序 递归| |
|[105. Construct Binary Tree from Preorder and Inorder Traversal](Tree/105+buildTree.cpp) | 先序 中序 递归|索引确定|
|[106. Construct Binary Tree from Inorder and Postorder Traversal](Tree/106+buildTree.cpp)   |中序 后序 递归 |索引确定|
|[114. Flatten Binary Tree to Linked List](Tree/144+preorderTraversal.cpp)   | 后序 递归 |注意指针连接|
|[116. Populating Next Right Pointers in Each Node](Tree/116+connect.cpp)   | 先序 递归|考虑到特殊情况即可|
|[222. Count Complete Tree Nodes](Tree/222+countNodes.cpp)  | 完全二叉树 | 利用其性质减少计算|
|[226. Invert Binary Tree](Tree/226+invertTree.cpp)   | 先序 递归 | 跟交换数字一样|
|[297. Serialize and Deserialize Binary Tree](Tree/297+serialize.cpp) | 序列化<br>反序列化 |  出入队列搜索树 <br>to_string()<br>stoi()字符转int |
|[652. Find Duplicate Subtrees](Tree/652+findDuplicateSubtrees.cpp) |后序 递归  | 巧用map<br>注意输出格式|
|[654. Maximum Binary Tree](Tree/654+constructMaximumBinaryTree.cpp) |前序 递归  |注意索引 注意返回值|
|   |  ||
|   |  ||

## 刷题顺序
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

## 算法与数据结构分类1

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
## 算法与数据结构分类2

•考察数据结构，比如链表、栈、队列、哈希表、图、Trie、二叉树等

•考察基础算法，比如深度优先、广度优先、二分查找、递归等

•考察基本算法思想：递归、分治、回溯搜索、贪心、动态规划等

---
## 算法与数据结构分类3
- Easy：常规字符串操作、常规数组操作、简单数据结构。
- Medium：数组操作、滑动窗口、哈希表、二分、搜索（bfs、dfs）、常规DP、单调栈、二叉树相关、排序算法、前缀树、堆、并查集等
- Hard：DP（背包相关、概率DP、简单数论算法、数位DP、记忆化搜索）、简单图算法（最短路、最小生成树）、数据结构实现、字符串算法（后缀数组、回文相关）


----
## 算法模式分类
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

## 数据结构

### 存储方式

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

-----

### 基本操作

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

### 刷题建议

**先刷二叉树，先刷二叉树，先刷二叉树**！**二叉树是最容易培养框架思维的，而且大部分算法技巧，本质上都是树的遍历问题**。

**只要涉及递归的问题，都是树的问题**。


数据结构的基本存储方式就是链式和顺序两种，基本操作就是增删查改，遍历方式无非迭代和递归。

刷算法题建议从「**树**」分类开始刷，结合框架思维，把这几十道题刷完，对于树结构的理解应该就到位了。这时候去看**回溯、动规、分治**等算法专题，对思路的理解可能会更加深刻一些。



---
## [C++标准模板库(STL)介绍](https://github.com/DuanYaQi/leetcode/blob/master/STL.md)



