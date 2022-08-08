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

### DFS

判环

1.借助一个标志列表 `flags`，用于判断每个节点 `i` （课程）的状态：

- 未被 DFS 访问：`i == 0`
- 已被其他节点启动的 DFS 访问：`i == 2`
- 已被当前节点启动的 DFS 访问：`i == 1`

2.对 `numCourse` 个节点依次执行 DFS，判断每个节点起步 DFS 是否存在环，若存在环直接返回 False。DFS 流程：

- 终止条件：
  - 当 `flag[i] == 2`，说明当前访问节点已被其他节点启动的 DFS 访问，无需再重复搜索，直接返回 True
  - 当 `flag[i] == 1`，说明在本轮 DFS 搜索中节点 `i` 被第 2 次访问，即**课程安排图有环**，直接返回 False

- 将当前访问节点 `i` 对应 `flag[i]` 置 1，即标记其本轮 DFS 访问过
- 递归访问当前节点 `i` 的所有邻接节点 `j`，当发现环直接返回 False
- 当前节点所有邻接节点已被遍历，并没有发现环，将当前节点 `flag` 置为 -1 并返回 True

3.若整个图 DFS 结束并未发现环，返回 True



```c++
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited; 
    bool gValid = true;    

public:
    void dfs(int u) {
        visited[u] = 1;

        for (auto &v : edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!gValid) return;
            } else if (visited[v] == 1) {
                gValid = false;
                return;
            }
        }
        visited[u] = 2;
    }


    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);

        for (auto &p : prerequisites) {
            edges[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses && gValid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        return gValid;
    }    
};
```





```c++
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> isVisit; 
    bool gValid = true;    

public:
    bool dfs(int u) {
        if (isVisit[u] == 1) return false;
        if (isVisit[u] == 2) return true;

        isVisit[u] = 1;
        for (auto v : edges[u]) {
            if (!dfs(v)) return false;
        }
        isVisit[u] = 2;

        return true;
    }


    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        isVisit.resize(numCourses);

        for (auto &p : prerequisites) {
            edges[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses; ++i) {
            if (!dfs(i)) {
                return false;
            }
        }

        return true;
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



----

## 565. 数组嵌套-DFS

```c++
class Solution {
public:

    void dfs(vector<int> &nums, int n, int &cnt, vector<bool> &isVis) {
        if (isVis[n]) return;

        isVis[n] = true;

        cnt++;
        dfs(nums, nums[n], cnt, isVis);

        return;
    }

    int arrayNesting(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            int cnt = 0;
            vector<bool> isVis(nums.size(), 0);
            dfs(nums, nums[i], cnt, isVis);
            mLongest = max(mLongest, cnt);
        }
        
        return mLongest;
    }

private:
    int mLongest = -1;    
};
```

超时





---

## 761. 特殊的二进制序列

对于本题而言，将 1 看成左括号 '(', 0 看成右括号 ')'，那么一个特殊的**二进制序列**就可以看成一个**合法的括号序列**。这种「映射」有助于理解题目中的操作，即交换两个相邻且非空的合法括号序列。但为了与题目保持一致，下面的部分仍然使用 1/0 进行叙述。

**思路与算法**

对于一个特殊序列而言，它**一定以 1 开始，以 0 结束**。这是因为：

- 长度为 1 的前缀中 1 的数量一定要大于等于 0 的数量，所以首位一定是 1；
- 由于 0 和 1 的数量相等，并且任意前缀中 1 的数量一定大于等于 0 的数量，那么任意后缀中 0 的数量一定大于等于 1 的数量，因此与上一条类似，末位一定是 0。

如果给定的字符串是一个「整体」的特殊序列，也就是说，**它无法完整地拆分成多个特殊序列**，那么它的首位 1 和末位 0 是不可能在任何交换操作中出现的。这里给出首位 1 的证明，末位 0 的证明是类似的：

> 如果首位 1 可以在交换操作中出现，那么包含它的子串是给定字符串（特殊序列）的一个前缀，同时这个子串也是一个特殊序列。对于字符串中剩余的**后缀部分**，**0 和 1 的数量一定相等**（因为给定字符串和前缀子串的 0 和 1 数量均相等）并且满足「每一个前缀中 1 的数量大于等于 0 的数量」（因为后缀部分的每一个前缀可以映射为给定字符串在同一位置结束的前缀，再扣掉前缀子串，由于前缀子串中 0 和 1 的数量相等，因此扣除后仍然满足要求），那么后缀部分也是一个特殊序列，这就说明给定字符串可以拆分成两个特殊序列，与假设相矛盾。
>
> 因此，我们可以把首位 1 和末位 0 直接移除，进一步考虑剩余的字符串。

如果给定的字符串可以拆分成多个特殊序列（这里规定每一个拆分出来的特殊序列都是一个「整体」，不能继续进行拆分），那么我们可以「分别」进一步考虑每一个特殊序列，即把某个特殊序列的首位 1 和末位 0 移除后，递归地进行相同的拆分操作。

在递归返回后，我们可以进行「合并」操作：将所有的特殊序列按照字典序进行降序排序，再拼接起来，就可以得到字典序最大的字符串。由于每一次我们可以交换两个相邻的特殊序列，因此按照冒泡排序的方法，我们可以将这些特殊序列任意进行的排列，也就一定能得到字典序最大的字符串。

细节

在编写代码时，我们可以使用一个计数器，并从头遍历给定的字符串。当我们遇到 1 时计数器加 1，遇到 0 时计数器减 1。当计数器为 0 时，我们就拆分除了一个「整体」的特殊序列。

当递归到的字符串长度小于等于 2 时，说明字符串要么为空，要么为 10，此时字符串就是字典序最大的结果，可以直接返回。







![image.png](assets/1659950222-oqdeGi-image.png)

如图，由题意知这个串只有 01，我们用坐标来表示。如果 `s[i] = 1`, 向斜上走，否则 `s[i] = 0`,  向斜下走。这样高度相同的区间就是一个特殊子串。

**我们用高度 `h=0` 将原字符串分割成一系列的特殊子串**，并称其为一个**山峰**。那么我们直接**对这些山峰排序就行了**。

但是呢，一个**山峰会有一些子峰**，如上图，**这些个子峰也是特殊子串**，子峰在山峰上不一定是高度降序的，子峰上还可能有子子峰，因此我们需要递归处理山峰，直到山峰变为最小（最小特殊子串10）。我们将**子峰降序排序**，保证字典序最大。最后**重组起来**，形成新的山峰。

这样一来，最后回到 `h=0` 分割出的山峰，这些山峰都已被新的替代，降序排序，然后累加起来，就是字典序最大的



```c++
class Solution {
public:
    string dfs(string &str)  //str为一个新的山峰
    {
        if(str=="10") return str;  //最小特殊串，直接返回
        vector<string>m;
        int n=str.size(),h=0,f=0,l=0;
        for(int i=0;i<n;i++)  //找出str中所有特殊子串，也就是[l,i]之间的串
        {
            if(str[i]&1) h++;  //'1': 高度加1
            else{// '0': 高度减1
                f=1; h--;  // f用来标记h=1是上升的，还是下降的，这里h--了，说明已经开始下降了
            }
            if(h==1){ //出现特殊子串
                if(!f) l=i+1; //上升时h=1,标记左端点
                else{// 下降时h=1,标记右端点
                   m.push_back(str.substr(l,i-l+1));  //特殊子串
                   l=i+1; f=0;  //更新左端点和标志位
                }
            }
        }
        for(string& s:m) s=dfs(s);  //对于每个特殊子串为一个新山峰，继续处理，处理指的是找特殊子串，排序
        //将str的每个特殊子串排序，保证大的在前边，字典序就会更大
        sort(m.begin(),m.end(),[](string& s1,string& s2){
            return s1>s2;
        });
        // 排序后，将str的特殊子串重组一下，形成新的str返回
        // 除特殊子串外，开始和结尾都会剩一个字符，分别是'1'和'0', 我们加上就行了
        string ans; ans+=str[0];
        for(string &s:m) ans+=s;
        ans+=str[str.size()-1];   
        return ans;
    }
    
