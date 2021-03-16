# Essential C++

## Question

- [ ] 2.2 调用函数-Pass by Reference  `我们无法令rval转而代表jval`。





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

### 2.1. 如何编写函数

返回类型 + 函数名 + 参数列表 + 函数体

返回类型 + 函数名 + 参数列表 = 函数原型

每个值类型都有值域（domain），避免溢出（overflow）



---

### 2.2. 调用函数

传址by reference 和 传值by value



#### **Pass by Reference**

​	reference 扮演着外界与对象之间一个间接手柄的角色。用 `&` 连接其关系。

```c++
int ival = 1024;	//对象，类型int
int *pi = &ival;	//pointer指针 指向一个int对象
int &rval = ival;	//reference引用 代表一个int对象

// 1 将jval赋值给rval代表的对象（也就是ival）。无法令rval转而代表jval，因为C++不允许改变reference所代表的对象 ??????????????????????????????????????????????????
int jval = 4096
rval = jval;

// 2 将ival（rval所代表的对象）的地址赋值给pi。并未令pi指向rval。
pi = &rval;
```

面对 **reference** 的所有操作都和面对 **reference 所代表的对象**所进行的操作**一致**。

当以 by reference 方式将对象作为函数参数传入时，对象本身并不会复制出另一份——复制的是对象的**地址**。函数中对该对象进行的任何操作，都相当于是对传入的对象进行间接操作。

将参数声明为 reference 的两个理由

- 希望直接对所传入的对象进行修改。
- 降低复制大型对象的额外负担。

**如果直接传入参数的地址，速度会更快。** 即以pointer形式。

pointer 参数和 reference 参数之间更重要的差异是，pointer 可能指向某个实际对象。需要检查其值。至于 reference，则必定会代表某个对象，所以不需要**检查**。

**传递内置类型时，不要使用传址方式。传址机制主要用于传递 class object。**



#### 作用域及范围

函数是暂时位于程序**堆栈**（内存内的一块特殊区域）之**上**。局部对象就放在这块区域中。当函数执行完毕，这块区域的内容便会被弃置。于是局部对象不复存在。局部对象不能以 pointer 或 reference 形式返回，因为不存在；需要以传值形式返回，返回的是对象的副本，在函数之外仍然存在。

为对象分配的内存，其存活时间成为**储存期**（storage duration）或**范围**（extent）。每次函数执行，都会为**局部对象**分配内存，函数结束便会将局部对象内存释放。称此对象具有**局部性范围**（local extent）。函数参数也具有局部性范围。

**对象**在程序内的**存活区域**称为该对象的**作用域**（scope）。**局部对象**在函数内拥有**局部作用域**（local scope），其名称在函数外不可见。

**对象**如果在**函数外声明**，具有所谓的**文件作用域**（file scope）。且从其声明点至文件末尾都可见。文件作用域内的对象也具备所谓的**静态范围**（static extent），即该对象的内存在 main() 开始执行前便已经分配好了，全程存在。

**内置**类型的对象，如果定义在**文件作用域**之内，**初始化为 0**。如果被定义在**局部作用域**，除非指定初值，否则**不会被初始化**。



#### 动态内存管理

**局部作用域**和**文件作用域**都是系统自动管理。第三种储存期形式称为**动态范围**（dynamic extent）。其内存由程序的**空闲空间**（free store）分配而来，也称**堆内存**（heap memory）。必须通过 **new** 表达式完成，**delete**进行释放。

```c++
// Type可为任意内置类型，或class类型
new Type (initial_value);
int *pi;
pi = new int;
```

先由堆分配出一个类型为 int 的对象，再将其地址赋给 p。默认由堆分配而来的对象，皆未经过初始化。

```c++
// new 另一种形式，可以指定初值
int *pi
pi = new int(1024);
delete pi;
```

同样先由堆分配出一个类型为 int 的对象，再将其地址赋给 p，但这个对象的值会被初始化为 1024。如果要从堆中分配数组

```c++
int *pia = new int[24];
delete [] pia;//注意delete数组需要 []
```

从堆分配一个数组，拥有24个整数，p被初始化为数组第一个元素的地址。数组中每个元素都未初始化。

**从堆分配而来的对象，具有动态范围。**

delete时**无需检查**，如果程序员不使用delete表达式，由堆分配而来的对象就永远不会被释放。成为**内存泄漏**（memory leak）



---

### 2.3. 提供默认参数值

### 2.4. 使用局部静态对象

### 2.5. 声明inline函数

### 2.6. 提供重载函数

### 2.7. 定义并使用模板函数

### 2.8. 函数指针带来更大的弹性

### 2.9. 设定头文件

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