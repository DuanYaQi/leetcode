# 线段树

用来维护区间信息的数据结构



线段树可以在 $O(\log N)$ 的时间复杂度内实现单点修改，区间修改，区间查询（区间求和，求区间最大值，求区间最小值）等操作。



线段树维护的信息在很多时候可以认为是满足（幺）半群的性质和信息。

一个幺半群 $M = (S,\circ,e)$，其中 $\circ$ 为在集合 $S$ 上定义的二元运算符，幺半群具有以下性质：

- 封闭性：$ \forall x \in S $ 和 $ \forall y \in S $ 有 $ x \circ y \in S $
- 结合律：$ \forall x, y, z \in S $ 有 $ (x \circ y) \circ z=x \circ(y \circ z) $
- 存在幺元：$ \exists e \in S $ 满足 $ \forall x \in S $ 有 $ e \circ x=x $，$e$ 为左幺元；或 $x\circ e = x$，$e$ 为右幺元。

线段树上的信息一般满足这样的性质，一些数域上的加法与乘法自然，考虑二元的 $max(x,y)$ 运算，此时幺元为 $ -\infty $ 也满足这样的性质（一般左右幺元相同时简称为幺元）













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

## 基本结构与建树

构造、修改的函数总体流程：

- 是叶子节点，边界条件，处理后 return

- 不是叶子节点，分裂左右子树递归



查询的函数总体流程：

- 完全覆盖查询区间，边界条件，return 值

- 不覆盖，分裂左右子树递归





### 数组模板

```c++
#define lc u<<1     // 2*u      左节点
#define rc u<<1|1   // 2*u + 1  右节点
class SegTree {             // 线段树不一定满二叉树，也不一定是完全二叉树，但一定是平衡二叉树
public:
    // 父节点索引为 u, 左孩子索引为 2*u, 右孩子索引为 2*u + 1
    // 子节点索引为 u, 父亲节点索引为 u / 2
    struct Node {           // 节点
        int l = 0, r = 0;   // 区间的左右端点,即[l,r]  
        int sum = 0;        // 区间和
    };
    
    vector<Node> tr;        // 数组表示的线段树
    vector<int> a;          // 大小为n的数组
    int n;

    SegTree() {}

    SegTree(vector<int> &a) {
        n = a.size();
        this->a = a;
        tr.resize(n * 4 + 1);   // 最好情况2n; 最差4n; +1索引从1开始
        build(1, 1, n);         // 根节点索引1，区间左右边界[1,n]
    }
    
    void push_up(int u) {	// 回溯时更新父结点
        tr[u].sum = tr[lc].sum + tr[rc].sum;    // 递归往回走的时候 一路上去更新, 更新祖先节点
    }

    void build(int u, int l, int r) {   // u为根节点索引 l左边界 r右边界
        tr[u] = {l, r};     		// 赋值左右边界
        if (l == r) {       		// 是叶子节点
            tr[u].sum = a[l - 1];	// 赋值返回，因为下标从1开始，所以是l-1
            return;
        }

        int mid = l + r >> 1;       // 非叶子节点，裂开
        build(lc, l, mid);          // lc = u<<1
        build(rc, mid + 1, r);      // rc = u<<1|1
        push_up(u);				    // 更新祖先节点
    }

    // 单点修改 递归寻找叶子节点 [x,x], 把该节点的值修改, 并且从下往上更新其组先节点的值
    void modify(int u, int x, int v) { 		// u为根节点索引 x为修改的位置 v为修改的值 
        if (tr[u].l == tr[u].r) { 			// 能满足tr[u].l == tr[u].r == x 叶子节点
            tr[u].sum += v; 				// 进来修改, 求区间和是累加，也可能是直接赋值
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;   // 非叶子节点，裂开
        if (x <= mid) modify(lc, x, v);
        if (x > mid)  modify(rc, x, v);
        push_up(u);				    		// 更新祖先节点
    }
    
    // 区间查询 [l,r] 的和，利用拆分与拼凑的思想，把大区间变为多个小区间的和
    int query(int u, int l, int r) { 			// u为根节点索引 l左边界 r右边界
        if (l <= tr[u].l && tr[u].r <= r)   	// 查询区间 [x,y] 完全覆盖当前节点区
            return tr[u].sum;               	// 间，立即回溯，返回该区间的sum值，让上一层累加
        
        int mid = tr[u].l + tr[u].r >> 1;   	// 非叶子节点，裂开
        int sum = 0;
        if (l <= mid) sum += query(lc, l, r); 	// 查询左边界比mid小，左子节点与区间 [x,y] 有重叠，递归访问左子树
        if (r > mid) sum += query(rc, l, r);  	// 查询右边界比mid小，右子节点与区间 [x,y] 有重叠，递归访问右子树
        return sum;
    }

};

```



![image-20220719225614973](assets/image-20220719225614973.png)





![image-20220719225521539](assets/image-20220719225521539.png)





![image-20220719230244307](assets/image-20220719230244307.png)

比如 [x,y] = [4, 9]        mid = 1 + 10 >> 1 = 5    裂开为 [4, 5] 和 [5, 9]







----

### 数组懒标记模板

```c++
#define lc u<<1     // 2*u      左节点
#define rc u<<1|1   // 2*u + 1  右节点
class SegTree {             // 线段树不一定满二叉树，也不一定是完全二叉树，但一定是平衡二叉树
public:
    // 父节点索引为 u, 左孩子索引为 2*u, 右孩子索引为 2*u + 1
    // 子节点索引为 u, 父亲节点索引为 u / 2
    struct Node {           // 节点
        int l = 0, r = 0;   // 区间的左右端点,即[l,r]  
        int sum = 0;        // 区间和
        int add;			// 懒标记
    };
    
    vector<Node> tr;        // 数组表示的线段树
    vector<int> a;          // 大小为n的数组
    int n;

    SegTree() {}

    SegTree(vector<int> &a) {
        n = a.size();
        this->a = a;
        tr.resize(n * 4 + 1);   // 最好情况2n; 最差4n; +1索引从1开始
        build(1, 1, n);         // 根节点索引1，区间左右边界[1,n]
    }
    
    void push_up(int u) {	// 回溯时更新父结点
        tr[u].sum = tr[lc].sum + tr[rc].sum;    // 递归往回走的时候 一路上去更新, 更新祖先节点
    }
    
    void push_down(int u) {	// 下传懒标记
        if (tr[u].add) { 	// 欠的钱不为 0
            tr[lc].sum += tr[u].add*(tr[lc].r - tr[lc].l + 1);
            tr[rc].sum += tr[u].add*(tr[rc].r - tr[rc].l + 1);
            tr[lc].add = tr[u].add;
            tr[rc].add = tr[u].add;
            tr[u].add = 0;
        }        
    }

    void build(int u, int l, int r) {   // u为根节点索引 l左边界 r右边界
        tr[u] = {l, r};     		// 赋值左右边界
        if (l == r) {       		// 是叶子节点
            tr[u].sum = a[l - 1];	// 赋值返回，因为下标从1开始，所以是l-1
            return;
        }

        int mid = l + r >> 1;       // 非叶子节点，裂开
        build(lc, l, mid);          // lc = u<<1
        build(rc, mid + 1, r);      // rc = u<<1|1
        push_up(u);				    // 更新祖先节点
    }

    // 单点修改 递归寻找叶子节点 [x,x], 把该节点的值修改, 并且从下往上更新其组先节点的值
    void modify(int u, int x, int v) { 		// u为根节点索引 x为修改的位置 v为修改的值 
        if (tr[u].l == tr[u].r) { 			// 能满足tr[u].l == tr[u].r == x 叶子节点
            tr[u].sum += v; 				// 进来修改, 求区间和是累加，也可能是直接赋值
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;   // 非叶子节点，裂开
        if (x <= mid) modify(lc, x, v);
        if (x > mid)  modify(rc, x, v);
        push_up(u);				    		// 更新祖先节点
    }
    
    // 区间修改 [x,y] 的和，
    void modify(int u, int x, int y, int v) { 	// u为根节点索引 x左边界 y右边界 v为修改的值 
        if (x <= tr[u].l && tr[u].r <= y) { 	// 修改区间 [x,y] 完全覆盖当前节点区
            tr[u].sum += (tr[u].r - tr[u].l + 1) * v; 	// 进来修改, 把v累加(tr[u].r - tr[u].l + 1)次
            tr[u].add += v;								// 懒标记 v
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;		// 不覆盖裂开
        push_down(u);							// “下次需要”，下传懒标记
        if (x <= mid) modify(lc, x, y, v);
        if (x > mid)  modify(rc, x, y, v);
        push_up(u);				    			// 向上回溯更新祖先节点
    }

    // 区间查询 [l,r] 的和，利用拆分与拼凑的思想，把大区间变为多个小区间的和
    int query(int u, int l, int r) { 			// u为根节点索引 l左边界 r右边界
        if (l <= tr[u].l && tr[u].r <= r)   	// 查询区间 [x,y] 完全覆盖当前节点区
            return tr[u].sum;               	// 间，立即回溯，返回该区间的sum值，让上一层累加
        
        int mid = tr[u].l + tr[u].r >> 1;   	// 非叶子节点，裂开
        int sum = 0;
        if (l <= mid) sum += query(lc, l, r); 	// 查询左边界比mid小，左子节点与区间 [x,y] 有重叠，递归访问左子树
        if (r > mid) sum += query(rc, l, r);  	// 查询右边界比mid小，右子节点与区间 [x,y] 有重叠，递归访问右子树
        return sum;
    }

};

```



![image-20220719235152483](assets/image-20220719235152483.png)

可以笨笨的对区间里每个数做一次单点修改，但这样时间复杂度是 $O(n)$

可以引入懒标记，懒惰修改（有点类似区间查询），完全覆盖时加 "懒标记"，就不再往下走了。可以理解为账本，欠子孙节点的钱。

“下次需要” 比如：第一次区间修改 [4,9]，然后进行了懒标记；第二次区间修改 [6, 7]，走到 [6, 8] 的时候有标记（账本），把账本分给其子孙节点。这样时间复杂度是 $O(logn)$





---

### 离散链表（动态开点）懒标记模板

```c++
const int maxn = 1e9 + 10;

class Node {           	// 线段树节点
    Node* lNode, rNode;   	// 区间的左右端点,即[l,r]  
    int l, r;   			// 区间的左右端点,即[l,r]  
    int sum;        		// 区间和
    int add;				// 懒标记
    int mid;				// 构造的时候就可以捎带计算一下
    
    Node () {}
    Node (int _l, int _r) {
        this->l = _l;
        this->r = _r;
        this->mid = _l + _r >> 1;
        this->sum = 0;
        this->add = 0;
        this->lNode = nullptr;
        this->rNode = nullptr;
    }
};

class SegTree {             // 线段树不一定满二叉树，也不一定是完全二叉树，但一定是平衡二叉树
private:
    Node* root;
    
public:
    SegTree() {
    	root = new Node(0, maxn);    
    }    
    
    void push_up(Node* node) {	// 回溯时更新父结点
        node->sum = node->lNode->sum + node->rNode->.sum;    // 递归往回走的时候 一路上去更新, 更新祖先节点
    }
    
    void push_down(Node* node) {	// 下传懒标记
        if (!node->lNode) node->lNode = new Node(node->l, node->mid);
        if (!node->rNode) node->rNode = new Node(node->mid + 1, node->r);
        if (node->add) { 	// 欠的钱不为 0
            node->lNode->sum += node->add*(node->r - node->l + 1);
            node->rNode->sum += node->add*(node->r - node->l + 1);
            node->lNode->add = node->add;
            node->rNode->add = node->add;
            node->add = 0;
        }        
    }
    
    // 单点修改 递归寻找叶子节点 [x,x], 把该节点的值修改, 并且从下往上更新其组先节点的值
    void modify(int u, int x, int v) { 		// u为根节点索引 x为修改的位置 v为修改的值 
        if (tr[u].l == tr[u].r) { 			// 能满足tr[u].l == tr[u].r == x 叶子节点
            tr[u].sum += v; 				// 进来修改, 求区间和是累加，也可能是直接赋值
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;   // 非叶子节点，裂开
        if (x <= mid) modify(lc, x, v);
        if (x > mid)  modify(rc, x, v);
        push_up(u);				    		// 更新祖先节点
    }
    
    // 区间修改 [x,y] 的和，也可以用于单点修改x=y即可
    void modify(Node* node, int x, int y, int v) { 	// u为根节点索引 x左边界 y右边界 v为修改的值 
        if (x <= node->l && node->r <= y) { 	// 修改区间 [x,y] 完全覆盖当前节点区
            node->sum += (node->r - node->l + 1) * v; 	// 进来修改, 把v累加(tr[u].r - tr[u].l + 1)次
            node->add += v;								// 懒标记 v
            return;
        }
        // 不覆盖裂开
        push_down(node);							// “下次需要”，下传懒标记
        if (x <= node->mid) modify(node->lNode, x, y, v);
        if (x > node->mid)  modify(node->rNode, x, y, v);
        push_up(node);				    			// 向上回溯更新祖先节点
    }

    // 区间查询 [l,r] 的和，利用拆分与拼凑的思想，把大区间变为多个小区间的和
    int query(Node* node, int l, int r) { 			// u为根节点索引 l左边界 r右边界
        if (l <= node->l && node->r <= r)   	// 查询区间 [x,y] 完全覆盖当前节点区
            return node->sum;               	// 间，立即回溯，返回该区间的sum值，让上一层累加
        
        // 非叶子节点，裂开
        int sum = 0;
        if (l <= node->mid) sum += query(node->lNode, l, r); 	// 查询左边界比mid小，左子节点与区间 [x,y] 有重叠，递归访问左子树
        if (r > node->mid) sum += query(node->rNode, l, r);  	// 查询右边界比mid小，右子节点与区间 [x,y] 有重叠，递归访问右子树
        return sum;
    }

};
```