    string makeLargestSpecial(string s) {
        int h=0,n=s.size(),l=0;
        vector<string>m;
        for(int i=0;i<n;i++)  //分割出每个山峰，h=0为分界点
        {
            if(s[i]&1) h++; //高度+1
            else h--;  //高度-1
            if(h==0){  //分界点
                m.push_back(s.substr(l,i-l+1));  //一个山峰，特殊子串
                l=i+1;  //更新左端点
            }
        }
        //对于每个山峰（特殊子串）的子峰排序重组，高度大的在前边，保证字典序最大
        for(string& str:m) str=dfs(str);
        //每个特殊子串已经是字典序最大，对其排序，相加后得到的结果就是字典序最大排列
        sort(m.begin(),m.end(),[](string& s1,string& s2){
            return s1>s2;
        });
        string ans;
        for(string& str:m) ans+=str;
        return ans;
    }
};
//小结论：
//1. 任何一个1后边都会有特殊子串
//2. 任何特殊子串都是以1开始的
//3. 交换后还是特殊的
```







---

# BFS

## 1306. 跳跃游戏 III

刚开始的错误写法，属于想多了，从尾往前，但其实正向bfs好一点

```c++
bool bfs(vector<int>& arr, int start, int zeroIdx) {
    int n = arr.size();
    queue<int> q;         // 存下标
    q.push(zeroIdx);

    bool vis[n+1]; memset(vis, false, sizeof vis);

    while (!q.empty()) {
        int p = q.front(); q.pop();

        if (vis[p]) continue;
        vis[p] = true;

        if (p == start) {
            return true;
        }

        for (int i = 0; i < n; ++i) {
            if (i + arr[i] == p || i - arr[i] == p)
                q.push(i);
        }
    }

    return false;
}

bool canReach(vector<int>& arr, int start) {
    int n = arr.size();
    int zeroIdx = find(arr.begin(), arr.end(), 0) - arr.begin();

    unordered_set<int> st;

    for (int i = 0; i < n; ++i) {
        if (arr[i] == 0)
            st.insert(i);
    }

    for (auto &idx : st)
        if (bfs(arr, start, idx))
            return true;

    return false;
}
```





```c++
bool canReach(vector<int>& arr, int start) {
    int n = arr.size();

    queue<int> q;
    q.push(start);

    bool vis[n+1]; memset(vis, false, sizeof vis);

    while (!q.empty()) {
        int idx = q.front(); q.pop();

        if (arr[idx] == 0) 
            return true;

        if (vis[idx]) continue;
        vis[idx] = true;

        if (idx + arr[idx] < n) q.push(idx + arr[idx]);
        if (idx - arr[idx] >= 0) q.push(idx - arr[idx]);           
    }

    return false;
}
```





---

## 1345. 跳跃游戏 IV

抽象成**无向图**，然后起点为0，终点为n，找到起点到终点的最短路径

然后每个点跟其相同值的点互通，每个点跟它前后点互通 **无向无权图**

暴力 bfs 遍历所有点所有边，$O(N^2)$ 





优化对于等值顶点构成的子图，其实在**遍历其中一个顶点时**，**就将整个子图访问一次**，**之后清空整个子图**，从而**避免重复访问该子图**



解题步骤：

- 使用map 保存图的顶点和边，即 key 为元素的值，value 记录的是索引
- 首个顶点入队，开始 BFS 搜索，当搜索到某个顶点时，将其连接的其它顶点入队
- 搜索中，分为三种情况
  - 向前跳 `if (idx + 1 < n)`
  - 向后跳 `if (idx - 1 >= 0)`
  - 等值跳 `for (auto &sameValueIdx : ump[arr[idx]])`

- 为了避免重复访问顶点，标记每个顶点是否访问过，访问过就不入队， `if (vis[idx]) continue;`
- 避免重复访问子图，需要将第一次添加等值子图入队之后，将该元素从map中删除，后续搜索不会在将该子图加入队列。 `ump.erase(arr[idx]);`
- 队列中放 pair，分别表示当前索引和步数 `queue<pii> q;    // 存 idx 和 step`



