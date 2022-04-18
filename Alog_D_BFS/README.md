# DFS/BFS

[树](DS_Tree/README.md) 中 **Sec 4.2 + Sec 4.3** 迭代遍历为 DFS，**Sec 4.4** 层序遍历为 BFS

[图](DS_Graph/README.md) 中 **图的遍历** 有 DFS/ BFS 详细概述





## 547. 省份数量

```c++
bool vis[205];

void dfs(vector<vector<int>>& isConnected, int u) {
    vis[u] = true;
    for (int i = 0; i < isConnected.size(); ++i) {
        if (isConnected[u][i] != 0 && vis[i] == false)
            dfs(isConnected, i);
    }
}

int findCircleNum(vector<vector<int>>& isConnected) {
    int res = 0;

    for (int i = 0; i < isConnected.size(); ++i) {
        vis[i] = false;
    }

    for (int i = 0; i < isConnected.size(); ++i) {
        if (vis[i] == false) {
            dfs(isConnected, i);
            res++;
        }
    }


    return res;
}
```



----

## 210. 课程表 II

本题是一道经典的「拓扑排序」问题。

给出一个包含 n 个节点的有向图 G，给出它的节点编号的一种排序，如果满足：

对于图 G 中的任意一条有向边 $(u, v)$，$u$ 在排列中都出现在 $v$ 的前面。

那么称该排列是图 G 的「拓扑排序」。



根据上述的定义，我们可以得出两个结论：

- 如果图 G 中存在环（即图 G 不是「有向无环图」），那么图 G 不存在拓扑排序。这是因为假设图中存在环 $x_1, x_2, \cdots, x_n$,，那么 $x_1$  在排列中必须出现在 $x_n$ 的前面，但 $x_n$ 同时也必须出现在 $x_1$ 的前面，因此不存在一个满足要求的排列，也就不存在拓扑排序；

- 如果图 G 是有向无环图，那么它的拓扑排序**可能不止一种**。举一个最极端的例子，如果图 G 值包含 n 个节点却没有任何边，那么任意一种编号的排列都可以作为拓扑排序。





有了上述的简单分析，我们就可以将本题建模成一个求拓扑排序的问题了：

- 我们将每一门课看成一个节点；

- **如果想要学习课程 A 之前必须完成课程 B**，那么**我们从 B 到 A 连接一条有向边**。这样一来，在拓扑排序中，B 一定出现在 A 的前面。



求出该图的拓扑排序，就可以得到一种符合要求的课程学习顺序。



BFS为什么不用特地判断是否有环：在任何时候（包括初始情况）环上的节点的入度都不会为0，所以这些节点永远不会被加入队列



### BFS

我们考虑拓扑排序中最前面的节点，该节点一定不会有任何入边，（也就是它没有任何的先修课程要求）。



当我们将一个节点加入答案中后，我们就可以移除它的所有出边，代表着它的相邻节点**少了一门先修课程的要求**。如果某个相邻节点变成了「**没有任何入边的节点**」，那么就代表着这门课可以开始学习了

按照这样的流程，我们不断地将没有入边的节点加入答案，直到答案中包含所有的节点（得到了一种拓扑排序）或者不存在没有入边的节点（图中包含环）。



开始时，所有入度为 0 的节点（意味着零基础可以直接修的课）都被放入队列中，它们就是可以作为拓扑排序最前面的节点，并且它们之间的相对顺序是无关紧要的。



在广度优先搜索的每一步中，我们取出队首的节点 u：

- 我们将 u 放入答案中；
- 我们移除 u 的所有出边，也就是将 u 的所有相邻节点的入度减少 1。如果某个相邻节点 v 的入度变为 0，那么我们就将 v 放入队列中。



![img](assets/fig1.png)



![0210.gif](assets/ca22fa351d5278e95c4c8c94aba6da42ae45d465ff3e8e82149777274293e194-0210.gif)

在广度优先搜索的过程结束后。如果答案中包含了这 n 个节点，那么我们就找到了一种拓扑排序，否则说明图中存在环，也就不存在拓扑排序了。

```c++
class Solution {
private:
    // 存储有向图
    vector<vector<int>> edges;
    // 存储每个节点的入度
    vector<int> indeg;
    // 存储答案
    vector<int> result;

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);	// 注意这里
            ++indeg[info[0]];
        }

        queue<int> q;
        // 将所有入度为 0 的节点放入队列中
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            // 从队首取出一个节点
            int u = q.front(); q.pop();
            // 放入答案中
            result.push_back(u);
            for (int v: edges[u]) {
                --indeg[v];
                // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
                if (indeg[v] == 0) q.push(v);
            }
        }

        if (result.size() != numCourses) return {};

        return result;
    }
};
```







---

## 207. 课程表

