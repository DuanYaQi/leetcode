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
        tr[u] = {l, r};     // 赋值左右边界
        if (l == r) {       // 是叶子节点
            tr[u].sum = a[l - 1];// 赋值返回，因为下标从1开始，所以是l-1
            return;
        }

        int mid = l + r >> 1;       // 不是叶子节点，裂开
        build(lc, l, mid);          // lc = u<<1
        build(rc, mid + 1, r);      // rc = u<<1|1
        push_up(u);				    // 更新祖先节点
    }

    // 递归寻找叶子节点 [x,x], 把该节点的值修改, 并且从下往上更新其组先节点的值
    void modify(int u, int x, int v) { // u为根节点索引 x为修改的位置 v为修改的值 
        if (tr[u].l == tr[u].r) { // 能满足tr[u].l == tr[u].r == x
            tr[u].sum = v; // 进来修改
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(lc, x, v);
        if (x > mid)  modify(rc, x, v);
        push_up(u);				    // 更新祖先节点
    }

    // 查询区间 [l,r] 的和，利用拆分与拼凑的思想，把大区间变为多个小区间的和
    int query(int u, int l, int r) { // u为根节点索引 l左边界 r右边界
        if (l <= tr[u].l && tr[u].r <= r)   // 查询区间 [x,y] 完全覆盖当前节点区
            return tr[u].sum;               // 间，立即回溯，返回该区间的sum值，让上一层累加
        
        int mid = tr[u].l + tr[u].r >> 1;
        int sum = 0;
        if (l <= mid) sum += query(lc, l, r); // 左子节点与区间 [x,y] 有重叠，递归访问左子树
        if (r > mid) sum += query(rc, l, r);  // 右子节点与区间 [x,y] 有重叠，递归访问右子树
        return sum;
    }

};

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
            ans += ST.query(1, getId(i, col1), getId(i, col2));
        }
        return ans;
    }   

private:
    int n, m;
    SegTree ST;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */