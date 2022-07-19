const int maxn = 1e9 + 10;

class Node {           	// 线段树节点
public:
    Node *lNode, *rNode;   	// 区间的左右端点,即[l,r]  
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
public:
    Node* root;

    SegTree() {
    	root = new Node(0, maxn);    
    }    
    
    void push_up(Node* node) {	// 回溯时更新父结点
        node->sum = node->lNode->sum + node->rNode->sum;    // 递归往回走的时候 一路上去更新, 更新祖先节点
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
    void modify(Node* node, int x, int v) { 		// u为根节点索引 x为修改的位置 v为修改的值 
        if (node->l == node->r) { 			// 能满足tr[u].l == tr[u].r == x 叶子节点
            node->sum += v; 				// 进来修改, 求区间和是累加，也可能是直接赋值
            return;
        }
        // 非叶子节点，裂开
        if (x <= node->mid) modify(node->lNode, x, v);
        if (x > node->mid)  modify(node->rNode, x, v);
        push_up(node);				    		// 更新祖先节点
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

class MyCalendarTwo {
public:
    MyCalendarTwo() {
        ST = SegTree();
    }
    
    bool book(int start, int end) {
        ST.modify(ST.root, start, end - 1, 1);
        
        for (int i = start; i < end; ++i) {
            if (ST.query(ST.root, i, i) > 2) {
                ST.modify(ST.root, start, end - 1, -1);
                return false;
            }
        }
        return true;        
    }

private:
    SegTree ST;    
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */