# 树

## 1. 二叉树

### 1.1. 种类

#### 1.1.1. 满二叉树

如果一棵树只有**度**为 **0** 的 **2** 的结点，并且度为 0 的结点在同一层上，则这棵二叉树为满二叉树。



#### 1.1.2. 完全二叉树

除了最底层节点可能没被填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最**左**边的若干位置。若最底层为第h层，则该层节点数范围为  $1$ ~ $2^h-1$ 个。

![1615869609545](assets/1615869609545.png)

优先级队列起始是一个堆，堆就是一颗完全二叉树，同时保证父子节点的顺序关系。



#### 1.1.3. 二叉搜索树

二叉搜索树是有**数值**的，且是一个**有序**树。

- 若其左子树不空，则左子树所有结点的值均小于它的根节点的值；
- 若其右子树不空，则右子树所有结点的值均大于它的根节点的值；
- 其左右子树也分别为二叉排序树。

![1615869776230](assets/1615869776230.png)

上两棵都是二叉搜索树



#### 1.1.4. 平衡二叉搜索树

AVL（Adelson-Velsky and Landis）树，它是一棵空树或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一颗平衡二叉树。

![1615869887421](assets/1615869887421.png)

​	最后一棵高度差超过1.



C++中**map、set、multimap，multiset**的底层实现都是**平衡二叉搜索树**。所有map、set的增删操作时间复杂度都是 `log(n)`，特别的**unordered_map、unordered_set**底层实现为**哈希表**。



---

### 1.2. 存储方式

链式存储，指针，不连续

顺序存储，数组，连续

​	父节点数组下标为 `i`， 左孩子为`i*2+1` ，右孩子为 `i*2 + 2`



----

### 1.3. 定义

```c++
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};
```



---

### 1.4. 遍历方式

深度优先遍历：先往深走，遇到叶子节点再往回走

- 前序遍历 递归、迭代   中左右
- 中序遍历 递归、迭代   左中右
- 后序遍历 递归、迭代   左右中（需要知道子树信息的一定是后序遍历）

广度优先遍历：一层一层的遍历.

- 层次遍历 迭代



#### 1.4.1. 递归遍历

递归三要素

1. **确定递归函数的参数和返回值**：确定哪些参数是递归过程中需要处理的，就在函数中加此参数。并且还要明确每次递归的返回值，确定递归函数返回类型。
2. **确定终止条件**：防止栈溢出。
3. **确定单层递归的逻辑**：确定每层递归要处理的信息。



确定递归函数的参数和返回值：

[94. Binary Tree Inorder Traversal](94+inorderTraversal.cpp)

[144. Binary Tree Preorder Traversal](144+preorderTraversal.cpp)

[145. Binary Tree Postorder Traversal](145+postorderTraversal.cpp)



#### 1.4.2. 迭代遍历

递归的实现：每一次递归第调用都会把函数的局部变量、参数值和返回地址等**压入调用栈**中，递归返回时，从栈顶弹出上一次递归的各项参数。

**注意空节点不入栈**

前序

```c++
vector<int> preorderTraversal (TreeNode* root) {
  	stack<TreeNode*> st;
    vector<int> res;
    if (!root) return res;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        res.push_back(node->value);
        if (node->right) st.push(node->right); //空节点不如栈 
        if (node->left)  st.push(node->left);  //栈先进后出 所有最后压左子树
    }
    return res;
}
```

中序 借助指针的遍历来帮助访问节点，栈用来处理节点上的元素。

```c++
vector<int> inorderTraversal (TreeNode* root) {
  	stack<TreeNode*> st;
    vector<int> res;
	TreeNode* cur = root;
    while (cur != NULL || !st.empty()) {
        if (cur != NULL) {
        	st.push(cur);
            cur = cur->left;
    	} else {
        	cur = st.top();
            st.pop();
            res.push_back(cur->val);
            cur = cur->right;
        }
    }
    return res;
}
```

后序

```c++

```

