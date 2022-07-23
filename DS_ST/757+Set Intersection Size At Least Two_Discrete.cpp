const int maxn = 1e9 + 10;
const int maxnn = 5e5;

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

        if (node.add == 0) { return; } 
        else if (node.add == 1) {
            tr[node.lNode].val = node.add == 1 ?  (tr[node.lNode].r - tr[node.lNode].l + 1) : 0; 
            tr[node.rNode].val = node.add == 1 ?  (tr[node.rNode].r - tr[node.rNode].l + 1) : 0;
            tr[node.lNode].add = node.add;
            tr[node.rNode].add = node.add;
            node.add = 0;  
        }  
    }
    
    
    // 区间修改 [l,r] 的和，也可以用于单点修改l=y即可
    void modify(Node &node, int l, int r, bool v) { 	// u为根节点索引 l左边界 y右边界 v为修改的值 
        if (l <= node.l && node.r <= r) { 	// 修改区间 [l,r] 完全覆盖当前节点区
            node.val = v == 1 ? (node.r - node.l + 1) : 0; 	// 进来修改, +=
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

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        //ST = SegTree();
        sort(intervals.begin(), intervals.end(), [] (vector<int> &v1, vector<int> &v2) {
            if(v1[1] != v2[1]) return v1[1] < v2[1];
            return v1[0] < v2[0];
        });

        for(auto it : intervals) {
            int l = it[0], r = it[1];
            int cnt = ST.query(ST.tr[1], l, r);
            if(cnt == 1) {
                for(int i = r; i >= l; i--) {
                    if(ST.query(ST.tr[1], i, i) == 0) {
                        ST.modify(ST.tr[1], i, i, 1);
                        break;
                    }
                }
            } else if(cnt == 0) {
                ST.modify(ST.tr[1], r, r, 1);
                ST.modify(ST.tr[1], r - 1, r - 1, 1);
            }
        }
        return ST.query(ST.tr[1], 0, maxn);
    }
private:
    SegTree ST;
};