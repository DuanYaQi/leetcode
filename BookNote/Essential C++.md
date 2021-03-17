# Essential C++

## Question

- [ ] 2.2. 调用函数-Pass by Reference  `我们无法令rval转而代表jval`。
- [ ] 3.6. 如何设计一个泛型算法-Function Object Adapter `less<int>` 中的 int 是根据什么设定的





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

break 在循环语句中作用是 **跳出循环并终于整个循环语句**继续执行

continue 在循环语句中作用是 **终止当前循环并重新执行新的循环**

**嵌套循环**中的break和continue都只对一层循环起作用，**用在内层循环时，只对内层循环其作用，对外层循环无影响**。



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

一般程序编写法则，以**参数传递**作为函数间的沟通方式，比“”直接将对象定义于 file scope”更适当。如果函数过度依赖定义于 file scope 内的对象，就比较难以在其他环境中重用。

**函数**内第二个参数是声明对象的一个 pointer，可以设定默认值为 0。reference 不同于 pointer，无法被设置为 0。reference一定得代表某个对象。

- 规则一，默认值的解析（resolve）操作由**最右边开始进行**，如果某个参数提供了默认值，那么这一参数右侧的所有参数都必须具有默认参数值。

```c++
//非法
void display (ostream &os = cout, const vector<int> &vec );
```

- 规则二，默认值只能指定一次，可以在函数**声明**处，也可以在函数**定义**处，但不能两个都指定。

为了更高的可见性，将默认值放在函数**声明**处。



---

### 2.4. 使用局部静态对象

需要将每次调用函数计算出来的元素值**储存**起来，在函数内声明**局部**（local）**对象**并不能解决该问题。因为局部对象在每次调用函数时建立，并在函数结束的同时被弃置。

如果将对象定义于文件作用域之中，又过于冒险。**为了节省函数间的通信问题而将对象定于于文件作用域内，比较冒险。通常文件作用域对象会打乱不同函数间的独立性。**

解法便是使用**局部静态对象**（local static object）。

```c++
const vector<int>*
fibon_seq (int size) {
	static vector<int> elems;
	// ....
	return &elems;
}
```

elems 被定义为函数中的局部静态对象。和局部非静态对象不同的是，**局部静态对象所处的内存空间，即使在不同的函数调用过程中，依然持续存在**。不像之前一样在函数每次被调用就被破坏又被重新建立。



---

### 2.5. 声明inline函数

一个大函数编程三个小函数，执行性能不理想，只好再将三个小函数重新组合成一个。**将这些函数声明为 inline**

面对一个 inline 函数，编译器可将该函数的**调用操作**改为以一份函数代码**副本代替**。这将使获得性能改善。

最适合被声明为inline的函数：**体积小，常被调用，所从事的计算并不复杂。**



---

### 2.6. 提供重载函数

**函数重载**（function  overloading）机制，是我们可以传入**不同类型甚至不同数量的参数**给函数。

**参数列表**（parameter list）不相同（类型或数量）的两个或多个函数，可以拥有相同的函数名称。

编译器**无法**根据**返回类型**来区分两个具有相同名称的函数。



---

### 2.7. 定义并使用模板函数

复杂函数重载的方案是，将同样的代码复制多份，然后针对不同部分进行修改。

**函数模板**（function template）机制让我们得以将**单一函数的内容**与传入的**各种类型**绑定（bind）起来。

函数模板将参数列表中指定的全部参数的类型信息抽离了出来。 关键字 **template**，其后紧接着以成对尖括号包围起来的一个或多个标识符。这些标识符用以表示推迟决定的类型。

```c++
template <typename elemType>
void display_message(const strign &msg, 
                     const vector<elemType> &vec) {
	cout << msg;
    for (int ix = 0; ix < vec.size(); ++ix) {
        elemType t = vec[ix];
        cout << t << '';
    }
}
```

关键字typename表示，elemType在函数中是一个**暂时放置类型的占位符**。

函数模板的参数列表通常由两种类型构成，一类是**明确**的类型，另一类是**暂缓决定**的类型。

如果函数具备多种实现方式，我们可将它**重载**（overload），其每份实例提供的是相同的通用服务。如果让程序代码主体不变，仅仅改变其中用到的数据类型，可通过函数模板达到。

函数模板同时也可以是重载函数

```c++
template <typename elemType>
void display_message(const strign &msg, 
                     const vector<elemType> &vec);

template <typename elemType>
 void display_message(const strign &msg, 
                     const list<elemType> &vec);                    
```



---

### 2.8. 函数指针带来更大的弹性

相同的过程，只有调用的函数名不一样时，可以用函数指针。

**函数指针**（pointer to function），指明其所指函数的**返回类型**及**参数列表**。函数指针的定义必须将*放在某个位置，表示这份定义所表现的是一个指针，最后，给予一个名称。

```c++
const vector<int>* (*seq_ptr)(int);

返回类型 const vector<int>*    这里比较复杂返回类型是个容器指针
参数列表内容为int
名程为seq_ptr
```



```c++
bool seq_elem (int pos, int &elem, const vector<int>* (*seq_ptr)(int)){
    
    const vector<int> *pseq = seq_ptr(pos);
    
    if (!pseq) {
        elem = 0;
        return false;
    }
    
    
    elem = (*pseq)[pos-1];
    return true;
}
```



```c++
const vector<int> *pseq = seq_ptr(pos);
```

会间接调用 seq_ptr 所指向的函数。

我们可以给予函数指针初值，初值为0，表示未指向任何函数。也可以拿某个函数的地址作为初值，提供**函数名**即可。

```c++
//将 fibon_seq() 的地址赋值给 seq_ptr
seq_ptr = fibon_seq;
```



特别的**函数指针数组**，存放**各函数地址**

```c++
const vector<int>* (*seq_array[])(int) = {
    fibon_seq, 	lucas_seq, 	pell_seq,
    triang_seq,	square_seq,	pent_seq
};
```



如果想要以明确函数的方式来产生 pell 数列，通过一组辅助记忆的常量来进行索引操作。也可以看做用**可以理解的单词代替数组下标数字**

```c++
enum ns_type {
    ns_fibon, 	ns_lucas, 	ns_pell,
    ns_triang, 	ns_square, 	ns_pent
};
```

关键字enum定义出**枚举类型**（enumerated type）。其中每个项称为**枚举项**（enumerator）。默认情况下，第一个枚举项为0，递增+1。



---

### 2.9. 设定头文件

如果五个程序文件都调用2.8中的`seq_elem()`函数前，就必须在每个文件顶部进行声明。

可以将函数声明放在头文件中，并在每个程序代码文件内**包含**（include）这些函数声明即可。

因此只需为函数**维护一份声明**即可，头文件控制名`.h`。不过可以有很多声明。**不把函数的定义放在头文件**，因为同一个程序的多个代码文件可能都会包含这个头文件。原因：

- **暴露**了实现细节
- 头文件被包含到不同的源文件中，会导致**链接冲突**
- 头文件被包含到不同的源文件中，会导致有多份实现被编译出来，**增大可执行体的体积**



“只定义一份”的规则有例外：inline函数的定义。**必须将inline函数的定义放在头文件中**，而不是放在不同的程序代码文件。风险：

- 使用 inline 的副作用，首先在于代码的体积变大了；其次则是，这个关键字严格算起来并不是 C 语言的关键字，使用它多少会带来一些移植性方面的风险
- 使用 static 。所有包含此头文件的源文件中都会存在此函数的一份副本，代码也有一定程度的膨胀。



**在文件作用域内定义的对象，如果被多个文件访问，就应该被声明在头文件中**。

```c++
const int seq_cnt = 6;
const vector<int>* (*seq_array[seq_cnt])(int); // error
```

这并不正确，因为它会被解读成 `seq_array`的定义而非声明。一个对象只能在程序中被定义一次。在上述定义前加上关键字 **extern**，它便成为一个声明：

```c++
extern const vector<int>* (*seq_array[seq_cnt])(int);
```

但为什么`seq_cnt`前不用加 extern ？因为`seq_cnt`是一个 **const object**，它的定义只要一出文件之外便不可见。意味着我们可以在多个代码文件中加以定义。而 `seq_array` 是一个**指向 const object 指针**。



如果头文件和程序代码文件位于同一磁盘目录下，可以使用双引号，如果不在同一目录，则使用尖括号。**减少编译器搜索头文件时间**。



---

##  3. 泛型编程风格

Standard Templated Library（STL）主要由两种组件构成：容器（container）和泛型算法（generic algorithm）。

---

### 3.1. 指针的算术运算

```c++
int min ( int array[24] ) {1,2,3,4,5,6,...,24}
```

array并**不会以传值方式**复制一份，而且可以传递**任意大小**（不一定为24）的array给函数。

当数组被传给函数，或是由函数中返回，仅有第一个元素的地址会被传递。

```c++
int min ( int *array ) {1,2,3,4,5,6,...,24}
```

函数可接受任意大小。指向array开头的指针，使我们得以开始对array进行读取操作。



题目：给定一个储存整数的vector/array，以及一个整数值。如果此值存在于 vector/array 内，返回一个指针指向该值；否则返回 0。则使用函数模板，

问题：

- 将array的元素传入find（），而非指明该array

- 将vector的元素传入find（），而非指明该vector

```c++
template <typename elemType>
elemType* find(const elemType *array, int size, const elemType &value) {
    if (!array || size < 1) return 0;
    for (int ix = 0; ix < size; ++ix) {
        if (array[ix] == value) return &array[ix];
    }
    return 0;
}
```

​	由于传递给find()的array是以其第一个元素的指针传入，可以通过指针访问元素，但也可以改用下标（subscript）运算符，就如同array是个对象（而非指针形式）一般。

事实上所谓**下标操作就是将array的起始地址加上索引值，产生出某个元素的地址，然后该地址再被提领（dereference）以返回元素值**。

```c++
array[2] ==  *(array + 2); //true
```

若 array 的第一个元素地址为1000，且array类型为int，那么array+2地址为1000 + 4 * 2。此为指针的算术运算。其中 4 为 int 的长度 4 byte。

另一种实现，通过指针来进行每个元素的定位。每次迭代 array 递增1。array为地址 *array为元素值。

```c++
template <typename elemType>
elemType* find(const elemType *array, int size, const elemType &value) {
    if (!array || size < 1) return 0;
    for ( int ix = 0; ix < size; ++ix, ++array ) {
        if ( *array == value ) return array;
    }
    return 0;
}
```



另一种实现，使用第两个指针取代参数size。此指针扮演着标兵的角色。可以让我们将array的声明从参数列表中完全移除。

```c++
template <typename elemType>
elemType* find(const elemType *first, const elemType *last, const elemType &value) {
    if (!first || !last ) return 0;
    for ( ; first != last; ++first ) {
        if ( *first == value ) return first;
    }
    return 0;
}
```



考虑完array，我们来考虑vector，与array不同的是vector可以为空，如果输入为空，则出错

因此定义两个内联函数，确定vector初始地址和最终地址。

```c++
template <typename elemType>
inline elemType* begin( const vector<elemType> &vec ) {
    return vec.empty() ? 0 : &vec[0];
}

inline elemType* end( const vector<elemType> &vec ) {
    return vec.empty() ? 0 : &vec[vec.size()-1];
}

find( begin(vec), end(vec), serach_value );
```



考虑完array，vector，我们来考虑list。**指针的算术运算**不适用于list，因为list元素不一定储存在**连续空间**里。

办法是，在底层指针的行为之上提供一层抽象，取代程序原本的”指针直接操作“方式。我们把**底层指针的处理通通放在此抽象层中**，让用户无须直接面对指针操作。见3.2



---

### 3.2. 了解Iterator（泛型指针）

抽象层的实现，需要一组对象。可提供有如内置运算符（++    *    ==    !=）一般的运算符，并允许我们只为这些运算符提供一份实现代码即可。**即list iterator的++运算符是指针前进到下一个元素。vector iterator的++运算符是将目前地址加上一个元素的大小。**

可以利用C++的类机制来达到目的。



每个标准容器都提供有一个名为 `begin()` 的操作函数，可返回一个iterator，指向**第一个元素**。另一个名为 `end()` 的操作函数返回的iterator，指向**最后一个元素的下一个位置**。

```c++
for ( iter = svec.begin(); iter != svec.end(); ++iter ) {
 	cout << *iter << '';   
}
```

上述包括，iterator的**赋值（assign）、比较（compare）、递增（increment）、提领（dereference）**操作。

iterator 定义需要 **迭代对象（容器）的类型** 和 **iterator所指的元素类型**，即返回值。

```c++
vector<string> svec;
iterator<vector, string> iter; 					//定义1

vector<string> svec;
vector<string>::iterator iter = svec.begin();	//定义2
```

此处iter被定义为一个iterator，指向一个vector，返回类型为string。其初值指向svec的第一个元素。双冒号表示此iterator乃是位于 string vector定义内的嵌套（nested）类型。



面对**const vector**（跟数组一样，不能动态增加了，因为const了），我们用**const_iterator**来遍历操作：

```c++
const vector<string> cs_vec;
vector<string>::const_iterator iter = cs_vec.begin();
```

**const_iterator** 允许读取vector的元素，不允许任何写入操作。

如果通过iter调用底部string元素所提供的操作，我们可以使用arrow（箭头）运算符：

```c++
cout << iter->size() << endl;// 跟指针类似
```



现在重新实现find（），让它同时支持**指针**和**容器的iterator**

```c++
template <typename IteratorType, typename elemType>

IteratorType
find(IteratorType first, IteratorType last, const elemType &value) {
    if (!first || !last ) return 0;
    for ( ; first != last; ++first ) {
        if ( *first == value ) return first;
    }
    return 0;
}
```



---

### 3.3. 所有容器的共通操作

所有容器类（包括string类）的共通操作：

- `==`（equality）和 `!=`（inequality）运算符，返回true或false
- `=`运算符，将某个容器复制给另一个容器
- `empty()` 会在容器无热河元素时返回true，否则false
- `size()` 返回容器内目前持有的元素个数
- `clear()` 删除所有元素



每个容器都提供了 `begin()` 和 `end()` 两个函数，分别返回指向容器的第一个元素和最后一个元素的下一位置的iterator

-  `begin()`  返回一个iterator，指向容器的第一个元素
-  `end()` 返回一个iterator，指向容器最后一个元素的下一位置。

所有容器都提供 `insert()` 用以插入元素，以及 `erase` 用以删除元素。

-  `insert()`  将单一或某个范围内的元素插入容器内
-  `erase()` 将容器内的单一元素或某个范围内的元素删除。



---

### 3.4. 使用顺序性容器

排列有序。 vecotr和list是两个最主要的顺序性容器。

**vector插入删除效率很低，访问效率高**。**list插入删除效率相对较高，访问效率低**。

vector比较适合数列。list适合随机插入数据。

deque也是顺序性容器。和vector相似，连续内存。适合**前端插入，末端删除**。

**定义**方式有五种

```c++
//1. 产生空容器
list<string> slist;
vector<int> ivec;

//2. 产生特定大小的容器。初值为默认值0
list<int> ilist(1024);
vector<string> svec(32);

//3. 产生特定大小容器，指定初值
list<string> slist(16, "unassigned");
vector<int> ivec(10, -1);

//4. 通过一堆iterator产生容器。iterator用来标示一整组作为初值的元素的范围
int ia[8] = {1, 1, 2, 3, 5, 8, 13, 21};
vector<int> fib(ia, ia+8);

//5. 根据某个容器产生出新容器。复制原容器内的元素，作为新容器的初值
list<string> slist; 		//空容器
//填充slist
list<string> slist2(slist);	//将slist赋值给slist2
```



有两个特别的操作函数，允许在容器末尾进行**插入和删除** `push_back()` 和 `pop_back()`。

`push_back()` 会在末端插入一个元素，`pop_back()` 会在删除最后一个元素，

此外，list和deque还提供了 `push_front()` 和`pop_front()`。

**读取**最前端元素的值 `front()` 或末端元素的值 `back()`。



`push_back()` 和 `push_front()` 都属于特殊化的插入操作。每个容器除了拥有通用的插入函数 `insert()` 还支持四种变形

```c++
iterator insert (iterator position, elemType value) 
    //将value插入至位置position前，返回被插入的元素。
void insert (iterator position, int count, elemType value) 
    //将count个value插入至位置position前。
void insert (iterator1 position, iterator2 first, iterator2 last) 
    //将[first,last)标识的元素插入至位置position前。
iterator insert (iterator position) 
    //将默认值插入至位置position前。
```



`pop_back()` 和 `pop_front()` 都属于特殊化的删除操作。每个容器除了拥有通用的删除函数 `erase()` 还支持四种变形

```c++
iterator erase (iterator position) 
    //删除位置position所指的元素。
iterator erase (iterator first, iterator last) 
    //删除[first,last)标识的元素的元素。
```



---

### 3.5. 使用泛型算法

```c++
#include<algorithm>
```

`find()` 搜索**无序**集合中是否存在某值；

`binary_search()` 用于**有序**集合的搜索；

`count()` 返回数值相符的元素数目；

`search()` 比对某个容器内是否存在某个**子序列**；

`max_element` 取数列最大元素值；



---

### 3.6. 如何设计一个泛型算法

给予一个整数vector，返回一个新的vector，其中包含原vector中小于10的所有数值。

```c++
bool less_than (int v1, int v2) {
    return v1 < v2 ? true : false;
}

bool greater_than (int v1, int v2) {
    return v1 > v2 ? true : false;
}

vector<int> filter (const vector<int> &vec, int filter_value, bool (*pred)(int int)){
    vector<int> nvec;
    for (int ix = 0; ix < vec.size(); ++ix) {
        if ( pred( vec[ ix ], filter_value) )
            nvec.push_back( vec[ix] );
    }
}

int main () {
    vector<int> big_vec;
    int value;
    // 填充big_vec和value
    vector<int> lt_10 = filter(big_vec, value, less_than );
    return 0;
}
```

定义了的**函数指针** `pred`，输入int和int，返回bool。



```c++
//找出每个等于10的元素
iterator find (iterator first, iterator last, int val);

int count_occurs (const vector<int> &vec, int val) {
    vector<int>::const_iterator iter = vec.begin();
	int occurs_count = 0;
    while ( (iter = find(iter, vec.end(), val)) != vec.end() ) {
        ++occurs_count;
        ++iter;//指向下一个元素，更改搜索范围
    }
    return occurs_count;
}
```



#### Function Object

**function object**，是某种class的实例对象，这类class对function call**运算符做了重载操作**，如此一来可使function object被当成一般函数来使用。



标准库事先定义了一组function object，分为算术运算（arithmetic）、关系运算（relational）和逻辑运算（logical）。以下列表中的type在实际使用时会被替换为内置类型或class类型

- 六个**算术**（加、减、非、乘、除、模）运算：`plus<type>，minus<type>，negate<type>，multiplies<type>，divides<type>，modules<type>`

- 六个**关系**运算：`less<type>，less_equal<type>，greater<type>，greater_equal<type>，equal_to<type>，not_equal_to<type>`
- 三个**逻辑**（&&    ||    ！）运算：`，，`



欲使用事先定义的function object，首先得包含相关头文件：

```c++
#include<functional>
```

sort函数默认使用底部元素类型所提供的less-than运算符，将元素**升序**排序。如果改用`greater_than` function object传入，元素就会**降序**排序。

```c++
sort(vec.begin, vec.end(), greater<int>() );
```

其中`greater<int>()` 会产生一个未命名的class template object，传给`sort()`。同理

```c++
binart_search(vec.begin, vec.end(), elem, greater<int>() );
```



#### Function Object Adapter

function object `less<type>` 期望外界传入两个值，如果第一个值小于第二个值就返回true。如果其中一个数是固定的。我们可以将`less<type>` 转化为一个**一元**（unary）运算符。可通过参数**绑定** bind 来完成。

**绑定适配器**（binder adapter） 会将function object的参数绑定至某特定值，使**二元**（binary）function object转换为**一元**。