![image-20220122183526461](assets/1642848377-fiRFrc-file_1642848381648.png)



```c++
typedef pair<int, int> pii;

int minJumps(vector<int>& arr) {
    int n = arr.size();

    // 保存相同值
    unordered_map<int, vector<int>> ump;

    for (int i = 0; i < n; ++i)
        ump[arr[i]].push_back(i);

    bool vis[n]; memset(vis, false, sizeof vis); // 不加vis数组会超时,每个结点访问一次进行一次计算即可

    queue<pii> q;    // pair 存 idx 和 step
    q.emplace(0, 0);

    int step = 0;
    while (q.size()) {
        auto [idx, step] = q.front(); q.pop();

        if (idx == n-1) return step;    // 搜到末尾，输出结果

        if (vis[idx]) continue;
        vis[idx] = true;

        int v = arr[idx];
        step++;

        // 处理 idx-1 的情况
        if (idx + 1 < n) q.emplace(idx+1, step);

        // 处理 idx+1 的情况
        if (idx - 1 >= 0) q.emplace(idx-1, step);

        // 处理值相等的情况
        for (auto &sameValueIdx : ump[arr[idx]]) {
            q.emplace(sameValueIdx, step);
        }

        ump.erase(arr[idx]);        // 用一次就删除，因为相同的值入一次队就可以了，不删会超时
    }

    return -1;
}
```



----

## 💗691. 贴纸拼词

```c++
class charmap {
public:
    int nums[26] = {0};
    int& operator[](char c) {
        return nums[c - 'a'];
    }
    int& data(int i) {
        return nums[i];
    }
};


int minStickers(vector<string>& stickers, string target) {
    int m = target.size(), n = stickers.size(), s0 = (1 << m) - 1, ans = 0;

    //cout << s0;

    queue<int> q;
    unordered_set<int> uset;
    q.push(0);//000000
    uset.insert(0);

    while (q.size()) {
        int qn = q.size();
        ans++;

        for (int k = 0; k < qn; ++k) {  // 遍历此层
            int s1 = q.front(); q.pop();
            for (string s : stickers) { // 遍历每个可选字符串
                int s2 = s1;
                charmap cnt;
                for (char c : s) {
                    cnt[c]++;
                }

                for (int i = 0; i < m; ++i) {   // 遍历可选字符串
                    char cN = target[i];
                    if ((s2 >> i & 1) == 0 && cnt[cN] > 0) {    // 如果这个位置状态为0, 并且可选字符串里可以提供这一处的单词
                        cnt[cN]--;          // 字母表此位置记录数量减
                        s2 |= 1 << i;       // s2 的这个为0的位置变1
                    }
                }

                if (s2 == s0) return ans;   // 如果它变成全1了 直接返回ans答案
                if (s2 > s1 && uset.count(s2) == 0) {   // s2 > s1 表示选了这个字符串是有进展的，即更新了位数，uset防止此状态重复入队
                    q.push(s2);
                    uset.insert(s2);
                }
            }
        }
    }

    return -1;
}
```





----

# 双向 BFS

**必须知道起点和终点才可以用**

双向BFS主要是用来解决单向BFS中搜索空间爆炸的问题，即从开头和结尾一起开始搜索，**当搜索到相同的值时**，意味着**找到了一条联通起点和终点的最短路径**



解题步骤：

- 为了从两个方向搜索，需要创建两个队列





---

## 1345. 跳跃游戏 IV

抽象成**无向图**，然后起点为0，终点为n，找到起点到终点的最短路径

然后每个点跟其相同值的点互通，每个点跟它前后点互通 **无向无权图**

暴力 bfs 遍历所有点所有边，$O(N^2)$ 





优化对于等值顶点构成的子图，其实在**遍历其中一个顶点时**，**就将整个子图访问一次**，**之后清空整个子图**，从而**避免重复访问该子图**



解题步骤：

- 使用map 保存图的顶点和边，即 key 为元素的值，value 记录的是索引
- 首个顶点入队，开始 BFS 搜索，当搜索到某个顶点时，将其连接的其它顶点入队
- 搜索中，分为三种情况
  - 向前跳 `if (idx + 1 < n)`
  - 向后跳 `if (idx - 1 >= 0)`
  - 等值跳 `for (auto &sameValueIdx : ump[arr[idx]])`

- 为了避免重复访问顶点，标记每个顶点是否访问过，访问过就不入队， `if (vis[idx]) continue;`
- 避免重复访问子图，需要将第一次添加等值子图入队之后，将该元素从map中删除，后续搜索不会在将该子图加入队列。 `ump.erase(arr[idx]);`
- 队列中放 pair，分别表示当前索引和步数 `queue<pii> q;    // 存 idx 和 step`







---

## 749. 隔离病毒



---

### 多重BFS（不是多源!!）

**大致思路**

不断重复下面循环，直到没有待隔离的病毒为止

- 广搜确定不同区域的：待感染区域的面积、隔离此区域所需要的隔离墙的数量
- 隔离这个病毒区



**具体实现**
用不同的数字代表地图中不同的状态：

```
0: 空地
1: 活的病毒
2: 被控制的病毒
```


然后一个死循环，**每次控制一个病毒区域**。如果已经没有活病毒了，就退出循环。

```c++
while (true) {
    bool has1 = false;
    
	// 这里进行病毒隔离操作，同时如果还有活病毒(1)，就把has1标记为true

    if (!has1)
        break;
}
```


至于控制活病毒的部分，需要几个变量：

```c++
int max1adjacent = 0;  // 活病毒的最大相邻待感染区域的大小
map<int, pair<int, int>> area2loc;  // [<待感染区域的面积, 其中一个活病毒的坐标>]
map<pair<int, int>, int> loc2wallNum;  // [<活病毒的坐标, 需要添加的墙的数量>]  //这里选一个idx最小的病毒队长的坐标就可以，因为病毒间是连通的
vector<vector<bool>> visited(n, vector<bool>(m, false));  // 哪个区域被遍历过了
```

