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