https://leetcode.cn/problems/falling-squares/solution/-by-lcbin-5rop/

```c++
class Node {
public:
    Node* left;
    Node* right;
    int l;
    int r;
    int mid;
    int v;
    int add;

    Node(int l, int r) {
        this->l = l;
        this->r = r;
        this->mid = (l + r) >> 1;
        this->left = this->right = nullptr;
        v = add = 0;
    }
};

class SegmentTree {
private:
    Node* root;

public:
    SegmentTree() {
        root = new Node(1, 1e9);
    }

    void modify(int l, int r, int v) {
        modify(l, r, v, root);
    }

    void modify(int l, int r,int v, Node* node) {
        if (l > r) return;
        if (node->l >= l && node->r <= r)
        {
            node->v = v;
            node->add = v;
            return;
        }
        pushdown(node);
        if (l <= node->mid) modify(l, r, v, node->left);
        if (r > node->mid) modify(l, r, v, node->right);
        pushup(node);
    }

    int query(int l, int r) {
        return query(l, r, root);
    }

    int query(int l, int r, Node* node) {
        if (l > r) return 0;
        if (node->l >= l && node-> r <= r) return node->v;
        pushdown(node);
        int v = 0;
        if (l <= node->mid) v = max(v, query(l, r, node->left));
        if (r > node->mid) v = max(v, query(l, r, node->right));
        return v;
    }

    void pushup(Node* node) {
        node->v = max(node->left->v, node->right->v);
    }

    void pushdown(Node* node) {
        if (!node->left) node->left = new Node(node->l, node->mid);
        if (!node->right) node->right = new Node(node->mid + 1, node->r);
        if (node->add)
        {
            Node* left = node->left;
            Node* right = node->right;
            left->v = node->add;
            right->v = node->add;
            left->add = node->add;
            right->add = node->add;
            node->add = 0;
        }
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> ans;
        SegmentTree* tree = new SegmentTree();
        int mx = 0;
        for (auto& p : positions)
        {
            int l = p[0], w = p[1], r = l + w - 1;
            int h = tree->query(l, r) + w;
            mx = max(mx, h);
            ans.push_back(mx);
            tree->modify(l, r, h);
        }
        return ans;
    }
};
```







https://leetcode.cn/problems/falling-squares/solution/cpython3java-1xian-duan-shu-dong-tai-kai-ed6a/

```c++
struct SegNode {
    int l;
    int r;
    int max_;
    int lazy_max;
    SegNode * left;
    SegNode * right;

    SegNode () {}
    SegNode (int l_, int r_)
    {
        l = l_;
        r = r_;
        max_ = 0;
        lazy_max = 0;
        left = nullptr;
        right = nullptr;
    }
};


class Solution 
{
public:
    SegNode * get_left(SegNode * rt)
    {
        if (rt->left == NULL)
        {
            rt->left = new SegNode(rt->l, (rt->l + rt->r) / 2);
        }
        return rt->left;
    }
    SegNode * get_right(SegNode * rt)
    {
        if (rt->right == NULL)
        {
            rt->right = new SegNode((rt->l + rt->r) / 2 + 1, rt->r);
        }
        return rt->right;
    }

    void push_up(SegNode * rt)
    {
        SegNode * ll = get_left(rt);
        SegNode * rr = get_right(rt);
        rt->max_ = max(ll->max_, rr->max_);
    }
    void push_down(SegNode * rt)
    {
        if (rt->lazy_max != 0)
        {
            int v = rt->lazy_max;
            SegNode * ll = get_left(rt);
            SegNode * rr = get_right(rt);

            ll->lazy_max = v;
            rr->lazy_max = v;
            ll->max_ = max(ll->max_, v);
            rr->max_ = max(rr->max_, v);

            push_up(rt);
            rt->lazy_max = 0;
        }
    }

    void update(SegNode * rt, int ul, int ur, int val)
    {
        if (ul <= rt->l && rt->r <= ur)
        {
            rt->max_ = val;
            rt->lazy_max = val;
            return ;
        }

        int mid = (rt->l + rt->r) / 2;
        SegNode * ll = get_left(rt);
        SegNode * rr = get_right(rt);

        push_down(rt);
        if (ur <= mid)
        {
            update(ll, ul, ur, val);
        }
        else if (mid + 1 <= ul)
        {
            update(rr, ul, ur, val);
        }
        else
        {
            update(ll, ul, ur, val);
            update(rr, ul, ur, val);
        }
        push_up(rt);
    }
    int query(SegNode * rt, int ql, int qr)
    {
        if (ql <= rt->l && rt->r <= qr)
        {
            return rt->max_;
        }

        int mid = (rt->l + rt->r) / 2;
        SegNode * ll = get_left(rt);
        SegNode * rr = get_right(rt);
        push_down(rt);

        if (qr <= mid)
        {
            return query(ll, ql, qr);
        }
        else if (mid + 1 <= ql)
        {
            return query(rr, ql, qr);
        }
        return max(query(ll, ql, qr), query(rr, ql, qr));
    }


    vector<int> fallingSquares(vector<vector<int>>& positions) 
    {
        int INF = (int)(1e9);

        SegNode * root = new SegNode(0, INF);

        vector<int> res;
        for (vector<int> & pos: positions)
        {
            int l = pos[0],    Len = pos[1];
            int r = l + Len - 1;
            int cur_h = query(root, l, r);
            update(root, l, r, cur_h + Len);

            int cur = root->max_;
            res.push_back(cur);
        }

        return res;
    }
};
```





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

