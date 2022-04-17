# 二分查找

## 704. 二分查找

定义 target 是在一个在左闭右闭的区间里，**也就是[left, right] （这个很重要非常重要）**。

区间的定义这就决定了二分法的代码应该如何写，**因为定义target在[left, right]区间，所以有如下两点：**

- while (left <= right) 要使用 <= ，因为left == right是有意义的，所以使用 <=
- if (nums[middle] > target) right 要赋值为 middle - 1，因为当前这个nums[middle]一定不是target，那么接下来要查找的左区间结束下标位置就是 middle - 1

```c++
int binartSearch(vector<int> &nums, int left, int right, int target) {
    int mid;
    while (left <= right) {
        mid = left + ((right - left) / 2); // 防止溢出 等同于(left + right)/2
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return -1;
}
```



---

## 35.搜索插入位置

这道题目，要在数组中插入目标值，无非是这四种情况。

![35_搜索插入位置3](assets/20201216232148471.png)

- 目标值在数组所有元素之前
- 目标值等于数组中某一个元素
- 目标值插入数组中的位置
- 目标值在数组所有元素之后

```c++
int searchInsert(vector<int>& nums, int target) {
    int n = nums.size();
    int left = 0;
    int right = n - 1; // 定义target在左闭右闭的区间里，[left, right]
    
    while (left <= right) { // 当left==right，区间[left, right]依然有效
        int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
        if (nums[middle] > target) {
            right = middle - 1; // target 在左区间，所以[left, middle - 1]
        } else if (nums[middle] < target) {
            left = middle + 1; // target 在右区间，所以[middle + 1, right]
        } else { // nums[middle] == target
            return middle;
        }
    }
    
    // 分别处理如下四种情况
    // 目标值在数组所有元素之前  [0, -1] return  right + 1 (right=-1)
    // 目标值等于数组中某一个元素  return middle;
    // 目标值插入数组中的位置 [left, right]，return  right + 1
    // 目标值在数组所有元素之后的情况 [left, right]， return right + 1
    return right + 1;
}
```





---

## 34.在排序数组中查找元素的第一个和最后一个位置(

寻找target在数组里的左右边界，有如下三种情况：

- 情况一：target 在数组范围的右边或者左边，例如数组{3, 4, 5}，target为2或者数组{3, 4, 5},target为6，此时应该返回{-1, -1}
- 情况二：target 在数组范围中，且数组中不存在target，例如数组{3,6,7},target为5，此时应该返回{-1, -1}
- 情况三：target 在数组范围中，且数组中存在target，例如数组{3,6,7},target为6，此时应该返回{1, 1}



### 寻找右边界

先来寻找右边界，确定好：计算出来的右边界是不包含target的右边界，左边界同理。可以写出如下代码

```c++
// 二分查找，寻找target的右边界（不包括target）
// 如果rightBorder为没有被赋值（即target在数组范围的左边，例如数组[3,3]，target为2），为了处理情况一
int getRightBorder(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]
    int rightBorder = -2; // 记录一下rightBorder没有被赋值的情况
    
    while (left <= right) { // 当left==right，区间[left, right]依然有效
        int middle = left + ((right - left) / 2);
        
        if (nums[middle] > target) {
            right = middle - 1; // target 在左区间，所以[left, middle - 1]
        } else { // 当nums[middle] == target的时候，更新left，这样才能得到target的右边界
            left = middle + 1;
            rightBorder = left;
        }
    }
    
    return rightBorder;
}
```



### 寻找左边界

```cpp
// 二分查找，寻找target的左边界leftBorder（不包括target）
// 如果leftBorder没有被赋值（即target在数组范围的右边，例如数组[3,3],target为4），为了处理情况一
int getLeftBorder(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]
    int leftBorder = -2; // 记录一下leftBorder没有被赋值的情况
    while (left <= right) {
        int middle = left + ((right - left) / 2);
        if (nums[middle] >= target) { // 寻找左边界，就要在nums[middle] == target的时候更新right
            right = middle - 1;
            leftBorder = right;
        } else {
            left = middle + 1;
        }
    }
    return leftBorder;
}
```





### 处理三种情况

左右边界计算完之后，看一下主体代码，这里把上面讨论的三种情况，都覆盖了

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBorder = getLeftBorder(nums, target);
        int rightBorder = getRightBorder(nums, target);
        // 情况一
        if (leftBorder == -2 || rightBorder == -2) return {-1, -1};
        // 情况三
        if (rightBorder - leftBorder > 1) return {leftBorder + 1, rightBorder - 1};
        // 情况二
        return {-1, -1};
    }
private:
     int getRightBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int rightBorder = -2; // 记录一下rightBorder没有被赋值的情况
        while (left <= right) {
            int middle = left + ((right - left) / 2);
            if (nums[middle] > target) {
                right = middle - 1;
            } else { // 寻找右边界，nums[middle] == target的时候更新left
                left = middle + 1;
                rightBorder = left;
            }
        }
        return rightBorder;
    }
    int getLeftBorder(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int leftBorder = -2; // 记录一下leftBorder没有被赋值的情况
        while (left <= right) {
            int middle = left + ((right - left) / 2);
            if (nums[middle] >= target) { // 寻找左边界，nums[middle] == target的时候更新right
                right = middle - 1;
                leftBorder = right;
            } else {
                left = middle + 1;
            }
        }
        return leftBorder;
    }
};
```



初学者建议大家一块一块的去分拆这道题目，正如本题解描述，想清楚三种情况之后，先专注于寻找右区间，然后专注于寻找左区间，左右根据左右区间做最后判断。



---

## 69.x 的平方根

二分查找第一个 res^2 大于x的元素，然后再减一

通过**不断猜测一个数字的平方** == x ? 然后不断修正这个数字

```c++
int mySqrt(int x) {
    int left = 1;  
    int right = x;
    int mid;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (pow(mid, 2) > x) {
            right = mid - 1;
        } else {
            left  = mid + 1; 
        } 
    }

    return left - 1;
}
```





---

## 367.有效的完全平方数

```c++
bool isPerfectSquare(int num) {
    if (num == 1) return true;
    if (num == 2 | num == 3) return false;

    int left = 0;
    int right = num / 2;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (pow(mid, 2) > num) {
            right = mid - 1;
        } else if (pow(mid, 2) < num) {
            left = mid + 1;
        } else {
            return true;
        }
    }

    return false;
}
```



---

## 14. 最长公共前缀

![fig4](assets/14_fig4.png)

最长公共前缀的长度**不会超过**字符串数组中的最短字符串的长度。用 $\textit{minLength}$ 表示字符串数组中的最短字符串的长度，则可以在 $[0,\textit{minLength}]$ 的范围内通过二分查找得到最长公共前缀的长度。每次取查找范围的中间值 $\textit{mid}$，判断每个字符串的长度为 $\textit{mid}$ 的前缀是否相同，如果相同则最长公共前缀的长度一定大于或等于 $\textit{mid}$，如果不相同则最长公共前缀的长度一定小于 $\textit{mid}$，通过上述方式将查找范围缩小一半，直到得到最长公共前缀的长度。

```c++

```









---

## 644. 子数组最大平均数 II

**连续数组**

min 表示数组 nums 的最小值，max 表示数组 nums 的最大值。最大平均字段和 一定在最大值与最小值之间，即区间 (min, max) 之间。

因为值全是max的时候，平均数是max；全是min的时候，平均数是min



二分思想是：通过不断猜测最大平均值，再通过验证更新猜测值，使每次猜测更加接近正确值。

- 如果猜测值太大，下一次猜一个更小的值
- 如果猜测值太小，下一次猜一个更大的值



以 max 和 min 作为猜测边界，每次猜测值为 mid = min + (max - min) /2。接下来寻找是否存在长度 >= k 的**连续子数组**的平均值大于 mid。

假设在数组 num 中存在一个长度为 j 的子数组，它的元素为 $a_1, a_2, a_3...,a_j$，它们的平均值 >= mid，即

- $(a_1+a_2+ a_3...+a_j)/j \geq mid$  或
- $(a_1+a_2+ a_3...+a_j) \geq j*mid$ 或
- $(a_1-mid) +(a_2-mid)+ (a_3-mid) ...+(a_j-mid) \geq 0$

数组中每个元素都减去 mid 后，如果存在长度 >= k 的子数组之和 >= 0，则表明数组 nums 中存在子数组的平均和 >= mid，此时令猜测区间的下边界为 mid；否则令猜测区间的上边界为 mid，然后继续该过程



在遍历数组 nums 时，将 nums[i] - mid 加到 sum[i] 上。如果 sum[k] >= 0，则直接令猜测区间的下界变为 mid。否则，按照下面思路不断求 nums 的前 i 项之和。



数组的前 j 项之和分别为 $sum_j$ 与 $sum_i$。因此第 j 到 i 项之和为 $sum_j - sum_i$。我们希望找到一对 i 和 j，使得 $j-i \ge k$ 时，有 $sum_j - sum_i \ge 0$。为了实现这一点，只需要计算第 $j-k$ 到 $j$ 项之和。这是因为如果最小的 $sum_i$ 都不能满足条件，则更大的值也无法满足条件。



使用 `prev` 变量存储从第 k 个位置开始的累加和。然后记录 `prev` 中出现过的最小值，即最小和。



每次寻找到一个新的 mid 后，都将它作为猜测区间的上边界或下边界，以不断缩小猜测范围。为了保证精度，使用 `error` 保证区间宽度小于 `10-5` 时，结束猜测。





```c++
public class Solution {
    public boolean check(int[] nums, double mid, int k) {
        double sum = 0, prev = 0, min_sum = 0;
        for (int i = 0; i < k; i++)
            sum += nums[i] - mid;
        if (sum >= 0)
            return true;
        for (int i = k; i < nums.length; i++) {
            sum += nums[i] - mid;
            prev += nums[i - k] - mid;
            min_sum = Math.min(prev, min_sum);
            if (sum >= min_sum)
                return true;
        }
        return false;
    }
    
    public double findMaxAverage(int[] nums, int k) {
        double max_val = Integer.MIN_VALUE;
        double min_val = Integer.MAX_VALUE;
        for (int n: nums) {
            max_val = Math.max(max_val, n);
            min_val = Math.min(min_val, n);
        }
        double prev_mid = max_val, error = Integer.MAX_VALUE;
        while (error > 0.00001) {
            double mid = (max_val + min_val) * 0.5;
            if (check(nums, mid, k))
                min_val = mid;
            else
                max_val = mid;
            error = Math.abs(prev_mid - mid);
            prev_mid = mid;
        }
        return min_val;
    }
    
}
```





```c++
class Solution {
public:
    
    bool check(vector<int>& nums, int k , double mid){
        vector<double> delta(nums.size());
        delta[0] = nums[0] - mid;
        for(int i = 1; i < nums.size(); ++i){
            delta[i] = nums[i] - mid + delta[i - 1];
        }
        double min_sum = 0, sum = delta[k - 1];
        for(int i = k; i < delta.size(); ++i){
            if((sum - min_sum) >= 0) return true;
            min_sum = min(min_sum, delta[i - k]);
            sum = delta[i];
        }
        if((sum - min_sum) >= 0) return true;
        return false;
    }
    
    
    double findMaxAverage(vector<int>& nums, int k) {
        double minn = INT_MAX, maxn = INT_MIN;
        for(int i = 0; i < nums.size(); i++){
            minn = min(minn, (double)nums[i]);
            maxn = max(maxn, (double)nums[i]);
        }
        while((maxn - minn) > 0.000001){
            double mid = (minn + maxn)/2;
            if(check(nums, k, mid))
                minn = mid;
            else
                maxn = mid;
        }
        return minn;
    }
};
```





实现 Check函数，就是前缀和的计算，即通过 目前和 - 前缀和 获取当前范围和。

特别要注意的是：条件是说 大于等于 k， 所以我们前缀和的计算数组的大小是 0 到 n-k



前缀和add，维护ij，addj-minAddi来求平均数，不需要固定i，只需要维护历史上最小的addi，也就是只需要固定j



---

## 643. 子数组最大平均数 I

```c++
class Solution {
public:
    bool check(vector<int>& nums, double mid, int k) {
        int n = nums.size();
        vector<double> preSum(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            preSum[i] = preSum[i-1] + nums[i-1] - mid;
        }
        

        for (int i = k; i <= n; ++i) {
            if (preSum[i] - preSum[i-k] >= 0) return true;
        }

        return false;
    }

    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double maxV = *max_element(nums.begin(), nums.end());
        double minV = *min_element(nums.begin(), nums.end());

        while (maxV - minV > 1e-5) {
            double mid = minV + (maxV - minV) / 2;
            if (check(nums, mid, k)) {
                minV = mid;
            } else {    // 不满足说明值太大，所以maxV变小为mid
                maxV = mid;
            }
        }

        return minV;
    }
};
```

