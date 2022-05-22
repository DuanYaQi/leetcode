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

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
```



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







### 352. 将数据流变为多个不相交区间

```c++
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





