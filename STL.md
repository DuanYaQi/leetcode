# C++标准模板库(STL)介绍

## 常用容器的特点及适用情况

string：与vector相似的容器，专门用于存储字符。随机访问快，在尾位置插入/删除速度快

array：固定大小数组。支持快速随机访问，不能添加或者删除元素

vector：可变大小的数组。底层数据结构为数组，支持快速随机访问，在尾部之外的位置插入或者删除元素可能很慢

list：双向链表。底层数据结构为双向链表，支持双向顺序访问。在list任何位置插入/删除速度很快

forward_list：单向链表。支持单项顺序访问。在forward_list任何位置插入/删除速度很快

deque：双端队列。底层数据结构为一个中央控制器和多个缓冲区，支持快速随机访问，在头尾位置插入/删除速度很快

stack：栈。底层用deque实现，封闭头部，在尾部进行插入和删除元素

queue：队列。底层用deque实现

priority_queue：优先队列。底层用vector实现，堆heap为处理规则来管理底层容器的实现

set：集合。底层为红黑树，元素有序，不重复

multiset：底层为红黑树，元素有序，可重复

map：底层为红黑树，键有序，不重复

multimap：底层为红黑树，键有序，可重复

hash_set：底层为哈希表，无序，不重复

hash_multiset：底层为哈希表，无序，可重复

hash_map：底层为哈希表，无序，不重复

hash_multimap：底层为哈希表，无序，可重复

**总结**：(这里仅代表做这几种操作时效率比较高，可能其他容器也支持这几种操作)

支持随机访问的容器：string,array,vector,deque
支持在任意位置插入/删除的容器：list,forward_list
支持在尾部插入元素：vector,string,deque





### Pre. 容器共通操作

所有容器类（包括string类）的共通操作：

- `==`（equality）和`!=`（inequality）运算符，返回true或false
- `=`运算符，将某个容器复制给另一个容器
- `empty()`会在容器无任何元素时返回true，否则false
- `size()`返回容器内目前持有的元素个数
- `clear()`删除所有元素
- `::iterator` 迭代器



每个容器还都提供了 `begin()` 和 `end()` 两个函数，分别返回指向容器的第一个元素和最后一个元素的下一位置的iterator

-  `begin()`  返回一个iterator，指向容器的第一个元素
-  `end()` 返回一个iterator，指向容器最后一个元素的下一位置。

所有容器都提供 `insert()` 用以插入元素，以及 `erase` 用以删除元素。

-  `insert()`  将单一或某个范围内的元素插入容器内
-  `erase()` 将容器内的单一元素或某个范围内的元素删除。

- `front()` 返回容器第一个元素。
- `back()` 返回容器最后一个元素。
- `swap()`交换两个容器的内容。





---

## 1. vector

https://hackingcpp.com/cpp/std/vector.html



向量，“变长数组”，“长度根据需要而自动改变的数组”。有时会碰到只用普通数组会超内存的情况，这种情况使用vector会便捷许多。vector还可以以邻接表的方式储存图，对**无法使用邻接矩阵**的题目（结点数太多）、又害怕**使用指针实现邻接表**的读者十分友好。

```c++
#include<vector>
using namespace std;
```



---

### 1.1 vector定义

```c++
vector<typename> name;//等同于一维数组name[SIZE],只不过其长度可以根据需要进行变化，比较节省空间。
//typename 可以是 int、double、char、结构体等，也可以是vector、set、queue等
vector<int> name;
vector<double> name;
vector<char> name;
vector<node> name;	//结构体类型

//二维数组  二维vector数组 当作两个都可变长的二维数组
vector<vector<int> > name;	//!!!!!!!! >>之间要加空格

//vector数组
vector<typename> Arrayname[arraySize];
vector<int> vi[100];	//vi[0]~vi[100]中每一个都是一个vector容器。 一维长度已经固定为100
//与vector<vector<int> > name;不同的是  其中一维长度是否已经固定


vector<int> v3(100,9);	//把100长度的数组v3所有值初始化为9

in={1,2,3,4,5,6,7};
vector<int> tin(in, in+7);	// 1 2 3 4 5 6 7
vector<int> tin(in, in+6);	// 1 2 3 4 5 6 

vector<int>(n, 0); 								//一维向量1xn 初始化为0
vector<vector<int>> dp(m, vector<int>(n, 0));  //二维向量mxn 初始化为0
```

[二维vector初始化](https://www.cnblogs.com/NirobertEinteson/p/11960285.html) 



---

### 1.2 vector容器内元素的访问

1. 通过下标访问

```c++
vector<int> vi;
printf("%d %",v[0],v[99]);
```

2. 通过迭代器访问

```c++
vector<typename>::iterator it;	//it为迭代器变量
vector<int> vi;
for(int i=1;i<=5;i++){
    vi.push_back(i);	//push_back(i)在vi的末尾添加元素i，即依次添加1 2 3 4 5 
}
```

通过类似下标和指针访问数组的方式来访问容器内的元素

```c++
#include<stdio.h>
#include<vector>
using namespace std;
int main(){
    vector<int> vi;
    for(int i=1;i<=5;i++){
        vi.push_back(i);
    }
    //vi.begin()为取vi的首元素地址，而it指向这个地址
   	vector<int>::iterator it=vi.begin();
    for(int i=0;i<5;i++){
        printf("%d ",*(it+i));			  			//1 2 3 4 5
    }
    return 0;
}
```

​	 `vi[i]`和`*(vi.begin()+i)`是等价的

​	`end()`取`vi`的尾元素地址的下一个地址。`end()`作为迭代器末尾标志，不储存任何元素。

```c++
#include<stdio.h>
#include<vector>
using namespace std;
int main(){
    vector<int> vi;
    for(int i=1;i<=5;i++){
        vi.push_back(i);
    }
    //vi.begin()为取vi的首元素地址，而it指向这个地址
   	
    for(vector<int>::iterator it=vi.begin();it!=vi.end();it++){
        printf("%d ",*it);			//1 2 3 4 5 
    }
    return 0;
}
```

​	**STL容器中，只有 vector 和 string 中，允许使用`vi.begin()+3`这种迭代器加上整数的写法**



---

### 1.3 vector常用函数

1. push_back(i) / emplace_back(i)

```C++
//在vector后面添加元素x，时间复杂度O(1)
#include<stdio.h>
#incldue<vector>
using namespace std;
int main(){
    vector<int> vi;
    for(int i=1;i<=3;i++){
        vi.emplace_back(i);	//push_back
    }
    for(int i=0;i<vi.size();i++){
        printf("%d ",vi[i]);		// 1 2 3
    }
    return 0;
}

//emplace_back() 和 push_back() 的区别，就在于底层实现的机制不同
//push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）
//emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
```

显然完成同样的操作，push_back() 的底层实现过程比 emplace_back() 更繁琐，换句话说，emplace_back() 的执行效率比 push_back() 高。因此，在实际使用时，建议大家优先选用 emplace_back()。

> 由于 emplace_back() 是 C++ 11 标准新增加的，如果程序要兼顾之前的版本，还是应该使用 push_back()。



2. pop_back()

```c++
//有添加就会有删除， 删除vector尾元素
#include<stdio.h>
#incldue<vector>
using namespace std;
int main(){
    vector<int> vi;
    for(int i=1;i<=3;i++){
        vi.push_back(i);
    }
    vi.pop_back();	//删除vi尾部元素
    for(int i=0;i<vi.size();i++){
        printf("%d ",vi[i]);		// 1 2 
    }
    return 0;
}
```



3. insert(it,x)

```c++
//向vector的任意迭代器it处插入一个元素x
#include<stdio.h>
#incldue<vector>
using namespace std;
int main(){
    vector<int> vi;
    for(int i=1;i<=5;i++){
        vi.push_back(i);	//1 2 3 4 5 
    }
    vi.insert(vi.begin()+2,-1);	//将-1插入vi[2]的位置
    for(int i=0;i<vi.size();i++){
        printf("%d ",vi[i]);		// 1 2 -1 3 4 5
    }
    return 0;
}
```



4. erase(it)/erase(first,last)

```c++
//删除迭代器为it处的元素
#include<stdio.h>
#incldue<vector>
using namespace std;
int main(){
    vector<int> vi;
    for(int i=5;i<=9;i++){
        vi.push_back(i);	//5 6 7 8 9
    }
    //删除8 
    vi.erase(vi.begin()+3);
    for(int i=0;i<vi.size();i++){
        printf("%d ",vi[i]);		// 5 6 7 9 
    }
    return 0;
}
```

```c++
//删除一个区间[fisrt,last)内的所有元素
#include<stdio.h>
#incldue<vector>
using namespace std;
int main(){
    vector<int> vi;
    for(int i=5;i<=9;i++){
        vi.push_back(i);	//5 6 7 8 9
    }
    //删除8 
    vi.insert(vi.begin()+1，vi.begin()+4);
    for(int i=0;i<vi.size();i++){
        printf("%d ",vi[i]);		// 5 9 
    }
    return 0;
}
```



5. append() 添加元素





6. clear() 删除全部

```c++
vector<int> vec{1,2,3,4,5};
vec.clear() 
```



7. remove() 删除容器中和指定元素值相同的所有元素

```c++
vector<int> demo{ 1,3,3,4,3,5 };

//交换要删除元素和最后一个元素的位置
auto iter = std::remove(demo.begin(), demo.end(), 3);

cout << "size is :" << demo.size() << endl;
cout << "capacity is :" << demo.capacity() << endl;

//输出剩余的元素
for (auto first = demo.begin(); first < iter;++first) {	// 1 4 5
    cout << *first << " ";
}
```

改变容器原来的大小和容量，因此需要借助 remove() 返回的迭代器（iter 为终点）完成正确的遍历。



8. reverse() 直接翻转vector

```c++
vector<int> demo{ 1,3,3,4,3,5 };

for (int v : demo)
    cout << v;
// 1 3 3 4 3 5

reverse(demo.begin(), demo.end());
for (int v : demo)
    cout << v;
// 5 3 4 3 3 1    
```







8. 判断相等

- 如果vector里面的元素类型是简单类型（内置类型），可以直接使用“==”或者“!=”进行比较

```c++
// 判断两个vector是否相等 直接用“==”
// 因为在STL里面，==和!=是可以直接使用的：
template< class T, class Alloc >
bool operator==( const vector<T,Alloc>& lhs,
                 const vector<T,Alloc>& rhs );
 
template< class T, class Alloc >
bool operator!=( const vector<T,Alloc>& lhs,
                 const vector<T,Alloc>& rhs );
```



7. 



---

### 1.4 vector的常见用途

1. 储存数据

   - vector本身可以作为数组使用，而且一些元素个数不确定的场合可以很好的节省空间
   - 有些场合需要根据一些条件把部分数据输出在同一行，数据中间用空格隔开。由于输出数据的个数是不确定的，为了更方便地处理最后一个满足条件的数据后面不输出额外的空格，可以下用vector记录所有需要输出的数据，然后一次性输出。

2. 用邻接表存储图

   使用vector实现邻接表 10.2.2







------

## 2. set

​	集合，是一个**内部自动有序**且**不包含重复元素**的容器。有可能出现需要去掉重读元素的情况，有可能元素比较大或者类型不是 `int` 型而不能直接开散列表，这种情况可以用set**保留元素本身而不是考虑它的个数**。	也可以再开一个数组进行下标和元素的对应来解决。

```c++
#include<set>
using namespace std;
```



---

#### 2.1 set定义

```c++
set<typename> name;	//typename 可以是 int、double、char、结构体等，也可以是vector、set、queue等
set<int> name;
set<double> name;
set<char> name;
set<node> name;	//node结构体类型

//二维数组  二维set数组
set<set<int> > name;	//!!!!!!!! >>之间要加空格

//set数组
set<typename> Arrayname[arraySize];

set<int> a[100];	//a[0]~a[100]中每一个都是一个set容器。 一维长度已经固定为100
```



---

#### 2.2 set容器内元素的访问

**只能通过迭代器访问**

```c++
set<typename>::iterator it;	//it为迭代器变量
set<int>::iterator it;	//it为迭代器变量
```

```c++
//只能通过*it方式访问
#include<stdio.h>
#include<vector>
using namespace std;
int main(){
    set<int> st;
    st.insert(3);	//将x插入set中
    st.insert(5);
    st.insert(2);
    st.insert(3);
//注意，不支持it<st.end()的写法
    for(set<int>::iterator it=st.begin();it!=st.end();it++){
        printf("%d ",*it);			//2 3 5 
    }
    return 0;
}
```



---

#### 2.3 set常用函数

1. insert(x)

   ```c++
   //向vector的任意迭代器it处插入一个元素x
   #include<stdio.h>
   #incldue<vector>
   using namespace std;
   int main(){
       set<int> st;
       st.insert(2);	
       st.insert(5);
       st.insert(4);
       printf("%d ",st.size());		// 3
       return 0;
   }
   ```

2. find(x)

   ```c++
   //返回set中对应值为value的迭代器
   #include<stdio.h>
   #incldue<set>
   using namespace std;
   int main(){
       set<int> st;
       st.insert(2);	
       st.insert(5);
       st.insert(4);
       set<int>::iterator it=st.find(2);//在set中查找2，返回迭代器
       printf("%d ",*it);		// 2
       return 0;
   }
   ```

5. erase(it)/erase(first,last)

   ```c++
   //删除迭代器为it处的元素
   #include<stdio.h>
   #incldue<set>
   using namespace std;
   int main(){
       set<int> st;
       st.insert(100);	
       st.insert(200);
       st.insert(100);
       st.insert(300);
       st.erase(st.find(100));
       st.erase(st.find(200));
      	for(set<int>::iterator it=st.begin();it!=st.end();it++){
           printf("%d ",*it);			//300
       }
       return 0;
   }
   
   //直接删除所需要删除的值
   #include<stdio.h>
   #incldue<set>
   using namespace std;
   int main(){
       set<int> st;
       st.insert(100);	
       st.insert(200);
       st.erase(100);
       for(set<int>::iterator it=st.begin();it!=st.end();it++){
           printf("%d ",*it);			//200
       }
       return 0;
   }
   ```

   ```c++
   //删除一个区间[fisrt,last)内的所有元素
   #include<stdio.h>
   #incldue<set>
   using namespace std;
   int main(){
       set<int> st;
       st.insert(20);	
       st.insert(10);
       st.insert(40);
       st.insert(30);
       set<int>::iterator it=st.find(30);//在set中查找2，返回迭代器
       st.erase(it,st.end());
       for(set<int>::iterator it=st.begin();it!=st.end();it++){
           printf("%d ",*it);			//10 20
       }
       return 0;
   }
   ```



---

#### 2.4 set的常见用途

​	set最主要的作用是**自动去重**并按**升序排序**，因此碰到**需要去重但是不方便直接开数组**的情况，可以尝试用set解决。
​	**延伸**：set 中元素是唯一的，如果需要处理不唯一的情况，则需要使用multiset。增加了unordered_set，以散列代替set内部的红黑树（自平衡二叉查找树）实现，使其可以用来处理只去重但不排序的需求，速度比set要快得多







---

## 3. string

​	在c语言中，一般使用字符数组`char str[]`来存放字符串，但是使用字符数组有时会显得操作麻烦。

```c++
#include<string>
using namespace std;
//！！！！！！！！string 和cstring不一样
```



---

#### 3.1 string定义

```c++
string str;	//str变量名
string str="abcd";
```



---

#### 3.2 string容器内元素的访问

1. **通过下标访问**

   ```C++
   #incldue<stdio.h>
   #include<string>
   using namespace std;
   int main(){
       string str="abcd";
       for(int i=0;i<str.length();i++){
           printf("%c",str[i]);	//abcd
       }
       return0
   }
   ```

   如果要**读入和输出**整个字符串，则只能用**cin和cout**;

   ```c++
   #include<isotream>
   #include<string>
   using namespace std;
   int main{
       string str;
       cin>>str;
       cout<<str;
       return 0;
   }
   ```

2. **通过迭代器访问**

   ```c++
   string::iterator it;	//it为迭代器变量
   ```

   这样就得到了迭代器it，并且可以通过*it来访问string里的每一位

   ```c++
   #include<isotream>
   #include<string>
   using namespace std;
   int main{
       string str="abcd";
       for(string::iterator it=st.begin();it!=st.end();it++){
           printf("%c ",*it);			//abcd
       }
       return 0;
   }
   ```

​	**STL容器中，只有vector和string中，允许使用`str.begin()+3`这种迭代器加上整数的写法**

---

#### 3.3 string常用函数

1. `+=`operator	

   ```c++
   //string的加法 直接拼接
   #include<isotream>
   #include<string>
   using namespace std;
   int main{
       string str1="abc",str2="xyz",str3;
       str3=str1+str2;
       str1+=str2;
       cout<<str1<<endl;	//abcxyz
       cout<<str3<<endl;	//abcxyz
       return 0;
   }
   ```

2. compare operator

   ```c++
   //两个string类型可以直接使用== ！= 等比较大小 字典序
   #include<isotream>
   #include<string>
   using namespace std;
   int main{
       string str1="aa",str2="aaa",str3="abc",str4="xyz";
       if(str1<str2) printf("ok1\n");	//ok1
       if(str1!=str3) printf("ok2\n");	//ok2
       if(str4>=str3) printf("ok3\n");	//ok3
       return 0;
   }
   ```

3. length()/size()

   ```C++
   //返回string的长度，即存放的字符数
   #include<stdio.h>
   #include<string>
   using namespace std;
   int main(){
       string str="abcxyz";	
       printf("%d %d",str.size(),str.length());// 6 6
       return 0;
   }
   ```

4. insert(x)

   ```c++
   //insert(pos,string) 在pos号位置插入字符串string
   string str="abcxyz" ,str2="opq";
   str.insert(3,str2);	//往str[3]处插入opq，str2的位置直接写"opq"也可以
   cout<<str<<endl; //abcopqxzy
   ```

   ```c++
   //insert(it,it2,it3)，it为原字符串的欲插入位置，it2和it3为待插字符串的首尾迭代器，用来表示串[it2,it3)将被插在it的位置上。
   string str="abcxyz" ,str2="opq";
   str.insert(str.begin()+3,str2.begin(),str2.end());
   cout<<str<<endl;//abcopqxyz
   ```

5. erase(it)/erase(first,last)

   ```c++
   //删除单个元素
   int main(){
       string str="abcdefg";
       str.erase(str.begin()+4);	//删除4号位
      	cout<<str<<endl;	//abcdfg
       return 0;
   }
   ```

   ```c++
   //删除一个区间[fisrt,last)内的所有元素
   int main(){
        string str="abcdefg";
       str.erase(str.begin()+2,str.end()-1);	//删除cdef
      	cout<<str<<endl;	//abg
       return 0;
   }
   ```

   ```c++
   //str.erase(pos,length) pos开始删除的起始位置，length为删除的字符个数
   int main(){
       string str="abcdefg";
       str.erase(3，2);	//删除de
      	cout<<str<<endl;	//abcfg
       return 0;
   }
   ```

6. substr()

   ```c++
   //substr(pos,len) 返回从pos号位开始、长度为len的子串
   int main(){
       string str="Thank you for your smile";
      	cout<<str.substr(0,5)<<endl;	//Thank
       cout<<str.substr(14,4)<<endl;	//your
       return 0;
   }
   ```

8. string::npos

   ```c++
   //本身的值为-1/4294967295 find函数失配时的返回值
   ```

9. find(x)

   ```c++
   //find(str2)，当str2是str的子串时，返回其在str中第一次出现的位置；如果str2不是str的子串，返回string::npos
   //find(str2,pos),从str的pos号位开始寻找str2
   int main(){
       string str="Thank you for your smile";
       string str2="you";
       string str3="me";
       if(str.find(str2)!=string::npos){
           cout<<str.find(str2)<<endl;
       }
       if(str.find(str2,7)!=string::npos){
           cout<<str.find(str2,7)<<endl;
       }
       if(str.find(str2)!=string::npos){
           cout<<str.find(str3)<<endl;
       }else{
           cout<<"i know"<<endl;
       }
       return 0;
   }
   ```

10. replace()

    ```c++
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

10. resize()

    ```c++
    //调整容器中有效数据区域的尺寸，如果尺寸变小，原来数据多余的截掉
    string s = "smiada";
    s.resize(2); // sm
    //。若尺寸变大，不够的数据用该函数第二个参数填充,影响size。
    string s = "smiada";
    s.resize(10, 'b');//smiadabbbb
    ```

    

11. append() 添加

```c++
string b;
b = "";	//对字符串清空
b.append("0000");
b.append("0001");
cout << b ; // 00000001
```





------

## 4. map-映射

​	映射，普通数组是`int`型映射到其他类型。`map`可以将**任何基本类型**（包括STL容器）映射到**任何基本类型**（包括STL容器）.

​	情况：判断给定数字在某个文件中是否出现过。如果数字很大`hashtable`数组无法开。`map`可以把数字当作字符串建立`string`到`int`的映射。

```c++
#include<map>
using namespace std;
```



---

#### 4.1 map定义

```c++
map<typename1, typename2> mp;	//键key	值value 两个类型

//字符到整形的映射，只能string不能char数组
map<string,int> mp;

//键和值也可以是stl容器
map<set<int>,string> mp;
```



---

#### 4.2 map容器内元素的访问

1. 通过下标访问

   ```c++
   map<char int> mp;
   mp['c']=20;
   mp['c']=30;//20被覆盖
   printf("%d\n",mp['c'])；//输出30
   ```

2. 通过迭代器访问

   ```c++
   map<typename1,typename2>::iterator it;	//it为迭代器变量
   ```

   ```c++
   //map可以用it->first来访问键，使用it->second来访问值
   map<char int> mp;
   mp['m']=20;
   mp['r']=30;
   mp['a']=40；
   for(map<char,int>::iterator it=mp.begin();it!=mp.end();it++){
   	printf("%c %d\n",it->first,it->second);
   }
   //a 40
   //m 20
   ```

   **map会以键从小到大的顺序自动排序**，即按a<m<r的顺序排列三对映射。

----

#### 4.3 map常用函数

1. find()

   ```c++
   //返回键为key的映射的迭代器
   map<char int> mp;
   mp['a']=1;
   mp['b']=2;
   mp['c']=3；
   map<char,int>::iterator it=mp.find('b');
   printf("%c %d\n",it->first,it->second);
   //b 2
   
   // 判断是否在不在
   if (mp.find('b') != mp.end()) {	// 在
       
   } else {						// 不在
       
   }
   ```

2. erase()

   ```c++
   //删除单个元素erase(it)   it为需要删除的元素的迭代器
   map<char int> mp;
   mp['a']=1;
   mp['b']=2;
   mp['c']=3；
   map<char,int>::iterator it=mp.find('b');
   mp.erase(it); //删除b 2
   for(map<char,int>::iterator it=mp.begin();it!=mp.end();it++){
   	printf("%c %d\n",it->first,it->second);
   }
   //a 1
   //c 3
   
   //erase(key)	key为欲删除的映射的键
   map<char int> mp;
   mp['a']=1;
   mp['b']=2;
   mp['c']=3；
   mp.erase('b'); //删除b 2
   for(map<char,int>::iterator it=mp.begin();it!=mp.end();it++){
   	printf("%c %d\n",it->first,it->second);
   }
   //a 1
   //c 3
   ```

   ```c++
   //删除一个区间内的所有元素	erase(first,last) [first,last）
   map<char int> mp;
   mp['a']=1;
   mp['b']=2;
   mp['c']=3；
   map<char,int>::iterator it=mp.find('b');
   mp.erase(it,mp.end()); //删除it之后的所有映射
   for(map<char,int>::iterator it=mp.begin();it!=mp.end();it++){
   	printf("%c %d\n",it->first,it->second);
   }
   //a 1
   ```



---

#### 4.4 unordered_map 

无序关联容器

```c++

struct Node { double x, y; };
 
int main() {
    Node nodes[3] = { {1, 0}, {2, 0}, {3, 0} };
 
    // mag 是将 Node 的地址映射到其在平面中的模的映射
    std::unordered_map<Node *, double> mag = {
        { nodes,     1 },
        { nodes + 1, 2 },
        { nodes + 2, 3 }
    };

	for(auto iter = mag.begin(); iter != mag.end(); ++iter){
        auto cur = iter->first;
        mag[cur] = std::hypot(cur->x, cur->y);
        std::cout << "The magnitude of (" << cur->x << ", " << cur->y << ") is ";
        std::cout << iter->second << '\n';
    }
}
```



---

#### 4.5 map的常见用途

1. 需要建立字符(或字符串)与整数之间映射的题目，使用map可以减少代码量
2. 判断大整数或者其他类型数据是否存在的题目，可以把map当作bool数组用
3. 字符串和字符串的映射可以也会用到

延伸:map的键和值是唯一的，如果一个键需要对应多个值，只能用multimap。还增加了unordered_map，以散列代替map内部红黑树，速度快







------

## 5. queue-队列

队列，实现**先进先出**的容器

```c++
#include<queue>
using namespace std;
```



#### 5.1 queue定义

```c++
queue<typename> name;	//typename 任意基本数据类型或容器
```



---

#### 5.2 queue容器内元素的访问

**只能通过front()来访问队首元素,或back()访问队尾元素**

```c++
queue<int> q;
for(int i=1;i<=5;i++){
    q.push(i);
}
printf("%d %d",q.front(),q.back());//1 5 
```



---

#### 5.3 queue常用函数

1. push()

   ```c++
   //push(x)将x压入队列
   queue<int> q;
   for(int i=1;i<=5;i++){
       q.push(i);
   }
   ```

2. front()\back()

   ```c++
   printf("%d %d",q.front(),q.back());//1 5 
   ```

3. pop()

   ```c++
   //令队首元素出队
   queue<int> q;
   for(int i=1;i<=5;i++){
       q.push(i);
   }
   printf("%d %d",q.front(),q.back());//1 5 
   for(int i=1;i<=3;i++){
       q.pop();//出队首元素三次 1 2 3 
   }
   printf("%d %d",q.front(),q.back());//4 5 
   ```



---

#### 5.4 queue的常见用途

1. 需要实现广度优先搜索时,使用queue代替
2. 使用`front()`和`pop()`函数前,必须用`empty()`判断队列是否为空.

延伸:双队列deque/优先队列priority_queue







------

## 6. priority_queue-优先队列

优先队列，其底层是用堆来进行实现的.优先队列中,**队首元素一定是当前队列中优先级最高**的那一个.例如在队列有如下元素,且定义好了优先级

```c++
//此处规定数字越大优先级越高
桃子	(优先级3)
梨子	(优先级4)
苹果	(优先级1)
```

那么出队的顺序为梨子(4)→桃子(3)→苹果(1).

当然,可以在任何时候往优先队列里push元素,而优先队列底层的数据结构堆heap会随时调整结构,使得每次的队首元素都是优先级最大的

```c++
#include<queue>
using namespace std;
```



---

#### 6.1 priority_queue定义

```c++
priority_queue<typename> name;	//typename 任意基本数据类型或容器
```



---

#### 6.2 priority_queue容器内元素的访问

**只能通过top()访问队首元素(堆顶元素)**,优先级最高的元素

```c++
priority_queue<int> q;
for(int i=1;i<=5;i++){
    q.push(i);
}
printf("%d",q.top());//5
```



---

#### 6.3 priority_queue常用函数

1. push()

   ```c++
   //push(x)将x压入队列
   priority_queue<int> q;
   for(int i=1;i<=5;i++){
       q.push(i);
   }
   ```

2. top()

   ```c++
   printf("%d",q.top());//5 
   ```

3. pop()

   ```c++
   //令队首元素(堆顶元素)出队
   priority_queue<int> q;
   for(int i=1;i<=5;i++){
       q.push(i);
   }
   printf("%d",q.top());//5
   q.pop();//出队首元素
   printf("%d",q.top());//4
   ```



---

#### 6.4 priority_queue内元素元素优先级的设置

1. 基本数据类型的优先级设置

   `int`型 `double`型 `char` 型,默认数字大的/字典序大的优先级高.队首元素为优先队列内元素最大的那个

   ```c++
   //等价
   priority_queue<int> q;
   priority_queue<int, vector<int>, less<int> > q;
   //第二个参数是来承载底层数据结构堆(heap)的容器,
   //第三个参数是对第一个参数的比较类,less<int>表示数字大的优先级越大,而greater<int>表示数字小的优先级越大
   priority_queue<int,vector<int>,greater<int> > q;
   ```

2. 结构体的优先级设置

   ```c++
   struct fruit{
       string name;
       int price;
   }
   //希望水果的价格高的为优先级高,就需要重载(overload)小于号"<".重载是指对已有的运算符进行重新定义,也就是改变小于号的功能
   struct fruit{
       string name;
       int price;
       friend bool operator < (fruit f1,fruit f2){
           return f1.price < f2.price;
       }
   }
   //fruit 增加了一个函数 friend 为友元
   //"bool operator <(fruit f1,fruit f2)"对fruit类型的操作符"<"进行重载
   //f1 > f2   f2 < f1
   //f1 == f2  !(f1<f2) && !(f2<f1)
   //"return f1.price < f2.price;" 以价格高的水果为优先级高
   ```

   ```c++
   struct fruit{
       string name;
       int price;
       friend bool operator < (fruit f1,fruit f2){
           return f1.price>f2.price;	//价格低的水果优先级高
       }
   }f1, f2, f3
   
   int main(){
   	priority_queue<fruit> q;
   	f1.name = "aaa";
   	f1.price = 3;
   	f2.name = "bbb";
   	f2.price = 4;
   	f3.name = "ccc";
   	f3.price = 1;
   	q.push(f1);
   	q.push(f2);
   	q.push(f3);
   	cout << q.top().name << "" << q.top.price << endl;
   	return 0;
   }
   
   ```
   
   ```c++
   //苹果1
   struct fruit{
       string name;
       int price;
   }f1,f2,f3
   
   struct cmp{
   	bool operator < (fruit f1, fruit f2){		//去掉friend
           return f1.price > f2.price;	//价格低的水果优先级高
       }
   }
   
   priority_queue<fruit, vector<fruit>, cmp> q;
   ```



**即便是基本数据类型或者其他STL容器,也可以通过同样的方式来定义优先级.**

如果结构体内的数据较为庞大(例如出现了字符串或者数组)，建议使用引用来提高效率，此时比较类的参数中需要加上`"const"`和`"&"`

```c++
friend bool operator < (const fruit &f1, const fruit &f2){
    return f1.price > f2.price;	//价格低的水果优先级高
}
   
bool operator () (const fruit &f1, const fruit &f2){
    return f1.price > f2.price;	//价格低的水果优先级高
}
```



---

#### 6.5 priority_queue的常见用途

1. 可以解决一些贪心问题,也可以对`dijkstra`算法进行优化(因为优先队列的本质是堆)
2. 使用`pop()`函数前,必须用`empty()`判断队列是否为空.







------

## 7. stack-栈

栈，后进先出的容器

当然,可以在任何时候往优先队列里push元素,而优先队列底层的数据结构堆heap会随时调整结构,使得每次的队首元素都是优先级最大的

```c++
#include<stack>
using namespace std;
```



---

#### 7.1 stack定义

```c++
stack<typename> name;	//typename 任意基本数据类型或容器
```



---

#### 7.2 stack容器内元素的访问

**只能通过top()访问队首元素(栈顶元素)**

```c++
stack<int> st;
for(int i=1;i<=5;i++){
    st.push(i);
}
printf("%d",st.top());//5
```



---

#### 7.3 stack常用函数

1. push()

   ```c++
   //push(x)将x入栈
   stack<int> st;
   for(int i=1;i<=5;i++){
       st.push(i);
   }
   ```
   
2. top()

   ```c++
   printf("%d",st.top());//5 
   ```
   
3. pop()

   ```c++
   //令栈顶元素出队
   stack<int> st;
   for(int i=1;i<=5;i++){
       st.push(i);
   }
   for(int i=1;i<=3;i++){
       st.pop();		//连续三次将栈顶元素出栈 5 4 3 
   }
   printf("%d",st.top());//2
   ```
   



---


#### 7.4 stack的常见用途

用来模拟实现一些**递归**，防止程序对栈内存的限制而导致程序运行出错.







------

## 8. pair

​	pair,当想要将两个元素绑在一起作为一个合成元素,又不想要因此定义结构体时,使用pair可以很方便的作为一个替代品.也就是说,pair实际上可以看作一个内部有两个元素的结构体,且这两个元素的类型是可以指定的.

```c++
struct pair{
    typename1 first;
    typename2 second;
}

#include<utility>   或   #include<map>
using namespace std;
```



---

#### 8.1 pair定义

```c++
pair<typename1,typename2> name;	//typename 任意基本数据类型或容器
//定义参数为string和int类型的pair
pair<string,int> p;
//如果想在定义pair时进行初始化,只需要跟上一个小括号,里面填写两个想要初始化的元素即可
pair<string, int>p("haha",5);

//临时构建一个pair
//将类型定义写在前面,后面用小括号内两个元素的方式
pair<string,int>("haha",5);
//使用自带的make_pair函数
make_pair("haha",5);
```



---

#### 8.2 pair容器内元素的访问

pair中只有两个元素，分别是first和second，按正常结构体的方式去访问.

```c++
pair<string,int> p;
p.first="haha";
p.second=5;
cout<<p.first<<" "<<p.second<<endl;
p=make_pair("xixi",55);
cout<<p.first<<" "<<p.second<<endl;
p=pair<string,int>("heihei",555);
cout<<p.first<<" "<<p.second<<endl;

//haha 5
//xixi 55
//heihei 555
```



---

#### 8.3 pair常用函数

​        比较操作数,两个pair类型数据可以直接使用== !=等等比较大小,**先以first的大小作为标准,只有当first相等时才去判别second的大小**

```c++
pair<int,int> p1(5,10);
pair<int,int> p2(5,15);
pair<int,int> p3(10,5);
if(p1<p3) printf("p1<p3\n");
if(p1<=p3) printf("p1<=p3\n");
if(p1<p2) printf("p1<p2\n");
//p1<p3
//p1<=p3
//p1<p2
```



---

#### 8.4 pair的常见用途

1. 用来代替二元结构体及其构造函数,可以节省编码时间
2. 作为map的键值对来进行插入,例如下面的例子

```c++
map<string,int> mp;
mp.insert(make_pair("heihei",5));
mp.insert(pair<string,int>("haha",10));
for(map<string,int>::iterator it=mp.begin();it!=mp.begin();it++){
	cout<<it->first<<" "<<it->second<<endl;
}
//haha 10
//heihei 5
```





---

## 9. algorithm头文件下的常用函数

#### 9.1 max()、min()和abs()

​	max(x,y)和min(x,y)分别返回x和y中的最大值和最小值，且**参数必须是两个**(可以是浮点数)。如果返回三个数x、y、z的最大值，可以使用max(x,max(y,z))的写法

​	abs(x)返回x的绝对值。注意：x必须是整数，浮点型的绝对值请用math头文件下的fabs

---

#### 9.2  swap()

​	swap(x,y)用来交换x和y的值

```c++
int x=1,y=2;
swap(x,y);
printf("%d %d",x,y);
//2 1
```



---

#### 9.3 reverse()

​	reverse(it,it2)可以将数组指针在[it,it2)之间的元素或容器的迭代器在[it,it2)范围内的元素进行反转。

```c++
int a[10]={10,11,12,13,14,15};
reverse(a.a+4);	//将a[0]~a[3]反转
//printf   13 12 11 10 14 15

string str="abcdefghi";
reverse(str.begin()+2,str.begin()+6);
//printf abfedcghi
```



---

#### 9.4 next_permutation()

next_permutation()给出一个序列在全排列中的下一个序列

```c++
123 132 213 231 312 321
```

这样231的下一个序列就是312

```c++
int a[10]={1,2,3};
do{
    printf("%d%d%d\n",a[0],a[1],a[2]);
}while(next_permutation(a,a+3));
//	123
    132
    213
    231
    312
    321
```



---

#### 9.5 fill()	

​	fill()可以把数组或容器中的某一段区间赋为某个相同的值。和memset不同，这里可以给数组类型对应范围中任意值。

```c++
int a[5]={1,2,3,4,5};
fill(a,a+5,233);
//printf 233 233 233 233 233
```



---

#### 9.6 sort()

1. sort的函数形式

```c++
sort(首元素地址(必填),尾元素地址的*下一个地址(必填),比较函数(非必填));
//默认递增

```

2. 比较函数cmp

- 基本数据类型排序

   默认从小到大排序，字典序

   ```c++
   bool cmp(int a,int b){
       return a>b;	//当a>b时把a放在b前面
   }
   sort(a,a+4,cmp);//从大到小排序
   
   ```

- 结构体类型排序

   ```c++
   struct node{
       int x,y;
   }ssd[10];
   
   bool cmp(node a,node b){
       return a.x>b.x;			//按x值从大到小对结构体数组ssd排序
   }
   
   bool cmp(node a,node b){
       if(a.x!=b.x)	return a.x>b.x;			
       else return a.y<b.y;
       //按x值从大到小对结构体数组ssd排序，若x相等然后再按y从小到大
   }
   
   sort(ssd,ssd+10,cmp);
   ```

- STL容器排序

   只有**vector、string、deque**是可以用sort的，set、map这种容器都是用红黑树实现的，元素本身有序。

   ```c++
   bool cmp(int a,int b){
       return a>b;	//当a>b时把a放在b前面
   }
   int main(){
       vector<int> vi;
       vi.push_back(3);
       vi.push_back(1);
       vi.push_back(2);
       sort(vi.begin(),vi.begin+3,cmp);
       printf//3 2 1
   }
   ```

   ```c++
   string str[3]={"bbbb","cc","aaa"};
   sort(str,str+3);//将string数组按字典序从小到大输出
   printf//aaa bbbb cc
       
   bool cmp(string str1,string str2){//按string的长度从小到大排序
   	return str1.length()<str2.length();
   }
   printf//cc aaa bbbb
   ```



---

#### 9.7 lower_bound()和upper_bound()

`lower_bound()`和`upper_bound()`需要用在一个**有序**数组或容器中。		

`lower_bound(first,last,val)`用来寻找在数组或容器的`[first,last)`范围内**第一个值大于等于**`val`元素的位置，如果是数组，返回该位置的指针；如果是容器，返回该位置迭代器

`upper_bound(first,last,val)`用来寻找在数组或容器的`[first,last)`范围内**第一个值大于**`val`元素的位置，如果是数组，返回该位置的指针；如果是容器，返回该位置迭代器

如果数组或容器中没有需要寻找的元素，则`lower_bound()`和`upper_bound()`均返回可以插入该元素的位置的指针或迭代器(即假设存在该元素时，该元素应当在的位置)

```c++
int a[10]={1,2,2,3,3,3,5,5,5,5};
int *lowerPos=lower_bound(a,a+10,-1);
int *upperPos=upper_bound(a,a+10,-1);
printf("%d %d",lowerPos-a,upperPos-a);//0 0
int *lowerPos=lower_bound(a,a+10,1);
int *upperPos=upper_bound(a,a+10,1);
printf("%d %d",lowerPos-a,upperPos-a);//0 1
int *lowerPos=lower_bound(a,a+10,3);
int *upperPos=upper_bound(a,a+10,3);
printf("%d %d",lowerPos-a,upperPos-a);//3 6
int *lowerPos=lower_bound(a,a+10,4);
int *upperPos=upper_bound(a,a+10,4);
printf("%d %d",lowerPos-a,upperPos-a);//6 6
int *lowerPos=lower_bound(a,a+10,6);
int *upperPos=upper_bound(a,a+10,6);
printf("%d %d",lowerPos-a,upperPos-a);//10 10
```

