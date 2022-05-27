# 线段树

用来维护区间信息的数据结构



线段树可以在 $O(\log N)$ 的时间复杂度内实现单点修改，区间修改，区间查询（区间求和，求区间最大值，求区间最小值）等操作。



线段树维护的信息在很多时候可以认为是满足（幺）半群的性质和信息。

一个幺半群 $M = (S,\circ,e)$，其中 $\circ$ 为在集合 $S$ 上定义的二元运算符，幺半群具有以下性质：

- 封闭性：$ \forall x \in S $ 和 $ \forall y \in S $ 有 $ x \circ y \in S $
- 结合律：$ \forall x, y, z \in S $ 有 $ (x \circ y) \circ z=x \circ(y \circ z) $
- 存在幺元：$ \exists e \in S $ 满足 $ \forall x \in S $ 有 $ e \circ x=x $，$e$ 为左幺元；或 $x\circ e = x$，$e$ 为右幺元。

线段树上的信息一般满足这样的性质，一些数域上的加法与乘法自然，考虑二元的 $max(x,y)$ 运算，此时幺元为 $ -\infty $ 也满足这样的性质（一般左右幺元相同时简称为幺元）







## 基本结构与建树









https://leetcode.cn/problems/car-pooling/solution/yi-ge-mo-ban-miao-sha-ji-dao-xiang-si-de-l4cr/

涉及区间更新，单点查询，区间和查询的问题一般可以考虑树状数组
类似的题有：

1094拼车

1109.航班预定统计

1854.人口最多的年份

面试题 16.10. 生存人数

1156: 新年彩灯Ⅰ

区间更新，单点查询模板：





---

## 区间合并

![image-20211009111244911](assets/1633749732-zEWeXS-image-20211009111244911.png)







---

### 2276. 统计区间中的整数数目

用一个 set 有序地维护所有不相交的区间，当加入区间 [left, right] 时，通过 lower_bound 快速找到第一个右端点大等于 left - 1 的区间，然后不断用接下来的区间和 [left, right] 合并，直到当前区间的左端点大于 right + 1。由于每个区间只会加入以及离开 set 一次，复杂度 $\mathcal{O}(n \log n)$。

```c++
class CountIntervals {
    typedef pair<int, int> pii; //先存right 再存left

    int ans = 0;
    set<pii> st;    // 存（右端点，左端点）    因为主要是为了找右端点进行比较

public:
    CountIntervals() {

    }
    
    void add(int left, int right) {
        // 只有满足下面条件才能插入并计算
        // 存在两个相邻集合A(ALeft, ARight)和B(BLeft, BRight) 
        // 条件一: left > ARight
        // 条件二: right < BLeft

        auto it = st.lower_bound(pii(left, -1e-9)); // 找到第一个 A 满足 ARight 比 left 大  满足条件一 (10, 7)
        while (it != st.end()) {             // 如果找到了
            if (right < it->second) break;   // 判断 right 是否小于 BLeft，及要求满足条件二跳出 

            /*合并区间*/
            left = min(left, it->second);    // min(5, 7) = 5
            right = max(right, it->first);   // max(8, 10) = 10
            ans -= (it->first - it->second + 1);
            st.erase(it++);
        }        

        st.insert(pii(right, left));
        ans += right - left + 1;

        return;
    }        
    
    int count() {
        return ans;
    }
};
```





Q：为什么用 left - 1 和 right + 1 比较，直接 left 和 right 不行吗？
A：为了把虽然不相交但是连续的区间也合并，比如 [1,3], [4, 6] 可以合并成 [1, 6]。当然对于本题而言这样的合并不需要。直接用 left 和 right 判断也可以，但作为模板的角度合并可能更合适一点。

```C++
class CountIntervals {
    typedef pair<int, int> pii;

    int ans = 0;
    set<pii> st;

public:
    CountIntervals() {
    }
    
    void add(int left, int right) {
        int L = left, R = right;
        // 这里 (R1, L1) >= (R2, L2)，若 R1 > R2 或 R1 = R2 且 L1 >= L2
        auto it = st.lower_bound(pii(left - 1, -2e9));
        while (it != st.end()) {
            if (it->second > right + 1) break;
            L = min(L, it->second);
            R = max(R, it->first);
            ans -= it->first - it->second + 1;
            st.erase(it++);
        }
        ans += R - L + 1;
        st.insert(pii(R, L));
    }
    
    int count() {
        return ans;
    }
};
```









----

### 352. 将数据流变为多个不相交区间

注意这道题目跟 2276 基本上是一模一样，唯一不同的就是这道题比较的时候**必须是** left - 1 和 right + 1 进行比较，而不能用 left 和 right 进行比较原因：

为了把虽然不相交但是连续的区间也合并，比如 [1,3], [4, 6] 可以合并成 [1, 6]。

```c++
class SummaryRanges {
    typedef pair<int, int> pii;
    set<pii> st;
    
public:
    SummaryRanges() {

    }
    
    void addNum(int val) {
        int left = val, right = val;
        auto it = st.lower_bound(pii(left-1, -1e9));

        while (it != st.end()) {
            if (it->second > right+1) break;
            left = min(left, it->second);
            right = max(right, it->first);
            st.erase(it++);
        }

        st.insert(pii(right, left));
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> ans;
        for (auto p : st) {
            ans.push_back({p.second, p.first});
        }
        return ans;
    }
};
```

lower_bound(i) 找到第一个大于等于 i 的数的位置，我们把 val 扩展成 [le=val, ri=val] 的区间

针对情况 1，it 找到 L0 的位置，因为 L0->right 大于 le-1；进入循环，L0->left 小于 ri+1 调整区间范围，找到最左和最右的位置，调整之后 it++ 再次进入循环，此时 L1->left 大于 ri + 1，无需调整出循环；

针对情况 2，it 找到 L0 的位置，因为 L0->right 大于 le-1；进入循环，L0->left 小于 ri+1 调整区间范围，找到最左和最右的位置，调整之后 it++ 再次进入循环；此时 L1->left 仍小于 right + 1，再次调整区间范围，找到最左和最右的位置，调整之后 it++ 再次进入循环，此时到达末尾，结束循环；

针对情况 3，it 找到 L0 的位置，因为 L0->right 大于 le-1；进入循环，L0->left 小于 ri+1 调整区间范围，找到最左和最右的位置，调整之后 it++ 再次进入循环；此时 L1->left 大于 ri + 1，无需调整出循环；(实际上跟情况1相同)

针对情况 4，it 找到 L1 的位置，因为 L1->right 大于 le-1；进入循环，L1->left 小于 ri+1 调整区间范围，找到最左和最右的位置，调整之后 it++ 再次进入循环；此时到达末尾，结束循环；

针对情况 5，it 找到 L1 的位置，因为 L1->right 大于 le-1；进入循环，L1->left 大于 ri+1 调整区间范围结束循环；单独插入

![image-20211009111244911](assets/1633749732-zEWeXS-image-20211009111244911.png)

针对情况 5 时，L1 可以不存在，即 `it == st.end()`











----

### 715. Range 模块

官方没有考虑的 case 

```c++
["RangeModule","addRange","addRange","addRange","removeRange","queryRange","queryRange"]
[[],[10,20],[20,25],[26,30],[14,16],[20,21],[25,26]]
```



此题不能用模板直接优化离散但连续的区间，因为它是前开后闭，因此必须 left，right 而不是 left-1 和 right+1

```c++
class RangeModule {
    typedef pair<int, int> pii;
    set<pii> st;
    
public:
    RangeModule() {
        /*因为插入、跟踪、删除全是半开区间，那就跟全开区间没区别*/
    }
    
    void addRange(int left, int right) {
        auto it = st.lower_bound(pii(left, -1e-9)); // 找第一个可以合并的区间

        while (it != st.end()) {        // 逐个合并
            auto [R, L] = *it;
            if (L > right)  break;      // 后面的不能合并了，提前退出循环
            left = min(left, L);
            right = max(right, R);
            st.erase(it++);
        }

        st.insert(pii(right, left));    // 把合并后的区间插入set，注意是{R, L}
    }
    
    bool queryRange(int left, int right) {
        auto it = st.lower_bound(pii(left, -1e-9)); // 找第一个可能包含[left, right)的区间

        if (it == st.end()) return false;           // 没有找到，直接返回false
        
        auto [R, L] = *it;
        if (L <= left && right <= R) return true;   // 判断这个区间是否包含所要查询的区间
        else return false;
    }
    
    void removeRange(int left, int right) { 
        auto it = st.lower_bound(pii(left, -1e-9)); // 找第一个可能包含[left, right)的区间
        int l1, r1, l2, r2; 
        bool flagL = false, flagR = false;
        while (it != st.end()) {
            auto [R, L] = *it;
            if (L > right) break;   // 后面的区间不用删了，提前退出循环
            
            if (left > L) {         // 部分区间在left的左边，此时需要添加多删除的部分区间
                flagL = true;
                l1 = L;
                r1 = left;
            }

            if (right < R) {        // 部分区间在right的右边，此时需要添加多删除的部分区间
                flagR = true;
                l2 = right;
                r2 = R;
            }
            st.erase(it++);         // 移除该区间
        }

        if (flagL) st.insert({r1, l1}); // 部分区间在left的左边，此时需要添加多删除的部分区间
        if (flagR) st.insert({r2, l2}); // 部分区间在right的右边，此时需要添加多删除的部分区间
        return;
    }
};
```

















