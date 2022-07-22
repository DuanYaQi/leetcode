const int maxn = 1e8 + 10;

class Node {           	// 线段树节点
public:
    Node *lNode, *rNode;   	// 区间的左右端点,即[l,r]  
    int l, r;   			// 区间的左右端点,即[l,r]  
    int maxv;               // 区间最大值
    int add;				// 懒标记
    int mid;				// 构造的时候就可以捎带计算一下
    
    Node () {}
    Node (int _l, int _r) {
        this->l = _l;
        this->r = _r;
        this->mid = _l + _r >> 1;
        this->maxv = 0;
        this->add = 0;
        this->lNode = nullptr;
        this->rNode = nullptr;
    }
};

class SegTree {             // 线段树不一定满二叉树，也不一定是完全二叉树，但一定是平衡二叉树
public:
    Node* root;

    SegTree() {
    	root = new Node(0, maxn);    
    }    
    
    void push_up(Node* node) {	// 回溯时更新父结点
        node->maxv = node->lNode->maxv + node->rNode->maxv;    // 递归往回走的时候 一路上去更新, 更新祖先节点
    }
    
    void push_down(Node* node) {	// 下传懒标记
        if (!node->lNode) node->lNode = new Node(node->l, node->mid);
        if (!node->rNode) node->rNode = new Node(node->mid + 1, node->r);
        if (node->add) { 	// 欠的钱不为 0
            node->lNode->maxv += (node->mid - node->l + 1) * node->add;  // +=
            node->rNode->maxv += (node->r - node->mid) * node->add;
            node->lNode->add += node->add;
            node->rNode->add += node->add;
            node->add = 0;
        }        
    }
    
    
    // 区间修改 [l,r] 的和，也可以用于单点修改l=y即可
    void modify(Node* node, int l, int r, int v) { 	// u为根节点索引 l左边界 y右边界 v为修改的值 
        if (l <= node->l && node->r <= r) { 	// 修改区间 [l,r] 完全覆盖当前节点区
            node->maxv += (node->r - node->l + 1) * v; 	                // 进来修改, +=
            node->add += v;						// 懒标记 v  +=
            return;
        }
        // 不覆盖裂开
        push_down(node);							// “下次需要”，下传懒标记
        if (l <= node->mid) modify(node->lNode, l, r, v);
        if (r > node->mid)  modify(node->rNode, l, r, v);
        push_up(node);				    			// 向上回溯更新祖先节点
    }

    // 区间查询 [l,r] 的和，利用拆分与拼凑的思想，把大区间变为多个小区间的和
    int query(Node* node, int l, int r) { 			// u为根节点索引 l左边界 r右边界
        if (l <= node->l && node->r <= r)   	// 查询区间 [l,r] 完全覆盖当前节点区
            return node->maxv;               	// 间，立即回溯，返回该区间的sum值，让上一层累加
        
        // 非叶子节点，裂开
        push_down(node);							// “下次需要”，下传懒标记
        int res = 0;
        if (l <= node->mid) res += query(node->lNode, l, r); 	// 查询左边界比mid小，左子节点与区间 [l,r] 有重叠，递归访问左子树
        if (r > node->mid) res += query(node->rNode, l, r);  	// 查询右边界比mid小，右子节点与区间 [l,r] 有重叠，递归访问右子树
        return res;
    }

};


class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        ST = SegTree();
        sort(intervals.begin(), intervals.end(), [] (vector<int> &v1, vector<int> &v2) {
            if(v1[1] != v2[1]) return v1[1] < v2[1];
            return v1[0] < v2[0];
        });
        
        for(auto it : intervals) {
            int l = it[0], r = it[1];
            int cnt = ST.query(ST.root, l, r);  
            if(cnt == 1) {  // 只跟一个点有交集
                for(int i = r; i >= l; i--) {   // 贪心的找到最右边不相交的点并修改
                    if(ST.query(ST.root, i, i) == 0) {
                        ST.modify(ST.root, i, i, 1);
                        break;
                    }
                }
            } else if(cnt == 0) {   // 没有任何元素被覆盖 贪心地将r和r-1覆盖，因为交集要求2，所以覆盖两个
                ST.modify(ST.root, r, r, 1);
                ST.modify(ST.root, r - 1, r - 1, 1);
            }
            // 如果 cnt >= 2 则说明这个区间里有两个点跟他是交集，跳过即可
        }
        return ST.query(ST.root, 0, maxn); //查询的是区间里有几个点跟他是交集
    }
private:
    SegTree ST;
};