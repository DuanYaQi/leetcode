# Sort

https://zhuanlan.zhihu.com/p/39516615

https://zhuanlan.zhihu.com/p/39519014



时间复杂度：

> 反映当数据量变化时，操作次数的多少;时间复杂度在评估时，要只保留最高项，并且不要最高项的系数。(下面用logN表示 log以2为底，N的对数)

空间复杂度：

> 是指算法在计算机内执行时，所需额外开辟的空间。

指标：

> 最高项的系数。

常数项：

> 与N的大小无关的操作。

稳定性：

> (1)稳定：如果a原本在b前面，而a=b，排序之后a仍然在b的前面。
> (2)不稳定：如果a原本在b的前面，而a=b，排序之后 a 可能会出现在 b 的后面。





**通用函数及其他**

(1)求数组长度（需要传数组，不要传数组指针）

```c++
/*  一定要注意传入的数组，而不是数组指针
	如果传入的是数组指针，sizeof 后出来的值为 8
*/
template <class T>
int len(T& arr) {
    int length = (int)sizeof(arr) / sizeof(arr[0]);  //
    return length
}
```



(2)交换数组两个数

```c++
/* ^符号 即”异或“运算符
  特点是与0异或，保持原值；
  与本身异或，结果为0。
*/
void exchange(int arr[], int a, int b) {
	if (a == b) return;
    arr[a] = arr[a] ^ arr[b];
    arr[b] = arr[a] ^ arr[b];
    arr[a] = arr[a] ^ arr[b];
}
```



(3)算法中的表达

```c++
* A代表平均时间复杂度
* B代表最坏时间复杂度
* E代表最好时间复杂度
* 省略了O()
    
/* 大数据样本下四钟最快算法的比较. 数据是随机整数，时间单位是秒

    数据规模|快速排序 归并排序 希尔排序 堆排序
    1000万 |  0.75  1.22    1.77    3.57
    5000万 |  3.78  6.29    9.48    26.54
	1亿    |  7.65  13.06   18.79   61.31
*/
```



(4)时间复杂度的大小比较

```c++
/*
  N! > x^N >... > 3^N > 2^N > N^x > 
								   ... > N^3 > N^2 > NlogN > N > logN > 1
*/
```



(5)数组和数组大小的结构体

```C++
struct arrWithSize{
    int *array;
    int size;
}
```



(6)初始化数组

```c++
	//一维 每个元素都没有初始化
    int *p = new int[10];
    //一维 每个元素初始化为 0
    int *p = new int[10](0);

    //二维 每个元素都没有初始化
    int (*bucket)[10] = new int[10][10];
    //二维 每个一维中含N个数，N为确定的数值。
    vector<vector<int>> bucket(N);

    //通过动态创建的数组，要进行内存释放，否则内存将泄漏
    //(本文中，未进行内存释放)
    delete []p;
```



(7)综合排序总结

- 思考一个排序时候，考虑时间复杂度中的指标和常数项，空间复杂度，稳定性.
- 代码规模，一定程度上说明了常数项的大小。（最终常数项的大小是看发生常数操作的次数）
- 系统的sort 方法，发现传进来的值为**数值型**，会使用**快排**，如果发现传的**还有比较器**，会使用**归并**
- 归并和快排哪种更快？
  快排比归并的常数项要低，所以要快。
- 为什么会有归并和快排两种呢？
  在比较的时候，使用**比较器**的时候，要追求一个**稳定性**，使用 **归并**排序 可以达**稳定**性的效果；使用快排不能够实现稳定性的效果。
- 面对大规模的时候，当排序量是小于等于60的时候，sort方法会在内部使用插入排序的方法（不一定是60，是一定的规模）当数据量很低的时候，插入排序的常数项低。
- 在c语言中有一版，把归并排序，改成非递归，是基于工程其他考虑。



(8)对比两个数组是否相同

```c++
bool isEqual(int firstArr[], int secondArr[]) {
    if ((fisrtArr == nullptr && secondArr != nullptr) || (fisrtArr != nullptr && secondArr != nullptr))
        return false;
    
    if (firstArr == nullptr && secondArr == nullptr) 
        return true;
    
    if (len(firstArr) != len(secondArr)) 
        return false;
    
    for (int i = 0; i < len(firstArr); ++i) {
        if (firstArr[i] != secondArr[i]) {
            cout << i << firstArr[i] << secondArr[i] << endl;
            return false;
        }
    }
    
    return true;
}
```



(9)复制数组

```c++
int* arrayCopy(int oldArray[], int length) {
    if (oldArray == nullptr) {
        return nullptr;
    }
    
    int* newArray = new int[length];
    for (int i = 0; i < length; ++i) {
        newArray[i] = oldArray[i];
    }
    
    return newArray;
}
```



(10)产生随机数组

```c++
struct arrWithSize{
    int *array;
    int size;
}

arrWithSize genRandomArr(int maxSize, int maxValue) {
    arrWithSize rArr;
    int size = (int)( (maxSize+1) * (rand()%10 / (double) 10) );
    cout << "{" << size << "}" << end;
    
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        // 随机生成[0, N]
        array[i] = (int)((maxValue+1) * (rand()%10 / (double)10));
    }
    rArr.size = size;
    rArr.array = array;
    
    return rArr;
}
```



(11)递归master公式（找最大值）

```c++
/*
     递归master公式
     T(N)的公式从大规模来看，不细分。
     T(N) = a * T(N/b)+O(n^d)
     N/b 是子过程数据量 ；a是子过程调用多少次；O(n^d)是出去过程之外剩下的数据量的多少
     if log(b)a > d => O(N^log(b)a)
     if log(b)a = d => O(N^d *logN)
     if log(b)a < d => O(N^d)
     注意 多个递归的规模必须一样，否则master公式失效。
 
  例如一个规模是1/3;一个是2/3;
     以下算法的时间复杂度：a = 2;b = 2;d = 0;所以时间复杂度为O(N)
*/
int process(int arr[], int L, int R) {
    if (L == R) {
        return arr[L];
    }
    
    int mid = (L + R) / 2;
    int leftMax = process(arr, L, mid);
    int rightMax = process(arr, mid+1, R);
	return (leftMax / rightMax) ? leftMax : rightMax;
}

int getMaxInArray(int arr[], int len) {
    return process(arr, 0, len - 1);
}
```





(12)比较器

``` c++
/*
	c++ 中的比较器要注意返回值要为 bool 类型
	比较器第一次比较完成后，下一次在比较的时候还是会含有第一次的排号的顺序
	是利用了 c++ 中 sort 函数的排序稳定性
*/
struct student{
    char name[10];
    int age;
    int classId;
}

// 年龄升序
bool cmpAge(student s1, student s2) {
    // 返回false的时候，相当于进行了一个交换操作
    return s2.age > s1.age;
}

// 班级升序
bool cmpClassId(student s1, student s2) {
    return s2.classId < s1.classId;
}

void testCmp() {
    student s1 =  {"opooc",21,100};
    student s2 =  {"cat",30,105};
    student s3 =  {"dog",1,107};
    student s4 =  {"daolao",2,107};
    student s5 =  {"dst",20,103};
    student allStu[] ={s1,s2,s3,s4,s5};
    
    sort(allStu, allStu + 5, cmpAge);
    sort(allStu, allStu + 5, cmpClassId);
}    
```



(13)vector容器

```c++
//声明一个一维容器
vector<int> vec;
//声明一个二维数组，里面每个一维数组大小为10(必填)
vector<vector<int>> vec(10);
//添加元素
vec.push_back(1);
//删除最后添加的元素
vec.pop_back();
//删除向量中迭代器指向元素
vec.erase(vec.begin() + 2); //vec[2]
//删除向量中[first,last)中元素 如下删除1234位置	前开后闭
vec.erase(vec.begin() + 1, vec.begin() + 5)
//在第零个元素前面插1
vec.insert(vec.begin(), 1);
//在第二个元素前插2
vec.insert(vec.begin() + 2, 2);
//在最后一个元素后面插的10
vec.insert(v.end(), 10);
//元素的个数
vec.size();
//清除所有元素
vec.clear();
//遍历整个数组
vector<int>:: iterator it;
for (it = vec.begin(); it != vec.end(); it++) {
    cout << *it;
}
```







---

# 非线性时间

## 归并排序 - 归并









---

## 快速排序 - 比较

https://mp.weixin.qq.com/s/8ZTMhvHJK_He48PpSt_AmQ

**快速排序是先将一个元素排好序，然后再将剩下的元素排好序**。

**快速排序的过程是一个构造二叉搜索树的过程**。



快速排序的基本思想：通过一趟排序将待排记录**分隔成独立的两部分**，其中一部分记录的关键字均比另一部分的关键字小，则可分别对这两部分记录继续进行排序，以达到整个序列有序。



实现逻辑:

> 快速排序使用分治法来把一个串（list）分为两个子串（sub-lists）。具体算法流程如下：
>
> 从数列中挑出一个元素，称为 “基准”（pivot）；
>
> 重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作；
>
> 递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序。



### 随机快速排序

> （交换排序; 时间A:NlogN,B:NlogN,E:NlogN;空间logN;不稳定）



```c++
void sort(int[] nums, int lo, int hi) {
    if (lo >= hi) {
        return;
    }
    // 对 nums[lo..hi] 进行切分
    // 使得 nums[lo..p-1] <= nums[p] < nums[p+1..hi]
    int p = partition(nums, lo, hi);
    // 去左右子数组进行切分
    sort(nums, lo, p - 1);
    sort(nums, p + 1, hi);
}
```



快速排序的核心无疑是 `partition` 函数， `partition` 函数的作用是在 `nums[lo..hi]` 中寻找一个分界点 `p`，通过交换元素使得 `nums[lo..p-1]` 都小于等于 `nums[p]`，且 `nums[p+1..hi]` 都大于 `nums[p]`：



![image-20220325123415928](assets/image-20220325123415928.png)

 `partition` 函数干的事情，其实就是把 `nums[p]` 这个元素排好序了。

剩下的元素有哪些？左边区域，右边区域，对子数组进行递归，用 `partition` 函数把剩下的元素也排好序。

![图片](assets/6400.gif)

 `partition` 函数每次都将数组切分成左小右大两部分，恰好和二叉搜索树左小右大的特性吻合。

```c++
int partition(int[] nums, int lo, int hi) {
    int pivot = nums[lo];
    // 关于区间的边界控制需格外小心，稍有不慎就会出错
    // 我这里把 i, j 定义为开区间，同时定义：
    // [lo, i) <= pivot；(j, hi] > pivot
    // 之后都要正确维护这个边界区间的定义
    int i = lo + 1, j = hi;
    // 当 i > j 时结束循环，以保证区间 [lo, hi] 都被覆盖
    while (i <= j) {
        while (i < hi && nums[i] <= pivot) {
            i++;
            // 此 while 结束时恰好 nums[i] > pivot
        }
        while (j > lo && nums[j] > pivot) {
            j--;
            // 此 while 结束时恰好 nums[j] <= pivot
        }
        // 此时 [lo, i) <= pivot && (j, hi] > pivot

        if (i >= j) {
            break;
        }
        swap(nums, i, j);
    }
    // 将 pivot 放到合适的位置，即 pivot 左边元素较小，右边元素较大
    swap(nums, lo, j);
    return j;
}
```

其中swap

```c++
// 原地交换数组中的两个元素
void swap(int[] nums, int i, int j) {
    nums[i] = nums[i] ^ nums[j];
    nums[j] = nums[i] ^ nums[j];
    nums[i] = nums[i] ^ nums[j];
}
```



**你甚至可以这样理解：快速排序的过程是一个构造二叉搜索树的过程**。



如果你每次运气都特别背，有一边的元素特别少的话，这样会导致二叉树生长不平衡：

这样的话，时间复杂度会大幅上升，后面分析时间复杂度的时候再细说。

**我们为了避免出现这种极端情况，需要引入随机性**。

常见的方式是在进行排序之前对整个数组执行 **洗牌算法** 进行打乱，或者在 `partition`函数中**随机选择数组元素**作为分界点，本文会使用前者。



```c++
// 洗牌算法，将输入的数组随机打乱
void shuffle(int[] nums) {
    Random rand = new Random();
    int n = nums.length;
    for (int i = 0 ; i < n; i++) {
        // 生成 [i, n - 1] 的随机数
        int r = i + rand.nextInt(n - i);
        swap(nums, i, r);
    }
}
```





快速排序就是一个**二叉树的前序遍历**

```c++
/* 二叉树遍历框架 */
void traverse(TreeNode root) {
    if (root == null) {
        return;
    }
    /****** 前序位置 ******/
    print(root.val);
    /*********************/
    traverse(root.left);
    traverse(root.right);
}
```











































---

## 冒泡排序 - 比较

https://zhuanlan.zhihu.com/p/39516615



---

## 插入排序 - 插入







---

## 希尔排序 - 插入





## 选择排序 - 选择











---

# 线性时间

## 堆排序 - 选择





---

## 基数排序









## 计数排序





---

# 总结

当n较大，则应采用时间复杂度为O(nlog2n)的排序方法：快速排序、堆排序或归并排序。



会问面试者知道哪些排序算法，选一个自己熟悉排序算法。讲下它的主要特点，比如**时间复杂度 / 稳定性** 这些

如果继续，一般会把重点放在 **快速排序** 和 **堆排**，进一步可能会要求手写实现。然后会讨论下在**输入是特定序列的情况下，当前的算法有什么缺点或优点**。



**基数排序**这类算法，会问下一些偏**理论**的问题，比如比较排序算法的**下界**是多少，为什么基数排序可以突破这个下界。



**『算法导论』的第二部分 『排序和顺序统计学』**，是很好的排序算法基础。几十页，认真看。

**『[编程珠玑](https://www.zhihu.com/search?q=编程珠玑&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A286065483})』第十一章 『排序』**，对快速排序做了细节性的讨论。

![img](assets/v2-c6acea068837aead97877f8fdf4a750f_720w.jpg)



![img](assets/v2-35c344cf0bac4720e57df56df9f23e86_720w.jpg)





![img](assets/v2-5e56c508652d1f3da2e95b209c8d572b_720w.jpg)



![八大经典排序算法原理（C++实现）](assets/v2-0650b3fe6427619f1d2390f94d52c4f6_1440w.jpg)





![img](assets/849589-20180402133438219-1946132192.png)





![img](assets/v2-2477e51d53090f1dfa44e91d1bfbc116_720w.jpg)

> **n指数据规模；**
>
> **k指“桶”的个数；**
>
> **In-place指占用常数内存，不占用额外内存；**
>
> **Out-place指占用额外内存**





---

# 内部非内部

![img](assets/v2-5ab3d2cfc00f3d4e61f0a7d9c1103f9c_720w.jpg)

内排序：所有排序操作都在**内存中**完成；

外排序：由于数据太大，因此把数据放在磁盘中，而排序**通过磁盘和内存**的数据传输才能进行；





---

# 比较非比较

- **比较类排序**：通过比较来决定元素间的相对次序，由于其时间复杂度不能突破O(nlogn)，因此也称为非线性时间比较类排序。
- **非比较类排序**：不通过比较来决定元素间的相对次序，它可以突破基于比较排序的时间下界，以线性时间运行，因此也称为线性时间非比较类排序。 



![img](assets/849589-20190306165258970-1789860540.png)



常见的**快速排序、归并排序、堆排序、冒泡排序**等属于**比较排序**。在排序的最终结果里，元素之间的次序依赖于它们之间的比较。每个数都必须和其他数进行比较，才能确定自己的位置。

- 在**冒泡排序**之类的排序中，问题规模为n，又因为需要比较n次，所以平均时间复杂度为O(n²)。
- 在**归并排序、快速排序**之类的排序中，问题规模通过分治法消减为logN次，所以时间复杂度平均O(nlogn)。

比较排序的优势是，适用于各种规模的数据，也不在乎数据的分布，都能进行排序。可以说，比较排序适用于一切需要排序的情况。



**计数排序、基数排序、桶排序**则属于**非比较排序**。非比较排序是通过确定每个元素之前，应该有多少个元素来排序。针对数组arr，计算arr[i]之前有多少个元素，则唯一确定了arr[i]在排序后数组中的位置。

非比较排序只要确定每个元素之前的已有的元素个数即可，所有一次遍历即可解决。算法时间复杂度O(n)。非比较排序时间复杂度底，但由于非比较排序需要占用空间来确定唯一位置。所以对数据规模和数据分布有一定的要求。



---

# 稳定非稳定

![排序算法的稳定性](assets/v2-0872ff222124611b3403a888be76c2b9_1440w.jpg)

假定在待排序的记录序列中，存在多个具有**相同的关键字**的记录，若**经过排序**，这些记录的**相对次序保持不变**，即在原序列中，A1=A2，且A1在A2之前，而在排序后的序列中，A1仍在A2之前，则称这种排序算法是稳定的；否则称为不稳定的。

排序算法是否为稳定的是由具体算法决定的，**不稳定的算法在某种条件下可以变为稳定的算法**，而**稳定的算法在某种条件下也可以变为不稳定的算法**。



常见算法的稳定性（要记住）

**不稳定排序算法**

堆排序、快速排序、希尔排序、直接选择排序

**稳定排序算法**

基数排序、冒泡排序、直接插入排序、折半插入排序、归并排序



---