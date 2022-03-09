# 数论



https://blog.csdn.net/qq_44013342/article/details/88023526#t9





## 62.不同路径

一共m,n的话,无论怎么走,走到终点都需要 (m - 1) + (n - 1) 步。

其中一定有 m - 1 步是要向下走的，但不用管什么时候向下走。

那么有几种走法呢？ 可以转化为，给你 m + n - 2 个不同的数，随便取 m - 1 个数，有几种取法。

**组合问题**
$$
C_{m+n-2}^{m-1}
$$


求组合的时候,要防止两个int相乘溢出！所以不能把算式的分子都算出来,分母都算出来再做除法。

```c++
int main(int m, int n) {
    int numberator = 1, denominator = 1;
    int count = m - 1;
    int t = m + n - 2;
    
    while (count--)
        numberator *= (t--);
    
    for (int i = 1; i <= m-1; ++i)
        denominator *= i;
    
    return numberator / denominator;
}
```

需要在计算分子的时候,不断除以分母,代码如下:

```c++
int main(int m, int n) {
    int numberator = 1, denominator = 1;
    int count = m - 1;
    int t = m + n - 2;
    
    while (count--) {
        numberator *= (t--);
    
        while (denominator != 0 && numerator % denominator == 0) {
            numberator /= denominator;
            denominator--;
        }
    }       
    
    return numberator;
}
```

时间复杂度:O(m)
空间复杂度:O(1)