```c++
vector<int> filter (const vector<int> &vec, int val, less<int> &lt){
    vector<int> nvec;
    vector<int>::const_iterator iter = vec.begin();
    
    //bind2nd(less<int> ,val); 内置函数 还有bind1st
    //会把val绑定于 less<int> 的第二个参数身上
    //less<int> 会将每个元素拿来和val比较
    
    while( (iter = find_if(iter, vec.end(), bind2nd(lt, val)) ) {
        nvec.push_back(*iter);
        iter++;
    }
    return nevc;
}
```

为了消除`filter()`与`vector`容器类型的依赖关系，以使`filter()`更加泛化。将`filter()`改为function template，并将元素类型加入template的声明中。为了消除它和容器类型间的依赖性，我们传入一对 `iterator[first,last)`，并在参数列表中增加另一个`iterator`，用以指定从何处开始复制元素。<span id="filter"></span>

```c++
template <typename InputIterator, typename OutputIterator, typename ElemType, typename Comp>

OutputIterator
filter (InputIterator first, InputIterator last, OutputIterator at, const ElemType &val, Comp pred)
{
    while( (first = find_if(first, last, bind2nd(pred, val))) != last ) {
        // 观察进行情形
        cout << "found value: " << *first << endl;
        
        // 执行assign操作，然后令两个iterator前进
        *at++ = *first++;
    }
    return at;
}

int main() {
    const int elem_size = 8;
    int ia[elem_size] = {12, 8, 43, 0, 6, 21, 3, 7};
    vector<int> ivec(ia, ia+elem_size);


    int ia2[elem_size];
    vector<int> ivec2(elem_size);

    cout << "filtering integer array for values less than 8" << endl;
    filter( ia, ia+elem_size, ia2, elem_size, less<int>() );
//？？？？？？？？？？？？？？？？？？？？？less<int>()
    cout << "filtering integer vector for values greater than 8" << endl;
    filter(ivec.begin(), ivec.end(), ivec2.begin(), elem_size, greater<int>() );

    return 0;
}
```



#### 小练习

将 `sub_vec()` 改为一个template function

```c++
vector<int> sub_vec (const vector<int> &vec, int val) {
    vector<int> local_vec(vec);
    sort(local_vec.begin(), local_vec.end());

    vector<int>::iterator iter = find_if( local_vec.begin(),
                                        local_vec.end(),
                                        bind2nd(greater<int>(), val));
    local_vec.erase(iter, local_vec.end());
    return local_vec;
}
```

写成模板形式

```c++
template <typename InputIterator, typename OutputIterator, typename ElemType, typename Comp>

OutputIterator
sub_vec (InputIterator first, InputIterator last, OutputIterator at, const ElemType &val, Comp pred)
{
    sort(first, last);
    last = find_if(first, last, bind2nd(pred, val)); //找到等于val的值
        
    while( first != last ) {
        // 观察进行情形
        cout << "found value: " << *first << endl;
        
        // 执行assign操作，然后令两个iterator前进
        *at++ = *first++;
    }
    return at;
}


// 注意 equal_to
int main() {
    const int elem_size = 8;
    int ia[elem_size] = {12, 8, 43, 0, 6, 21, 3, 7};
    vector<int> ivec(ia, ia+elem_size);


    int ia2[elem_size];
    vector<int> ivec2(elem_size);

    cout << "filtering integer array for values less than 8" << endl;
    sub_vec( ia, ia+elem_size, ia2, elem_size, equal_to<int>() ); 

    cout << "filtering integer vector for values greater than 8" << endl;
    sub_vec(ivec.begin(), ivec.end(), ivec2.begin(), elem_size, equal_to<int>() );

    return 0;
}
```



---

### 3.7. 使用Map

字典是map一个不错的实例。

map对象有一个名为 `first` 的member，对应于`key` ；有一个名为 `second` 的member，对应于`value`。

查询key是否在map中

- `if(words['study'])`，但这样如果不在，key会被自动加入map。
- `words.find('study')`，有返回iterator；没有返回end()；
- `words.count('study')`，统计个数。普通map肯定返回**最大为1**，如果要储存多分相同key值，需使用multimap。



---

### 3.8. 使用Set

set由一群 key 组合而成。适合判断某值是否在某个集合内。例如图遍历（graph traversal）。可以使用set储存遍历过的节点（node）。

对于任何 key 值，set 只能储存一份。如果要储存多份相同的 key 值，使用 multiset 。

默认less-than运算符进行排列。

插入 insert( val )  / insert(first, last) 



---

### 3.9. 如何使用Iterator Inserter

3.6中对filter()的**[实现](#filter)**，我们将源端中每一个符号条件的元素一一赋值至目的端

```c++
while( (first = find_if(first, last, bind2nd(pred, val))) != last ) {
    // 观察进行情形
    cout << "found value: " << *first << endl;

    // 执行assign操作，然后令两个iterator前进
    *at++ = *first++;
}
```

必须确定目的端容器足够大，返回有效的地址位置。让目的端跟输入一样大，却有些浪费资源。标准库提供了三个所谓的**插入适配器** insertion adapter，这些 adapter 让我们得以**避免使用**容器的 **assignment** 运算符。

- `back_inserter()` 会以容器的 `push_back()` 函数取代 assignment 运算符。对 vector 来说，这是比较适合的 inserter。传入 `back_inserter` 的参数，应该就是容器本身：

```c++
vector<int> result_vec;
unique_copy(ivec.begin(), ivec.end(), back_inserter(result_vec));
```

- `inserter()` 会以容器的 `insert()` 函数取代 assignment 运算符。`inserter()` 接受两个参数：一个是**容器**，另一个是 iterator，指向**容器内的插入操作起点**。

```c++
vector<string> svec_res;
unique_copy(svec.begin(), svec.end(), inserter( svec_res, svec_res.end()));
```

- `front_inserter()` 会以容器的 `push_front()` 函数取代 assignment 运算符。这个 inserter 只适用于 list 和 deque：

```c++
list<int> ilist_clone;
copy(ilist.begin(), ilist_end(), front_inserter(ilist_clone));
```



这些 adapter 并不能用在 array 上。array 并不支持元素插入操作。之前对 vector 每个位置的赋值操作，替换为在尾部**插入**操作，这样就**不用考虑**容器的**大小**问题，**效率比较高**。



---

### 3.10. 使用iostream Iterator

标准库由供输入及输出使用的 iostream iterator 类。称为 istream_iterator 和 ostream_iterator，分别支持单一类型的元素读取和写入。



就像所有的iterator一样，需要一对iterator `first`和`last`，用来标示元素范围。

```c++
#include<iterator>
istream_iterator<string> is(cin);
istream_iterator<string> eof;
```

`first` iterator，它将 `is` 定义为一个”绑定标准输入设备“的 `istream_iterator`。只要定义时不指明 istream 对象，即为`end-of-file` 即代表`last`。

```c++
ostream_iterator<string> os(cout, " ");
```

将 `os` 定义为一个”绑定至标准输出设备“ 的 `ostream_iterator` 。

```c++
//标注输入输出设备显示
int main() {
    istream_iterator<string> is(cin);
	istream_iterator<string> eof;
    
    vector<string> text;
    copy(is, eof, back_inserter(text));
    
    sort(text.begin(), text.end());
    
    ostream_iterator<string> os(cout, " ");
    copy(text.begin(), text.end(), os);
    return 0;
}
```



```c++
//文件读写
int main() {
    ifstream in_file("input.txt");
    ofstream out_file("output.txt");
    
    if(!in_file || !out_file) {
        cerr << "!! unable to open the necessary files." << endl;
        return -1;
    }
    
    istream_iterator<string> is(in_file);			//绑定的对象不同
	istream_iterator<string> eof;
    
    vector<string> text;
    copy(is, eof, back_inserter(text));
    
    sort(text.begin(), text.end());
    
    ostream_iterator<string> os(out_file, " "); 	//绑定的对象不同
    copy(text.begin(), text.end(), os);
    return 0;
}
```







---

## 4. 基于对象的编程风格



---

## 5. 面向对象编程风格



---

## 6. 以template进行编程



---

## 7. 异常处理