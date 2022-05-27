# 地平线问答 ans

## 模型部署

- Q：int8 模型量化

饱和量化和非饱和量化，KL 散度，我们创新性的使用 KL 散度，并且设定了一个利用率的值，

https://github.com/DuanYaQi/Swin-Transformer-TensorRT/blob/master/pytorch_quantization/calib/histogram.py



https://github.com/RAYKALI/simple-int8-pytorch-implement

https://github.com/Wulingtian/EfficientNetv2_TensorRT_int8



- Q：卷积加速的方式？

1）im2col + gemm 把矩阵铺开，然后利用通用矩阵乘的优化，加速计算，在调整成固定的 shape

2）fft 的原理是时域的卷积和频域的乘法是等价的，同时时域的乘法和频域的卷积也是等价的。可以把待卷积的数组进行 fft 变换，在频域做乘法，然后再进行 ifft 变换即可得到卷积的结果。

3）strassen 算法原理是基于分治的思想，把大矩阵乘法拆分成小矩阵乘法和小矩阵加法运算，通过 7 个用于辅助计算的中间矩阵，但是它要求矩阵的 size 必须是 2 的幂次

4）winograd 跟 strassen 很想，用更多的加法计算来减少乘法计算，从而降低计算量。





- Q：为什么加法计算比乘法计算快？

乘法计算占很多指令周期的

比如51单片机，计算一条加法指令需要一个机器周期，乘法指令需要四个机器周期





---

## CUDA

- Q：CUDA 内存模型

thread 里自己的寄存器，thread 有自己的 local 局部内存

block 里有 shared 共享内存（很多 thread 可以一起使用）

gird 里有 global 全局内存，constant 常量内存，texture 纹理内存







---

## C++

- Q：堆和栈的区别？

存放数据分配不同，栈存放的数据是编译器分配的，堆存放的数据是由程序员管理的

内存空间中形式不同，栈是一片连续的空间，堆呈现方式是链表的形式

扩展方向不同，栈向低地址扩展；堆向高地址扩展

申请方式的不同，栈是直接分配出去一部分连续的空间，堆是在链表上依次寻找满足申请大小的节点，如果找到，把这个节点从链表上去除，以便后续的申请

安全性不同，栈不会产生内存碎片，相对比较安全；堆是动态申请，需要手动释放，并且容易产生内存泄漏和内存碎片

效率不同，栈申请效率高；堆申请效率低，申请方便，容易产生碎片。

存放内容不同，栈存放的是局部变量和函数的参数；堆是程序员控制的内容





- Q：指针和引用的区别？

c语言使用，可以使用指针，但是不能使用引用

是否为空，指针可以只初始化不赋值，但是引用必须绑定到具体的对象上

是否可变，指针可以变，可以指向其它的位置，引用一旦绑定就不能改变

是否有内存空间，指针本身是占有内存空间的，引用不占有内存空间，只是个别名

是否可以多级，指针可以多级，引用不可以



- void const fun(){} 和 void fun(){}能否编译正确

不能，返回值不能作为函数重载的唯一区分





- 空类多大？

1 字节， 为了给类的不同对象分配唯一一个存储空间，会为空类安插一个char即 1 byte。

在类中成员变量占用空间，成员函数不占用空间。

声明该类型时必须在内存中占有一定空间，要不然就无法知道这个类存在、也就无法区分A1与A2。





- 引用的实现原理？



----

### STL

- Q：六大组件？

容器，算法，迭代器，容器适配器，仿函数，空间配置器



- Q：适配器？

容器适配器，是采用容器来形成更高级的数据结构：栈，队列，优先队列，不具备容器的特性，比如不能用迭代器来遍历元素，不能用容器的一些通用函数，如 `clear()`

迭代器适配器，比如逆向的迭代器 rbegin

函数适配器，仿函数



- Q：allocator 实现原理？

在 C++ 中，内存的配置和释放如下：

new 运算分为两部分

delete 运算分为两部分



allocator 将这两个阶段的操作区分开来：

内存配置由 `alloc::allocate()` 负责

内存配置由 `alloc::deallocate()` 负责

对象构造由 `::construct()` 负责

对象析构由 `::destroy()` 负责



- Q: unordered_map原理，hashtable原理 

哈希表

链地址法，解决数据存储位置发生冲突的哈希表

使用无序容器存储时，会**先申请一整块连续的存储空间**，但此空间并不是直接用来存储键值对的，而是存储各个链表的**头指针**，各键值对真正的存储位置是**各个链表的节点**。









