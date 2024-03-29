# DP

- [ ] 376.摆动序列



推荐做atcoder的dp contest 包含常见种类的dp入门题 https://atcoder.jp/contests/dp/tasks



**误区**: 以为把状态转移公式背下来,照葫芦画瓢改改,就开始写代码,甚至不清楚dp[i]表示的是什么。



五步动态规划
1. 确定**dp数组**(dp table)以及**下标的含义**
2. 确定**递推公式**
3. dp数组如何**初始化**
4. 确定**遍历顺序**
5. 举例推导dp数组







## 动态规划理论基础

如果某一问题有很多重叠子问题，使用动态规划是最有效的。



动态规划中每一个状态一定是由上一个状态推导出来的，

贪心没有状态推导，而是从**局部**直接选最优的。





---

### 解题步骤

1. 确定**dp数组**(dp table)以及**下标的含义**
2. 确定**递推公式**
3. dp数组如何**初始化**
4. 确定**遍历顺序**
5. 举例推导dp数组



先确定递推公式,然后在考虑初始化，因为一些情况是**递推公式决定了dp数组要如何初始化**!

**推导dp[i]的时候,一定要时刻想着dp[i]的定义,否则容易跑偏。**

**这体现出确定dp数组以及下标的含义的重要性!**



---

### Debug

```c++
if (error occur) {
    print(dp数组);
    
    if (与自己预先思路模拟推导结果一致) {
        get(递归公式、初始化或者遍历顺序有问题);
    } else {
        get(代码实现细节有问题);
    }
}
```



**debug 三问**

- 这道题目我举例推导状态转移公式了么?
- 我打印dp数组的日志了么?
- 打印出来了dp数组和我想的一样么?





---

## 509. 斐波那契数

给定 n，计算 `F(n)`
$$
F(0)=0,F(1) = 1 \\
F(n) = F(n-1) + F(n-2) \quad n>1
$$


1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 第i个数的斐波那契值为 dp[i]
i    : 代表数字的序列
```



2. 确定**递推公式**

```c++
dp[i] = dp[i-1] + dp[i-2];
```



3. dp数组如何**初始化**

```c++
dp[0] = 0;
dp[1] = 1;
```





4. 确定**遍历顺序**

从递推公式可以看出，第i项依赖前两项，因此遍历的顺序是从前到后遍历的。



5. 举例推导dp数组

```c++
N = 10;
dp[0] = 0; dp[1] = 1;
dp[2] = 1 + 0 = 1;
dp[3] = 1 + 1 = 2;
dp[4] = 2 + 1 = 3;
dp[5] = 3 + 2 = 5;
dp[6] = 5 + 3 = 8;
dp[7] = 8 + 5 = 13;
dp[8] = 13 + 8 = 21;
dp[9] = 21 + 13 = 34;
dp[10] = 34 + 21 = 55;
```





```c++
int fib(int n) {
    if (n <= 1) return n;
    vector<int> dp(n+1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}
```

时间复杂度:O(n)
空间复杂度:O(n)



---

### 优化

我们只需要维护两个数值就可以了,不需要记录整个序列。

```c++
int fib(int n) {
    if (n <= 1) return n;
    int dp[3];
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[2] = dp[0] + dp[1];
        dp[0] = dp[1];
        dp[1] = dp[2];            
    }

    return dp[2];
}
```

时间复杂度:O(n)
空间复杂度:O(1)





---

## 70. 爬楼梯

需要 n 阶你才能到达楼顶，每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢?




1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 爬到第i层的方法数
i    : 当前的层数
```



2. 确定**递推公式**

爬到第一层楼梯有一种方法,爬到二层楼梯有两种方法。那么第一层楼梯再跨两步就到第三层 ,第二层楼梯再跨一步就到第三层。所以到**第三层楼梯的状态**可以由**第二层楼梯和到第一层楼梯状态推导**出来

```c++
dp[i] = dp[i-1] + dp[i-2];
```



3. dp数组如何**初始化**

```c++
dp[0] = 0;//不用考虑第0层的初始化，小于2层直接输出答案
dp[1] = 1;
dp[2] = 2;
```



4. 确定**遍历顺序**

从递推公式可以看出，第i项依赖前两项，因此遍历的顺序是从前到后遍历的。



5. 举例推导dp数组

```c++
N = 10;
dp[1] = 1;
dp[2] = 2;
dp[3] = 2 + 1 = 3;
dp[4] = 3 + 2 = 5;
dp[5] = 5 + 3 = 8;
dp[6] = 8 + 5 = 13;
dp[7] = 13 + 8 = 21;
dp[8] = 21 + 13 = 34;
dp[9] = 34 + 21 = 55;
```



```c++
int climbStairs(int n) {
    if(n <= 2) return n;
    int dp[3];
    dp[0] = 1;
    dp[1] = 2;

    for (int i = 3; i <= n; ++i) { //直接第三层开始 i代表层数
        dp[2] = dp[0] + dp[1];
        dp[0] = dp[1];
        dp[1] = dp[2];
    }

    return dp[2];
}
```



时间复杂度:O(n)
空间复杂度:O(1)



---

**拓展**

一步一个台阶,两个台阶,三个台阶,直到 m个台阶,有多少种方法爬到n阶楼顶。 完全背包题

当m等于3时

```c++
dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
```



```c++
int climbStairs(int n, int m) {
    vector<int> dp(n+1, 0)
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) { //直接第1层开始 i代表层数
        for (int j = 1; j <= m; ++j) {
            if (i - j >= 0) 
                dp[i] += dp[i-j];
        }
    }

    return dp[n];
}
```







---

## 746. 使用最小花费爬楼梯

cost[i] 是第i步的上楼梯的花费，花费一次可以爬一步或两步




1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 爬到第i步的花费
i    : 当前的步数
```



2. 确定**递推公式**

```c++
dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);

因此要取 dp[n + 1];
```



3. dp数组如何**初始化**

```c++
dp[0] = 0;
dp[1] = 0;
```



4. 确定**遍历顺序**

从递推公式可以看出，第i项依赖前两项，因此遍历的顺序是从前到后遍历的。



5. 举例推导dp数组

```c++
N = 10;

dp[0] = 0;
dp[1] = 0;
dp[2] = 0 + 10 = 10;
dp[3] = 0 + 15 = 15;
```



```c++
int minCostClimbingStairs(vector<int>& cost) {
    int dp[1010]; memset(dp, 0, sizeof dp);

    for (int i = 2; i <= cost.size(); ++i) {
        dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
    }

    return dp[cost.size()];
}
```

时间复杂度:O(n)
空间复杂度:O(n)



**优化**

```c++
int minCostClimbingStairs(vector<int>& cost) {
    int N = cost.size();
    if (N < 2) return min(cost[0], cost[1]);

    int dp[2];
    dp[0] = cost[0];
    dp[1] = cost[1];

    for (int i = 2; i < N; ++i) { //从第二层开始
        dp[2] = cost[i] + min(dp[1], dp[2]);
        dp[0] = dp[1];
        dp[1] = dp[2];
    }
    // 注意最后一步可以理解为不用花费,所以取倒数第一步,第二步的最少值
    return min(dp[2], dp[1]);
}
```

时间复杂度:O(n)
空间复杂度:O(1)









---

## 62.不同路径



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][j]: 到达i,j的路径数
i,j     : matrix索引
```



2. 确定**递推公式**

```c++
dp[i][j] = dp[i-1][j] + 1 + dp[i][j-1];  // i-1 >= 0        j-1 >= 0 
// 只能从左边或者右边到达 因此把这两种情况加一下就好


```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[i][0] = 1;
dp[0][j] = 1;  
```



4. 确定**遍历顺序**

从递推公式可以看出，第i项依赖前两项，因此遍历的顺序是**从上到下**、**从左到右**遍历的。



5. 举例推导dp数组





```c++
int uniquePaths(int m, int n) {
    int dp[m][n];
    for (int i = 0; i < m; ++i)
        dp[i][0] = 1;

    for (int j = 0; j < n; ++j)
        dp[0][j] = 1;


    for (int i = 1; i < m ;++i) {
        for (int j = 1; j < n; ++j) {

            dp[i][j] = dp[i][j-1] + dp[i-1][j];
        }
    }

    return dp[m-1][n-1];
}
```



时间复杂度:O(mn)
空间复杂度:O(mn)



---

### 优化

其实用一个一维数组(也可以理解是**滚动数组**)就可以了,可以优化点空间:

```c++
int uniquePaths(int m, int n) {
    int dp[n];
    
    for (int j = 0; j < n; ++j)
        dp[j] = 1;


    for (int i = 1; i < m ;++i) {
        for (int j = 1; j < n; ++j) {
            dp[j] += dp[j-1][j-1]; //其实就是本身跟他前一项相加
        }
    }

    return dp[n-1];
}
```



时间复杂度:O(mn)
空间复杂度:O(n)

> 只跟他 i-1 和 j-1 有关的，都可以用滚动数组，直接计算完替换原来的值。
>
> 优化空间复杂度，其实就是找到需要几个值，就可以。不是所有值都需要保留







---

## 63. 不同路径 II

有障碍物了



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][j]: 到达i,j的可用路径数
i,j     : matrix索引
```



2. 确定**递推公式**

```c++
dp[i][j] = dp[i-1][j] + 1 + dp[i][j-1];  // i-1 >= 0        j-1 >= 0 
// 只能从左边或者右边到达 因此把这两种情况加一下就好
如果这里边有一个是1，就不能加
```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[i][0] = 1; 没有障碍物的的话 否则为INF
dp[0][j] = 1;  
```



4. 确定**遍历顺序**

从递推公式可以看出，第i项依赖前两项，因此遍历的顺序是**从上到下**、**从左到右**遍历的。



5. 举例推导dp数组





```c++
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int M = obstacleGrid.size();    //row
    int N = obstacleGrid[0].size(); //col

    int dp[M][N];

    if (obstacleGrid[0][0] == 1)
        return 0;

    
    //可用用一行替换 for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
    int flag = 0;
    for (int i = 0; i < M; ++i) {
        if (flag) {
            dp[i][0] = INT_MAX;
            continue;
        }
        if (obstacleGrid[i][0] == 0) {
            dp[i][0] = 1;
        } else {
            dp[i][0] = INT_MAX;
            flag = 1;
        }      
    }


    flag = 0;
    for (int j = 0; j < N; ++j) {
        if (flag) {
            dp[0][j] = INT_MAX;
            continue;
        }
        if (obstacleGrid[0][j] == 0) {
            dp[0][j] = 1;
        } else {
            dp[0][j] = INT_MAX;
            flag = 1;
        }
    }

    for (int i = 1; i < M; ++i) {
        for (int j = 1; j < N; ++j) {
            if (obstacleGrid[i][j] == 1) {
                dp[i][j] = INT_MAX;
            } else if (dp[i-1][j] == INT_MAX && dp[i][j-1] == INT_MAX) {
                dp[i][j] = INT_MAX;//continue?
            } else if (dp[i-1][j] == INT_MAX) {
                dp[i][j] = dp[i][j-1];
            } else if (dp[i][j-1] == INT_MAX) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }   
    }

    return dp[M-1][N-1]==INT_MAX? 0 : dp[M-1][N-1];
}
```



时间复杂度:O(mn)
空间复杂度:O(mn)



```c++
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int M = obstacleGrid.size();    //row
    int N = obstacleGrid[0].size(); //col

    vector<vector<int>> dp(M, vector<int>(N, 0));

    if (obstacleGrid[0][0] == 1)
        return 0;


    for (int i = 0; i < M && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
    for (int j = 0; j < N && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;

    for (int i = 1; i < M; ++i) {
        for (int j = 1; j < N; ++j) {
            if (obstacleGrid[i][j] == 1) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }   
    }

    return dp[M-1][N-1];
}
```





---

## 343. 整数拆分



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 拆分i时的最大值
i    : 被拆分的数
```



2. 确定**递推公式**

`dp[i]` 最大乘积，从1遍历j，然后有两种渠道得到 `dp[i]`

- 一个是 `j * (i-j)` 直接相乘
- 一个是 `j * dp[i-j]`，相当于是拆分 (i-j)，

```c++
dp[i] = max(dp[i], max( (i-j)*j, dp[i-j]*j ));  

// 为什么还要跟dp[i] 做比较 ？
// 因为每次循环j都会计算出不同的 dp[i]，比如前边的 2 2 的4 dp[i] 比 3 1的 3 dp[i]要大

// 为什么 max( (i-j)*j, dp[i-j]*j )？
// 因为 i-j表示的是第一个乘数    dp[i-j]也可以表示第一个乘数    二者本质意义一样
```



3. dp数组如何**初始化**

`dp[0] dp[1]` 不应该初始化,也就是没有意义的数值。这里只初始化 `dp[2] = 1`,从dp[i]的定义来说,拆分数字2,得到的最大乘积是1

```c++
// 边界条件
dp[2] = 1; 
```



4. 确定**遍历顺序**

从递推公式可以看出，dp[i] 依赖 dp[i-j]，因此遍历的顺序是**从前到后**遍历的。



5. 举例推导dp数组





```c++
int integerBreak(int n) {
    int dp[59] = {0};
    //memset(dp, 0, sizeof(dp));

    dp[2] = 1;

    for (int i = 3; i <= n; ++i) {

        for (int j = 2; j < i; ++j) {
            dp[i] = max(dp[i], max(j*(i-j), j*dp[i-j]));
        }
    }

    return dp[n];
}
```



时间复杂度:O(n2)
空间复杂度:O(n)









---

## 96. 不同的二叉搜索树



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: n个节点时能构成的二叉搜索树
i    : 节点数
```



2. 确定**递推公式**

`dp[i]` 乘积，从1遍历j，确定父亲节点，计算左右子树的组合情况，然后相乘得到 `dp[i]`

 `dp[mid-1] * dp[i - mid]`



```c++
dp[i] += dp[mid-1] * dp[i-mid];  

```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[0] = 1; 
dp[1] = 1;
```



4. 确定**遍历顺序**

从递推公式可以看出，dp[i] 依赖 dp[i-j]，因此遍历的顺序是**从前到后**遍历的。



5. 举例推导dp数组





```c++
int numTrees(int n) {
    int dp[n+1];

    if (n == 1) return 1;

    dp[0] = 1;
    dp[1] = 1;


    for (int i = 2; i <= n; ++i) {
        dp[i] = 0;

        for (int mid = 1; mid <= i; ++mid) {
            dp[i] += dp[mid-1]*dp[i-mid];
        }
    }

    return dp[n];
}
```



时间复杂度:O(n2)
空间复杂度:O(n)







---

## 376. 摆动序列

Wait！！！！！！！！！！！！！！！

1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 前n个连续数组最大和
i    : 数组位置
```



2. 确定**递推公式**

加之前：`dp[i] = dp[i-1] + nums[i]`

不加之前：`dp[i] = nums[i]`



```c++
dp[i] = max(nums[i], dp[i-1] + nums[i])
```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[0] = nums[0]; 
```



4. 确定**遍历顺序**

从递推公式可以看出，dp[i] 依赖 dp[i-j]，因此遍历的顺序是**从前到后**遍历的。



5. 举例推导dp数组







---

## 53. 最大子序和

1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 前n个连续数组最大和
i    : 数组位置
```



2. 确定**递推公式**

加之前：`dp[i] = dp[i-1] + nums[i]`

不加之前：`dp[i] = nums[i]`



```c++
dp[i] = max(nums[i], dp[i-1] + nums[i])
```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[0] = nums[0]; 
```



4. 确定**遍历顺序**

从递推公式可以看出，dp[i] 依赖 dp[i-j]，因此遍历的顺序是**从前到后**遍历的。



5. 举例推导dp数组





---

## 256. 粉刷房子/剑指 Offer II 091. 粉刷房子

```c++
int minCost(vector<vector<int>>& costs) {
    int m = costs.size();
    vector<vector<int>> dp(m, vector<int>(3, 0));

    for (int i = 0; i < 3; ++i)
        dp[0][i] = costs[0][i];


    for (int i = 1; i < m; ++i) {
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0];
        dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1];
        dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2];
    }



    return min(dp[m-1][0], min(dp[m-1][1], dp[m-1][2]));
} 
```





---

## 741. 摘樱桃

由于从 $(N-1,N-1)$ 返回 $(0,0)$ 的这条路径，可以等价地看成从 $(0,0)$ 到 $(N-1,N-1)$ 的路径，因此问题可以等价转换成，有两个人从 $(0,0)$ 出发，向下或向右走到 $(N-1,N-1)$ 时，摘到的樱桃个数之和的最大值。

由于同一个格子只能摘取一次，需要判断两人是否到达了同一个格子。

假设两人同时出发，且速度相同。无论两人怎么走，在时间相同的情况下，他们向右走的步数加上向下走的步数之和是一个定值（设为 k）。设两人的坐标为 $(x_1, y_1)$ 和 $(x_2,y_2)$，则 $x_1+y_1=x_2+y_2=k$。那么当 $x_1=x_2$ 时，必然有 $y_1=y_2$，即两个人到达了同一个格子。

定义 $f[k][x_1][x_2]$ 表示两个人（设为 $A$ 和 $B$）分别从 $(x_1,k-x_1)$ 和 $(x_2,k-x_2)$ 同时出发，到达 $(N-1,N-1)$ 摘到的樱桃个数之和的最大值。

如果 $(x_1,k-x_1)$ 或 $(x_2,k-x_2)$ 是荆棘，则 $f[k][x_1][x_2]=-\infty$，表示不合法的情况。

枚举 A 和 B 上一步的走法，来计算 $f[k][x_1][x_2]$。有四种情况：

- 都往右：从 $f[k-1][x_1][x_2]$ 转移过来

- A 往下，B 往右：从 $f[k-1][x_1-1][x_2]$ 转移过来
- A 往右，B 往下：从 $f[k-1][x_1][x_2-1]$ 转移过来
- 都往下：从 $f[k-1][x_1-1][x_2-1]$ 转移过来

取这四种情况的最大值，加上 $grid[x_1][k-x_2]$ 和 $grid[x_2][k-x_2]$ 的值，就得到了 $f[k][x_1][x_2]$，如果 $x_1=x_2$，则只需加上 $grid[x_1][k-x_1]$。

最后答案为 $max(f[2n-2][n-1][n-1],0)$，取 $max$ 是因为路径可能被荆棘挡住，无法从 (0, 0) 到达 (N-1, N-1).



代码实现时，我们可以将 A 和 B 走出的路径的上轮廓看成是 A 走出的路径，下轮廓看成是 B 走出的路径，即视作 A 始终不会走到 B 的下方，则有 $x_1\le x_2$，在代码实现时保证这一点，可以减少循环次数。



```c++
int n = grid.size();

// 三维数组指针
int ***f = (int ***)malloc(sizeof(int **) * (n * 2 - 1));
for (int i = 0; i < n * 2 - 1; ++i) {
    f[i] = (int **)malloc(sizeof(int *) * n);
    for (int j = 0; j < n; ++j) {
        f[i][j] = (int *)malloc(sizeof(int) * n);
        for (int k = 0; k < n; ++k) {
            f[i][j][k] = INT_MIN;
        }
    }
}

// 三维动态数组
vector<vector<vector<int>>> f(n * 2 - 1, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
```



```c++
class Solution {
public:
    // 樱桃能摘到的情况
    // 其上下左右为0或1
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<vector<vector<int>>> dp(2 * n - 1, vector<vector<int>>(n, vector<int>(n, INT_MIN)));	// 为什么是 2 * n - 1, 为什么是 INT_MIN
        dp[0][0][0] = grid[0][0];

        for (int k = 1; k < 2 * n - 1; ++k) {
            for (int x1 = max(k - n + 1, 0); x1 <= min(k, n - 1); ++x1) { //x1的起始和终止状态?
                int y1 = k - x1;
                if (grid[x1][y1] == -1) {
                    continue;
                }

                for (int x2 = x1; x2 <= min(k, n - 1); ++x2) {//x2的起始和终止状态?
                    int y2 = k - x2;
                    if (grid[x2][y2] == -1) {
                        continue;
                    }

                    int res = dp[k - 1][x1][x2]; // 都往右

                    if (x1) {
                        res = max(res, dp[k-1][x1-1][x2]);   // A往下 B往右
                    }

                    if (x2) {
                        res = max(res, dp[k-1][x1][x2-1]);   // A往右 B往下
                    }

                    if (x1 && x2) {
                        res = max(res, dp[k-1][x1-1][x2-1]); // 都往下
                    }

                    res += grid[x1][y1];
                    if (x2 != x1) {
                        res += grid[x2][y2];
                    }
                    dp[k][x1][x2] = res;
                }
            }
        }        

        return max(dp.back().back().back(), 0);
    }
};
```







---

# DP-Bag

背包

对于⾯试的话，其实掌握**01背包**，和**完全背包**，就够⽤了，最多可以再来⼀个**多重背包**。

![image-20220306154832293](assets/image-20220306154832293.png)

完全背包⼜是也是01背包稍作变化而来，即：**完全背包的物品数量是无限的**。





**背包问题具备的特征**：

是否可以根据一个 target（直接给出或间接求出），target 可以是数字也可以是字符串，再给定一个数组 arrs，问：能否使用 arrs 中的元素做各种排列组合得到 target。



**背包问题解法：**
01 背包
如果是 01 背包，即数组中的元素不可重复使用，外循环遍历 arrs，内循环遍历 target，且内循环倒序

完全背包
（1）如果是完全背包，即数组中的元素可重复使用并且不考虑元素之间顺序，arrs 放在外循环（保证 arrs 按顺序），target在内循环。且内循环正序。
（2）如果组合问题需考虑元素之间的顺序，需将 target 放在外循环，将 arrs 放在内循环，且内循环正序。



https://leetcode-cn.com/problems/partition-equal-subset-sum/solution/yi-tao-kuang-jia-jie-jue-bei-bao-wen-ti-p9saf/





---

## 分析

一般问题：我们有 $n$ 件物品和一个容量为 C 的背包，记第 i 件物品的重量 (weight) 为 $w_i$，价值 (value) 为 $v_i$，求将哪些物品装入背包可使价值总和最大。

> **0-1 背包**：如果限定每件物品最多只能选取 1 次，（即 0 或 1 次），则问题称为 `0-1 背包问题`

> **完全背包**：如果每件物品最多可以选取无限次，则问题称为 `完全背包问题`



假设放入背包中的物品 i 的数目为 $k_i$，则上述背包问题可以表达为：
$$
\max \ \sum_{i=0}^{n-1}\ k_{i} \cdot v_{i}
$$
限于 s.t.

$$
\sum_{i=0}^{n-1} k_{i} \cdot w_{i} \leqslant C, \quad \left\{\begin{array}{lll} k_{i} \in\{0,1\} & \textcolor{red}{\longleftarrow} & \text { 「0-1背包问题」 } \\ k_{i} \in\{0,1,2, \ldots,+\infty\} & \textcolor{red}{\longleftarrow} & \text { 「完全背包问题」 } \end{array}\right.
$$
0-1背包 和 完全背包 是两种最为常见的背包问题，其他类型的背包问题，如多重背包、分组背包等可参考网上的一些资料， 如：《背包问题九讲》[（网页版）](https://leetcode-cn.com/link/?target=http%3A%2F%2Fcuitianyi.com%2FPack%2F) [（PDF版）](https://leetcode-cn.com/link/?target=https%3A%2F%2Fcomzyh.com%2Fupload%2FPDF%2FPack-PDF-Comzyh.pdf)



**动态规划**是解决 [0-1 背包问题] 和 [完全背包问题] 的**标准做法**。

### 1. [0-1 背包问题]

一般地，我们定义：`dp[i][j]` 表示**前 i** 件物品放入一个**容量为 j** 的背包可以获得的最大价值（每件物品最多放一次），则状态转移过程可表示为：

- 不选择第 i 件物品，则问题转化为了前 i-1 件物品放入容量为 j 的背包中所获得的价值 `dp[i][j] = dp[i-1][j]`

- 选择第 i 件物品，则问题转化为了前 i-1 件物品放入容量为 $j-w_i$ 的背包中所获得的价值**再加上**本物品的**价值**  $dp[i][j] = dp[i-1][j-w_i] + v_i$。

> 注意，第 i 件物品能放入 1 个的前提是  $j-w_i \ge 0$ ，即 $w_i \le j$，背包还有容量放入 1 个第 i 件物品



两种情况取较大者，状态转移方程为
$$
dp[i][j] = max(dp[i-1][j],dp[i-1][j-w_i] + v_i)
$$



### 2. [完全背包问题]

类似于 01 背包，但不同的是每件物品有无限个供应：从每件物品的数量来考虑，有取 0 件、取 1 件、取 2 件......取 k 件等很多种。

一般地，我们定义：`dp[i][j]` 表示**前 i** 件物品放入一个**容量为 j** 的背包可以获得的最大价值（每件物品有无限个），因此 `dp[i][j]` 为以下可能方案中的最大值：

- 第 i 件物品选 0 个的最大价值 $dp[i-1][j]$

- 第 i 件物品选 1 个的最大价值 $dp[i-1][j-w_i] + v_i$

- 第 i 件物品选 2 个的最大价值 $dp[i-1][j-2 \cdot w_i] + 2 \cdot v_i$

  ......

- 第 i 件物品选 3 个的最大价值 $dp[i-1][j-k\cdot w_i] + k\cdot v_i$

> 注意，第 i 件物品能放入 k 个的前提是  $j-k\cdot w_i \ge 0$ ，即 $k\cdot w_i \le j$，背包还有容量放入 k 个第 i 件物品



k+1 种情况取较大者，状态转移方程为
$$
dp[i][j] = max(dp[i-1][j],dp[i-1][j-k\cdot w_i] + k\cdot v_i),\ \ 0\le k\cdot w_i \le j
$$


由状态方程可知，我们可以借鉴「0−1 背包」问题的求解方式来解决「完全背包问题」，但对于每件物品而言每次都需要枚举所有可行的物品数目 k，这无疑会大大增加系统的开销。

事实上，我们可以对上述状态转移方程进行优化，得到更为简洁的表达（见下）。

将上述状态转移方程展开可得：
$$
dp[i][j] = \max \{ \ dp[i-1][j],\quad \textcolor{red}{dp[i-1][j-w_i] + v_i}, \textcolor{teal}{\ dp[i-1][j-2\cdot w_i] + 2\cdot v_i}, \ \ \ \\ \ ..., \ \textcolor{blue}{dp[i-1][j-k\cdot w_i] + k\cdot v_i} \ \} ,\quad \quad \quad 0<=k\cdot w_i<=j  \tag{1}
$$
而恰巧的是对于 $dp[i][j-w_i]$ 我们有：
$$
dp[i][j-w_i] = \max \{ \ \textcolor{red}{dp[i-1][j-w_i]}, \ \textcolor{teal}{dp[i-1][j-2\cdot w_i] + v_i}, \quad \quad \quad \quad \quad \quad \quad \quad \\ \ ..., \ \textcolor{blue}{dp[i-1][j-k\cdot w_i] + (k-1)\cdot v_i} \ \} , w_i<=k\cdot w_i<=j
\tag{2}
$$
观察发现式 2 与式 1 中的后 k 项刚好相差了一个 $v_i$ ，将式 2 代入式 1 可得简化后的「完全背包问题」的「状态转移方程」为：
$$
dp[i][j] = \max \{ \ dp[i-1][j],\quad \textcolor{red}{dp[i]}[j-w_i] + v_i\ \} ,\quad 0<=w_i<=j \ \ \quad \quad \quad \quad \quad \quad
\tag{3}
$$


> ⚠️ 注意，式 3 与「0-1 背包问题」的状态转移方程及其相似，差别（以红色标注）在于第二项中的状态转移是来自上一行还是本行。这也决定了具体编程实现时状态更新方式的异同。







---

### 对比总结

两种背包问题的状态转移方程对比总结如下：

$$
0-1背包：dp[i][j] = \max\left\{ \ dp[i-1][j],\quad \textcolor{red}{dp[i-1]}[j-w_i] + v_i \ \right\},\quad 0<=w_i<=j \quad \quad\\
完全背包：\ dp[i][j] = \max \{ \ dp[i-1][j],\quad \textcolor{red}{dp[i]}[j-w_i] + v_i\ \} ,\quad \quad \quad 0<=w_i<=j \quad \quad
$$







---

### 模板

```c++
// 01背包
int dp[n+1][m+1]; memset(dp, 0, sizeof(dp));	// 表示前i件物品恰放入一个容量为j的背包可以获得的最大价值
for (int i = 0; i < n; i++) {				//遍历n个物品
    for (int j = m; j >= 0;j--) {			//遍历m个容量 逆序遍历
        if (j >= w[i]) {				//能装，判断装不装再装
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i]);
        } else {
            dp[i][j] = dp[i-1][j];
        }
        //第i个物体不选 dp[i][j]=dp[i-1][j];
        //第i个物体若选 dp[i][j]=dp[i-1][j-w[i]]+v[i]
    } 
}
```



```c++
// 多重背包
int dp[n+1][m+1]; memset(dp, 0, sizeof(dp));	// 表示前i件物品恰放入一个容量为j的背包可以获得的最大价值
for (int i = 0; i < n; i++) {				//遍历n个物品
    for (int j = m; j >= 0; j--) {			//遍历m个容量 逆序遍历
        if (j >= w[i]) {				//能装，判断装不装再装
            dp[i][j] = max(dp[i-1][j], dp[i][j-w[i]] + v[i]);
        } else {
            dp[i][j] = dp[i-1][j];
        }
        //第i个物体不选 dp[i][j]=dp[i-1][j];
        //第i个物体若选 dp[i][j]=dp[i][j-w[i]]+v[i]
    } 
}
```





⚠️ 求最优解的背包问题中，有的题目要求 **恰好装满背包** 时的最优解，有的题目则要求 **不超过背包容量** 时的最优解。两种问法**状态初始化不同**。

初始化的 dp 数组事实上就是在背包中没有放入任何物品时的合法状态：

1. 如果要求**恰好装满背包**，那么在初始化时 `dp[i][0]=0`，其它 `dp[i][*]` 均设为 $-\infty$。这是因为此时只有容量为 0 的背包可能被价值为 0 的 nothing “恰好装满”，而其它容量的背包均没有合法的解，属于未定义的状态。
   - 答案在 `dp[m][n]`
2. 如果只是要求**不超过背包容量**而使得背包中的物品价值尽量大，初始化时应将 `dp[*][*]` 全部设为 0。这是因为对应于任何一个背包，都有一个合法解为 “什么都不装”，价值为 0。答案两种情况，
   - dp存是否满足前 i 个数构成 j，答案在满足 `dp[*][j] == true` 的最大 `j`
   - dp存前 i 件物品恰放入一个容量为 j 的背包可以获得的最大价值，答案在 `dp[m][n]`





⚠️求最优解的背包问题中，有的题目要求**判断**是否可以装入背包，有的题目要求**计算**装入背包的最小最大**物品个数**，有的要求**计算**装入背包的**方法数**。区别是在**能装入时的那一条状态转移方程不同**。

|                  |    if (j - w >= 0) （可装）时的状态转移方程    |           初始化            |                             含义                             |
| ---------------- | :--------------------------------------------: | :-------------------------: | :----------------------------------------------------------: |
| 判断能否装入背包 |    ` dp[i][j] = dp[i-1][j] || dp[i-1][j-w]`    | 全 false，`dp[*][0] = true` | 前 i 个数中选取元素，**是否**可以使这些元素之**和刚好**为 j  |
| 能组成的最大值   |                      同上                      |            同上             |              找最大 `j` 满足`dp[*][j] == true`               |
| 能组成的最大值   | `dp[i][j] = max(dp[i-1][j], dp[i-1][j-w] + v)` |            全 0             |    前 i 件物品恰放入一个容量为 j 的背包可以获得的最大价值    |
|                  |                                                |                             |                                                              |
| 计算最大物品个数 | `dp[i][j] = max(dp[i-1][j], dp[i-1][j-w] + 1)` |            全 0             | 从前 i 个硬币中组成金额 j 所需最多的硬币数<br/>如果不能满足装入，结果为 0 |
| 计算最小物品个数 | `dp[i][j] = min(dp[i-1][j], dp[i-1][j-w] + 1)` |   全 inf，`dp[*][0] = 0;`   | 从前 i 个硬币中组成金额 j 所需最少的硬币数<br>如果不能满足装入，结果为 inf |
|                  |                                                |                             |                                                              |
| 计算方法数       |    `dp[i][j] = dp[i-1][j] + dp[i-1][j-w];`     |    全 0，`dp[0][0] = 1;`    |      前 i 个数中选取元素，使这些元素之和等于 j 的方案数      |
|                  |                                                |                             |                                                              |

>以上状态转移方程均为 01 背包为例，w 为重量，v 为价值。
>
>
>
>判断能否装入背包：416
>
>能组成的最大值：1049
>
>能组成的最小值：没有意义的问题
>
>
>
>计算最大物品个数：474（一般限制条件比较复杂，不能简单的贪心）
>
>计算最小物品个数：322，279
>
>
>
>计算方法数：494
>
>







---

### 组合数和排列数

```c++
for (int i = 0; i < coins.size(); i++) { 		// 遍历物品
    for (int j = coins[i]; j <= amount; j++) { 	// 遍历背包容量
    	if (j - coins[i] >= 0)
            dp[j] += dp[j - coins[i]];
    }
}
```

假设：coins[0] = 1，coins[1] = 5。那么就是先把1加入计算，然后再把5加入计算，得到的方法数量只有{1, 5}这种情况。而不会出现{5, 1}的情况。得到的是组合数



```c++
for (int j = 0; j <= amount; j++) { 			// 遍历背包容量
    for (int i = 0; i < coins.size(); i++) { 	// 遍历物品
    	if (j - coins[i] >= 0) 
            dp[j] += dp[j - coins[i]];
    }
}
```

背包容量的每⼀个值，都是经过 1 和 5 的计算，包含了{1, 5} 和 {5, 1}两种情况。得到的是排列数。



遇到排列数如果 dp 数组意义不明确，不要轻易把 dp 数组设计成背包问题来做，用普通 dp 方法来做好一点





---

### 输出路径

```C++
int n,m;
int v[MAX],w[MAX];
int dp[MAX];
bool path[MAX][MAX];
int V;
void solve() {
    memset(dp,0,sizeof(dp));
   	memset(path,false,sizeof(path));
   	for (int i=0; i<n; i++) {       
      	for (int j=V; j>=w[i]; j--)
        	if (dp[j-w[i]]+v[i] > dp[j]) {
                dp[j] = dp[j-w[i]]+v[i];
                path[i][j] = true;//cout<<i<<j<<endl;
        	}
   	}
    
    cout<< dp[V] <<endl;
    
    int ans[MAX];    
    int k=0;    
    for (int i=n-1;i>=0;i--) {
        if (path[i][V]){
            ans[++k]=i;
        	V-=w[i];
       	}
   	}
    
   	//输出所选择的物品
   	for(int i=k;i>0;i--)
     	cout<<ans[i]<<endl;
}
```







---

### 优化

滚动数组优化，优化时需要倒着遍历，因为第 i 次倒着遍历取到的值就是 i-1时刻的值

完全背包的状态转移方程优化，去除对物品数量 k 的循环，`dp[i][j-w] + v` 











---

## 0-1背包

### 416. 分割等和子集

`nums[i]` 对应于常规背包问题中的第 i 件物品的重量。我们的目标是从 nums 中选取若干个数字使其恰好等于数组总和的一半，记为 $target = \frac{sum(nums)}{2}$

对于本体，定义 `dp[i][j]` 表示从前 i 个数字中选出若干个，刚好可以使得被选出的数字和为 j。
$$
dp[i][j] = dp[i-1][j]  \ \ \ or \ \ \ dp[i-1][j - nums[i]]
$$
初始化时，`dp[i][0] = true`，表示从前 i 个数字中可以选出若干个使得其和为 0.即不选任何数字即可得到 0.



这一步保证了值是恰好相等的 `j - nums[i-1] == 0 ` ，



- **二维DP**

```c++
bool canPartition(vector<int>& nums) {
    int n = nums.size();

    int sum = accumulate(nums.begin(), nums.end(), 0);

    if (sum & 1) return false;
    int target = sum / 2;

    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    for (int i = 0; i <= n; ++i) // 示从前 i 个数字中可以选出若干个使得其和为 0.   即不选任何数字即可得到 0.
        dp[i][0] = true;


    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= target; ++j) {
            if (j - nums[i-1] < 0) {    // 容量不够，无法选择第i个数字 nums[i-1]
            	dp[i][j] = dp[i-1][j];  // 不选, 跟上一个物品的状态一样
            } else {                    // 容量足够 选或者不选
               	dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]]; 
            }
        }
    }

    return dp[n][target];
}


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;
        for (int i = 1; i < n; i++) {
            int num = nums[i];
            for (int j = 1; j <= target; j++) {
                if (j >= num) {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][target];
    }
};
```

我们定义了一个 $(n+1) \times (target+1)$ 的二维数组 dp，其中第一维为 n+1 也意味着：第 i 个数字为 nums[i-1]，第 1 个数字为 nums[0]，第 0 个数字为空。

也可有其他定义方法，比如定义 dp 的第一维为 n，相对应的第 i 个数字为 nums[i]，第 0 个数字即为 nums[0] 而非空。

复杂度分析

时间复杂度：$O(n×target)$，其中 n 是数组的长度，target 是数组元素和的一半。

空间复杂度：$O(n×target)$。



[1,5,11,5]

<img src="assets/image-20220419132059239.png" alt="image-20220419132059239" style="zoom: 150%;" />





- **一维DP**

动态规划的滚动数组优化如下：

在上面的状态转移方程中，每一行的 `dp[i][*]` 状态值都只与上一行的 `dp[i-1][*]` 状态值有关，因此可基于**滚动数组**的思想进行对状态空间 dp 进行优化而省去第一维度：
$$
\textcolor{red}{dp[j]}=dp[j] ∣ dp[j−nums[i-1]]\ .
$$

且需要注意的是第二层的循环我们需要从大到小计算，因为如果我们从小到大更新 dp 值，那么在计算 dp[j] 值的时候，dp[j−nums[i]] 已经是被更新过的状态，不再是上一行的 dp 值。



```c++
bool canPartition(vector<int>& nums) {
    int n = nums.size();

    int sum = accumulate(nums.begin(), nums.end(), 0);
    int maxNum = *max_element(nums.begin(), nums.end());

    if (sum & 1) return false;
    int target = sum / 2;
    if (maxNum > target) return false;

    vector<bool> dp(target + 1, false); 

    dp[0] = true;

    for (int i = 1; i < n; ++i) {
        int num = nums[i];        // 当前重量
        for (int j = target; j >= 0; --j) {	// 必须逆序，因为要保证 dp[j-num] 是前一时刻的
            if (j - num < 0) {    // 容量不够，无法选择第i个数字 nums[i-1]
                dp[j] = dp[j];    // 不选, 跟上一个物品的状态一样   
                // 后边这个dp[j]是前一时刻的值 即dp[i-1][j]
            } else {                    // 容量足够 选或者不选
                dp[j] = dp[j] || dp[j-num]; 
                // 后边这个dp[j] || dp[j-num] 是前一时刻的值 即dp[i-1][j] || dp[i-1][j-num]
            }
        }
    }

    return dp[target];
}
```

时间复杂度：$O(n \times \textit{target})$，其中 n 是数组的长度，target 是整个数组的元素和的一半。需要计算出所有的状态，每个状态在进行转移时的时间复杂度为 $O(1)$。

空间复杂度：$O(\textit{target})$，其中 target 是整个数组的元素和的一半。空间复杂度取决于 dp 数组，在不进行空间优化的情况下，空间复杂度是 $O(n \times \textit{target})$，在进行空间优化的情况下，空间复杂度可以降到 $O(\textit{target})$。







- **输出结果**

```c++
bool canPartition(vector<int>& nums) {
    int n = nums.size();

    int sumn = accumulate(nums.begin(), nums.end(), 0);

    if (sumn & 1) return false;

    int target = sumn / 2;

    vector<bool> dp(target + 1, false);
    vector<vector<bool>> path(n, vector<bool>(target + 1, false)); // path！！！
    dp[0] = true;

    for (int i = 0; i < n; ++i) {
        int num = nums[i];
        for (int j = target; j >= 0; --j) {
            if (j - num < 0) {
                dp[j] = dp[j];
                //path[i][j] = dp[j];	//！！！！ 注意这句不能要，放不下也没必要记录
            } else {
                dp[j] = dp[j] | dp[j-num];
                path[i][j] = dp[j];	//！！！！ 只记录拿取的就可以
            }
        } 
    }

    /*输出！！！*/
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= target; ++j) {
            cout << path[i][j] << " ";
        } 
        cout << endl;
    }
        

    int ans[n+1];    // 注意这里是 n+1的大小，有可能全取
    int idx = 0;    
    for (int i = n - 1; i >= 0; i--) {
        if (path[i][target]){
            ans[++idx] = i;
            target -= nums[i];
        }
    }

    //输出所选择的物品
    for(int i = idx; i > 0; i--)
        cout << ans[i] << " ";


    return dp[target];
}
```



![image-20220420200834996](assets/image-20220420200834996.png)

​	

---

### 474. 一和零

状态转移方程如下：

$$
\textit{dp}[i][j][k]=\begin{cases} \textit{dp}[i - 1][j][k], & j<\textit{zeros} ~~ | ~~ k<\textit{ones} \\ \max(\textit{dp}[i - 1][j][k], \textit{dp}[i - 1][j - \textit{zeros}][k - \textit{ones}] + 1), & j \ge \textit{zeros} ~ \& ~ k \ge \textit{ones} \end{cases}
$$
最终得到 $\textit{dp}[l][m][n]$ 的值即为答案



三维DP

```c++
int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));
	/*预处理01个数*/
    for (int i = 0; i < strs.size(); ++i) {
        int zeroN = 0, oneN = 0;
        for (auto &c : strs[i]) {
            if (c == '0') zeroN++;
            else oneN++;
        }
        nums[i][0] = zeroN;
        nums[i][1] = oneN;
    } 


    vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

    for (int i = 1; i <= strs.size(); ++i) {
        int zeroN = nums[i-1][0], oneN = nums[i-1][1];

        for (int j = m; j >= 0; --j) {      // m 要求 0
            for (int k = n; k >= 0; --k) {  // n 要求 1
                if (j - zeroN < 0 || k - oneN < 0) {
                    dp[i][j][k] = dp[i-1][j][k];
                } else {
                    dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j-zeroN][k-oneN]+1);
                }
            }
        }
    }

    return dp[len][m][n];
}
```



滚动数组优化至二维

```c++
int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();
    vector<vector<int>> nums(len, vector<int>(2, 0));
	/*预处理01个数*/
    for (int i = 0; i < strs.size(); ++i) {
        int zeroN = 0, oneN = 0;
        for (auto &c : strs[i]) {
            if (c == '0') zeroN++;
            else oneN++;
        }
        nums[i][0] = zeroN;
        nums[i][1] = oneN;
    } 


    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < strs.size(); ++i) {
        int zeroN = nums[i][0], oneN = nums[i][1];

        for (int j = m; j >= 0; --j) {      // m 要求 0
            for (int k = n; k >= 0; --k) {  // n 要求 1
                if (j - zeroN < 0 || k - oneN < 0) {
                    dp[j][k] = dp[j][k];
                } else {
                    dp[j][k] = max(dp[j][k], dp[j-zeroN][k-oneN]+1);
                }
            }
        }
    }

    return dp[m][n];
}
```

时间复杂度：$O(lmn + L)$，其中 l 是数组 strs 的长度，m 和 n 分别是 0 和 1 的容量，L 是数组 strs 中的所有字符串的长度之和。

动态规划需要计算的状态总数是 O(lmn)，每个状态的值需要 O(1) 的时间计算。
对于数组 strs 中的每个字符串，都要遍历字符串得到其中的 0 和 1 的数量，因此需要 O(L) 的时间遍历所有的字符串。
总时间复杂度是 O(lmn + L)。

空间复杂度：O(mn)，其中 m 和 n 分别是 0 和 1 的容量。使用空间优化的实现，需要创建 m+1 行 n+1 列的二维数组 dp。



输出结果

```c++
int findMaxForm(vector<string>& strs, int m, int n) {
    int len = strs.size();

    vector<vector<int>> nums(len, vector<int>(2, 0));
    for (int i = 0; i < len; ++i) {
        nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
        nums[i][1] = strs[i].size() - nums[i][0];
    }

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<vector<int>>> path(len, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

    for (int i = 0; i < len; ++i) {
        int zeroN = nums[i][0], oneN = nums[i][1];

        for (int j = m; j >= 0; --j) {
            for (int k = n; k >= 0; --k) {
                if (j - zeroN < 0 || k - oneN < 0) {
                    dp[j][k] = dp[j][k];
                } else {
                    dp[j][k] = max(dp[j][k], dp[j - zeroN][k - oneN] + 1);
                    path[i][j][k] = dp[j][k];//！！！
                }
            }
        }
    }

    int ans[len+1];
    int idx = 0, mm = m, nn = n;
    for (int i = len - 1; i >= 0; --i) {
        if (path[i][mm][nn]) {
            ans[++idx] = i;
            mm -= nums[i][0];
            nn -= nums[i][1];
        }
    }

    for (int i = idx; i > 0; --i) 
        cout << ans[i] << " ";

    return dp[m][n];
}
```





---

### 494. 目标和

选或不选，选了 +nums[i]，不选 -nums[i]



记数组的元素和为 sum，添加 - 号的元素之和为 neg，则其余添加 + 的元素之和为 sum−neg，得到的表达式的结果为

$$
(\textit{sum}-\textit{neg})-\textit{neg}=\textit{sum}-2\cdot\textit{neg}=\textit{target}
$$
即

$$
\textit{neg}=\dfrac{\textit{sum}-\textit{target}}{2}
$$
由于数组 nums 中的元素都是非负整数，neg 也必须是非负整数，所以上式成立的前提是 sum−target 是非负偶数。若不符合该条件可直接返回 0。

若上式成立，问题转化成在数组 nums 中选取若干元素，使得这些元素之和等于 neg，计算选取元素的方案数。我们可以使用动态规划的方法求解。

定义二维数组 dp，其中 $\textit{dp}[i][j]$ 表示在数组 nums 的前 i 个数中选取元素，使得这些元素之和等于 j 的方案数。假设数组 nums 的长度为 n，则最终答案为 $\textit{dp}[n][\textit{neg}]$。

当没有任何元素可以选取时，元素和只能是 0，对应的方案数是 1，因此动态规划的边界条件是：

$$
\textit{dp}[0][j]=\begin{cases} 1, & j=0 \\ 0, & j \ge 1 \end{cases}
$$
当 $1 \le i \le n$ 时，对于数组 nums 中的第 i 个元素 num（i 的计数从 1 开始），遍历 $0 \le j \le \textit{neg}$，计算 $\textit{dp}[i][j]$ 的值：

如果 $j < \textit{num}$，则不能选 num，此时有 $\textit{dp}[i][j] = \textit{dp}[i - 1][j]$；

如果 $j \ge \textit{num}$，则如果不选 num，方案数是 $\textit{dp}[i - 1][j]$，如果选 num，方案数是 $\textit{dp}[i - 1][j - \textit{num}]$，此时有 $\textit{dp}[i][j] = \textit{dp}[i - 1][j] + \textit{dp}[i - 1][j - \textit{num}]$。

因此状态转移方程如下：

$$
\textit{dp}[i][j]=\begin{cases} \textit{dp}[i - 1][j], & j<\textit{nums}[i] \\ \textit{dp}[i - 1][j] + \textit{dp}[i - 1][j - \textit{nums}[i]], & j \ge \textit{nums}[i] \end{cases}
$$
最终得到 $\textit{dp}[n][\textit{neg}]$ 的值即为答案。

由此可以得到空间复杂度为 $O(n \times \textit{neg})$ 的实现。

```c++
int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();


    int sumn = accumulate(nums.begin(), nums.end(), 0);

    if ((sumn - target)  < 0 || (sumn - target)  & 1) return 0;

    int neg = (sumn - target) / 2;  //目标数变成负数个数



    vector<vector<int>> dp(n+1, vector<int>(neg+1, 0));    // 在数组 nums 的前 i 个数中选取元素，使得这些元素之和等于 j 的方案数。
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        int num = nums[i-1];

        for (int j = neg; j >= 0; --j) {
            if (j - num < 0) {  //不能选
                dp[i][j] = dp[i-1][j];
            } else {            // 能选 能选一定要选，而不是max
                dp[i][j] = dp[i-1][j] + dp[i-1][j-num];
            }
        } 

    }

    return dp[n][neg];
}
```



**滚动优化至一维**

```c++
int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();


    int sumn = accumulate(nums.begin(), nums.end(), 0);

    if ((sumn - target)  < 0 || (sumn - target)  & 1) return 0;

    int neg = (sumn - target) / 2;  //目标数变成负数个数


    vector<int> dp(neg+1, 0);    // 在数组 nums 的前 i 个数中选取元素，使得这些元素之和等于 j 的方案数。
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        int num = nums[i];

        for (int j = neg; j >= 0; --j) {
            if (j - num < 0) {  //不能选
                dp[j] = dp[j];
            } else {            // 能选
                dp[j] = dp[j] + dp[j-num];
            }
        } 

    }

    return dp[neg];
}
```



**输出结果**

```c++
int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();


    int sumn = accumulate(nums.begin(), nums.end(), 0);

    if ((sumn - target)  < 0 || (sumn - target)  & 1) return 0;

    int neg = (sumn - target) / 2;  //目标数变成负数个数


    vector<int> dp(neg + 1, 0);    // 在数组 nums 的前 i 个数中选取元素，使得这些元素之和等于 j 的方案数。
    vector<vector<int>> path(n, vector<int>(neg + 1, 0));
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        int num = nums[i];

        for (int j = neg; j >= 0; --j) {
            if (j - num < 0) {  //不能选
                dp[j] = dp[j];
            } else {            // 能选
                dp[j] = dp[j] + dp[j-num];
                path[i][j] = dp[j];
            }
        } 

    }

    int ans[n+1];
    int idx = 0, negg = neg;
    for (int i = n-1; i >= 0; --i) {
        if (path[i][negg] && negg >= 0) {
            ans[++idx] = i;
            negg -= nums[i];
        }
    }

    for (int i = idx; i > 0; --i)
        cout << ans[i] << " ";

    return dp[neg];
}
```



---

### 1049. 最后一块石头的重量 II

本题其实就是**尽量让石头分成重量相同的两堆**，相撞之后剩下的石头最小，这样就化解成01背包问题了。

```c++
int lastStoneWeightII(vector<int>& stones) {
    int n = stones.size();

    int sumn = accumulate(stones.begin(), stones.end(), 0);

    int target = sumn / 2;

    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));  //前i个数字 可以组成的最大数字

    for (int i = 1; i <= n; ++i) {
        int num = stones[i - 1];

        for (int j = target; j >= 0; --j) {
            if (j - num < 0) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - num] + num);
            }
        }
    }

    /*
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= target; ++j) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        */

    return sumn - dp[n][target] * 2;   
}
```



**滚动数组优化**

```c++
int lastStoneWeightII(vector<int>& stones) {
    int n = stones.size();

    int sumn = accumulate(stones.begin(), stones.end(), 0);

    int target = sumn / 2;

    vector<int> dp(target + 1, 0);  //前i个数字 可以组成的最大数字

    for (int i = 1; i <= n; ++i) {
        int num = stones[i - 1];

        for (int j = target; j >= 0; --j) {
            if (j - num < 0) {
                dp[j] = dp[j];
            } else {
                dp[j] = max(dp[j], dp[j - num] + num);
            }
        }
    }

    /*
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= target; ++j) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        */

    return sumn - dp[target] * 2;   
}
```



**不能输出路径**



---

## 完全背包

### 322. 零钱兑换

https://leetcode-cn.com/problems/coin-change/solution/322-ling-qian-dui-huan-cong-zui-po-su-de-1g1m/



给定一个整数数组 coins，表示不同面额的硬币；以及一个整数 amount，表示总金额。本题要求的是在每种硬币的数量是无限的情况下，计算并返回可以凑成总金额所需的**最少的硬币个数** 。

每种硬币的数量是无限的，这是一个典型的「完全背包」求最优解问题。对于本题，定义二维数组 $dp[i][j]$ 表示：从前 i 个硬币中组成金额 j 所需最少的硬币数量。

基于题目要求，上述完全背包的状态转移方程可修改为：
$$
dp[i][j] = \min\left\{ \ dp[i-1][j-k\cdot w_i] + k \ \right\}\ ,\quad 0<=k\cdot w_i<=j \quad\quad
$$
对应于对于第 i 个硬币，选 0、1、2、...、k 个组成金额 j 时所对应的最小硬币数目。

初始化时，`dp[i][0] = 0`，表示从前 i 个硬币中凑出金额 0 所需要的硬币数目为 0。【不选任何硬币即可得到 0 】

其他不合法的或未定义的状态则可以设置为正无穷或一个不可能取到的较大值。



- **朴素完全背包**

每计算一个 `dp[i][j]` 需要遍历 k 种状态(每个coin可以存在0-k个)所以时间复杂度为$O(n^3)$，所以应该超时，但竟然没超。

```c++
int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();
	const int inf = 0x3f3f3f3f;
    int dp[n + 1][amount + 1]; memset(dp, inf, sizeof(dp)); // 前i个数字组成j的最小个数

    for (int i = 0; i <= n; ++i) 
        dp[i][0] = 0;

    for (int i = 1; i <= n; ++i) {	// 遍历物品
        int num = coins[i-1];		// 能过的原因是这一步，后边两个计算用到num了！！！！！！

        for (int j = 0; j <= amount; ++j) {	// 遍历包的体积
            for (int k = 0; k <= (int)j / num; ++k) {
                dp[i][j] = min(dp[i][j], dp[i-1][j - k * num] + k);// 注意这里是+k，不是+1！！！！！！！！
            }
        }
    }

    return dp[n][amount] == inf ? -1 : dp[n][amount];
}
```



但是如果用 `vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INT_MAX / 2));` 就会超时



j和k反着遍历也是一样的，为后续优化做准备

```C++
int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();
	const int inf = 0x3f3f3f3f;
    int dp[n + 1][amount + 1]; memset(dp, inf, sizeof(dp)); // 前i个数字组成j的最小个数

    for (int i = 0; i <= n; ++i) 
        dp[i][0] = 0;

    for (int i = 1; i <= n; ++i) {	                            // 遍历物品
        int num = coins[i-1];   // O(n^3)能过的原因是这一步，后边两个计算用到num了！！！！！！

        for (int j = amount; j >= 0; --j) {	                    // 遍历包的体积
            for (int k = (int)j / num; k >= 0; --k) {           // 遍历每个物品有多少个的K种情况
                dp[i][j] = min(dp[i][j], dp[i-1][j - k * num] + k);
            }
        }
    }

    return dp[n][amount] == inf ? -1 : dp[n][amount];
}
```





- **滚动数组优化至二维**

为什么 j 和 k 不反向遍历也可以通过？？？

**对于纯完全背包问题，其for循环的先后循环是可以颠倒的，但如果问装满背包有几种方式的话？ 那么两个for循环的先后顺序就有很⼤区别了**

```c++
int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();
    const int inf = 0x3f3f3f3f;

    int dp[amount + 1]; memset(dp, inf, sizeof(dp));


    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int num = coins[i-1];

        for (int j = amount; j >= 0; --j) {
            for (int k = (int)j / num; k >= 0; --k) {
                dp[j] = min(dp[j], dp[j - k*num] + k);
            }
        }
    }
    return dp[amount] == inf ? -1 : dp[amount];
}
```

只是优化了空间





- **状态转移方程优化**

$$
dp[i][j] = \min\left\{ \ dp[i-1][j-k\cdot w_i] + k \ \right\}\ ,\quad 0<=k\cdot w_i<=j \quad\quad
$$

将上述状态转移方程展开可得：
$$
dp[i][j] = \min \{ \ dp[i-1][j],\quad \textcolor{red}{dp[i-1][j-w_i] + v_i}, \textcolor{teal}{\ dp[i-1][j-2\cdot w_i] + 2\cdot v_i}, \ \ \ \\ \ ..., \ \textcolor{blue}{dp[i-1][j-k\cdot w_i] + k\cdot v_i} \ \} ,\quad \quad \quad 0<=k\cdot w_i<=j  \tag{1}
$$
而恰巧的是对于 $dp[i][j-w_i]$ 我们有：
$$
dp[i][j-w_i] = \min \{ \ \textcolor{red}{dp[i-1][j-w_i]}, \ \textcolor{teal}{dp[i-1][j-2\cdot w_i] + v_i}, \quad \quad \quad \quad \quad \quad \quad \quad \\ \ ..., \ \textcolor{blue}{dp[i-1][j-k\cdot w_i] + (k-1)\cdot v_i} \ \} , w_i<=k\cdot w_i<=j
\tag{2}
$$
观察发现式 2 与式 1 中的后 k 项刚好相差了一个 $v_i$ ，将式 2 代入式 1 可得简化后的「完全背包问题」的「状态转移方程」为：
$$
dp[i][j] = \min \{ \ dp[i-1][j],\quad \textcolor{red}{dp[i]}[j-w_i] + v_i\ \} ,\quad 0<=w_i<=j \ \ \quad \quad \quad \quad \quad \quad
\tag{3}
$$


> ⚠️ 注意，式 3 与「0-1 背包问题」的状态转移方程及其相似，差别（以红色标注）在于第二项中的状态转移是来自上一行还是本行。这也决定了具体编程实现时状态更新方式的异同。



```c++
int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();
    const int inf = 0x3f3f3f3f;
    int dp[n + 1][amount + 1]; memset(dp, inf, sizeof(dp)); // 前i个数字组成j的最小个数

    for (int i = 0; i <= n; ++i) 
        dp[i][0] = 0;

    for (int i = 1; i <= n; ++i) {	// 遍历物品
        int num = coins[i-1];		// 能过的原因是这一步，后边两个计算用到num了,这里相当于缓存了一下！！！！！！

        for (int j = 0; j <= amount; ++j) {	// 遍历包的体积     
            if (j - num < 0) {              // 如果装不下延续上一时刻的状态
                dp[i][j] = dp[i-1][j];      
            } else {                        // 可以装到，选择装或不装 的最小数量
                dp[i][j] = min(dp[i-1][j], dp[i][j - num] + 1);	// 注意第二项不是 dp[i-1][j-num] + 1 而是 dp[i][j-num] + 1
            }
        }
    }

    return dp[n][amount] == inf ? -1 : dp[n][amount];
}
```











---

### 518. 零钱兑换 II

请你计算并返回可以凑成总金额的**硬币组合数**

`dp[i][j]` **长度为i的序列和为j的方案数**。



而恰巧的是对于 $dp[i][j-w_i]$ 我们有：
$$
dp[i][j-w_i] =   \ \textcolor{red}{dp[i-1][j-w_i]}+
\ \textcolor{teal}{dp[i-1][j-2\cdot w_i]}+
\quad \quad \quad \quad \quad \quad \quad \quad \\ \ ...+ \ \textcolor{blue}{dp[i-1][j-k\cdot w_i]} \ , w_i<=k\cdot w_i<=j
\tag{2}
$$
观察发现式 2 与式 1 中的后 k 项刚好相等 ，将式 2 代入式 1 可得简化后的「完全背包问题」的「状态转移方程」为：
$$
dp[i][j] = \ dp[i-1][j]+ 
\textcolor{red}{dp[i]}[j-w_i]\quad 0<=w_i<=j \ \ \quad \quad \quad \quad \quad \quad
\tag{3}
$$


> ⚠️ 注意，式 3 与「0-1 背包问题」的状态转移方程及其相似，差别（以红色标注）在于第二项中的状态转移是来自上一行还是本行。这也决定了具体编程实现时状态更新方式的异同。



```c++
int change(int amount, vector<int>& coins) {
    int n = coins.size();

    int dp[n+1][amount+1]; memset(dp, 0, sizeof(dp));   // 前i个数中选元素，元素和为j的组合数


    for (int i = 0; i <= n; ++i)    // 和0的组合数均为1，都不选
        dp[i][0] = 1;

    for (int i = 1; i <= n; ++i) {
        int w = coins[i-1];

        for (int j = 0; j <= amount; ++j) {
            if (j - w < 0) {    // 不能选
                dp[i][j] = dp[i-1][j];
            } else {            // 能选
                dp[i][j] = dp[i-1][j] + dp[i][j-w];     // 注意这里是 = 号 不是+=号
            }
        }
    }

    return dp[n][amount];
}
```







---

### 279. 完全平方数

可以随便取，所以是完全背包



取较小者，状态转移方程为
$$
dp[i][j] = min(dp[i-1][j],dp[i-1][j-k\cdot w_i] + k\cdot v_i),\ \ 0\le k\cdot w_i \le j
$$

```C++
int numSquares(int n) {
    int maxn = sqrt(n); //找到搜索上界 3

    const int inf = 0x3f3f3f3f;
    int dp[maxn + 1][n + 1]; memset(dp, inf, sizeof(dp)); //前i个数，其平方数的和构成i的最少数量

    for (int i = 0; i <= maxn; ++i) {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= maxn; ++i) {
        int w = i * i;
        for (int j = 0; j <= n; ++j) {
            if (j - w < 0) {
                dp[i][j] = dp[i-1][j];
            } else {
                for (int k = (int)j / w; k >= 0; --k) {
                    dp[i][j] = min(dp[i][j], dp[i-1][j-w*k] + k);// 注意这里是+k，不是+1！！！！！！！！
                }
            }
        }
    }

    return dp[maxn][n];
}
```

超时，滚动数组优化也超时。只能优化状态转移方程，省去中间的 for 循环



将上述状态转移方程展开可得：
$$
dp[i][j] = \min \{ \ dp[i-1][j],\quad \textcolor{red}{dp[i-1][j-w_i] + v_i}, \textcolor{teal}{\ dp[i-1][j-2\cdot w_i] + 2\cdot v_i}, \ \ \ \\ \ ..., \ \textcolor{blue}{dp[i-1][j-k\cdot w_i] + k\cdot v_i} \ \} ,\quad \quad \quad 0<=k\cdot w_i<=j  \tag{1}
$$
而恰巧的是对于 $dp[i][j-w_i]$ 我们有：
$$
dp[i][j-w_i] = \min \{ \ \textcolor{red}{dp[i-1][j-w_i]}, \ \textcolor{teal}{dp[i-1][j-2\cdot w_i] + v_i}, \quad \quad \quad \quad \quad \quad \quad \quad \\ \ ..., \ \textcolor{blue}{dp[i-1][j-k\cdot w_i] + (k-1)\cdot v_i} \ \} , w_i<=k\cdot w_i<=j
\tag{2}
$$
观察发现式 2 与式 1 中的后 k 项刚好相差了一个 $v_i$ ，将式 2 代入式 1 可得简化后的「完全背包问题」的「状态转移方程」为：
$$
dp[i][j] = \min \{ \ dp[i-1][j],\quad \textcolor{red}{dp[i]}[j-w_i] + v_i\ \} ,\quad 0<=w_i<=j \ \ \quad \quad \quad \quad \quad \quad
\tag{3}
$$


> ⚠️ 注意，式 3 与「0-1 背包问题」的状态转移方程及其相似，差别（以红色标注）在于第二项中的状态转移是来自上一行还是本行。这也决定了具体编程实现时状态更新方式的异同。



```c++
 int numSquares(int n) {
     int maxn = sqrt(n); //找到搜索上界 3

     const int inf = 0x3f3f3f3f;
     int dp[maxn + 1][n + 1]; memset(dp, inf, sizeof(dp)); //前i个数，其平方数的和构成i的最少数量

     for (int i = 0; i <= maxn; ++i) 
         dp[i][0] = 0;

     for (int i = 1; i <= maxn; ++i) {
         int w = i * i;
         for (int j = 0; j <= n; ++j) {
             if (j - w < 0) {
                 dp[i][j] = dp[i-1][j];
             } else {
                 dp[i][j] = min(dp[i-1][j], dp[i][j-w] + 1);
             }
         }
     }

     return dp[maxn][n];
 }
```







# 全排列 DP

## 377. 组合总和 Ⅳ



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 表示选取的元素之和等于 i 的方案数
```



2. 确定**递推公式**

如果存在一种排列，其中的元素之和等于 i，则该排列的最后一个元素一定是数组 nums 中的一个元素。假设该排列的最后一个元素是 num，则一定有 num≤i，对于元素之和等于 i−num 的每一种排列，在最后添加 num 之后即可得到一个元素之和等于 i 的排列，因此在计算 dp[i] 时，应该计算**所有的 dp[i−num] 之和**。

```c++
for (int k = 0; k < nums.size(); ++k)
    if (i - nums[k] > 0)
		dp[i] += dp[i-nums[k]];
```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[0] = 1; 
```

不选取任何元素时，元素之和才为 0，因此只有 1 种方案。



4. 确定**遍历顺序**

外层循环是遍历从 1 到 target 的值，内层循环是遍历数组 nums 的值，在计算 dp[i] 的值时，nums 中的**每个小于等于 i 的元素都可能作为元素之和等于 i 的排列的最后一个元素**。







5. 举例推导dp数组





```c++
int combinationSum4(vector<int>& nums, int target) {
    int n = nums.size();

    int dp[target+1]; memset(dp, 0, sizeof(dp));     // dp[0] 组合成 target 的方案数

    dp[0] = 1;

    for (int i = 1; i <= target; ++i) {             // 遍历每个值
        for (int j = 0; j < n; ++j) {              
            int num = nums[j];                      
            if (i - num >= 0 && dp[i] < INT_MAX - dp[i - num] ) { 
                dp[i] += dp[i-num];
            }
        }
    }

    return dp[target];
}
```









----

## 139. 单词划分

跟 377 一样，没必要非得用完全背包来做，一维 dp 数组已经有很好的解释了。



`dp[i]` 表示是否可以从dict中选取一些元素 组成长度为 s.substr(0, i) 的字符串



```c++
bool wordBreak(string s, vector<string>& wordDict) {
    int m = s.size(); 

    bool dp[m + 1]; memset(dp, false, sizeof(dp));   //表示前 i 个单词，是否可以组成长度为 j 的字符串 

    dp[0] = true;

    for (int i = 1; i <= m; ++i) {

        for (int j = 0; j < wordDict.size(); ++j) {
            string str = wordDict[j];
            int sSize = str.size();
            if (i - sSize >= 0 && str == s.substr(i - sSize, sSize))	// 能取，并且完全相同
                dp[i] = dp[i] || dp[i - sSize];		// 注意要跟自己的状态一起转移，因为可能 for j 前边已经有true了
        }
    }

    return dp[m];
}
```





----

# 打家劫舍

## 198.打家劫舍



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 	打劫i以内的房屋能拿到的最多钱
i：		第i个房屋    
```



2. 确定**递推公式**

决定 dp[i] 的因素就是第i个房间偷还是不偷

- 偷：`dp[i] = d[i-2] + nums[i]`  第i-1房间不考虑
- 不偷：`dp[i] = dp[i-1]`（但也不是非要偷 i-1，因为dp[i-1] 也有偷或不偷两种情况）

```c++
dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[0] = nums[0]; //就是一定偷0，值最大 
dp[1] = max(nums[0], nums[1]); //挑一个偷
```



4. 确定**遍历顺序**

从递推公式可以看出，dp[i] 依赖 dp[0:i-1]，因此遍历的顺序是**从前到后**遍历的。



5. 举例推导dp数组



```c++
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int dp[n];
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);


    for (int i = 2; i < n; ++i) {
        dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
    }
    return dp[n-1];
}
```







## 213.打家劫舍II

唯⼀区别就是成环了。



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 	打劫i以内的房屋能拿到的最多钱
i：		第i个房屋    
```



2. 确定**递推公式**

成环的三种情况

- 不考虑首尾元素，
- 考虑首元素，不考虑尾元素，
- 考尾元素，不考虑首元素，

相当于把环拉直 按198.打家劫舍求解‘

但其实二三情况就包含了第一种情况

```c++
dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[0] = nums[0]; //就是一定偷0，值最大 
dp[1] = max(nums[0], nums[1]); //挑一个偷
```



4. 确定**遍历顺序**

从递推公式可以看出，dp[i] 依赖 dp[0:i-1]，因此遍历的顺序是**从前到后**遍历的。



5. 举例推导dp数组



```c++
int robRange(vector<int>& nums, int start, int end) {
    if (end - start == 0) return nums[start];
    if (end - start == 1) return max(nums[start], nums[start + 1]);

    int dp[nums.size()+1];
    dp[start] = nums[start];
    dp[start + 1] = max(nums[start], nums[start + 1]);
    for (int i = start + 2; i <= end; ++i) {
        dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
    }
    return dp[end];
}


int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int noStart = robRange(nums, 1, n-1);
    int noEnd = robRange(nums, 0, n-2);
    return max(noStart, noEnd);
}
```



----

## 337.打家劫舍 III

变成树了



### 记忆化递推

**本题⼀定是要后序遍历，因为通过递归函数的返回值来做下⼀步计算。**如果抢了当前节点，两个孩⼦就不是动，如果没抢当前节点，就可以**考虑**抢左右孩⼦（注意这里说的是“考虑”）

> 为什么是考虑？
>
> 当前左右孩子值很小，所有我要**左右孩子节点**的**孩子节点**



```c++
unordered_map<TreeNode* , int> umap; // 记录计算过的结果    
int rob(TreeNode* root) {
    //进来了就说明 该节点 root 是可以被选择的
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return root->val; 
    if (umap[root]) return umap[root];

    int val1 = root->val;
    if (root->left) val1 += rob(root->left->left) + rob(root->left->right);
    if (root->right) val1 += rob(root->right->left) + rob(root->right->right);  

    int val2 = rob(root->left) + rob(root->right);
    umap[root] = max(val1, val2);
    return umap[root];
}
```





---

### 动态规划

树形dp，树上进行状态转移

递归三部曲为框架，融合动规五部曲的内容



1. **确定递归函数的参数和返回值**

要求⼀个节点 偷与不偷的两个状态所得到的⾦钱，那么返回值就是⼀个长度为2的数组。

```c++
vector<int> robTree(TreeNode* cur);
```

返回数组就是dp数组。



2. **确定终止条件** 

```c++
if (cur == NULL) return vector<int>{0, 0};
```

空节点的话，很明显，无论偷还是不偷都是 0



3. **确定单层递归的逻辑**

```c++
vector<int> left = robTree(cur->left); // 左
vector<int> right = robTree(cur->right); // 右

// 偷cur
int val1 = cur->val + left[0] + right[0];
// 不偷cur
int val2 = max(left[0], left[1]) + max(right[0], right[1]);

return {val2, val1};
```

- 偷当前节点，那么左右孩子就不能偷，`val1 = cur->val + left[0] + right[0]; `

- 不偷当前节点，考虑是否偷左右孩子 `val2 =
  max(left[0], left[1]) + max(right[0], right[1]);`

最后当前节点的状态就是{val2, val1}; 即：{不偷当前节点得到的最大金钱，偷当前节点得到的最大金钱}





1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 	下标为0记录不偷该节点所得到的的最大金钱，下标为1记录偷该节点所得到的的最大金钱。
i：	    0/1
```

长度为2的数组怎么标记树中每个节点的状态呢？
在递归的过程中，**系统栈会保存**每⼀层递归的参数。





2. 确定**递推公式**

```c++
与确定单层递归的逻辑相同
```



3. dp数组如何**初始化**

```c++
if (cur == NULL) return vector<int>{0, 0};
```

递归的最后一层就是 dp 的初始化



4. 确定**遍历顺序**

后序遍历， 先计算左右子树的状态，再计算是否考虑加根节点。

```c++
// 下标0：不偷，下标1：偷
vector<int> left = robTree(cur->left); // 左
vector<int> right = robTree(cur->right); // 右
// 中
```



5. 举例推导dp数组





```c++
vector<int> robTree(TreeNode* cur) {
    if (cur == nullptr) return vector<int> {0, 0};

    vector<int> left = robTree(cur->left);
    vector<int> right = robTree(cur->right);

    int val1Choice = cur->val + left[0] + right[0];
    int val0Choice = max(left[0], left[1]) + max(right[0], right[1]);

    return vector<int> {val0Choice, val1Choice};
}

int rob(TreeNode* root) {
    vector<int> res = robTree(root);
    return max(res[0], res[1]);
}
```







---

# 股票问题

## 121. 买卖股票的最佳时机



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][0]:  第i天持有股票所得最多现金。
dp[i][1]:  第i天不持有股票所得最多现金
i：	      第i天
```



2. 确定**递推公式**

两种情况

- 持有，第 i 天买入，变成持有状态    `dp[i][1] = - prices[i] `
- 持有，第 i-1 天就持有                        `dp[i][0] = dp[i-1][0] `



- 未持有，第 i 天卖出，变成未持有状态     `dp[i][0] = dp[i-1][0] + prices[i]` 
- 未持有，第 i-1 天就未持有                         `dp[i][1] = dp[i-1][1]` 





3. dp数组如何**初始化**

```c++
dp[0][0] = -prices[0]; 
dp[0][1] = 0; 
```



4. 确定**遍历顺序**

从递推公式可以看出，因此遍历的顺序是**从前到后**遍历的。



5. 举例推导dp数组

![image-20220413162703132](assets/image-20220413162703132.png)

左边一列就是更新最小的 price

右边是找哪一天卖出去最合适

```c++
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(), vector<int>(2, 0));

    dp[0][0] = -prices[0]; // 持有
    dp[0][1] = 0; // 未持有

    for (int i = 1; i < prices.size(); ++i) {
        dp[i][0] = max(dp[i-1][0], -prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] + prices[i]); // 找哪一天卖出去钱最多
    }

    return dp[prices.size()-1][1];	// 不持有股票状态所得⾦钱⼀定⽐持有股票状态得到的多


}
```





---

## 122. 买卖股票的最佳时机II

本题股票可以买卖多次了（注意只有⼀只股票，所以再次购买前要出售掉之前的股票）



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][0]:  第i天持有股票所得最多现金。
dp[i][1]:  第i天不持有股票所得最多现金
i：	      第i天
```

**注意这里说的是“持有”，“持有”不代表就是当天“买入”！也有可能是昨天就买入了，今天保持持有的状态**





2. 确定**递推公式**

两种情况

- 持有，第i天买入，变成持有状态    `dp[i][1] = dp[i-1][1] - prices[i] ` 昨天不持有股票的现金减去今天股票的价格
- 持有，第i-1天就持有                        `dp[i][0] = dp[i-1][0] `



- 未持有，第i天卖出，变成未持有状态     `dp[i][0] = dp[i-1][0] + prices[i]` 
- 未持有，第i-1天就未持有                         `dp[i][1] = dp[i-1][1]` 





3. dp数组如何**初始化**

```c++
dp[0][0] = 0 - prices[0]; 
dp[0][1] = 0; 
```





4. 确定**遍历顺序**

从递推公式可以看出，因此遍历的顺序是**从前到后**遍历的。





5. 举例推导dp数组

```c++
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(), vector<int>(2, 0));

    dp[0][0] = 0 - prices[0];    // 持有
    dp[0][1] = 0;    // 不持有

    for (int i = 1; i < prices.size(); ++i) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] + prices[i]);
    }

    return dp[prices.size()-1][1];
}
```







---

## 123. 买卖股票的最佳时机III

⾄多买卖两次，这意味着可以买卖⼀次，可以买卖两次，也可以不买卖。



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][j]:  第i天状态j所剩最大现金

⼀天⼀共就有五个状态，
0. 没有操作
1. 第⼀次买⼊
2. 第⼀次卖出
3. 第⼆次买⼊
4. 第⼆次卖出
```





2. 确定**递推公式**

`dp[i][1]`，表示的是第 i 天，买入股票的状态，**并不是说⼀定要第 i 天买入股票**。



达到 `dp[i][1]` 状态，有两个具体操作：

- 操作一：第 i 天买入股票，那么 `dp[i][1] = dp[i-1][0] - prices[i]`
- 操作二：第 i 天没有操作，而是沿用前一天买入的状态，`dp[i][1] = dp[i-1][1]`



`dp[i][2]` 也有两个操作

- 操作一：第 i 天卖出股票了，那么 `dp[i][2] = dp[i-1][1] + prices[i]`
- 操作二：第 i 天没有操作，沿用前一天卖出股票的状态，即：`dp[i][2] = dp[i-1][2]`



达到 `dp[i][3]` 状态，有两个具体操作：

- 操作一：第 i 天买入股票，那么 `dp[i][3] = dp[i-1][2] - prices[i]`
- 操作二：第 i 天没有操作，而是沿用前一天买入的状态，`dp[i][3] = dp[i-1][3]`



`dp[i][4]` 也有两个操作

- 操作一：第 i 天卖出股票了，那么 `dp[i][4] = dp[i-1][3] + prices[i]`
- 操作二：第 i 天没有操作，沿用前一天卖出股票的状态，即：`dp[i][4] = dp[i-1][4]`











3. dp数组如何**初始化**



```c++
//第0天没有操作
dp[0][0] = 0; 

// 第0天做第⼀次买入的操作
dp[0][1] = 0 - prices[0]; 

// 第0天做第一次卖出的操作 当天买当天卖为0
dp[0][2] = 0;

// 第0天做第二次买入的操作
dp[0][3] = 0 - prices[0];

// 第0天做第二次卖出的操作 当天买当天卖为0
dp[0][4] = 0;
```





4. 确定**遍历顺序**

从递推公式可以看出，因此遍历的顺序是**从前到后**遍历的。





5. 举例推导dp数组

![image-20220414115900419](assets/image-20220414115900419.png)



最大的时候⼀定是卖出的状态，而两次卖出的状态现金最大⼀定是最后一次卖出。所以最终最大利润是 `dp[4][4]`



```c++
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(), vector<int>(5, 0));

    dp[0][0] = 0;
    dp[0][1] = -prices[0];  // 第i天 第一次买入
    dp[0][2] = 0;           // 第i天 第一次卖出
    dp[0][3] = -prices[0];  // 第i天 第二次买入
    dp[0][4] = 0;           // 第i天 第二次卖出

    for (int i = 1; i < prices.size(); ++i) {
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        dp[i][2] = max(dp[i-1][2], dp[i-1][1] + prices[i]);
        dp[i][3] = max(dp[i-1][3], dp[i-1][2] - prices[i]);
        dp[i][4] = max(dp[i-1][4], dp[i-1][3] + prices[i]);
    }

    return dp[prices.size() - 1][4];
}
```





---

## 188. 买卖股票的最佳时机 IV

⾄多买卖 k 次，与123完全一致



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][j]:  第i天状态j所剩最大现金

⼀天⼀共就有五个状态，
0. 没有操作
1. 第⼀次买⼊
2. 第⼀次卖出
3. 第⼆次买⼊
4. 第⼆次卖出
5. 第三次买⼊
6. 第三次卖出    
...
...    
```





2. 确定**递推公式**

`dp[i][1]`，表示的是第 i 天，买入股票的状态，**并不是说⼀定要第 i 天买入股票**。



```c++
for (int i = 1; i < prices.size(); ++i) {
    for (int j = 1; j < 2*k + 1; ++j) {
        if (j & 1) dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] - prices[i]); //奇数
        else dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + prices[i]);
    }
}
```





3. dp数组如何**初始化**



```c++
vector<vector<int>> dp(prices.size(), vector<int>(2*k + 1, 0));

dp[0][0] = 0;
for (int i = 1; i < 2 * k + 1; i++) {
    if (i & 1) dp[0][i] = -prices[0];   // 奇数
}
```





4. 确定**遍历顺序**

从递推公式可以看出，因此遍历的顺序是**从前到后**遍历的。





5. 举例推导dp数组

最大的时候⼀定是卖出的状态，而两次卖出的状态现金最大⼀定是最后一次卖出。=

```c++
int maxProfit(int k, vector<int>& prices) {
    if (prices.size() == 0) return 0;

    vector<vector<int>> dp(prices.size(), vector<int>(2*k + 1, 0));

    dp[0][0] = 0;
    for (int i = 1; i < 2 * k + 1; i++) {
        if (i & 1) dp[0][i] = -prices[0];   // 奇数
        else dp[0][i] = 0; 
        // cout << dp[0][i] << " ";
    }

    for (int i = 1; i < prices.size(); ++i) {
        for (int j = 1; j < 2*k + 1; ++j) {
            if (j & 1) dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] - prices[i]); //奇数
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + prices[i]);
        }
    }


    return dp[prices.size()-1][2*k];
}
```





## 309. 最佳买卖股票时机含冷冻期

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第⼆天买入股票 (即冷冻期为 1 天)。



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][0]:  第i天持有股票所得最多现金
dp[i][1]:  两天前就卖出了股票，度过了冷冻期
dp[i][2]:  今天卖出股票
dp[i][3]:  今天为冷冻期状态，冷冻期状态不可持续
i：	      第i天
```

**注意这里说的是“持有”，“持有”不代表就是当天“买入”！也有可能是昨天就买入了，今天保持持有的状态**





2. 确定**递推公式**

- 达到买入股票状态（状态⼀）即：`dp[i][0]`，有两个具体操作：
  - 第 `i-1` 天就持有，延续前一天状态 `dp[i-1][0]`
  - 第 `i-1` 天不持有，第 i 天买入
    - 前一天是冷冻期  `dp[i-1][3] - prices[i]`
    - 前一天不是冷冻期 `dp[i-1][1] - prices[i]`




- 达到保持卖出状态（状态二）即：`dp[i][1]`，有两个具体操作：
  - 第 `i-1` 天不是冷冻期，保持卖出状态 `dp[i-1][1]`
  - 第 `i-1` 天是冷冻期，保持卖出状态 `dp[i-1][3]`



- 今天卖出股票（状态三）即：`dp[i][2]`，有一个操作：

  - 第 `i-1` 天持有，今天卖出 `dp[i-1][0] + prices[i]`

    

- 今天为冷冻期状态（状态四）即：`dp[i][3]`，：
  
  - 第 `i-1` 天卖出股票 `dp[i-1][2]`



```c++
dp[i][0] = max(dp[i-1][0], max(dp[i-1][3], dp[i-1][1]) - prices[i]);
dp[i][1] = max(dp[i-1][1], dp[i-1][3]);
dp[i][2] = dp[i-1][0] + prices[i];
dp[i][3] = dp[i-1][2];    
```

​	



3. dp数组如何**初始化**

```c++
dp[0][0] = -prices[0]; 
dp[0][1] = 0;
dp[0][2] = 0; 
dp[0][3] = 0;
```





4. 确定**遍历顺序**

从递推公式可以看出，因此遍历的顺序是**从前到后**遍历的。





5. 举例推导dp数组

```c++
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(), vector<int>(2, 0));

    dp[0][0] = 0 - prices[0];    // 持有
    dp[0][1] = 0;    // 不持有

    for (int i = 1; i < prices.size(); ++i) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] + prices[i]);
    }

    return dp[prices.size()-1][1];
}
```















---

## 714. 买卖股票的最佳时机含手续费

本题有了手续费





1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][0]:  第i天持有股票所得最多现金。
dp[i][1]:  第i天不持有股票所得最多现金
i：	      第i天
```

**注意这里说的是“持有”，“持有”不代表就是当天“买入”！也有可能是昨天就买入了，今天保持持有的状态**





2. 确定**递推公式**

两种情况

- 持有，第i天买入，变成持有状态    `dp[i][1] = dp[i-1][1] - prices[i] - fee ` 昨天不持有股票的现金减去今天股票的价格
- 持有，第i-1天就持有                        `dp[i][0] = dp[i-1][0] `



- 未持有，第i天卖出，变成未持有状态     `dp[i][0] = dp[i-1][0] + prices[i]` 
- 未持有，第i-1天就未持有                         `dp[i][1] = dp[i-1][1]` 





3. dp数组如何**初始化**

```c++
dp[0][0] = 0 - prices[0] - fee; 
dp[0][1] = 0; 
```





4. 确定**遍历顺序**

从递推公式可以看出，因此遍历的顺序是**从前到后**遍历的。





5. 举例推导dp数组

```c++
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(), vector<int>(2, 0));

    dp[0][0] = 0 - prices[0] - fee;    // 持有
    dp[0][1] = 0;    // 不持有

    for (int i = 1; i < prices.size(); ++i) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] - prices[i] - fee);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] + prices[i]);
    }

    return dp[prices.size()-1][1];
}
```















---

# 接雨水

## 42. 接雨水

对于下标 i，下雨后水能到达的最大高度等于下标 i 两边的最大高度的最小值，下标 i 处能接的雨水量等于下标 i 处的水能到达的最大高度减去 $\textit{height}[i]$。

朴素的做法是对于数组 $\textit{height}$ 中的每个元素，分别向左和向右扫描并记录左边和右边的最大高度，然后计算每个下标位置能接的雨水量。假设数组 $\textit{height}$ 的长度为 $n$，该做法需要对每个下标位置使用 $O(n)$ 的时间向两边扫描并得到最大高度，因此总时间复杂度是 $O(n^2)$。



上述做法的时间复杂度较高是因为需要对每个下标位置都向两边扫描。如果已经知道每个位置两边的最大高度，则可以在 O(n) 的时间内得到能接的雨水总量。使用动态规划的方法，可以在 O(n) 的时间内预处理得到每个位置两边的最大高度。

创建两个长度为 n 的数组 $\textit{leftMax}$ 和 $\textit{rightMax}$。对于 $0 \le i<n$，$\textit{leftMax}[i]$ 表示下标 i 及其左边的位置中，$\textit{height}$ 的最大高度，$\textit{rightMax}[i]$ 表示下标 i 及其右边的位置中，$\textit{height}$ 的最大高度。

显然，$\textit{leftMax}[0]=\textit{height}[0]$，$\textit{rightMax}[n-1]=\textit{height}[n-1]$。两个数组的其余元素的计算如下：

当 $1 \le i \le n-1$ 时，$\textit{leftMax}[i]=\max(\textit{leftMax}[i-1], \textit{height}[i])$；

当 $0 \le i \le n-2$ 时，$\textit{rightMax}[i]=\max(\textit{rightMax}[i+1], \textit{height}[i])$。

因此可以正向遍历数组 $\textit{height}$ 得到数组 $\textit{leftMax}$ 的每个元素值，反向遍历数组 $\textit{height}$ 得到数组 $\textit{rightMax}$ 的每个元素值。

在得到数组 $\textit{leftMax}$ 和 $\textit{rightMax}$ 的每个元素值之后，对于 $0 \le i<n$，下标 i 处能接的雨水量等于 $\min(\textit{leftMax}[i],\textit{rightMax}[i])-\textit{height}[i]$。遍历每个下标位置即可得到能接的雨水总量。

动态规划做法可以由下图体现。

![fig1](assets/23036.png)



```c++
int trap(vector<int>& height) {
    int n = height.size();
    if (n == 0) {
        return 0;
    }
    vector<int> leftMax(n);
    leftMax[0] = height[0];
    for (int i = 1; i < n; ++i) {
        leftMax[i] = max(leftMax[i - 1], height[i]);
    }

    vector<int> rightMax(n);
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        rightMax[i] = max(rightMax[i + 1], height[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += min(leftMax[i], rightMax[i]) - height[i];
    }
    return ans;
}
```









----

# 子序列

## 不连续

### 300. 最长递增子序列 LIS

https://blog.csdn.net/qq_41765114/article/details/88415541



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 以 i 结尾的最长递增子序列长度
i    : 以 i 结尾
```



2. 确定**递推公式**

在 dp 表 $j\in [0, \dots,i-1]$ 中比对时，若 nums[i] > nums[j]，

那么 dp[j] + 1 **可能**为 dp[i] 的最终值。

需要在所有的可能值中取最大值。

```c++
if (nums[i] > nums[j])  dp[i] = max(dp[i], dp[j] + 1);
```



3. dp数组如何**初始化**

```c++
dp[0] = 1;
```



4. 确定**遍历顺序**

两层循环，遍历的顺序是从前到后遍历的。第二层 $j\in [0, \dots,i-1]$ ，每次外层循环完一次，更新一次值。



5. 举例推导dp数组



<img src="assets/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNzY1MTE0,size_16,color_FFFFFF,t_70.png" alt="在这里插入图片描述" style="zoom: 50%;" />



<img src="assets/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNzY1MTE0,size_16,color_FFFFFF,t_70-16492104292793.png" alt="在这里插入图片描述" style="zoom:50%;" />



<img src="assets/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNzY1MTE0,size_16,color_FFFFFF,t_70-16492104358815.png" alt="在这里插入图片描述" style="zoom:50%;" />



<img src="assets/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNzY1MTE0,size_16,color_FFFFFF,t_70-16492104399287.png" alt="在这里插入图片描述" style="zoom:50%;" />



<img src="assets/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxNzY1MTE0,size_16,color_FFFFFF,t_70-16492104735069.png" alt="在这里插入图片描述" style="zoom:50%;" />



```c++
int lengthOfLIS(vector<int>& nums) {
    if (nums.size() == 1) return 1;

    vector<int> dp(nums.size(), 1);
    int res = 0;
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j])  dp[i] = max(dp[i], dp[j] + 1);
        }
        res = dp[i] > res ? dp[i] : res;
    }

    return res;
}
```





---

### 1143. 最长公共子序列 LCS



1. 确定**dp数组**以及**下标的含义**

```C++
dp[i][j]: 长度为[0, i - 1]的字符串text1与长度为[0, j - 1]的字符串text2的最长公共子序列为dp[i][j]
    
i       : 以 i 结尾
```



2. 确定**递推公式**

主要就是两种情况： text1[i - 1] 与 text2[j - 1] 相同，text1[i - 1] 与 text2[j - 1] 不相同

- 如果 text1[i - 1] 与 text2[j - 1] 相同，那么找到了⼀个公共元素，所以`dp[i][j] = dp[i - 1][j - 1] + 1;`
- 如果 text1[i - 1] 与 text2[j - 1] 不相同，那就看看 `text1[0, i - 2]`与 `text2[0, j - 1]` 的最长公共子序列 和 `text1[0, i - 1]` 与 `text2[0, j - 2]` 的最长公共子序列，取最大的。即 `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);`



```c++
if (text1[i - 1] == text2[j - 1]) {
	dp[i][j] = dp[i - 1][j - 1] + 1;
} else {
	dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
}
```



3. dp数组如何**初始化**

```c++
test1[0, i-1]和空串的最长公共⼦序列自然是0，所以dp[i][0] = 0
同理dp[0][j]也是0。
其他下标都是随着递推公式逐步覆盖，初始为多少都可以，那么就统⼀初始为0。
vector<vector<int>> vec(text.size()+1, vector<int>(text2.size()+1, 0)); 
```



4. 确定**遍历顺序**

从前向后，从上到下来遍历这个矩阵。



5. 举例推导dp数组



![image-20220406093936394](assets/image-20220406093936394.png)

```C++
int longestCommonSubsequence(string text1, string text2) {
    int n1 = text1.size(), n2 = text2.size();
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    int res = -0x3f3f3f3f;
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }

            res = max(res, dp[i][j]);
        }   
    }

    return res;
}
```







---

### 522. 最长特殊序列 II

题目翻译：给出一个字符串数组，在里面找出字符串满足`当前字符串不是字符串数组中其他字符串的子序列`，返回满足条件的字符串中 `最长的字符串的长度` 

```c++
bool isSubsequence(string &s1, string &s2) {
    int m = s1.size(), n = s2.size();

    if (m > n) {		
        return false;
    }

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i < m + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[m][n] == m;	// m一定是最小的
}

int findLUSlength(vector<string>& strs) {
    int res = -1;
    for (int i = 0; i < strs.size(); ++i) {
        bool flag = true;
        for (int j = 0; j < strs.size(); ++j) {
            if (i == j) continue;

            if (isSubsequence(strs[i], strs[j])) {  //如果它是其它字符串的子串
                flag = false;
                break;
            } 
        }

        if (flag) res = max(res, (int)strs[i].size());
    }    

    return res;
}
```





---

### 1035. 不相交的线

1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][j]: 以 i-1 结尾的字符串和 以j-1 结尾的子序列的最大连线数
i       : 以 i 结尾
```



2. 确定**递推公式**

- 如果 `nums[i-1] == nums[j-1]`，`dp[i][j] = dp[i-1][j-1] + 1;`
- 否则 `dp[i][j] = max(dp[i][j-1], dp[j-1][i]);`



```c++
if (nums[i-1] == nums[j-1]) {
    dp[i][j] = dp[i-1][j-1] + 1;
} else {
    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
}
```



3. dp数组如何**初始化**

```c++
test1[0, i-1]和空串的最长公共⼦序列自然是0，所以dp[i][0] = 0
同理dp[0][j]也是0。
其他下标都是随着递推公式逐步覆盖，初始为多少都可以，那么就统⼀初始为0。
vector<vector<int>> vec(text.size()+1, vector<int>(text2.size()+1, 0)); 
```



4. 确定**遍历顺序**

从前向后，从上到下来遍历这个矩阵。



5. 举例推导dp数组



### 873. 最长的斐波那契子序列的长度

```c++
class Solution {
public:
    // dp[j][k] 表示在以第j和第k为子序列的后两位时，能找到的最长子序列的长度
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int j = 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) { // 必须保证 j < k
                int iNum = arr[k] - arr[j];
                auto it = lower_bound(arr.begin(), arr.end(), iNum);
                if (it != arr.end() && *it == iNum) {
                    int i = it - arr.begin();
                    if (i < j)  // 必须要保证 i < j
                        dp[j][k] = max(dp[i][j] + 1, 3);
                }
            }
        }

        int res = 0;
        for (auto &oneD : dp)
            for (auto &num : oneD)
                res = max(res, num);

        return res;
    }
};
```





----

## 连续

### 674. 最长连续递增序列



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 以 i 结尾的最长递增子序列长度
i    : 以 i 结尾
```



2. 确定**递推公式**

- 若 nums[i] > nums[i-1]，那么 dp[i] = dp[i-1] + 1 。
- 若 nums[i] <= nums[i-1]，那么 dp[i] = 1。

```c++
if (nums[i] > nums[j])  dp[i] = dp[i-1] + 1;
else dp[i] = 1;
```



3. dp数组如何**初始化**

所有连续递增序列默认都为 1，即自身

```c++
vector<int> dp(nums.size(), 1); 
```



4. 确定**遍历顺序**

一层循环，遍历的顺序是从前到后遍历的。



5. 举例推导dp数组



```c++
int findLengthOfLCIS(vector<int>& nums) {
    int n = nums.size();

    vector<int> dp(n, 1);

    for (int i = 1; i < n; ++i) {
        if (nums[i] > nums[i-1])
            dp[i] = dp[i-1] + 1;
    }

    return *max_element(dp.begin(), dp.end());
}
```





---

### 718. 最长重复子数组

简易版1143. LCS



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][j]: 长度为 [0, i - 1] 的 nums1 与长度为 [0, j - 1] 的 nums 的连续子序列长度
    
i    : 以 i 结尾
```



2. 确定**递推公式**

nums[i-1] 与 nums2[i-1]相同

那么找到了⼀个公共元素，所以 `dp[i][j] = dp[i - 1][j - 1] + 1;`

> 注意它为什么要加 `dp[i-1][j-1]` 这样就限定了子数组的连续性

```c++
if (nums1[i - 1] == nums2[j - 1]) {
	dp[i][j] = dp[i - 1][j - 1] + 1;
}
```



3. dp数组如何**初始化**

```c++
nums1[0, i-1]和空串的最长公共⼦序列自然是0，所以dp[i][0] = 0
同理dp[0][j]也是0。
其他下标都是随着递推公式逐步覆盖，初始为多少都可以，那么就统⼀初始为0。
vector<vector<int>> vec(text.size()+1, vector<int>(text2.size()+1, 0)); 
```



4. 确定**遍历顺序**

从前向后，从上到下来遍历这个矩阵。



5. 举例推导dp数组

![image-20220406123729625](assets/image-20220406123729625.png)



```c++
int findLength(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    int res = -0x3f3f3f3f;
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (nums1[i - 1] == nums2[j - 1]) 
                dp[i][j] = dp[i-1][j-1] + 1;

            res = max(dp[i][j], res);
        }
    }

    return res;
}
```





---

### 53. 最大子序和



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i]: 下标为 i 大和连续子数组
    
i    : 以 i 结尾
```



2. 确定**递推公式**

- 如果 `dp[i-1] + nums[i] >= 0` ， 则 `dp[i] = dp[i-1] + nums[i]`
- 如果 `dp[i-1] + nums[i] < 0`   ， 则 `dp[i] = nums[i]`



```c++
dp[i] = max(dp[i - 1] + nums[i], nums[i]);
```



3. dp数组如何**初始化**

```c++
vector<int> dp(nums.size(), 0); 
dp[0] = nums[0];
```



4. 确定**遍历顺序**

从前向后来遍历。



5. 举例推导dp数组

```c++

```



---

## 回文

### 647. 回文子串





### 516. 最长回文子串







## 编辑距离

### 392. 判断子序列

就是判断 1143. 最长公共子序列 

```c++
bool isSubsequence(string s, string t) {
    int n1 = s.size(), n2 = t.size();

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[n1][n2] == n1;
}
```







---

### 72. 编辑距离



1. 确定**dp数组**(dp table)以及**下标的含义**

```C++
dp[i][j]:   代表 word1 中前 i 个字符，变换到 word2 中前 j 个字符，最短需要操作的次数
```

需要考虑 word1 或 word2 一个字母都没有，即全增加/删除的情况，所以预留 `dp[0][j]` 和 `dp[i][0]`





2. 确定**递推公式**

增 `dp[i][j] = dp[i][j-1] + 1`，i 比 j 少了一个字母，在 i 结尾插入这个字母 

删 `dp[i][j] = dp[i-1][j] + 1`，i 比 j 多了一个尾字母，在 j 结尾插入这个字母 

改 字母不同：`dp[i][j] = dp[i-1][j-1] + 1`，

​     字母相同：`dp[i][j] = dp[i-1][j-1]`

配合增删改这三种操作，需要对应的 dp 把操作次数，取三种的最小



```c++
增： D[i][j-1] 为 A 的前 i 个字符和 B 的前 j - 1 个字符编辑距离的子问题。即对于 B 的第 j 个字符，我们在 A 的末尾添加了一个相同的字符，那么 D[i][j] 最小可以为 D[i][j-1] + 1

删： D[i-1][j] 为 A 的前 i - 1 个字符和 B 的前 j 个字符编辑距离的子问题。即对于 A 的第 i 个字符，我们在 B 的末尾添加了一个相同的字符，那么 D[i][j] 最小可以为 D[i-1][j] + 1

改： D[i-1][j-1] 为 A 前 i - 1 个字符和 B 的前 j - 1 个字符编辑距离的子问题。即对于 B 的第 j 个字符，我们修改 A 的第 i 个字符使它们相同，那么 D[i][j] 最小可以为 D[i-1][j-1] + 1。特别地，如果 A 的第 i 个字符和 B 的第 j 个字符原本就相同，那么我们实际上不需要进行修改操作。在这种情况下，D[i][j] 最小可以为 D[i-1][j-1]
```



3. dp数组如何**初始化**

```c++
// 边界条件
dp[0] = 1; 
```

不选取任何元素时，元素之和才为 0，因此只有 1 种方案。



4. 确定**遍历顺序**

按顺序计算，当计算 `dp[i][j]` 时，`dp[i - 1][j]` ， `dp[i][j - 1]` ， `dp[i - 1][j - 1]` 均已经确定了







5. 举例推导dp数组

![img](assets/62ea5e33d1ee2396c74c87941269bc1e53cd7385c341c49b160129f2e49de80e-图片.png)

**i = 0，表示此时 word1 是个空字符串，只能增加 1，2，3 得到 "r", "ro", "ros"**

![img](assets/d892c5f4463bc801dff85fed4c8b8e76ed0d178b1b917a4447b642c243d46c51-图片.png)

**j = 0，表示此时 word2 是个空字符串，只能删除 1，2，3，4，5 得到 ""**

```c++
int minDistance(string word1, string word2) {
    int n1 = word1.size(), n2 = word2.size();

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    for (int i = 1; i <= n1; ++i)
        dp[i][0] = i;

    for (int i = 1; i <= n2; ++i)
        dp[0][i] = i;

    int add, del, change;
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            add = dp[i-1][j] + 1;
            del = dp[i][j-1] + 1;

            if (word1[i - 1] == word2[j - 1]) {
                change = dp[i-1][j-1];
            } else {
                change = dp[i-1][j-1] + 1;
            }

            dp[i][j] = min(add, min(del, change));
        }
    }

    return dp.back().back();
}   
```







---

### 115. 不同的子序列

s 为字符串，t为待匹配的短字符串

相对于编辑距离，简单了不少，因为本题只有删除操作，不用考虑替换增加之类，但比 392 更有难度，因为要有很多子序列

1. 确定**dp数组**(dp table)以及**下标的含义**

```c++
dp[i][j]:	以 i-1 为结尾的 s 子序列中出现以 j-1 为结尾的 t 的个数
```



2. 确定**递推公式**

s[i - 1] 与 t[j - 1] 相等
s[i - 1] 与 t[j - 1] 不相等

```c++
当s[i - 1] 与 t[j - 1]相等时，dp[i][j]可以有两部分组成。

一部分是用s[i - 1]来匹配，那么个数为dp[i - 1][j - 1]。
一部分是不用s[i - 1]来匹配，个数为dp[i - 1][j]。
    
所以当 s[i - 1] 与 t[j - 1] 相等时，dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]
```

>  例如： s：bagg 和 t：bag ，s[3] 和 t[2]是相同的，但是字符串s也可以不用s[3]来匹配，即用s[0]s[1]s[2]组成的bag。当然也可以用s[3]来匹配，即：s[0]s[1]s[3]组成的bag。



```C++
当 s[i - 1] 与 t[j - 1] 不相等时，不能用 s[i - 1] 来匹配，即：dp[i - 1][j]
所以递推公式为：dp[i][j] = dp[i - 1][j];
```





3. dp数组如何**初始化**

```c++
dp[i][0] 表示：以i-1为结尾的s可以随便删除元素，出现空字符串的个数。
那么dp[i][0]一定都是1，因为也就是把以i-1为结尾的s，删除所有元素，出现空字符串的个数就是1。

dp[0][j]：空字符串s可以随便删除元素，出现以j-1为结尾的字符串t的个数。
那么dp[0][j]一定都是0，s如论如何也变成不了t。    
    
dp[0][0]应该是1，空字符串s，可以删除0个元素，变成空字符串t。    
```



4. 确定**遍历顺序**

```c++
左上到右下
```



5. 举例推导dp数组

![115.不同的子序列](assets/115.不同的子序列.jpg)



```c++
int numDistinct(string s, string t) {
    int n1 = s.size(), n2 = t.size();
    // dp[i][j] 表示 s 前 i 个字符串包含 t 的前 j 个字符串的个数
    vector<vector<unsigned long long>> dp(n1 + 1, vector<unsigned long long>(n2 + 1, 0));

    for (int i = 0; i <= n1; ++i) 
        dp[i][0] = 1;

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (s[i - 1] == t[j - 1]) {  //不相等
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp.back().back();
}
```







---

### 583. 两个字符串的删除操作



1. 确定**dp数组**(dp table)以及**下标的含义**

```c++
dp[i][j]:	以i-1为结尾的字符串word1，和以j-1位结尾的字符串word2，想要达到相等，所需要删除元素的最少次数
```



2. 确定**递推公式**

- 当word1[i - 1] 与 word2[j - 1]相同的时候
- 当word1[i - 1] 与 word2[j - 1]不相同的时候

```c++
当word1[i - 1] 与 word2[j - 1]相同的时候，dp[i][j] = dp[i - 1][j - 1];
```



```C++
当word1[i - 1] 与 word2[j - 1]不相同的时候，有三种情况：
    
情况一：删word1[i - 1]，最少操作次数为dp[i - 1][j] + 1
情况二：删word2[j - 1]，最少操作次数为dp[i][j - 1] + 1
情况三：同时删word1[i - 1]和word2[j - 1]，操作的最少次数为dp[i - 1][j - 1] + 2

那最后当然是取最小值
```





3. dp数组如何**初始化**

```c++
dp[i][0]：word2为空字符串，以i-1为结尾的字符串word1要删除多少个元素，才能和word2相同呢?
dp[i][0] = i

dp[0][j]：word1为空字符串，以j-1为结尾的字符串word2要删除多少个元素，才能和word1相同呢?
dp[0][j] = j    
    
dp[0][0]应该是0，空字符串word1为空字符串，可以删除0个元素，变成空字符串word2。    
```



4. 确定**遍历顺序**

```c++
左上到右下
```



5. 举例推导dp数组

![583.两个字符串的删除操作1](assets/20210714101750205.png)

```c++
int minDistance(string word1, string word2) {
    int n1 = word1.size(), n2 = word2.size();

    // dp[i][j] 表示  字符串word1前i个字符串 变成 word2 前j个字符所需要的最小步数
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    for (int i = 0; i <= n1; ++i)
        dp[i][0] = i;

    for (int j = 0; j <= n2; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = min(dp[i-1][j-1] + 2, min(dp[i-1][j] + 1, dp[i][j-1] + 1));
            }
        }
    }

    return dp.back().back();
}
```









---

# 脑筋急转弯

## 396. 旋转函数

记数组nums 的元素之和为 numSum。根据公式，可以得到：

$$
F(0) = 0 \times \textit{nums}[0] + 1 \times \textit{nums}[1] + \ldots + (n-1) \times \textit{nums}[n-1]F(0)=0×nums[0]+1×nums[1]+…+(n−1)×nums[n−1]\\
F(1) = 1 \times \textit{nums}[0] + 2 \times \textit{nums}[1] + \ldots + 0 \times \textit{nums}[n-1] = F(0) + \textit{numSum} - n \times \textit{nums}[n-1]
$$


更一般地，当 $1 \le k \lt n$ 时，$F(k) = F(k-1) + \textit{numSum} - n \times \textit{nums}[n-k]$。我们可以不停迭代计算出不同的 $F(k)$，并求出最大值。


```c++
int maxRotateFunction(vector<int>& nums) {
    int n = nums.size();

    int sumn = accumulate(nums.begin(), nums.end(), 0);

    vector<int> F(n, 0);
    for (int i = 0; i < n; ++i) {
        F[0] += (i * nums[i]);
    }


    for (int i = 1; i < n; ++i) {
        F[i] = F[i-1] + sumn - n * nums[n-i];
    }

    return *max_element(F.begin(), F.end());
}
```





## 152. 乘积最大子数组

思路：最大值乘以一个负数之后可能变为最小值
   最小值乘以一个负数之后可能成为最大值

​           该数就是一个最大值/该数就是一个最小值

用 `maxx[i]` 记录以第i个元素结尾的子数组乘积最大值
用 `minn[i]` 记录以第i个元素结尾的子数组乘积最小值
$$
maxx[i]=max(maxx[i-1]*num[i],minn[i-1]*num[i],num[i])\\
minn[i]=min(maxx[i-1]*num[i],minn[i-1]*num[i],num[i])
$$


```c++
int maxProduct(vector<int>& nums) {
    int n = nums.size(); 

    vector<int> dpMax(n, 0);
    vector<int> dpMin(n, 0);

    dpMax[0] = nums[0];
    dpMin[0] = nums[0];

    int res = nums[0];
    for (int i = 1; i < n; ++i) {
        dpMax[i] = max(max(dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]), nums[i]);
        dpMin[i] = min(min(dpMin[i-1] * nums[i], dpMax[i-1] * nums[i]), nums[i]);

        res = max(res, dpMax[i]);
    }

    return res;
}
```





# 241. 为运算表达式设计优先级

我们把字符串按照操作符分割为两个子表达式，然后将两个子表达式的结果集进行当前 `op` 的操作，组装成新的结果集，对每个 `op` 分别进行分割得到的结果集之和就是最终的答案。而子表达式又是相同的问题，可以采用递归进行计算，最终会递归到一个`digit` 上。

![image.png](assets/1656633782-AKtLNr-image.png)

```c++
vector<int> diffWaysToCompute(string expression) {
    if (expression.size() == 0) {
        return {};
    } 

    vector<int> ans;
    int n = expression.size();
    for (int i = 0; i < n; ++i) {
        char c = expression[i];

        if (!isdigit(c)) {      // 当碰到操作符
            vector<int> left = diffWaysToCompute(expression.substr(0, i));
            vector<int> right = diffWaysToCompute(expression.substr(i+1, n));

            for (int lnum : left) {
                for (int rnum : right) {
                    if (c == '+') {
                        ans.push_back(lnum + rnum);
                    } else if (c == '-') {
                        ans.push_back(lnum - rnum);
                    } else {
                        ans.push_back(lnum * rnum);
                    }
                }
            }
        }
    }

    if (ans.size() == 0) {      // 结果集是空，证明该字符串是数字，将数字加入结果集
        ans.push_back(stoi(expression));
    }

    return ans;
}
```

该问题牵涉到括号的**组合**问题，一般使用**递归+回溯**的思想。主要想法：

其一，递归回溯。可以产生所有的组合方式。

其二，每个小组合方式相当于一个子集，不断的将计算结果返回给上一层。

- 举例：`a + (b - (c * d))`会不断的变成`a + (b - (res1 * res2)) `-> `a + (res1 - res2)` -> `res1 + res2`
- 似乎计算结果不需要`for`循环？其实有这种情况，`a + (b - (c * d))`和`a + (b - c) * d))`，这里 `a + res2`，`res2`就可能有多种情况。