这样就可以在遍历完成之时，立刻得到这次要控制的位置，以及这次控制需要安装多少隔离墙。遍历的方法为：

```c++
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        if (isInfected[i][j] == 1 && !visited[i][j]) {  // 这是一个活病毒的位置 && 这个区域还没有被遍历过
            has1 = true;
            visited[i][j] = true;
            pair<int, int> oneOfThisArea = {i, j};
            int thisAdjacent = 0;  // 这个待感染区域的大小
            int thisWallNum = 0;  // 控制这个区域的话，需要安装隔离墙的数量
            set<pair<int, int>> counted;  // 已经统计过的待感染区域  // 注意不能通过将visited标记为true的方式来判断某个待感染区域是否被统计过，因为待感染区域对于不同的病毒块互不影响
			
			// 这里进行BFS，同时记录这片区域的待感染区域的大小、需要安装隔离墙的数量

            max1adjacent = max(max1adjacent, thisAdjacent);
            area2loc[thisAdjacent] = oneOfThisArea;
            loc2wallNum[oneOfThisArea] = thisWallNum;
        }
    }
}
```

具体BFS方法为：

```c++
queue<pair<int, int>> q;
q.push({i, j});
while (q.size()) {
    auto[x, y] = q.front();
    q.pop();
    for (int d = 0; d < 4; d++) {
        int tx = x + direction[d][0];
        int ty = y + direction[d][1];
        if (tx >= 0 && tx < n && ty > 0 && ty < m) {  // 下一个单元在合法范围内
            if (isInfected[tx][ty] == 1 && !visited[tx][ty]) {  // 下一个单元是未被标记的病毒
                visited[tx][ty] = true;
                q.push({tx, ty});
            }
            else if (isInfected[tx][ty] == 0) {  // 下一个单元格是待感染区域
                thisWallNum++;  // 不论这个待感染区域是否被统计过，都要安装隔离墙（区域只统计一次，但隔离墙最多要安装4面）
                if (!visited[tx][ty]) {  // 这个区域还未被统计过
                    visited[tx][ty] = true;
                    thisAdjacent++;      // 待感染区域的大小面积+1
                }                                        
            }
        }
    }
}
```

这样，遍历完成后，我们就知道了最大的待感染面积 及其 对应的感染区域的某个病毒的位置，然后就把它们标记为2（隔离过了）

```c++
if (!max1adjacent) {  // 待感染区域面积为0，说明没有活病毒了或者全部被病毒感染了（其实似乎不用has1
变量即可）
    break;
}

pair<int, int> oneOfThisArea = area2loc[max1adjacent];
ans += loc2wallNum[oneOfThisArea];

// 再次BFS标记此区域病毒为已隔离
// 其他区域扩散
```

具体BFS方法为：

```C++
queue<pair<int, int>> q;
q.push(oneOfThisArea);
isInfected[oneOfThisArea.first][oneOfThisArea.second] = 2;
while (q.size()) {
    auto[x, y] = q.front();
    q.pop();
    for (int d = 0; d < 4; d++) {
        int tx = x + direction[d][0];
        int ty = y + direction[d][1];
        if (tx >= 0 && tx < n && ty > 0 && ty < m) {
            if (isInfected[tx][ty] == 1) {
                isInfected[tx][ty] = 2;
                q.push({tx, ty});
            }
        }
    }
}
```


其他区域扩散的具体实现为：

```c++
visited = vector<vector<bool>>(n, vector<bool>(m, false));
for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
        if (isInfected[x][y] == 1 && !visited[x][y]) {
            visited[x][y] = true;
            for (int d = 0; d < 4; d++) {
                int tx = x + direction[d][0];
                int ty = y + direction[d][1];
                if (tx >= 0 && tx < n && ty >= 0 && ty < m) {
                    if (isInfected[tx][ty] == 0) {  // 空地
                        isInfected[tx][ty] = 1;  // 被病毒感染
                        visited[tx][ty] = true;  // 防止继续感染拓展
                    }
                }
            }
        }
    }
}
```

- 时间复杂度O(mn)
- 空间复杂度O(mn)
  
  
  

```c++
/*
    0: 空地
    1: 活の病毒
    2: 被控制の病毒
*/
const int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
private:
    int ans = 0; // 存答案
public:
    int containVirus(vector<vector<int>>& isInfected) {
        int n = isInfected.size();
        int m = isInfected[0].size();
        while (true) {
            bool has1 = false;

            int max1adjacent = 0;  // 活病毒的最大相邻待感染区域的大小
            map<int, pair<int, int>> area2loc;  // [<待感染区域的面积, 其中一个活病毒的坐标>]
            map<pair<int, int>, int> loc2wallNum;  // [<活病毒的坐标, 需要添加的墙的数量>]
            vector<vector<bool>> visited(n, vector<bool>(m, false));  // 哪个区域被遍历过了
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (isInfected[i][j] == 1 && !visited[i][j]) {  // 这是一个活病毒的位置 && 这个区域还没有被遍历过
                        has1 = true;
                        visited[i][j] = true;
                        pair<int, int> oneOfThisArea = {i, j};
                        int thisAdjacent = 0;  // 这个待感染区域的大小
                        int thisWallNum = 0;  // 控制这个区域的话，需要安装隔离墙的数量
                        set<pair<int, int>> counted;  // 已经统计过的待感染区域  // 注意不能通过将visited标记为true的方式来判断某个待感染区域是否被统计过，因为待感染区域对于不同的病毒块互不影响

                        queue<pair<int, int>> q;
                        q.push({i, j});
                        while (q.size()) {
                            auto[x, y] = q.front();
                            q.pop();
                            for (int d = 0; d < 4; d++) {
                                int tx = x + direction[d][0];
                                int ty = y + direction[d][1];
                                if (tx >= 0 && tx < n && ty >= 0 && ty < m) {  // 下一个单元在合法范围内
                                    if (isInfected[tx][ty] == 1 && !visited[tx][ty]) {  // 下一个单元是未被标记的病毒
                                        visited[tx][ty] = true;
                                        q.push({tx, ty});
                                    }
                                    else if (isInfected[tx][ty] == 0) {  // 下一个单元格是待感染区域
                                        thisWallNum++;  // 不论这个待感染区域是否被统计过，都要安装隔离墙（区域只统计一次，但隔离墙最多要安装4面）
                                        if (!counted.count({tx, ty})) {  // 这个区域还未被统计过
                                            counted.insert({tx, ty});
                                            thisAdjacent++;
                                        }                                        
                                    }
                                }
                            }
                        }

                        max1adjacent = max(max1adjacent, thisAdjacent);
                        area2loc[thisAdjacent] = oneOfThisArea;
                        loc2wallNum[oneOfThisArea] = thisWallNum;
                    }
                }
            }
            if (!max1adjacent) {  // 待感染区域面积为 0,说明没有活病毒了或者全部被病毒感染了(其实似乎不用 has1 变量即可)
                break;
            }
            pair<int, int> oneOfThisArea = area2loc[max1adjacent];	// 找到最大扩展面积的病毒坐标
            ans += loc2wallNum[oneOfThisArea];	// 
			
            /*控制病毒*/
            queue<pair<int, int>> q;
            q.push(oneOfThisArea);
            isInfected[oneOfThisArea.first][oneOfThisArea.second] = 2;//已控制
            while (q.size()) {
                auto[x, y] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int tx = x + direction[d][0];
                    int ty = y + direction[d][1];
                    if (tx >= 0 && tx < n && ty >= 0 && ty < m) {
                        if (isInfected[tx][ty] == 1) { //是病毒
                            isInfected[tx][ty] = 2;    //标记为2，已控制
                            q.push({tx, ty});
                        }
                    }
                }
            }
			
            /*扩展病毒*/
            visited = vector<vector<bool>>(n, vector<bool>(m, false));
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    if (isInfected[x][y] == 1 && !visited[x][y]) {
                        visited[x][y] = true;
                        for (int d = 0; d < 4; d++) {
                            int tx = x + direction[d][0];
                            int ty = y + direction[d][1];
                            if (tx >= 0 && tx < n && ty >= 0 && ty < m) {
                                if (isInfected[tx][ty] == 0) {  // 空地
                                    isInfected[tx][ty] = 1;  // 被病毒感染
                                    visited[tx][ty] = true;  // 防止继续感染拓展
                                }
                            }
                        }
                    }
                }
            }

            if (!has1)
                break;
        }
        return ans;
    }
};
```





---

### 单源BFS

根据题意进行模拟即可

我们首先可以对矩阵 isInfected 进行广度优先搜索，具体地，当我们遍历到 isInfected 中的一个 1 时，就从这个 1 对应的位置开始进行广度优先搜索，这样就可以得到连续的一块被病毒感染的区域。

在搜索的过程中，如果当前是第 idx (idx≥1) 块被病毒感染的区域，我们就把这些 1 都赋值成 −idx，这样就可以防止重复搜索，并且可以和非病毒区域 00 区分开来。同时，由于我们每次需要选择「对未感染区域的威胁最大」的区域设置防火墙，因此我们还需要存储：

- 该区域相邻的未感染区域（即 0）的位置和个数；

- 如果需要位该区域设置防火墙，那么需要防火墙的个数。

对于前者，我们在广度优先搜索的过程中，只要在扩展 1 时搜索相邻的 0，就可以把这个 0 对应的位置放在一个哈希集合中。这里使用哈希集合的原因是同一个 0 可能会和多个 1 相邻，可以防止重复计算。同时，由于多个 1 可能出现在不同的感染区域中，如果通过修改矩阵 isInfected 的形式来标记这些 0，会使得代码编写较为麻烦。

对于后者，计算的方法是类似的，在扩展 1 时如果搜索到相邻的 0，那么我们就需要在 1 和 0 之间的这条网格边上建一个防火墙。同一个 0 和多个 1 相邻，就需要建立多个防火墙，因此我们只需要使用一个变量在广度优先搜索的过程中计数即可，无需考虑重复的情况。



在广度优先搜索完成后，如果我们没有发现任何感染区域，说明区域内不存在病毒，我们直接返回 0 作为答案。否则，我们需要找到「对未感染区域的威胁最大」的区域，这里只需要找出对应的哈希集合的大小最大的那块区域即可。

在确定了区域（假设是第 idx 块区域）后，我们把矩阵中所有的 −idx 都变成 2，这样可以不影响任何搜索和判断；除此之外的所有负数都恢复成 1。此外，所有哈希集合中存储的（除了第 idx 块区域对应的以外）所有相邻位置都需要从 0 变成 1，表示病毒的传播。

最后，如果我们发现区域一共只有一块，那么这次防火墙建立后，不会再有病毒传播，可以返回答案；否则我们还需要继续重复执行上述的所有步骤。