----

## DL







---

## ML



- 



---

## Algorithm

- Q：topk 问题

| 算法                   | 思路                                                         | 时间复杂度      |
| ---------------------- | ------------------------------------------------------------ | --------------- |
| 普通排序               | 另数组有序，然后取出前 K 个数字                              | $O(N\log N)$    |
| 冒泡排序               | 只冒 K 个泡，得到前 K 个数字                                 | $O(N K)$        |
| 维护小顶堆（大小为 k） | 前 K 个元素生成一个小顶堆<br>用于存储最大的 K 个元素 <br>从第 K+1 个元素开始扫描和堆顶比较<br>如果被扫描元素大于堆顶，替换堆顶并调整堆<br>直到扫描完所有 n-k 个元素，最终堆中存的 | $O(N\log K)$    |
| 维护大顶堆（大小为 N） | 先 $O(N)$ 建堆，然后调整 K 次                                | $O(N+k \log N)$ |
| 随机选择排序           | 快排                                                         | $O(N)$          |
| 插入排序               |                                                              | $O(kN)$         |





```c++
int findKthLargest(vector<int>& nums, int k) {
    /*I. */
    shuffle(nums);
    int n = nums.size();
    int lo = 0, hi = n - 1;
    
    while (lo <= hi) {
        p = partition(nums, lo, hi);
        if (p > n-k) {
            hi = p - 1;
        } else if (p < n+k) {
            lo = p + 1;
        } else {
            return nums[p];
        }
    }

    return -1;
}


// 对 nums[lo..hi] 进行切分
int partition(vector<int> &nums, int lo, int hi) {
    int pivot = nums[lo];

    int i = lo + 1, j = hi;

    while (i <= j) {
        while (i < hi && nums[i] <= pivot) i++;
        while (j > lo && nums[j] > pivot) j--;

        if (i >= j) break;

        swap(nums[i], nums[j]);
    }

    swap(nums[lo], nums[j]);
    return j;
}

// 洗牌算法，将输入的数组随机打乱
void shuffle(vector<int> &nums) {
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        int r = i + rand() % (n - i);
        swap(nums[i], nums[r]);
    }
}
```

这个代码框架其实非常像我们前文 **二分搜索框架** 的代码，这也是这个算法高效的原因，但是时间复杂度为什么是 `O(N)` 呢？

显然，这个算法的时间复杂度也主要集中在 `partition` 函数上，我们需要估算 `partition` 函数执行了多少次，每次执行的时间复杂度是多少。

最好情况下，每次 `partition` 函数切分出的 `p` 都恰好是正中间索引 `(lo + hi) / 2`（二分），且每次切分之后会到左边或者右边的子数组继续进行切分，那么 `partition` 函数执行的次数是 logN，每次输入的数组大小缩短一半，即时间复杂度减小一半。

所以总的时间复杂度为：

```
# 等差数列
N + N/2 + N/4 + N/8 + ... + 1 = 2N = O(N)
```

当然，类似快速排序，快速选择算法中的 `partition` 函数也可能出现极端情况，最坏情况下 `p` 一直都是 `lo + 1` 或者一直都是 `hi - 1`，这样的话时间复杂度就退化为 `O(N^2)` 了：

```
N + (N - 1) + (N - 2) + ... + 1 = O(N^2)
```

这也是我们在代码中使用 `shuffle` 函数的原因，通过**引入随机性来避免极端情况的出现**，让算法的效率保持在比较高的水平。随机化之后的**快速选择算法的复杂度可以认为是 O(N)**。







- Q：快排不稳定的原因？

快排的不稳定是来自于最后的那一次交换(j指向元素与基准元素的交换），有可能 $nums[j]$ 和 $nums[j-1]$ 是相同的





- Q：插入排序？

寻找倒数第 K 个最大值，即排序问题中从大到小排序中第 K 个值

插入排序在每一轮排序时一定会取到当下轮次中的最值（最大、最小）

```c++
int findKthLargest(vector<int> &nums, int k) {
    int n = nums.size();

    for (int i = 0; i < k; ++i) {
        int maxn = 0;

        for (int j = 0; j < n - i; j++) {
            if (nums[j] > nums[maxn])
                maxn = j;
        }

        if (i == k - 1) return nums[maxn];

        int temp = nums[maxn];
        nums[maxn] = nums[n - i - 1];
        nums[n - i - 1] = temp;
    }

    return nums[n - k];
} 
```

