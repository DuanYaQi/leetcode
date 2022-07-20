const int maxn = 1e9 + 10;

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
        node->maxv = max(node->lNode->maxv, node->rNode->maxv);    // 递归往回走的时候 一路上去更新, 更新祖先节点
    }
    
    void push_down(Node* node) {	// 下传懒标记
        if (!node->lNode) node->lNode = new Node(node->l, node->mid);
        if (!node->rNode) node->rNode = new Node(node->mid + 1, node->r);
        if (node->add) { 	// 欠的钱不为 0
            node->lNode->maxv += node->add;  // +=
            node->rNode->maxv += node->add;
            node->lNode->add += node->add;
            node->rNode->add += node->add;
            node->add = 0;
        }        
    }
    
    
    // 区间修改 [l,r] 的和，也可以用于单点修改l=y即可
    void modify(Node* node, int l, int r, int v) { 	// u为根节点索引 l左边界 y右边界 v为修改的值 
        if (l <= node->l && node->r <= r) { 	// 修改区间 [l,r] 完全覆盖当前节点区
            node->maxv += v; 	                // 进来修改, +=
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
        if (l <= node->mid) res = max(res, query(node->lNode, l, r)); 	// 查询左边界比mid小，左子节点与区间 [l,r] 有重叠，递归访问左子树
        if (r > node->mid) res = max(res, query(node->rNode, l, r));  	// 查询右边界比mid小，右子节点与区间 [l,r] 有重叠，递归访问右子树
        return res;
    }

};


class MyCalendar {
public:
    MyCalendar() {
        ST = SegTree();
    }
    
    bool book(int start, int end) {
        int maxnum = ST.query(ST.root, start, end-1);

        if (maxnum == 1) return false;
        ST.modify(ST.root, start, end-1, 1);
        return true; 
    }

private:
    SegTree ST;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */