# 树/二叉树

## 1. 种类

### 1.1. 满二叉树

国内定义：除最后一层无任何子节点外，每一层上的所有结点都有两个子结点的二叉树。满二叉树外观上是一个**三角形**。

国外定义：如果一棵树只有**度**为 **0** 的 **2** 的结点，并且度为 0 的结点在同一层上，则这棵二叉树为满二叉树。



### 1.2. 完全二叉树

除了最底层节点可能没被填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最**左**边的若干位置。若最底层为第h层，则该层节点数范围为  $1$ ~ $2^h-1$ 个。

![1615869609545](assets/1615869609545.png)

优先级队列起始是一个堆，堆就是一颗完全二叉树，同时保证父子节点的**顺序**关系。



### 1.3. 二叉搜索树

二叉搜索树是有**数值**的，且是一个**有序**树。

- 若其左子树不空，则左子树所有结点的值均小于它的根节点的值；
- 若其右子树不空，则右子树所有结点的值均大于它的根节点的值；
- 其左右子树也分别为二叉排序树。

![1615869776230](assets/1615869776230.png)

上两棵都是二叉搜索树



### 1.4. 平衡二叉搜索树

AVL（Adelson-Velsky and Landis）树，它是一棵空树或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一颗平衡二叉树。

![1615869887421](assets/1615869887421.png)

​	最后一棵高度差超过1.



C++中**map、set、multimap，multiset**的底层实现都是**平衡二叉搜索树**。所有map、set的增删操作时间复杂度都是 `log(n)`，特别的**unordered_map、unordered_set**底层实现为**哈希表**。



### 1.5. Complete/Perfect/Full

国外定义的**满**二叉树 Full Binary Tree 是指一棵二叉树的所有节点要么**没有孩子节点**，要么有**两个孩子节点**；

**完全**二叉树对应 Complete Binary Tree；有**顺序**限制。

**国内**定义的**满**二叉树 Perfect Binary Tree是指除最后一层无任何子节点外，每一层上的所有结点都有两个子结点的二叉树。

![img](assets/trees.png)



---

## 2. 存储方式

链式存储，指针，不连续

顺序存储，数组，连续	父节点数组下标为 `i`， 左孩子为`i*2+1` ，右孩子为 `i*2 + 2`



----

## 3. 定义

```c++
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};
```



---

## 4. 遍历方式

深度优先遍历：先往深走，遇到叶子节点再往回走

- 前序遍历 递归、迭代   中左右
- 中序遍历 递归、迭代   左中右
- 后序遍历 递归、迭代   左右中（需要知道子树信息的一定是后序遍历）

广度优先遍历：一层一层的遍历.

- 层次遍历 迭代



---

### 4.1. 递归遍历

递归三要素

1. **确定递归函数的参数和返回值**：确定哪些参数是递归过程中需要处理的，就在函数中加此参数。并且还要明确每次递归的返回值，确定递归函数返回类型。
2. **确定终止条件**：防止栈溢出。
3. **确定单层递归的逻辑**：确定每层递归要处理的信息。



确定递归函数的参数和返回值：

[94. Binary Tree Inorder Traversal](94+inorderTraversal.cpp)

[144. Binary Tree Preorder Traversal](144+preorderTraversal.cpp)

[145. Binary Tree Postorder Traversal](145+postorderTraversal.cpp)



---

### 4.2. 迭代遍历

递归的实现：每一次递归第调用都会把函数的局部变量、参数值和返回地址等**压入调用栈**中，递归返回时，从栈顶弹出上一次递归的各项参数。

**注意空节点不入栈**

#### 前序

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

#### 中序 

借助指针的遍历来帮助访问节点，栈用来处理节点上的元素。

```c++
vector<int> inorderTraversal (TreeNode* root) {
  	stack<TreeNode*> st;
    vector<int> res;
	TreeNode* cur = root;
    while ( !cur || !st.empty()) {
		if (!cur) {
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

#### 后序

```c++
vector<int> PostorderTraversal (TreeNode* root) {
    stack<TreeNode*> st;
    vector<int> res;
    if (!root) return res;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        res.push_back(node->value);
        if (node->left)  st.push(node->left);  //栈先进后出 所有最后压左子树
        if (node->right) st.push(node->right); //空节点不如栈 
    }
    reverse(res.begin(), res.end());//反转 左右中
    return res;
}
```

这样的风格不统一。



---

### 4.3. 统一迭代遍历

将访问的节点放入栈中，把要处理的节点也放入栈中，但是做标记。

即要处理的节点放入栈之后，**紧接着放入一个空指针作为标记**。**标记法**

#### 中序

```c++
// 左中右 压栈为 右中左
vector<int> inorderTraversal(TreeNode* root) {
    vecotr<int> res;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        if (node != NULL) {
            st.pop(); //弹出，避免重复操作，再将右中左节点添加到栈中
            if (node->right) st.push(node->right);	// 添加右节点
            st.push(node);							// 添加中节点
            st.push(NULL);							// 访问过中节点，但是还没有处理，加入空做标记
            	
            if (node->left) st.push(node->left);	// 添加左节点
        } else {			// 遇到空节点时，将下一个节点放进结果集
            st.pop();		
            node = st.top();
            st.pop();
            res.push_back(node->val);
        }
    }
    return res;
}
```



#### 前序

```c++
// 中左右 压栈为 右左中
vector<int> PreTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
    	TreeNode* node = st.top();
        if (node != NULL) {
            st.pop();
            if (node->right) 	st.push(node->right);
            if (node->left) 	st.push(node->left);
            st.push(node); 	//放中节点，
            st.push(NULL);	//访问过加null
        } else {
            st.pop();
            node = st.top();
            st.pop();
            res.push_back(node->val);
        }
    }
    return res;
}
```



#### 后序

```c++
// 左右中 压栈为 中右左
vector<int> PreTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
    	TreeNode* node = st.top();
        if (node != NULL) {
            /* 可省略
            st.pop();
            st.push(node); 	//放中节点，
            */
            st.push(NULL);	//访问过加null
            if (node->right) 	st.push(node->right);
            if (node->left) 	st.push(node->left);
        } else {
            st.pop();
            node = st.top();
            st.pop();
            res.push_back(node->val);
        }
    }
    return res;
}
```



---

### 4.4. 层序遍历

#### 自顶向下

即逐层的，从左到右访问所有节点

需要借助一个辅助数据结构即**队列**来实现，队列先进先出，符合一层一层**宽度优先遍历**的逻辑（用**栈**先进后出是模拟**深度优先遍历**也就是**递归**的逻辑。）

```c++
vector<vector<int>> levelOrder(TreeNode* root) {
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<vector<int>> res;
    while (!que.empty()) {
        int size = que.size();
        vector<int> vec;

        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();	//注意这个在循环里
            que.pop();
            vec.push_back(node->val);
            if (node->left)   que.push(node->left);
            if (node->right)  que.push(node->right);
        }
        res.push_back(vec);
    }
    return res;
} 
```



#### 自底向上

```c++
自顶向下处理后 直接反转 
reverse();
```



#### 习题

**199. binary tree right side view** 二叉树的右视图



```c++
vector<int> rightSideView(TreeNode* root) {
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<int> res;

    while (!que.empty()) {
        int size = que.size();

        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            if (i == size-1 ) res.push_back(node->val);
            if (node->left)   que.push(node->left);
            if (node->right)  que.push(node->right);
        }
    }
    return res;
}
```



**637. Average of Levels in Binary Tree** 二叉树的层平均值

```c++
vector<double> averageOfLevels(TreeNode* root) {
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);
    vector<double> res;

    while (!que.empty()) {
        int size = que.size();
        double asum = 0;	//!!!!!!!!!!!!!注意清零
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            asum += node->val;
            if (node->left)   que.push(node->left);
            if (node->right)  que.push(node->right);
        }
        res.push_back(double(asum/size));
    } 
    return res;
}  
```



**429. N-ary Tree Level Order Traversal**  N叉树的层序遍历

```c++
vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        queue<Node*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            Node* node = que.front();
            vector<int> vec;
            int size = que.size();

            for (int i = 0; i < size; ++i) {
                Node* node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (!node->children.empty()) {
                    int vsize = node->children.size();
                    for (int j = 0; j < vsize; ++j) {
                        que.push(node->children[j]);
                    }
                }    
            }
            res.push_back(vec);
        }
        return res;
    }