```c++
class Solution {
private:
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    int containVirus(vector<vector<int>>& isInfected) {
        auto pair_hash = [fn = hash<int>()](const pair<int, int>& o) {
            return (fn(o.first) << 16) ^ fn(o.second);
        };

        int m = isInfected.size(), n = isInfected[0].size();
        int ans = 0;
        while (true) {
            vector<unordered_set<pair<int, int>, decltype(pair_hash)>> neighbors;
            vector<int> firewalls;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (isInfected[i][j] == 1) {
                        queue<pair<int, int>> q;
                        unordered_set<pair<int, int>, decltype(pair_hash)> neighbor(0, pair_hash);
                        int firewall = 0, idx = neighbors.size() + 1;
                        q.emplace(i, j);
                        isInfected[i][j] = -idx;

                        while (!q.empty()) {
                            auto [x, y] = q.front();
                            q.pop();
                            for (int d = 0; d < 4; ++d) {
                                int nx = x + dirs[d][0];
                                int ny = y + dirs[d][1];
                                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                                    if (isInfected[nx][ny] == 1) {
                                        q.emplace(nx, ny);
                                        isInfected[nx][ny] = -idx;
                                    }
                                    else if (isInfected[nx][ny] == 0) {
                                        ++firewall;
                                        neighbor.emplace(nx, ny);
                                    }
                                }
                            }
                        }
                        neighbors.push_back(move(neighbor));
                        firewalls.push_back(firewall);
                    }
                }
            }
            
            if (neighbors.empty()) {
                break;
            }

            int idx = max_element(neighbors.begin(), neighbors.end(), [](const auto& v0, const auto& v1) { return v0.size() < v1.size(); }) - neighbors.begin();
            ans += firewalls[idx];
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (isInfected[i][j] < 0) {
                        if (isInfected[i][j] != -idx - 1) {
                            isInfected[i][j] = 1;
                        }
                        else {
                            isInfected[i][j] = 2;
                        }
                    }
                }
            }
            for (int i = 0; i < neighbors.size(); ++i) {
                if (i != idx) {
                    for (const auto& [x, y]: neighbors[i]) {
                        isInfected[x][y] = 1;
                    }
                }
            }
            if (neighbors.size() == 1) {
                break;
            }
        }
        return ans;
    }
};
```



- 时间复杂度：$O(mn(m+n))$。每一次广度优先搜索需要的时间为 $O(mn)$，而矩阵中任意两个位置的曼哈顿距离最大值为 $m+n-2$，因此在 $O(m+n)$ 次搜索后，所有还没有被隔离的病毒会连成一个整体。

- 空间复杂度：$O(mn)$，即为广度优先搜索中的队列以及哈希集合需要使用的空间。







----

# 记忆化搜索

- 记忆化搜索的框架。 总共可以归纳为以下四步：
    1）合法性剪枝
    2）偏序关系剪枝
    3）记忆化剪枝
    4）递归计算结果并返回



**1）合法性剪枝**

因为在递归计算的时候，我们必须保证传入参数的合法性，所以这一步是必要的，比如坐标为负数之类的判断；

**2）偏序关系剪枝**

偏序关系其实就是代表了状态转移的方向，例如只允许值大的往值小的方向走，这就是一种偏序关系；如果不满足偏序关系的就不能继续往下搜索了；

**3）记忆化剪枝**

记忆化剪枝就是去对应的哈希数组判断这个状态是否曾经已经计算过，如果计算过则直接返回，时间复杂度  ；

**4）递归计算结果并返回**

这一步就是深度优先搜索的递归过程，也是递归子问题取最优解的过程，需要具体问题具体分析；





- 记忆化搜索的优点

**1、忽略边界判断**

状态转移的时候完全不需要进行边界判断，只需要在递归调用的出口进行统一判断即可，这样使得代码更加简洁清晰；

**2、编码方便**

相比动态规划而言，不用去关心子问题的枚举顺序问题，也不用管数组下标越界问题，只要按照深度优先搜索的思路，把代码框架写好，再加入记忆化部分的代码即可，实现方便，手到擒来；







## 模板

```c++
int dfs(mem)
{
    // 终止条件
    if (xxx) return -1;
    if (xxx) return 0;
    if (mem[xxx] != -1) return mem[xxx];

    // 求解体
    int minval = INT_MAX;
    for () {
        int val = dfs(mem);
        if (val) {
            minval = min(minval, val);
        }
    }

    // 当次记忆化结果更新，回溯
    return mem[xxx] = minval;
}
```





## 01背包

### 416. 分割等和子集

递归搜索：常规的递归搜索 dfs(i, *args) 在到达一个位置 i 时无非有两种情况（选或不选）：

- 跳过 i 位置：直接考虑下一步；
- 选择 i 位置：根据实际情况判断该选择是否可行，以及选择 i 之后的下一步操作如何进行。

恰好对应于选或不选第 ii 件物品。只不过目标为从 nums 中选出若干个数字使其和恰好等于数组总和的一半，记为 $target = \frac{sum}{2}$

![image.png](assets/1602391112-KnTcoJ-image.png)

针对每一个元素，都有“减去”和“不减”两种选项。

输入 [1, 1, 1, 4, 5]，总和 sum 为12，取半half 为6；
针对第一个元素，减去得 5，不减得 6，依次产生完全二叉树；
**出现负数直接返回否，等于0直接返回是**。

```c++
class Solution {
public:
    bool dfs(int i, int target, vector<int>& nums) {
        if (target == 0) return true;
        // target为负数 或 nums数组遍历完 返回false
        if (target < 0 || i == nums.size()) return false;

        // 选这个数字   减这个数字
        bool b1 = dfs(i+1, target - nums[i], nums);

        // 不选这个数字 不减这个数字
        bool b2 = dfs(i+1, target, nums);

        return b1 || b2;
    }

    bool canPartition(vector<int>& nums) {
        int sumn = accumulate(nums.begin(), nums.end(), 0);

        if (sumn & 1) return false;

        int target = sumn / 2;

        return dfs(0, target, nums);
    }
};
```

上述算法的时间复杂度接近 $O(2^n),\ n=len(nums)$ ，因此不适合 nums 中元素较多的情况。

很多**自上而下的递归搜索过程**都可以修改为复杂度更低的**自下而上的动态规划过程**。





里面有大量重复元素。思考发现，在二叉树的**同一层**出发，如果剩下的数字`remain`一样大，它后续的分支是完全相同的。

![image.png](assets/1602391190-WnafLv-image.png)

> “只选第一个1”和“只选第二个1”的结果是一样的；
> 同一层的两个`remain`如果相同，它们的子树就完全相同。

针对这种情况我们引入记忆化搜索。

每次递归，我们检查这个`remain`是否在这一层出现过。如果是，就跳过这个结点。