经典的「拓扑排序」问题。

看课程表 II





---

## 630. 课程表 III











---

## 1462. 课程表 IV



## 

1. 构建一个图表示从i到j是否可达，默认为false
2. 构建方式
   - prerequisites来直接构建
   - 基于中间k点即Flyod方式来判断是否可达





floyed 算法
判断从 i 到 j 是否有路径。
判断从 i 途径 mid 到 j 是否有路径。

```c++
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // 先修课程，grpah[i][j] = 1 表示 i 是 j 的先修课程
        bool graph[numCourses][numCourses];
        memset(graph, 0, sizeof(bool)*numCourses*numCourses);
		
         // 构建图
        for (const auto &data : prerequisites) {
            graph[data[0]][data[1]] = true;
        }
	
        
        // Floyd算法的本质是DP，而k是DP的阶段，因此要写最外面
        for (int k = 0; k < numCourses; ++k) {
            for (int i = 0; i < numCourses; ++i) {
                for (int j = 0; j < numCourses; ++j) {
                    // i 是 k 的先导课程，k 是 j 的先导课程
                    if (graph[i][k] && graph[k][j]) {
                        graph[i][j] = true;
                    }
                }
            }
        }
       
        // 遍历quries直接从graph得到结果
        vector<bool> res;
        for (const auto &q : queries) {
            if (graph[q[0]][q[1]]) res.push_back(true);
            else res.push_back(false);
        }

        return res;
    }

     
};

```



```c++
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        int n = numCourses;
        vector<vector<int>> graph(n);

        for (auto &pre : prerequisites) {
            graph[pre[0]].push_back(pre[1]);
        }

        vector<vector<bool>> isReached(n, vector<bool>(n));
        for (int i = 0; i < n; i++) {
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto &v : graph[u]) {
                    if (!isReached[i][v]) { /* 从课程i到达的其他课程进行标记 */
                        isReached[i][v] = true;
                        q.push(v);
                    }
                }
            }
        }

        vector<bool> ans;
        for (auto &query : queries) {
            ans.push_back(isReached[query[0]][query[1]]);
        }
        return ans;
    }
};
```



```c++
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
		edges.resize(numCourses);
        indeg.resize(numCourses);
        pre.resize(numCourses);
        
        for(auto &v:prerequisites){
            int v1=v[0],v2=v[1];
            edges[v1].push_back(v2);
            indeg[v2]++;
        }

        queue<int> q;
        for(int i=0;i<numCourses;i++){
            if(degree[i]==0)
                q.push(i);
        }
        while(!q.empty()){
            int course=q.front();
            q.pop();
            for(auto next:edge[course]){
                degree[next]--;
                pre[next].insert(pre[course].begin(),pre[course].end());
                pre[next].insert(course);
                if(degree[next]==0)
                    q.push(next);
            }
        }
        vector<bool>res;
       
        for(auto q:queries){
            if(pre[q[1]].find(q[0])!=pre[q[1]].end())
                res.push_back(true);
            else
                res.push_back(false);
        }
        return res;
    }
    
private:
    vector<vector<int>> edge;
    vector<int> degree;
    vector<set<int>> pre;
};
```







---

## LCP 52. 二叉搜索树染色

其实和二叉搜索树一点关系都没有。

每个点的颜色只取决于最后一次包含该点的操作。用 set 维护所有颜色待确定的点，倒序处理询问，每次利用 lower_bound 方法从 set 中取出所有在询问范围内的点染色后删掉。因为每个点只会被删掉一次，所以总体复杂度 $\mathcal{O}((n + q)\log n)$，其中 n 是节点数量，q 是询问数量。



**ERROR**

```c++
int getNumber(TreeNode* root, vector<vector<int>>& ops) {
    dfs(root);

    int cnt = 0;

    for (int i = ops.size() - 1; i >= 0; --i)  {   //1e5 倒着来
        if (!st.size()) break;

        for (int j = ops[i][1]; j <= ops[i][2]; ++j) {
            if (!st.count(j)) continue;
            st.erase(j);
            if (ops[i][0]) cnt++;
        }

    }

    return cnt;
}
```





```c++
set<int> st;

/*把所有节点放入set中，BST中序得到有序数组，不过无所谓，set就是有序的*/
void dfs(TreeNode* node) {  
    if (node == nullptr) return;
    dfs(node->left);
    st.insert(node->val);
    dfs(node->right);
}

int getNumber(TreeNode* root, vector<vector<int>>& ops) {
    dfs(root);

    int cnt = 0;

    for (int i = ops.size() - 1; i >= 0; --i)  {   //1e5 倒着来
        if (!st.size()) break;	// 剪枝:set为空说明全染好了，直接break即可
		
        // lower_bound 寻找在数组或容器范围内第一个值大于等于val元素的位置
        while (true) {
            // ops[i][1] = start
            // ops[i][2] = end
            // 值必须在 ops[i][1]~ops[i][2] 左闭右闭之间才能染色并从 set 中删除
            auto it = st.lower_bound(ops[i][1]);	// 找第一个值大于等于start元素的位置
            if (it == st.end()) break;				// 剪枝：如果没有大于等于start的值,即所有值都小于start,不在染色区间, *(it++)>=(*it) 没必要在while中退出
            if (*it > ops[i][2]) break;				// 剪枝：如果该值比end还大,不在染色区间，*(it++)>=(*it) 没必要在while中退出
            st.erase(*it);	// 删除这个元素 这个元素值必在  之间 
            if (ops[i][0]) cnt++;
        }

    }

    return cnt;
}
```





```c++
class Solution {
    set<int> st;

    void dfs(TreeNode *node) {
        if (node == nullptr) return;
        st.insert(node->val);
        dfs(node->left);
        dfs(node->right);
    }

public:
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        dfs(root);
        int ans = 0;
        for (int i = (int) ops.size() - 1; i >= 0; i--) {
            while (true) {
                auto it = st.lower_bound(ops[i][1]);
                if (it == st.end() || (*it) > ops[i][2]) break;
                st.erase(it);
                if (ops[i][0]) ans++;
            }
        }
        return ans;
    }
};
```





---

# 322. 零钱兑换-BFS

该问题可建模为以下优化问题：

$$
\min_{x} \sum_{i=0}^{n - 1} x_i \ \text{subject to} \sum_{i=0}^{n - 1} x_i \times c_i = S
$$
其中，S 是总金额，$c_i$  是第 i 枚硬币的面值，$x_i$ 是面值为 $c_i$ 的硬币数量，由于 $x_i \times c_i$ 不能超过总金额 S，可以得出 $x_i$ 最多不会超过 $\frac{S}{c_i}$ ，所以 $x_i$ 的取值范围为 $[{0, \frac{S}{c_i}}]$. 一个简单的解决方案是通过回溯的方法枚举每个硬币数量子集 $[x_0\dots\ x_{n - 1}]$ ，针对给定的子集计算它们组成的金额数，如果金额数为 S，则记录返回合法硬币总数的最小值，反之返回 -1。

该做法的时间复杂度为 $O(S^n)$，会超出时间限制，因此必须加以优化。



## 方法一：记忆化搜索

利用动态规划，可以在多项式的时间范围内求解。首先，定义：

- $F(S)$：组成金额 S 所需的最少硬币数量
- $[c_0\dots c_{n-1}]$：可选的 n 枚硬币面额值

这个问题有一个最优子结构的性质。

假设我们知道 $F(S)$，即组成金额 S 最少的硬币数，最后一枚硬币的面值是 C。转移方程为
$$
F(S) = F(S-C) +1
$$
由于不确定最后一枚硬币面值是什么，所以需要枚举每个硬币面额值 $c_0, c_1, c_2 \ldots c_{n -1}$ 并选择其中的最小值。
$$
F(S)=\min _{i=0 . . n-1} F\left(S-c_{i}\right)+1  \ \ \ \text{subject to} \ \ \ S-c_{i} \geq 0 \\

\begin{array}{c}
F(S)=0, \text { when } S=0 \\
F(S)=-1, \text { when } n=0
\end{array}
$$


![img](assets/e0fd2252775b89649ceb6e867ff0e546ec77621edb566693482c8588a98066b8-file_1583404923188.jpeg)

在上面的递归树中，我们可以看到许多子问题被多次计算。例如，$F(1)$ 被计算了13次。为了避免重复计算，我们要将子问题的答案存在一个数组中进行记忆化。保证每个子问题最多只被计算一次。

```c++
class Solution {
    vector<int>count;
    int dp(vector<int>& coins, int rem) {
        if (rem < 0) return -1;
        if (rem == 0) return 0;
        if (count[rem - 1] != 0) return count[rem - 1];
        int Min = INT_MAX;
        for (int coin:coins) {
            int res = dp(coins, rem - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[rem - 1] = Min == INT_MAX ? -1 : Min;
        return count[rem - 1];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1) return 0;
        count.resize(amount);
        return dp(coins, amount);
    }
};
```



复杂度分析

**时间复杂度**：$O(Sn)$，其中 S 是金额，n 是面额数。我们一共需要计算 S 个状态的答案，且每个状态 F(S) 由于上面的记忆化的措施只计算了一次，而计算一个状态的答案需要枚举 n 个面额值，所以一共需要 O(Sn) 的时间复杂度。

**空间复杂度**：$O(S)$，我们需要额外开一个长为 S 的数组来存储计算出来的答案 F(S) 。























