# 数组

## 基础

数组是非常基础的数据结构，在面试中，考察数组的题目一般在思维上都不难，主要是考察对**代码的掌控能力**

也就是说，想法很简单，但实现起来 可能就不是那么回事了。

首先要知道数组在内存中的存储方式，这样才能真正理解数组相关的面试题

**数组是存放在连续内存空间上的相同类型数据的集合。**

数组可以方便的通过下标索引的方式获取到下标下对应的数据。

举一个字符数组的例子，如图所示：

![算法通关数组](assets/算法通关数组.png)





需要两点注意的是

- **数组下标都是从0开始的。**
- **数组内存空间的地址是连续的**



正是**因为数组的在内存空间的地址是连续的，所以我们在删除或者增添元素的时候，就难免要移动其他元素的地址。**



例如删除下标为3的元素，需要对下标为3的元素后面的所有元素都要做移动操作，如图所示：

![算法通关数组1](assets/算法通关数组1.png)



而且大家如果使用 C++的话，要注意 vector 和 array 的区别，**vector 的底层实现是 array**，严格来讲 **vector 是容器，不是数组**。



**数组的元素是不能删的，只能覆盖。**





二维数组如图

![算法通关数组2](assets/算法通关数组2.png)



**C++中二维数组在地址空间上是连续的**。





---

## 209.长度最小的子数组

[力扣题目链接(opens new window)](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)

给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。

示例：

输入：s = 7, nums = [2,3,1,2,4,3] 输出：2 解释：子数组 [4,3] 是该条件下的长度最小的子数组。



![209.长度最小的子数组](assets/209.长度最小的子数组.gif)

所谓滑动窗口，**就是不断的调节子序列的起始位置和终止位置，从而得出我们要想的结果**。







---

## 498. 对角线遍历

```c++
class Solution {
private: 
    int mM, mN;
public:
    inline bool isValid(int i, int j) {
        if (i >= 0 && i < mM && j >= 0 && j < mN) return true;
        return false;
    }

    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        vector<int> res;
        mM = mat.size();
        mN = mat[0].size();
        int sum = mM * mN;

        int cnt = 0;
        int lineNo = 1;
        while(cnt != sum) {
            if (lineNo & 1) {   // 奇数
                int startI = lineNo - 1, startJ = 0;
                while (!isValid(startI, startJ)) {      //跳过非法点
                    startI--;
                    startJ++;
                }
                while (isValid(startI, startJ)) {       //进入合法点
                    res.emplace_back(mat[startI][startJ]);
                    cnt++;
                    startI--;
                    startJ++;
                }
            } else {            // 偶数
                int startI = 0, startJ = lineNo - 1;
                while (!isValid(startI, startJ)) {      //跳过非法点
                    startI++;
                    startJ--;
                }
                while (isValid(startI, startJ)) {       //进入合法点
                    res.emplace_back(mat[startI][startJ]);
                    cnt++;
                    startI++;
                    startJ--;
                }
            }
            lineNo++;
        }

        return res;
    }
};
```

