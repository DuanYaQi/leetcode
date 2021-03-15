# Leetcode
My Leetcode Solution


## 树

|  题目  |知识点|技巧|
|  :----  |:----:|:----:|
|[105. Construct Binary Tree from Preorder and Inorder Traversal](https://github.com/DuanYaQi/leetcode/blob/master/Tree/105%2BbuildTree.cpp) | 先序 中序 递归|确定起始索引|
|[106. Construct Binary Tree from Inorder and Postorder Traversal](https://github.com/DuanYaQi/leetcode/blob/master/Tree/106%2BbuildTree.cpp)   |中序 后序 递归 |确定起始索引|
|[114. Flatten Binary Tree to Linked List](https://github.com/DuanYaQi/leetcode/blob/master/Tree/114%2Bflatten.cpp)   | 后序 递归 |注意指针连接|
|[116. Populating Next Right Pointers in Each Node](https://github.com/DuanYaQi/leetcode/blob/master/Tree/116%2Bconnect.cpp)   | 先序 递归|考虑到特殊情况即可|
|[222. Count Complete Tree Nodes](https://github.com/DuanYaQi/leetcode/blob/master/Tree/222%2BcountNodes.cpp)   | 完全二叉树 | 利用其性质减少计算|
|[226. Invert Binary Tree](https://github.com/DuanYaQi/leetcode/blob/master/Tree/226%2BinvertTree.cpp)   | 先序 递归 | 跟交换数字一样|
|[297. Serialize and Deserialize Binary Tree](https://github.com/DuanYaQi/leetcode/blob/master/Tree/297%2Bserialize.cpp) | 序列化 反序列化 |  队列出入栈搜索树 <br><br/>to_string()<br><br/>string::npos 表示find()没有找到<br><br/>stoi()字符转int |
|[652. Find Duplicate Subtrees](https://github.com/DuanYaQi/leetcode/blob/master/Tree/652%2BfindDuplicateSubtrees.cpp) |  ||
|[654. Maximum Binary Tree](https://github.com/DuanYaQi/leetcode/blob/master/Tree/654%2BconstructMaximumBinaryTree.cpp) |  ||
|   |  ||
|   |  ||

------
## STL
### vector

```c++
#include<vector>
vector<typename> name;	    //typename 任意基本数据类型或容器
vector<vector<int> > name;	//二维vector数组 当作两个都可变长的二维数组!!!!!!!! >>之间要加空格 
v[i];                       //下标访问元素
v.push_back(x);             //在vector后面添加元素x
v.pop_back();               //删除vector尾部元素
v.clear();                  //清空vector中所有元素
v.size();                   //返回vector内元素的个数

//STL容器中，只有vector和string中，允许使用vi.begin()+3这种迭代器加上整数的写法
v.insert(v.begin()+2,-1);  //向vector的任意迭代器it处插入一个元素x  将-1插入v[2]的位置
v.erase(v.begin()+2);       //删除迭代器为it处的元素
v.erase(first,last);        //删除一个区间[fisrt,last)内的所有元素
```


### string

```c++
#include<string>
s[i];                       //下标访问元素
string str1="a",str2="x";   //operator+=直接拼接
str1+=str2;         

//两个string类型可以直接使用== ！= 等比较大小 字典序
int main{
    string str1="aa",str2="aaa",str3="abc",str4="xyz";
    if(str1<str2) printf("ok1\n");	//ok1
    if(str1!=str3) printf("ok2\n");	//ok2
    if(str4>=str3) printf("ok3\n");	//ok3
    return 0;
}

s.length();/s.size();       //返回string的长度
s.clear();                  //清空string中所有元素
s.substr(pos,len);          //substr(pos,len) 返回从pos号位开始、长度为len的子串
int main(){
    string str="Thank you for your smile";
   	cout<<str.substr(0,5)<<endl;	//Thank
    cout<<str.substr(14,4)<<endl;	//your
    return 0;
}
string::npos                //本身的值为-1/4294967295 find函数失配时的返回值
s.find(x)                   //str.find(str2)，当str2是str的子串时，返回其在str中第一次出现的位置；如果str2不是str的子串，返回string::npos
                            //str.find(str2,pos),从str的pos号位开始寻找str2


//STL容器中，只有vector和string中，允许使用vi.begin()+3这种迭代器加上整数的写法

insert(x)                   //插入
//insert(pos,string) 在pos号位置插入字符串string
string str="abcxyz" ,str2="opq";
str.insert(3,str2);	//往str[3]处插入opq，str2的位置直接写"opq"也可以
cout<<str<<endl; //abcopqxzy

//insert(it,it2,it3)，it为原字符串的欲插入位置，it2和it3为待插字符串的首尾迭代器，用来表示串[it2,it3)将被插在it的位置上。
string str="abcxyz" ,str2="opq";
str.insert(str.begin()+3,str2.begin(),str2.end());
cout<<str<<endl;//abcopqxyz


erase();                    //删除
//删除单个元素
int main(){
    string str="abcdefg";
    str.erase(str.begin()+4);	//删除4号位
   	cout<<str<<endl;	//abcdfg
    return 0;
}

//删除一个区间[fisrt,last)内的所有元素
int main(){
    string str="abcdefg";
    str.erase(str.begin()+2,str.end()-1);	//删除cdef
   	cout<<str<<endl;	//abg
    return 0;
}

//str.erase(pos,length) pos开始删除的起始位置，length为删除的字符个数
int main(){
    string str="abcdefg";
    str.erase(3，2);	//删除de
   	cout<<str<<endl;	//abcfg
    return 0;
}

s.replace()                    
//replace(pos,len,str2)	把str从pos号位开始，长度为len的子串替换为str2
//replace(it1,it2,str2)把str的迭代器[it1，it2)范围的子串替换为str2
int main(){
    string str="Maybe you will turn around";
    string str2="will not";
    string str3="surely";
    cout<<str.replace(10,4,str2)<<endl;
    //Maybe you will not turn around
    cout<<str.replace(str.begin(),str.begin()+5,str3)<<endl;
    //surely you will turn around
    return 0;
}

```
------

### queue

```c++
#include<queue>
queue<typename> name;	//typename 任意基本数据类型或容器
q.front();              //第一个元素
q.back();               //最后一个元素
q.push();               //push(x)将x压入队列
q.pop();                //令队首元素出队
q.empty();              //检测queue是否为空,true为空,false为非空
q.size();               //返回queue内元素的个数
```

-----