### 729. 我的日程安排表 I

```c++
typedef pair<int, int> pii;
class MyCalendar {
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        // 二分优化
        auto it = st.lower_bound(pii(end, -1e-9)); // 找到第一个 A 满足 ARight 比 start 大

        if (it == st.begin() || (--it)->second <= start) {
            st.insert({start, end});
            return true;
        }
        
        return false;
    }

private:
    set<pii> st;    
};
```





---

### 308. 二维区域和检索 - 可变

https://leetcode.cn/problems/range-sum-query-2d-mutable/

```c++
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        n = matrix.size(), m = matrix[0].size();
        vector<int> a;
        for (auto &row : matrix) {
            for (auto &num : row) {
                a.emplace_back(num);
            }
        }
        ST = SegTree(a);
    }
    
    int getId(int x, int y) {
        return x * m + y + 1; // +1 因为ST数组索引从1开始
    }

    void update(int row, int col, int val) {
        ST.modify(1, getId(row, col), val);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int ans = 0;

        // 因为 getId(i, col1) 到 getId(i, col2) 不是连续的，所以要单独计算每行连续的
        // 如果是连续的，可以直接 ans = ST.ask(1, getId(row1, col1), getId(row2, col2), true);
        for (int i = row1; i <= row2; ++i) {
            // ans += ST.ask(1, getId(i, col1), getId(i, col2)).sum;
            ans += ST.ask(1, getId(i, col1), getId(i, col2), true);
        }
        return ans;
    }   

private:
    int n, m;
    SegTree ST;
};
```





----

### 731. 我的日程安排表 II

利用线段树，假设我们开辟了数组 arr[0,⋯,1e9]，初始时每个元素的值都为 0，对于每次行程预定的区间 [start,end) ，则我们将区间中的元素  arr[start,⋯,end−1] 中的每个元素加 1，如果数组 arr 的最大元素大于 2时，此时则出现某个区间被安排了 2 次上，此时返回 false，同时将数组区间 arr[start,⋯,end−1] 进行减 1 即可恢复。实际我们不必实际开辟数组 arr，可采用动态线段树，懒标记 lazy 标记区间 `[l,r]` 进行累加的次数，tree 记录区间 `[l,r]` 的最大值，每次动态更新线段树即可。



```c++
class MyCalendarTwo {
public:
    MyCalendarTwo() {

    }

    void update(int start, int end, int val, int l, int r, int idx) {
        if (r < start || end < l) {
            return;
        } 
        if (start <= l && r <= end) {
            tree[idx].first += val;
            tree[idx].second += val;
        } else {
            int mid = (l + r) >> 1;
            update(start, end, val, l, mid, 2 * idx);
            update(start, end, val, mid + 1, r, 2 * idx + 1);
            tree[idx].first = tree[idx].second + max(tree[2 * idx].first, tree[2 * idx + 1].first);
        }
    }

    bool book(int start, int end) {            
        update(start, end - 1, 1, 0, 1e9, 1);
        if (tree[1].first > 2) {
            update(start, end - 1, -1, 0, 1e9, 1);
            return false;
        }
        return true;
    }
private:
    unordered_map<int, pair<int, int>> tree;
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