---

# 树状数组



## 原理

![img](assets/fenwick.svg)

用一个大节点表示一些小节点的信息，进行查询的时候只需要查询一些大节点而不是所有的小节点。



最上面八个方块就代表数组 $a$

下面的一些剩下的方块就代表数组 $a$ 的上级 -- c数组

可以看出：

$c_2$ 管理的是 $a_1$ 和 $a_2$

$c_4$ 管理的是 $a_1$, $a_2$, $a_3$, $a_4$

$c_6$ 管理的是 $a_5$ 和 $a_6$

$c_8$ 管理的所有 8 个数



如果要计算数组 $a$ 的区间和，比如说算 $a_{51}\sim a_{91}$ 的区间和，可以采用类似倍增的思想：

- 从 91 开始往前跳，发现 $c_n$ 只管 $a_{91}$ 这个点
- 那么就会找 $a_{90}$, 发现 $c_{n-1}$ 管的是 $a_{90}$ 和 $a_{89}$;
- 那么就会直接跳到 $a_{88}$, 发现 $c_{n-2}$ 管的是 $a_{81}\sim a_{88}$ 这些数
- 下次查询从 $a_{80}$ 往前找，以此类推



---

## 用法及操作

怎么知道 $c_i$ 管理的是数组 $a$ 中哪个区间呢？

### lowbit

```c++
// x 的二进制表示中，最低位的 1 的位置
// lowbit(0b1011 0000) == 0b0010000
//          ~~~^ ~~~~
// lowbit(0b1011 0100) == 0b0000100
//          ~~~~ ~^~~

int lowbit(int x) {    
    return x & -x;
}
```

对于 $x=88$, 有 $ 88_{(10)}=0101 1000_{(2)} $

发现第一个 1 以及他后边的 0 组成的二进制是 $1000$

1000 对应的十进制是 8，所以 $c_{88}$ 一共管理 8 个 $a$  数组中的元素。

有符号数采用补码表示。在补码表示下，数 $x$ 的相反数 $-x = ~x + 1$，即反码 + 1



#### 单点修改

使用 lowbit 函数，我们可以实现很多操作，例如单点修改，将 $a_x$ 加上 k，只需要更新 $a_x$ 的所有上级：

```c++
void add(int x, int y) {
    while (x <= n) {	//不能越界，n为总长
        c[x] = c[x] + k;
        x = x + lowbit(x);
    }
}
```



#### 前缀求和

```c++
int getSum(int x) {
    int ans = 0;
    while (x >= 1) {
        ans = ans + c[x];
        x = x - lowbit(x); 
    }
    return ans;
}
```



#### 区间求和

若维护序列 $a$ 的差分数组 $b$, 此时我们对 $a$ 的一个前缀 $r$ 求和，即 $ \sum_{i=1}^{r} a_{i} $ ，由差分数组定义得 $ a_{i}=\sum_{j=1}^{i} b_{j} $

进行推导
$$
\begin{equation}
 \begin{aligned} & \sum_{i=1}^{r} a_{i} \\=& \sum_{i=1}^{r} \sum_{j=1}^{i} b_{j} \\=& \sum_{i=1}^{r} b_{i} \times(r-i+1) \\=& \sum_{i=1}^{r} b_{i} \times(r+1)-\sum_{i=1}^{r} b_{i} \times i \end{aligned} 
\end{equation}
$$






https://leetcode.cn/problems/car-pooling/solution/yi-ge-mo-ban-miao-sha-ji-dao-xiang-si-de-l4cr/

涉及区间更新，单点查询，区间和查询的问题一般可以考虑树状数组
类似的题有：

1094拼车

1109.航班预定统计

1854.人口最多的年份

面试题 16.10. 生存人数

1156: 新年彩灯Ⅰ

区间更新，单点查询模板：





