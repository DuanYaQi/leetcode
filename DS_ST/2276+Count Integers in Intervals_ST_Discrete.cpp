const int maxn = 1e9 + 10;
const int maxnn = 1e6 + 1e5;

class SegTree {             // 线段树不一定满二叉树，也不一定是完全二叉树，但一定是平衡二叉树
public:
    struct Node {           	// 线段树节点
        int l, r;   			// 区间的左右端点,即[l,r] 
        int lNode, rNode;       // 区间的左右孩子索引 
        int val;               // 是否覆盖
        int add;				// 懒标记
        int mid;				// 构造的时候就可以捎带计算一下
    }tr[maxnn] {};

    int idx = 0;
    SegTree() {   
    	tr[++idx] = {0, maxn, 0, 0, 0, 0, (1 + maxn >> 1)};
    }    
    
    void push_up(Node &node) {	// 回溯时更新父结点
        node.val = tr[node.lNode].val + tr[node.rNode].val;    // 递归往回走的时候 一路上去更新, 更新祖先节点
    }
    
    void push_down(Node &node) {	// 下传懒标记
        if (!node.lNode) {
            node.lNode = ++idx;
            int ll = node.l, rr = (node.l + node.r) >> 1;
            int midd = ll + rr >> 1;
            tr[idx] = {ll, rr, 0, 0, 0, 0, midd};
        }
        if (!node.rNode) {
            node.rNode = ++idx;
            int ll = ((node.l + node.r) >> 1) + 1, rr = node.r;
            int midd = ll + rr >> 1;
            tr[idx] = {ll, rr, 0, 0, 0, 0, midd};
        }

        if (node.add != 0) {
            tr[node.lNode].val = (node.mid - node.l + 1) * node.add; 
            tr[node.rNode].val = (node.r - node.mid) * node.add;
            tr[node.lNode].add = node.add;
            tr[node.rNode].add = node.add;
            node.add = 0; 
        }  
    }
    
    
    // 区间修改 [l,r] 的和，也可以用于单点修改l=y即可
    void modify(Node &node, int l, int r, int v) { 	// u为根节点索引 l左边界 y右边界 v为修改的值 
        if (l <= node.l && node.r <= r) { 	// 修改区间 [l,r] 完全覆盖当前节点区
            node.val = (node.r - node.l + 1) * v; 	// 进来修改, +=
            node.add = v;						            // 懒标记 v  +=
            return;
        }
        // 不覆盖裂开
        push_down(node);							// “下次需要”，下传懒标记
        if (l <= node.mid) modify(tr[node.lNode], l, r, v);
        if (r > node.mid)  modify(tr[node.rNode], l, r, v);
        push_up(node);				    			// 向上回溯更新祖先节点
    }

    // 区间查询 [l,r] 的和，利用拆分与拼凑的思想，把大区间变为多个小区间的和
    int query(Node &node, int l, int r) { 			// u为根节点索引 l左边界 r右边界
        if (l <= node.l && node.r <= r)   	// 查询区间 [l,r] 完全覆盖当前节点区
            return node.val;               	// 间，立即回溯，返回该区间的sum值，让上一层累加
        
        // 非叶子节点，裂开
        push_down(node);							// “下次需要”，下传懒标记
        int res = 0;
        if (l <= node.mid) res += query(tr[node.lNode], l, r); 	// 查询左边界比mid小，左子节点与区间 [l,r] 有重叠，递归访问左子树
        if (r > node.mid) res += query(tr[node.rNode], l, r);  	// 查询右边界比mid小，右子节点与区间 [l,r] 有重叠，递归访问右子树
        return res;
    }

};

class CountIntervals {
public:
    CountIntervals() {

    }
    
    void add(int left, int right) {
        ST.modify(ST.tr[1], left, right, 1);
    }
    
    int count() {
        return ST.query(ST.tr[1], 0, maxn);
    }

private:
    SegTree ST;
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */