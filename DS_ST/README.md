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

### 6066. 统计区间中的整数数目

用一个 set 有序地维护所有不相交的区间，当加入区间 [left, right] 时，通过 lower_bound 快速找到第一个右端点大等于 left - 1 的区间，然后不断用接下来的区间和 [left, right] 合并，直到当前区间的左端点大于 right + 1。由于每个区间只会加入以及离开 set 一次，复杂度 $\mathcal{O}(n \log n)$。

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