```



**515.Find Largest Value in Each Tree Row** 在每个树行中找最大值

```c++
vector<int> largestValues(TreeNode* root) {
    vector<int> res;
    queue<TreeNode*> que;
    if (root != NULL) que.push(root);

    while (!que.empty()) {
        TreeNode* node = que.front();
        int size = que.size();
        int flag = 0x80000000; //INT_MIN

        for (int i = 0; i < size; ++i) {
            TreeNode* node = que.front();
            que.pop();
            flag = node->val > flag ? node->val : flag;
            if (node->left)     que.push(node->left);
            if (node->right)    que.push(node->right);
        }
        res.push_back(flag);
    }
    return res;
}
```



**116. Populating Next Right Pointers in Each Node** 填充每个节点的下一个右侧节点指针

```c++
Node* connect(Node* root) {
    queue<Node*> que;
    if (root != NULL) que.push(root);
    while (!que.empty()) {
        int size = que.size();
        Node* node;
        Node* prenode;

        for (int i = 0; i < size; ++i) {
            if (i == 0) {
                prenode = que.front();
                que.pop();
                node = prenode;
            } else {
                node = que.front();
                que.pop();
                prenode->next = node;
                prenode = prenode->next;
            }
            if (node->left)     que.push(node->left);
            if (node->right)    que.push(node->right);
        }
        prenode->next = NULL; 	// prenode 或者 node 都可以
    }
    return root;
}
```





**117. Populating Next Right Pointers in Each Node II** 填充每个节点的下一个右侧节点指针 II

```c++
与116一模一样
```



---

## 5.  翻转二叉树

**226. Invert Binary Tree**

```c++
TreeNode* invertTree(TreeNode* root) {
    if (root == NULL) return root;
    TreeNode* tmp = root->right;
    root->right = root->left;
    root->left = tmp;
    // swap(root->left, root->right)
    invertTree(root->left);
    invertTree(root->right);
    return root;
}
```

针对二叉树的问题，解题前，想清楚究竟是**前中后层序哪种遍历**。



迭代的写法，保证原来的迭代遍历，只是把节点加入容器之后，再进行swap更换位置。

节点加入容器，是为了后续继续遍历。



---

## #1-5. 小结

**红黑树**就是一种**二叉平衡搜索树**，C++中 `map、multimap、set、multiset` 的底层实现机制就是二叉平衡搜索树，再具体就是红黑树

树的遍历有一种很厉害的方法 **morris遍历**

递归写法。**实际项目开发中，避免递归**。因为项目代码参数、调用关系都比较复杂，不容易控制递归深度，甚至会栈溢出。

栈实现递归写法（即迭代）

**栈实现递归写法（迭代统一）**。一定要掌握前后中序一种迭代的写法，面试官看写出了递归，会进一步考察能不能写出相应的迭代。





---

# 二叉树的属性

---

## 6. 对称二叉树

比较两个子树的里侧和外侧的元素是否相等。

**后序遍历**，一个树遍历顺序是左右中，另一个是右左中。

![image-20220225095910153](assets/image-20220225095910153.png)

因为要遍历两棵树⽽且要**⽐较内侧和外侧节点**，所以准确的来说是**⼀个树的遍历顺序是左右中**，**⼀个树的遍历顺序是右左中**。



**101. Symmetric Tree**

```c++
bool compare(TreeNode* left, TreeNode* right) {
    if (left == NULL && right != NULL) return false;
    else if (left != NULL && right == NULL) return false;
    else if (left == NULL && right == NULL) return true;
    else if (left->val != right->val) return false; 
    else return compare(left->left, right->right) && compare(left->right, right->left);
}

bool isSymmetric(TreeNode* root) {
    if (root == NULL) return true;
    return compare(root->left, root->right);
}
```



迭代法

```c++
bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    queue<TreeNode*> que;
    que.push(root->left);
    que.push(root->right);

    while (!que.empty()) {
        TreeNode* nodeL = que.front(); que.pop();
        TreeNode* nodeR = que.front(); que.pop();

        if (nodeL == nullptr && nodeR == nullptr) continue;
        if (nodeL == nullptr || nodeR == nullptr || (nodeL->val != nodeR->val)) return false;

        que.push(nodeL->left);
        que.push(nodeR->right);
        que.push(nodeL->right);
        que.push(nodeR->left);
    }
    return true;
}
```

这个迭代法，其实是把**左右两个⼦树要⽐较的元素顺序放进⼀个容器**，然后**成对成对的取出来进⾏⽐较**，那么其实使⽤栈也是可以的。



```c++
bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    stack<TreeNode*> st;
    st.push(root->left);
    st.push(root->right);

    while (!st.empty()) {
        TreeNode* nodeL = st.top(); st.pop();
        TreeNode* nodeR = st.top(); st.pop();

        if (nodeL == nullptr && nodeR == nullptr) continue;
        if (nodeL == nullptr || nodeR == nullptr || nodeL->val != nodeR->val) return false;

        st.push(nodeL->left);
        st.push(nodeR->right);
        st.push(nodeL->right);
        st.push(nodeR->left);
    }
    return true;
}
```





---

## 7. 二叉树的深度

**104. Maximum Depth of Binary Tree**

最⼤深度是指从根节点到最远叶⼦节点的最⻓路径上的节点总数。

```c++
int maxDepth(TreeNode* root) {
    if (root==NULL) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
```



**111. Minimum Depth of Binary Tree**

最⼩深度是从**根节点**到最近**叶⼦节点**的最短路径上的节点数量。

说明: 叶⼦节点是指没有⼦节点的节点。

```c++
int minDepth(TreeNode* root) {
    if (root == NULL) return 0;

    int lDepth = minDepth(root->left);
    int rDepth = minDepth(root->right);

    if (root->left == NULL && root->right != NULL) return 1 + rDepth;
    if (root->left != NULL && root->right == NULL) return 1 + lDepth;
    
    return lDepth > rDepth ? 1 + rDepth : 1 + lDepth;
}
```



```c++
int minDepth(TreeNode* root) {
    queue<TreeNode*> que;
    if (root == nullptr) return 0;
    que.push(root);
    int depth = 0;

    while (!que.empty()) {
        int size = que.size();
        depth++;
        for (int i = 0; i < size; ++i) {
            TreeNode* node = que.front();
            que.pop();

            if (node->left != nullptr) que.push(node->left);
            if (node->right != nullptr) que.push(node->right);

            if (node->left == nullptr && node->right == nullptr) return depth;  //提前找到叶子节点 就可以退出了
        }

    }
    return depth;
}
```



---

## 8. 二叉树节点数

**222. Count Complete Tree Nodes**

完全二叉树

判断其左右子树是否为完全二叉树，是的话直接计算深度并且 `2^h-1`

```c++
int countNodes(TreeNode* root) {
    if (root == NULL) return 0;
    TreeNode* l = root->left;
    TreeNode* r = root->right;
    int ldepth = 1;
    int rdepth = 1;

    while (l) {
        ++ldepth;
        l = l->left;
    }

    while (r) {
        ++rdepth;
        r = r->right;
    }

    if (ldepth == rdepth) {
        return pow(2, ldepth) - 1;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}
```



## 9. 二叉树的高度/平衡二叉树

左右两个子树的高度差的绝对值不超过1

```c++
int getHeight(TreeNode* node) {
    if (node == NULL) return 0;

    int lheight = getHeight(node->left);
    if (lheight == -1) return -1;
    int rheight = getHeight(node->right);
    if (rheight == -1) return -1;

    if (abs(lheight - rheight) > 1) return -1;

    return 1 + max(lheight, rheight);
}

bool isBalanced(TreeNode* root) {
    return getHeight(root)==-1 ? false : true;
}
```

![1616324886994](assets/1616324886994.png)

求深度从上到下查，前序遍历。求高度从下到上查，后序遍历。最大深度也就是根的高度，也用后序遍历。



## 10. 二叉树的所有路径

```c++
void dps (TreeNode* root, vector<string> &res, string ans) {
    TreeNode* l = root->left;
    TreeNode* r = root->right;

    if (!l && !r) {
        res.push_back(ans); 
        return;
    }   

    if (l!=NULL) {
        dps(l, res, ans + "->" + to_string(l->val));
    }

    if (r!=NULL) {
        dps(r, res, ans + "->" + to_string(r->val));
    }   

    return;
}

```

回溯递归是一一对应的，有一个递归，就要有一个回溯



## #6-10. 小结





---

## 11. 左叶子之和

**404. 左叶子之和**

```c++
int sumOfLeftLeaves(TreeNode* root) {
    if ( root == NULL ) return 0;

    int leftnum = sumOfLeftLeaves( root->left );;
    int rightnum = sumOfLeftLeaves( root->right );

    int midnum = 0;
    if ( root->left && !root->left->left && !root->left->right ) {
        midnum = root->left->val;
    }

    return midnum + leftnum + rightnum;
}
```

递归 后序，因为要通过递归函数的返回值累加求取左叶子数值之和。

**需要通过节点的父节点判断本节点的属性。**



---

## 12. 树左下角的值

**513. 找树左下角的值**

```c++
int findBottomLeftValue(TreeNode* root) {
    if (root == NULL) return 0;
    queue<TreeNode*> que;
    que.push(root);
    int res = 0;

    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; ++i) {
            TreeNode* node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
            if (i == 0) res = node->val;
        }         
    }

    return res;
}
```

**在最后一行，找到最左边的值。**



如果需要遍历整棵树，递归函数就不能有返回值。如果需要遍历某一条固定路线，递归函数就一定要有返回值！



## 13. 路径总和



**112. 路经总和**

```c++
bool traversal(TreeNode* root, int targetSum, int count) {
    if (!root->left && !root->right && count == targetSum) {    //遇到叶子结点且值相同,即找到路径 直接返回true
        return true;
    }

    if (!root->left && !root->right) {      //遇到叶子结点但值不同,没有找到路径 返回false
        return false;
    }

    if (root->left) {       // 处理左节点
        if (traversal(root->left, targetSum, count + root->left->val)) return true;
    }

    if (root->right) {      // 处理右节点
        if (traversal(root->right, targetSum, count + root->right->val)) return true;
    }

    return false;
}

bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == NULL) return false;
    return traversal(root, targetSum, root->val);
}
```

**遍历的路线，不要求遍历整颗树，所以递归函数需要返回值。**



**113. 路径总和II**

```c++
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    if(root == NULL) return res;
    tmp.push_back(root->val);
    traversal(root, targetSum, root->val);
    return res;
}


vector<vector<int>> res;
vector<int> tmp;
void traversal(TreeNode* root, int targetSum, int count) {
    if (!root->left && !root->right && count == targetSum) {
        res.push_back(tmp);
        return;
    }

    if (!root->left && !root->right) {
        return;
    }

    if (root->left) {
        tmp.push_back(root->left->val);
        traversal(root->left, targetSum, count + root->left->val);
        tmp.pop_back();
    }

    if (root->right) {
        tmp.push_back(root->right->val);
        traversal(root->right, targetSum, count + root->right->val);
        tmp.pop_back();
    }

    return;
}
```



**遍历整个树，找到所有路径，所以递归函数不要返回值**



---

# 二叉树的修改与构造

## 14.  构造二叉树

**106. 从中序和后序遍历序列构造二叉树**

```c++
TreeNode* traversal (vector<int>& inorder, int instart, int inend, 
                     vector<int>& postorder, int poststart, int postend) {
    if (inend < instart || postend < poststart) return nullptr;

    int mid = instart;
    int rootval = postorder[postend];
    for (int i = instart; i <= inend; ++i) {
        if (inorder[i] == rootval) {
            mid = i;
            break;
        }
    }

    TreeNode* root = new TreeNode(rootval);
    root->left = traversal(inorder, instart, mid - 1, 
                           postorder, poststart, poststart + mid - instart - 1);
    root->right = traversal(inorder, mid + 1, inend, 
                            postorder, poststart + mid - instart, postend - 1);

    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return traversal(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
};

```

​    `leftsize = index - instart;`

![图片](assets/640.webp)



**105. 从中序和前序遍历序列构造二叉树**

```c++
TreeNode* build(vector<int>& preorder, int prestart, int preend, 
                vector<int>& inorder, int instart, int inend) {
    if (preend < prestart || inend < instart) return nullptr;

    int index;
    for (int i = instart; i < inend; ++i) {
        if (inorder[i] == preorder[prestart]) {
            index = i;
            break;
        }
    } 
	

    TreeNode* root = new TreeNode(preorder[prestart]);
    root->left = build(preorder, prestart + 1, prestart + index - instart,
                       inorder, instart, index - 1);

    root->right = build(preorder, prestart + index - instart + 1, preend,
                        inorder, index + 1, inend);
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return build(preorder, 0 , preorder.size()-1, inorder, 0 ,inorder.size()-1);
}
```

​    `leftsize = index - instart;`

![图片](assets/640-1616562491143.webp)



---

## 15. 构造一颗最大的二叉树

**654. 最大二叉树**

```c++
TreeNode* build(vector<int>& nums, int l, int r) {
    if (l >= r) return nullptr;

    int index = l;
    for (int i = l + 1; i < r; i++) { 
        if (nums[i] > nums[index])  index = i;
    }

    TreeNode* root = new TreeNode(nums[index]);

    root->left = build(nums, l, index);
    root->right = build(nums, index+1, r);
    return root;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return build(nums, 0 ,nums.size());  //左闭右开
}
```



---

## #11-15. 小结

回溯隐藏，函数形参

深度最大一定是叶子节点

下标索引数组，不要新开数组

if控制空节点进不进递归



---

## 16. 合并两个二叉树

**617. 合并二叉树**

```c++
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (root1 == NULL) return root2;
    if (root2 == NULL) return root1;
    root1->val += root2->val;
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);

    return root1;
}
```



```c++
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (root1 == NULL) return root2;
    if (root2 == NULL) return root1;

    queue<TreeNode*> que1;
    queue<TreeNode*> que2;

    que1.push(root1);
    que2.push(root2);


    while (!que1.empty() && !que2.empty()) {
        TreeNode* node1 = que1.front();
        que1.pop();
        TreeNode* node2 = que2.front();
        que2.pop();

        node1->val += node2->val;

        if (node1->left && node2->left) {
            que1.push(node1->left);
            que2.push(node2->left);
        } 

        if (node1->right && node2->right) {
            que1.push(node1->right);
            que2.push(node2->right);
        }

        if (!node1->left && node2->left) {
            node1->left = node2->left;
        }

        if (!node1->right && node2->right) {
            node1->right = node2->right;
        } 
    }

    return root1;
}
```







# 二叉搜索树的属性

## 17. 二叉搜索树中的搜索

**700. 二叉搜索树中的搜索**

```c++
TreeNode* searchBST(TreeNode* root, int val) {
    if (root == NULL) return root;

    if (root->val == val) return root;
    if (root->val < val) return searchBST(root->right, val);
    if (root->val > val) return searchBST(root->left, val);

    return nullptr;
}
```





## 18. 验证二叉搜索树

**98. 验证二叉搜索树**

```c++
bool isValidBST(TreeNode* root) {
    if (root == NULL) return true;  
    traversal(root);

    for (int i = 1; i < res.size(); ++i) {
        if (res[i] <= res[i-1]) return false;
    }
    return true;
}