```c++
bool dfs(int i, int remain, vector<int>& nums, vector<vector<int>> &memo) {
    if (remain == 0) return true;
    if (remain < 0 || i == nums.size()) return false;

    // 记忆化
    if (memo[i][remain] != -1) return memo[i][remain];
    memo[i][remain] = dfs(i+1, remain - nums[i], nums, memo) || dfs(i+1, remain, nums, memo);    //注意这里是 || 有一条路可以满足就行   

    /*
        // 选这个数字   减这个数字
        bool b1 = dfs(i+1, remain - nums[i], nums)
        // 不选这个数字 不减这个数字
        bool b2 = dfs(i+1, remain, nums);
        */

    return memo[i][remain];
}

bool canPartition(vector<int>& nums) {
    int sumn = accumulate(nums.begin(), nums.end(), 0);

    if (sumn & 1) return false;

    int target = sumn / 2;

    vector<vector<int>> memo(nums.size(), vector<int>(target + 1, -1)); //memo[i][j]里存出现过，就直接返回它的值

    return dfs(0, target, nums, memo);
}    
```



![image.png](assets/1602391399-Lobwlk-image.png)

可以看到，现在每一层同一个`remain`数字只出现一次。





---

### 474. 一和零

最重要的一点，如果传入的参数中有 cnt，那么 memo 里的索引要有 cnt，i，m，n

暴力遍历 22/71

```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int nowM, int nowN, int cnt, int i) {
    if (nowM > m || nowN > n) return 0; // 超过了 不满足
    // 以下情况为 nowM <= m 和 nowN <= n的情况
    if (i == nums.size()) return cnt;   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以

    // 要
    int i1 = dfs(nums, m, n, nowM + nums[i][0], nowN + nums[i][1], cnt + 1, i + 1);
    // 不要
    int i2 = dfs(nums, m, n, nowM, nowN, cnt, i+1);

    return max(i1, i2);
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
	vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    int b = dfs(nums, m, n, 0, 0, 0, 0);
    return b;
}
```



用 `vector<unordered_set<int>>` ，WA 66/71

```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int nowM, int nowN, int cnt, int i) {
    if (nowM > m || nowN > n) return 0; // 超过了 不满足
    // 以下情况为 nowM <= m 和 nowN <= n的情况
    if (i == nums.size()) return cnt;   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以

    int idx = nowM * 610 + nowN;
    if (dp[i].find(idx) != dp[i].end()) return 0;
    dp[i].insert(idx);

    // max(要, 不要)    
    return max(dfs(nums, m, n, nowM + nums[i][0], nowN + nums[i][1], cnt + 1, i + 1), dfs(nums, m, n, nowM, nowN, cnt, i+1));
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    dp.resize(len);
    vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    return dfs(nums, m, n, 0, 0, 0, 0);
}

vector<unordered_set<int>> dp; 
```



转成用三维数组存，WA 66/71

```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int nowM, int nowN, int cnt, int i, vector<vector<vector<int>>> &memo) {
    if (i > nums.size() || nowM > m || nowN > n) return 0; // 超过了 不满足
    // 以下情况为 nowM <= m 和 nowN <= n的情况
    if (i == nums.size()) return cnt;   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以

    if (memo[i][nowM][nowN] != -1) return memo[i][nowM][nowN];
    memo[i][nowM][nowN] = max(dfs(nums, m, n, nowM + nums[i][0], nowN + nums[i][1], cnt + 1, i + 1, memo), 
                              dfs(nums, m, n, nowM, nowN, cnt, i+1, memo));

    // max(要, 不要)    
    return memo[i][nowM][nowN];
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    vector<vector<vector<int>>> memo(len, vector<vector<int>>(m+1, vector<int>(n+1, -1)));
    return dfs(nums, m, n, 0, 0, 0, 0, memo);
}
```



应该自顶向下，而之前的写法是自底向上！！！！！！！！！



自顶向下还是 WA 66/71？？？？？？？？

```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int cnt, int i, vector<vector<vector<int>>> &memo) {
    if (m < 0 || n < 0) return 0; // 减成负数了 不满足
    // 以下情况为 m>=0 和 n>=0 的情况
    if (i == nums.size()) { return cnt;}   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以,这里也相当于剪枝，要求i不越界


    if (memo[i][m][n] != -1) return memo[i][m][n];

    int i1 = dfs(nums, m, n, cnt, i+1, memo);
    int i2 = dfs(nums, m - nums[i][0], n - nums[i][1], cnt + 1, i + 1, memo);

    // max(要, 不要)    
    memo[i][m][n] = max(i1, i2);        
    return memo[i][m][n];
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    vector<vector<vector<int>>> memo(len, vector<vector<int>>(m+1, vector<int>(n+1, -1)));
    return dfs(nums, m, n, 0, 0, memo);
}
```



==不能传cnt进来，如果传进来，就需要单独再开一个维度保存cnt的索引==



记忆化

```c++
int dfs(vector<string>& strs, int m, int n, int index, vector<vector<vector<int>>>& meo) {
    if (index == strs.size()) {
        return 0;
    }
    if (meo[index][m][n] != -1) {
        return meo[index][m][n];
    }
    int zero = count(strs[index].begin(), strs[index].end(), '0');
    int one = strs[index].size() - zero;
    int a = dfs(strs, m, n, index + 1, meo);
    int b = 0;
    if (m - zero >= 0 && n - one >= 0) {
        b = 1 + dfs(strs, m - zero, n - one, index + 1, meo);
    }
    return meo[index][m][n] = max(a, b);
}

int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<vector<int>>> meo(strs.size(), vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
    return dfs(strs, m, n, 0, meo);
}
```









#### 答案对但超时

45
60

```
["011","1","11","0","010","1","10","1","1","0","0","0","01111","011","11","00","11","10","1","0","0","0","0","101","001110","1","0","1","0","0","10","00100","0","10","1","1","1","011","11","11","10","10","0000","01","1","10","0"]
44
39
```

```
["1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0","1","0"]
30
30
```



