# 栈与队列

游戏开发可能使用栈结构，**编程语言的一些功能实现也会使用栈结构，实现函数递归调用就需要栈。**



**递归的实现就是：每一次递归调用都会把函数的局部变量、参数值和返回地址等压入调用栈中**，然后递归返回的时候，从栈顶弹出上一次递归的各项参数，所以这就是递归为什么可以返回上一层位置的原因。



栈溢出，系统输出的异常是`Segmentation fault`（当然不是所有的`Segmentation fault` 都是栈溢出导致的） ，如果你使用了递归，就要想一想是不是无限递归了，那么系统调用栈就会溢出。



**在企业项目开发中，尽量不要使用递归！**在项目比较大的时候，由于参数多，全局变量等等，使用递归很容易判断不充分return的条件，非常容易无限递归（或者递归层级过深），**造成栈溢出错误（这种问题还不好排查！）**





---

## 基础

队列是先进先出，栈是先进后出。

**C++中stack 是容器么？**

栈和队列是STL（C++标准库）里面的两个**数据结构**。C++标准库是有多个版本的，那么来介绍一下，三个最为普遍的STL版本：

- HP STL

其他版本的C++ STL，一般是以HP STL为蓝本实现出来的，HP STL是C++ STL的**第一个实现版本**，而且开放源代码。

- P.J.Plauger STL

由 P.J.Plauger 参照HP STL实现出来的，被 Visual C++ 编译器所采用，不是开源的。

- SGI STL

由 Silicon Graphics Computer Systems 公司参照 HP STL 实现，被 Linux 的 C++ 编译器GCC 所采用，SGI STL 是开源软件，源码可读性甚高。



**我们使用的stack是属于那个版本的STL？**

接下来介绍的栈和队列也是SGI STL里面的数据结构，**我们一般使用的STL也是SGI STL**，知道了使用版本，才知道对应的底层实现。





**我们使用的STL中stack是如何实现的？**/ **stack 提供迭代器来遍历stack空间么？**

栈提供push 和 pop 等等接口，所有元素必须符合先进后出规则，所以栈不提供走访功能，也不提供迭代器(iterator)。不像是set 或者map 提供迭代器iterator来遍历所有元素。

> **栈是以底层容器完成其所有的工作，对外提供统一的接口，底层容器(deque, list, vector, ...)是可插拔的（也就是说我们可以控制使用哪种容器来实现栈的功能）。**



所以 STL 中栈往往不被归类为容器，而被归类为 container adapter（容器适配器）。

从下图中可以看出，栈的内部结构，栈的底层实现可以是vector，deque，list 都是可以的， 主要就是数组和链表的底层实现。

![图片](assets/640.png)

**「我们常用的SGI STL，如果没有指定底层实现的话，默认是以deque为缺省情况下栈的低层结构。」**

deque是一个双向队列，只要封住一段，只开通另一端就可以实现栈的逻辑了。

**「SGI STL中 队列底层实现缺省情况下一样使用deque实现的。」**

我们也可以指定vector为栈的底层实现，初始化语句如下：

```c++
std::stack<int, std::vector<int> > third;  // 使用vector为底层容器的栈
```

刚刚讲过栈的特性，对应的队列的情况是一样的。





队列 先进先出的数据结构，同样不允许有遍历行为，不提供迭代器， **SGI STL中队列一样是以deque为缺省情况下的底部结构。**

也可以指定 list 为起底层实现，初始化queue的语句如下：

```c++
std::queue<int, std::list<int>> third; // 定义以list为底层容器的队列
```

所以STL中**队列也不被归类为容器**，而被归类为container adapter（ 容器适配器）。

我这里讲的都是（clck）C++ 语言中情况， 使用其他语言的同学也要思考栈与队列的底层实现问题， 不要对数据结构的使用浅尝辄止，而要深挖起内部原理，才能夯实基础！



## 232. 用栈实现队列

使用栈来模式队列的行为，如果仅仅用一个栈，是一定不行的，所以需要两个栈**「一个输入栈，一个输出栈」**，这里要注意输入栈和输出栈的关系。



peek()的实现，直接复用了pop()。

再多说一些代码开发上的习惯问题，在工业级别代码开发中，最忌讳的就是 实现一个类似的函数，直接把代码粘过来改一改就完事了。

这样的项目代码会越来越乱，**「一定要懂得复用，功能相近的函数要抽象出来，不要大量的复制粘贴，很容易出问题！（踩过坑的人自然懂）」**



```c++
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        stIn.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (stOut.empty()) {            //如果为空，则把栈in里的数据全部加入栈out中
            while (!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }

        int result = stOut.top();
        stOut.pop();
        return result;
    }
    
    /** Get the front element. */
    int peek() {
        int res = this->pop();
        stOut.push(res);    //再加回去
        return res;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return stIn.empty() && stOut.empty() ? true : false;
    }

private:
    stack<int> stIn;
    stack<int> stOut;    
};
```



## 225. 用队列实现栈

**「用两个队列que1和que2实现栈的功能，que2其实完全就是一个备份的作用」**

重点在pop，备份back前所有的元素，然后将back pop出去，然后恢复备份

```c++
class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        _qu1.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int res = _qu1.back();
        int size = _qu1.size(); 
        while ( size - 1 != 0 ) { //要留最后一个元素去除
            _qu2.push(_qu1.front());
            _qu1.pop();
            size--;
        }

        _qu1.pop();
        _qu1 = _qu2;

        while (!_qu2.empty()) {
            _qu2.pop();
        }
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return _qu1.back();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return _qu1.empty();
    }

private:
    queue<int> _qu1;
    queue<int> _qu2;
};
```



## 20. 有效的括号

```c++
class Solution {
public:
    bool isValid(string s) {
        stack<int> st;

        for (int i = 0; i < s.size(); i++) {
            // 三个左
            if (s[i] == '(') st.push(')');
            else if (s[i] == '{') st.push('}');
            else if (s[i] == '[') st.push(']');
            // 三个右
            else if (st.empty() || s[i] != st.top()) return false; // 为右括号且不为空 返回false； 为右括号且与栈顶元素不同，即不对应
            else if (s[i] == st.top()) st.pop(); //为右且前一个为对应的左，pop出
            else st.push(s[i]);
        }

        return st.empty();
    }
};
```





## 1047. 删除字符串中的所有相邻重复项

```c++
string removeDuplicates(string S) {
    stack<int> st;
    for (char s : S) {
        if (!st.empty() && st.top() == s) {
            st.pop();
        } else {
            st.push(s);
        }
    }

    string res;
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}
```





---

## 150. 逆波兰表达式求值

逆波兰表达式：是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。

该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。

**所以RPN（后缀表达式）对计算机来说是非常友好的**

**其实逆波兰表达式相当于是二叉树中的后序遍历**

```c++
int evalRPN(vector<string>& tokens) {
    stack<int> st;
    int a, b, c;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            if (tokens[i] == "+") {
                st.push(a + b);
            } else if (tokens[i] == "-") {
                st.push(b - a);
            } else if (tokens[i] == "*") {
                st.push(a * b);
            } else if (tokens[i] == "/") {
                st.push(b / a);
            }
        } else {
            st.push(stoi(tokens[i]));
        }
    }
    return st.top();
}
```



---

## 239. 滑动窗口最大值







---

## 347.前 K 个高频元素