vector<int> res;    
void traversal(TreeNode* root) {
    if (root == NULL) return;
    traversal(root->left);
    res.push_back(root->val);
    traversal(root->right);
} 
```





## 19. 二叉搜索树的最小绝对差

**530. 二叉搜索树的最小绝对差**

```c++
public:
    int getMinimumDifference(TreeNode* root) {
        if (root == NULL) return 0;
        traversal(root);

        int ans = INT_MAX;
        for (int i = 1; i < res.size(); ++i) {
            ans = res[i] - res[i-1] < ans ? res[i] - res[i-1] : ans;
        }
        return ans;
    }

private: 
    vector<int> res;
    void traversal(TreeNode* root) {
        if (root == NULL) return; 
        traversal(root->left);
        res.push_back(root->val);
        traversal(root->right);
        return;
    }
```



## 20. 二叉搜索树中的众数

**501. 二叉搜索树中的众数**

```c++
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        if (root == NULL) return res;
        traversal(root);
        vector<pair<int, int>> vec(mp.begin(), mp.end());
        sort(vec.begin(), vec.end(), cmp);

        res.push_back(vec[0].first);
        for (int i = 1; i < vec.size(); i++) {
            if (vec[i].second == vec[0].second) res.push_back(vec[i].first);
            else break;
        }
        return res;
    }

    bool static cmp (const pair<int, int> a, const pair<int, int> b) {
        return a.second > b.second ? true : false;
    }