```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int cnt, int i, unordered_map<string, int> &memo) {
    if (m < 0 || n < 0) return 0;
    if (i == nums.size()) return cnt;

    string key = to_string(i) + "_" + to_string(m) + "_" + to_string(n) + "_" + to_string(cnt);
    if (memo.find(key) != memo.end()) return memo[key];

    // max(不要, 要) 
    return memo[key] = max(dfs(nums, m, n, cnt, i+1, memo), 
                           dfs(nums, m - nums[i][0], n - nums[i][1], cnt + 1, i + 1, memo));
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    unordered_map<string, int> memo;

    return dfs(nums, m, n, 0, 0, memo);
}
```



#### unordered_map 优化

**key 从 string 优化为 int**

优化后，不要用 string 作为 key，用 int，把索引拉平

```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int cnt, int i, unordered_map<long long, int> &memo) {
    if (m < 0 || n < 0) return 0;
    if (i == nums.size()) return cnt;

    long long key = cnt * (601*101*101) + i * (101*101) + m * (101)  +  n;
    if (memo.find(key) != memo.end()) return memo[key];

    // max(不要, 要) 
    return memo[key] = max(dfs(nums, m, n, cnt, i+1, memo), 
                           dfs(nums, m - nums[i][0], n - nums[i][1], cnt + 1, i + 1, memo));
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    unordered_map<long long, int> memo;

    return dfs(nums, m, n, 0, 0, memo);
}
```



#### `vector<unordered_set<int>>` 优化

注意算idx的时候包括cnt，不用算 i 的原因是 `memo[i]`中包括了

```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int nowM, int nowN, int cnt, int i, vector<unordered_set<int>> &memo) {
    if (nowM > m || nowN > n) return 0; // 超过了 不满足
    // 以下情况为 nowM <= m 和 nowN <= n的情况
    if (i == nums.size()) return cnt;   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以

    int idx = cnt * (101*101) + nowM * 110 + nowN;
    if (memo[i].find(idx) != memo[i].end()) return -9;
    memo[i].insert(idx);

    // max(要, 不要)    
    return max(dfs(nums, m, n, nowM + nums[i][0], nowN + nums[i][1], cnt + 1, i + 1, memo), dfs(nums, m, n, nowM, nowN, cnt, i+1, memo));
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    vector<unordered_set<int>> memo(len); 

    return dfs(nums, m, n, 0, 0, 0, 0, memo);
}
```

这里 `if (memo[i].find(idx) != memo[i].end()) return cnt;` **无论返回多少都可以，没有关系？？？？？？？？？？？？？？？？？？**





#### 三维数组

```c++
int dfs(const vector<vector<int>> &nums, int m, int n, int i, vector<vector<vector<int>>> &memo) {
    if (i == nums.size()) { return 0;}   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以,这里也相当于剪枝，要求i不越界

    if (memo[i][m][n] != -1) return memo[i][m][n];

    int i1 = dfs(nums, m, n, i+1, memo);
    int i2 = 0;
    if (m - nums[i][0] >= 0 && n - nums[i][1] >= 0) {
        i2 = 1 + dfs(nums, m - nums[i][0], n - nums[i][1], i + 1, memo);
    }
    // max(要, 不要)    
    return memo[i][m][n] = max(i1, i2);
}

int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));

    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    } 

    vector<vector<vector<int>>> memo(len, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
    return dfs(nums, m, n, 0, memo);
}
```





---

### 1755.最接近目标值的子序列和



### 2035.将数组分成两个数组并最小化数组和的差





### 805.数组的均值分割









---

## 完全背包

### 322. 零钱兑换

该问题可建模为以下优化问题：

$$
\min_{x} \sum_{i=0}^{n - 1} x_i \ \text{subject to} \sum_{i=0}^{n - 1} x_i \times c_i = S
$$
其中，S 是总金额，$c_i$  是第 i 枚硬币的面值，$x_i$ 是面值为 $c_i$ 的硬币数量，由于 $x_i \times c_i$ 不能超过总金额 S，可以得出 $x_i$ 最多不会超过 $\frac{S}{c_i}$ ，所以 $x_i$ 的取值范围为 $[{0, \frac{S}{c_i}}]$. 一个简单的解决方案是通过回溯的方法枚举每个硬币数量子集 $[x_0\dots\ x_{n - 1}]$ ，针对给定的子集计算它们组成的金额数，如果金额数为 S，则记录返回合法硬币总数的最小值，反之返回 -1。

该做法的时间复杂度为 $O(S^n)$，会超出时间限制，因此必须加以优化。





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
int dfs(vector<int>& coins, int rem, vector<int> &memo) {
    if (rem < 0) return -1;
    if (rem == 0) return 0;

    // 有记忆, 直接返回所需的最少硬币个数
    if (memo[rem] != -2) return memo[rem];    


    int minCnt = INT_MAX;
    for (int i = 0; i < coins.size(); ++i) {
        int cnt = dfs(coins, rem - coins[i], memo);
        if (cnt != -1 ) minCnt = min(cnt, minCnt);
    }

    memo[rem] = (minCnt == INT_MAX ? -1 : minCnt + 1);  //记忆化部分，通过数组记住金额为amount时，所需的最少硬币个数

    return memo[rem];
}

int coinChange(vector<int>& coins, int amount) {
    vector<int> memo(amount + 1, -2);    // memo[i]当前剩余金额为i时的最小选择硬币数
    int ans = dfs(coins, amount, memo);
    return ans == -2 ? -1 : ans;
}
```



复杂度分析

**时间复杂度**：$O(Sn)$，其中 S 是金额，n 是面额数。我们一共需要计算 S 个状态的答案，且每个状态 F(S) 由于上面的记忆化的措施只计算了一次，而计算一个状态的答案需要枚举 n 个面额值，所以一共需要 O(Sn) 的时间复杂度。

**空间复杂度**：$O(S)$，我们需要额外开一个长为 S 的数组来存储计算出来的答案 F(S) 。







---

### 518. 零钱兑换 II







### 279. 完全平方数





### 377. 组合总和 Ⅳ





### 139. 单词拆分





