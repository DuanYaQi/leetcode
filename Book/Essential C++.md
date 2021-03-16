# Essential C++



## 1. C++编程基础

### 1.1. 如何撰写C++程序



### 1.2. 对象的定义与初始化

```c++
// 构造函数语法 constructor syntax
int num_tries(0);

#include<complex>
complex<double> purei(0, 7);
```

如果对象需要多个初值，用 = （assignment）运算符赋值（沿袭自C语言）无法实现 



---

### 1.3. 撰写表达式

#### 运算符的优先级

​	上层优先于下层/同一行由左至右

逻辑运算符NOT

算数运算符 *  /  %

算数运算符 +  -

关系运算符 <  >  <=  >=

关系运算符 ==  !=

逻辑运算符 AND

逻辑运算符 OR

赋值assignment 运算符 =



---

### 1.4. 条件语句和循环语句

switch 每个 case 最后要记得 break 

while 用 break 或 continue 终止迭代



---

### 1.5. 如何运用array和vector

vector 是个 class template，所以在类名后的尖括号内需要指定其元素类型，大小写在元素名后的小括号中

```c++
vector<int> vt(vt_size);
```



---

### 1.6. 指针带来弹性

操作指针（代表某特定内存地址），不直接操作对象。

```c++
int a = 1024;
int *p = &a;  // 指针 p 保存 a 所在的内存地址  &取址运算符 *取值运算符
```

指针：既可以让我们操作指针包含的内存地址，也可以让我们操作指针所指的对象值。

一个未指向任何对象的指针，地址值为0。或称为 null 指针。

class object 关联了可以调用的操作。如果要通过指针来选择操作，必须改用 `->` （arrow） 而非 `.` （dot）



---

### 1.7. 文件的读写

**写**

```c++
#include<fstream>
// 以输出模式开启seq_data.txt
ofstream outfile("seq_data.txt"); 
// 以追加模式打开，保留原文件内容，新数据加末尾
ofstream outfile("seq_data.txt", ios_base::app); 
if (!outfile) 
    cerr << "Error" << endl;
else 
    outfile << user_name << num_tries << num_right << endl;
```

**读**

```c++
// 以读取模式开启文件
ifstream infile("seq_data.txt");
if (!infile)
    cerr << "Error";
else{
    while (infile >> name) {
        infile >> nt >> nc;
        if (....) {....}
    }
}
// while 每次迭代三个>> 会读完一行信息，直到末尾。
```

**读写**

```C++
// 同时读写 in/append mode
fstream iofile("seq_data.txt", ios_base::in|ios_base::app);
if (!iofile)
    cerr << "Error";
else{
    // 文件重新定位至起始处
    iofile.seekg(0);
}
```

追加模式打开档案，文件位置会位于**末尾**。因为写入操作会添加在文件末尾。




---

## 2. 面向过程的编程风格



---

## 3. 泛型编程风格



---

## 4. 基于对象的编程风格



---

## 5. 面向对象编程风格



---

## 6. 以template进行编程



---

## 7. 异常处理