private:
    map<int,int> mp;
    void traversal(TreeNode* root) {
        if (root == NULL) return;
        traversal(root->left);
        mp[root->val]++;
        traversal(root->right);
    }   
```





# 二叉树公共祖先问题

## 21. 二叉树的最近公共祖先

**236. 二叉树的最近公共祖先**

```c++
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == p || root == q || root == NULL) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root;

    if (left != NULL && right == NULL) {
        return left;
    } else if (left == NULL && right != NULL) {
        return right;
    }

    return NULL;
}
```



## #16-21. 小结

一起操作两个数，用队列层序遍历。



---

## 22. 删除二叉搜索树中的节点

**450. 删除二叉搜索树中的节点**

```c++
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;
    if (root->val == key) {
        if (root->left == NULL) return root->right;
        else if (root->right == NULL) return root->left;
        else {
            TreeNode* cur = root->right;
            while (cur->left != nullptr) {
                cur = cur->left;
            }
            cur->left = root->left;
            TreeNode* tmp = root;
            root = root->right;
            delete(tmp);

            return root;
        }
    }

    TreeNode* tmp = new TreeNode(NULL);
    if (root->val > key) root->left = deleteNode(root->left, key);
    else root->right = deleteNode(root->right, key);

    return root;
}
```





---

# 二叉搜索树的修改与构造

---

## 23. 修剪二叉搜索树

**669. 修剪二叉搜索树**

```c++
TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (root == nullptr) return nullptr;
    if (root->val < low) {
        TreeNode* right = trimBST(root->right, low, high);
        return right;
    }

    if (root->val > high) {
        TreeNode* left = trimBST(root->left, low, high);
        return left;
    }

    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);

    return root;
}
```





---

## 24. 构造一棵二叉搜索树

**108. 将有序数组转换为二叉搜索树**

```c++
TreeNode* getBST(vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;
    int index = start + (end - start) / 2;
    TreeNode* root = new TreeNode(nums[index]);
    root->left = getBST(nums, start, index - 1);
    root->right = getBST(nums, index + 1, end);
    return root;
}
```



---

## 25. 把二叉搜索树转换为累加树

**538. 把二叉搜索树转换为累加树**

```c++
int tmp = 0;
void traversal(TreeNode* root) {
    if (root == nullptr) return;
    traversal(root->right);
    root->val = root->val + tmp;
    tmp = root->val;
    traversal(root->left);
    return;
}

TreeNode* convertBST(TreeNode* root) {
    traversal(root);
    return root;
}
```



涉及到二叉树的构造,无论普通二叉树还是二叉搜索树一定前序,都是先构造中节点。
求普通二叉树的属性,一般是后序,一般要通过递归函数的返回值做计算。
求二叉搜索树的属性,一定是中序了,要不白瞎了有序性了。








