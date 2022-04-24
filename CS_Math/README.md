# 数论



https://blog.csdn.net/qq_44013342/article/details/88023526#t9





## 定理

| 定理     | 解释                                                         |
| -------- | ------------------------------------------------------------ |
| 同余定理 | 给定一个正整数m，如果两个整数a和b满足a-b能够被m整除，即(a-b)/m得到一个整数，那么就称整数a与b对模m同余，记作a≡b(mod m)。对模m同余是整数的一个等价关系。 |
| 尾随零   | 2 和 5 的个数的最小值，就是尾随零的个数                      |
|          |                                                              |
|          |                                                              |


交换两个数字
```c++
// in-place swap
// 异或 任何数与自己异或为0 与0异或为自己
a = a ^ b; 
b = a ^ b; // b = a^b^b = a^0 = a
a = a ^ b; 

// 加和
a = a + b;
b = a - b;
a = a - b;
```


---




## 1523. 在区间范围内统计奇数数目

把尾部奇数+1变成偶数

把头部奇数-1变成偶数

cnt = (end - start) / 2

```c++
int countOdds(int low, int high) {
    if (high & 1) high++;
    if (low & 1) low--;
    return (high - low) / 2;
}
```





---

## 1979. 最大公约数

欧几里得算法，即辗转相除法
$$
gcd(a,b)=gcd(b,a \operatorname{mod} b).
$$


```c++
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int findGCD(vector<int>& nums) {
    int maxn = *max_element(nums.begin(), nums.end());
    int minn = *min_element(nums.begin(), nums.end());

    return gcd(maxn, minn);
}
```

时间复杂度：$O(n + \log M)$，其中 n 为 nums 的长度，M 为 nums 的最大值。遍历数组寻找最大值与最小值的时间复杂度为 $O(n)$，计算最大公约数的时间复杂度为 $O(\log M)$。

空间复杂度：O(1)。





---

## 最小公倍数

```c++
int lcm(int a, int b) {
    int g = gcd(a, b);
    return a * b / g;
}
```





---

## 43. 字符串相乘

该算法是通过两数相乘时，乘数某位与被乘数某位相乘，与产生结果的位置的规律来完成。具体规律如下：

- 乘数 num1 位数为 M，被乘数 num2 位数为 N， `num1 x num2` 结果 res 最大总位数为 `M+N`
- `num1[i] x num2[j]` 的结果为 tmp(位数为两位，"0x","xy"的形式)，其第一位位于 `res[i+j]`，第二位位于 `res[i+j+1]`。



![img](assets/171cad48cd0c14f565f2a0e5aa5ccb130e4562906ee10a84289f12e4460fe164-image.png)

```c++
class Solution {
    public String multiply(String num1, String num2) {
        if (num1.equals("0") || num2.equals("0")) {
            return "0";
        }
        int[] res = new int[num1.length() + num2.length()];
        for (int i = num1.length() - 1; i >= 0; i--) {
            int n1 = num1.charAt(i) - '0';
            for (int j = num2.length() - 1; j >= 0; j--) {
                int n2 = num2.charAt(j) - '0';
                int sum = (res[i + j + 1] + n1 * n2);
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }

        StringBuilder result = new StringBuilder();
        for (int i = 0; i < res.length; i++) {
            if (i == 0 && res[i] == 0) continue;
            result.append(res[i]);
        }
        return result.toString();
    }
}
```





```c++
string multiply(string num1, string num2) {
    //每一位相乘结果在res[i+1] res[i+j+1]这两位里 累加即可
    if(num1 == "0" || num2 == "0"){return "0";}
    int size1 = num1.length(), size2 = num2.length();
    vector<int> memo(size1+size2, 0);
    string res = "";
    for(int i = size1-1; i>=0; i--){
        int n1 = num1[i]-'0';
        for(int j = size2-1; j>=0; j--){
            int n2 = num2[j]-'0';
            int tempSum = memo[i+j+1]+n1*n2;
            memo[i+j+1] = tempSum % 10;
            memo[i+j] += tempSum / 10;
        }
    }
    bool flag = true;
    for(int i = 0; i<memo.size(); i++){
        if(memo[i] != 0 || !flag){
            flag = false;
            res.push_back(memo[i]+'0');
        }
    }
    return res;
}
```











---

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





---

## 48. 旋转图像

用翻转代替旋转

我们还可以另辟蹊径，用翻转操作代替旋转操作。我们还是以题目中的示例二

$$
\begin{bmatrix} 5 & 1 & 9 & 11 \\ 2 & 4 & 8 & 10 \\ 13 & 3 & 6 & 7 \\ 15 & 14 & 12 & 16 \end{bmatrix}
$$


作为例子，先将其通过水平轴翻转得到：

$$
\begin{bmatrix} 5 & 1 & 9 & 11 \\ 2 & 4 & 8 & 10 \\ 13 & 3 & 6 & 7 \\ 15 & 14 & 12 & 16 \end{bmatrix} \xRightarrow[]{水平翻转} \begin{bmatrix} 15 & 14 & 12 & 16 \\ 13 & 3 & 6 & 7 \\ 2 & 4 & 8 & 10 \\ 5 & 1 & 9 & 11 \end{bmatrix}
$$
再根据主对角线翻转得到：
$$
\begin{bmatrix} 15 & 14 & 12 & 16 \\ 13 & 3 & 6 & 7 \\ 2 & 4 & 8 & 10 \\ 5 & 1 & 9 & 11 \end{bmatrix} \xRightarrow[]{主对角线翻转} \begin{bmatrix} 15 & 13 & 2 & 5 \\ 14 & 3 & 4 & 1 \\ 12 & 6 & 8 & 9 \\ 16 & 7 & 10 & 11 \end{bmatrix}
$$
就得到了答案。这是为什么呢？对于水平轴翻转而言，我们只需要枚举矩阵上半部分的元素，和下半部分的元素进行交换，即

$$
\textit{matrix}[\textit{row}][\textit{col}] \xRightarrow[]{水平轴翻转}\textit{matrix}[n - \textit{row} - 1][\textit{col}]
$$
对于主对角线翻转而言，我们只需要枚举对角线左侧的元素，和右侧的元素进行交换，即

$$
\textit{matrix}[\textit{row}][\textit{col}] \xRightarrow[]{主对角线翻转} \textit{matrix}[\textit{col}][\textit{row}]
$$


将它们联立即可得到：

$$
\begin{aligned} \textit{matrix}[\textit{row}][\textit{col}] & \xRightarrow[]{水平轴翻转} \textit{matrix}[n - \textit{row} - 1][\textit{col}] \\ &\xRightarrow[]{主对角线翻转} \textit{matrix}[\textit{col}][n - \textit{row} - 1] \end{aligned}
$$


```c++
void rotate(vector<vector<int>>& matrix) {
    int row = matrix.size();

    for (int i = 0; i < row / 2; ++i) {
        for (int j = 0; j < row; ++j) {
            swap(matrix[i][j], matrix[row - i - 1][j]);
        }
    }

    for (int i = 0; i < row; ++i) {
        for (int j = i + 1; j < row; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}
```



---

## 223. 矩形面积

两个单独的矩阵面积 - 重复的面积，注意要判断重复部分的高，负值表示不重叠。

```c++
int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    int s1 = (ax2 - ax1) * (ay2 - ay1);
    int s2 = (bx2 - bx1) * (by2 - by1);

    int overlapWidth = min(ax2, bx2) - max(ax1, bx1), overlapHeight = min(ay2, by2) - max(ay1, by1);

    int coverArea = max(overlapWidth, 0) * max(overlapHeight, 0);


    return s1 + s2 - coverArea;
}
```



---

## 50. Pow(x, n)

**快速幂**本质是分治，当 n 为负数时，可以计算正数，再取倒数。



如果我们要计算 $x^{64}$，我们可以按照：
$$
x→x^2
 →x^4
 →x^8
 →x^{16}
 →x^{32}
 →x^{64}
$$
的顺序，从 x 开始，每次直接把上一次的结果进行平方，计算 6 次就可以得到 $x^{64}$ 的值，而不需要对 x 乘 63 次 x。



如果我们要计算 $x^{77}$ ，我们可以按照：

$$
x \to x^2 \to x^4 \to x^9 \to x^{19} \to x^{38} \to x^{77}
$$
的顺序，在 $x \to x^2，x^2 \to x^4，x^{19} \to x^{38}$ 这些步骤中，我们直接把上一次的结果进行平方，而在 $x^4 \to x^9，x^9 \to x^{19}，x^{38} \to x^{77}$，这些步骤中，我们把上一次的结果进行平方后，还要额外乘一个 x。

直接从左到右进行推导看上去很困难，因为在每一步中，我们不知道在将上一次的结果平方之后，还需不需要额外乘 x。但如果我们从右往左看，分治的思想就十分明显了：

- 当我们要计算 $x^n$  时，我们可以先递归地计算出 $y = x^{\lfloor n/2 \rfloor}$，其中 $\lfloor a \rfloor$ 表示对 a 进行下取整；

- 根据递归计算的结果，如果 $n$ 为偶数，那么 $x^n = y^2$ ；如果 n 为奇数，那么 $x^n = y^2 \times x$；

- 递归的边界为 $n = 0$，任意数的 0 次方均为 1。

由于每次递归都会使得指数减少一半，因此递归的层数为 $O(\log n)$，算法可以在很快的时间内得到结果。

```c++
double quickMul(double x, long long N) {
    if (N == 0) {
        return 1.0;
    }
    double y = quickMul(x, N / 2);
    return N % 2 == 0 ? y * y : y * y * x;
}

double myPow(double x, int n) {
    long long N = n;
    return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, N);
}
```



时间复杂度：$O(\log n)$，即为递归的层数。

空间复杂度：$O(\log n)$，即为递归的层数。这是由于递归的函数调用会使用栈空间。



由于递归需要使用额外的栈空间，我们试着将递归转写为迭代。在方法一中，我们也提到过，从左到右进行推导是不容易的，因为我们不知道是否需要额外乘 x。但我们不妨找一找规律，看看哪些地方额外乘了 x，并且它们对答案产生了什么影响。





我们还是以 $x^{77}$  作为例子：
$$
x \to x^2 \to x^4 \to^+ x^9 \to^+ x^{19} \to x^{38} \to^+ x^{77}
$$

并且把需要额外乘 x 的步骤打上了 + 标记。可以发现：

$x^{38} \to^+ x^{77}$ 中额外乘的 x 在 $x^{77}$ 中贡献了 $x$；

$x^9 \to^+ x^{19}$  中额外乘的 x 在之后被平方了 2 次，因此在 $x^{77}$ 中贡献了 $x^{2^2} = x^4$ ；

$x^4 \to^+ x^9$ 中额外乘的 x 在之后被平方了 3 次，因此在 $x^{77}$ 中贡献了 $x^{2^3} = x^8$ ；

最初的 x 在之后被平方了 6 次，因此在 $x^{77}$ 中贡献了 $x^{2^6} = x^{64}$ 。



我们把这些贡献相乘，$x \times x^4 \times x^8 \times x^{64}$,  恰好等于 $x^{77}$ 。而这些贡献的指数部分又是什么呢？它们都是 2 的幂次，这是因为每个额外乘的 xx 在之后都会被平方若干次。而这些指数 1，4，8 和 64，恰好就对应了 77 的二进制表示 $(1001101)_2$ 中的每个 11！

因此我们借助整数的二进制拆分，就可以得到迭代计算的方法，一般地，如果整数 nn 的二进制拆分为

$$
n = 2^{i_0} + 2^{i_1} + \cdots + 2^{i_k}
$$

那么

$$
x^n = x^{2^{i_0}} \times x^{2^{i_1}} \times \cdots \times x^{2^{i_k}}
$$
这样以来，我们从 x 开始不断地进行平方，得到 $x^2, x^4, x^8, x^{16}, \cdots$ ，如果 n 的第 k 个（从右往左，从 0 开始计数）二进制位为 1，那么我们就将对应的贡献 $x^{2^k}$ 计入答案。

```c++
double quickMul(double x, long long N) {
    double ans = 1.0;
    // 贡献的初始值为 x
    double x_contribute = x;
    // 在对 N 进行二进制拆分的同时计算答案
    while (N > 0) {
        if (N % 2 == 1) {
            // 如果 N 二进制表示的最低位为 1，那么需要计入贡献
            ans *= x_contribute;
        }
        // 将贡献不断地平方
        x_contribute *= x_contribute;
        // 舍弃 N 二进制表示的最低位，这样我们每次只要判断最低位即可
        N /= 2;
    }
    return ans;
}

double myPow(double x, int n) {
    long long N = n;
    return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
}
```



- 时间复杂度：$O(\log n)$，即为对 n 进行二进制拆分的时间复杂度。
- 空间复杂度：$O(1)$。









## 311. 稀疏矩阵的乘法

暴力

```c++
vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
    vector<vector<int>> res(mat1.size(), vector<int>(mat2[0].size(), 0));

    for (int i = 0; i < mat1.size(); ++i) {
        for (int j = 0; j < mat2[0].size(); ++j) {
            for (int k = 0; k < mat1[0].size(); ++k) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return res;
}
```





三元组

```c++
struct ijv {
    int i;
    int j;
    int val;
};


vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
    vector<vector<int>> res(mat1.size(), vector<int>(mat2[0].size(), 0));

    vector<ijv> m1, m2;


    for (int i = 0; i < mat1.size(); ++i) {
        for (int j = 0; j < mat1[0].size(); ++j) {
            if (mat1[i][j] != 0) {
                m1.push_back({i, j, mat1[i][j]});
            }
        }
    }


    for (int i = 0; i < mat2.size(); ++i) {
        for (int j = 0; j < mat2[0].size(); ++j) {
            if (mat2[i][j] != 0) {
                m2.push_back({i, j, mat2[i][j]});
            }
        }
    }

    for (auto v1 : m1) {
        for (auto v2 : m2) {
            if (v1.j != v2.i) continue;	// a的列 = b的行

            res[v1.i][v2.j] += v1.val * v2.val;
        }
    }

    return res;
}
```







---

## 子串、非空子串、真子串、非空真子串、求数公式

|          子串           |  （无重复）非空子串   |        真子串         |       非空真子串        |
| :---------------------: | :-------------------: | :-------------------: | :---------------------: |
| $\frac {(1+n)*n}{2}+1 $ | $\frac {(1+n)*n}{2} $ | $\frac {(1+n)*n}{2} $ | $\frac {(1+n)*n}{2}-1 $ |

- 串 S = “database" 的非空子串数目（34）

无重复：8*9/2=36

有重复的，减去重复项：对于第一个a来说，第二个、第三个a是重复的，也就是有两个重复项；36 - 2 = 34



- 串 S = "www.88.com"的非空子串数目为：50。

无重复：10*11/2=55

有重复的，减去重复项：对于第一个 w 来说 55 - 2 = 53

对于第一个 8 来说 53 - 1 = 52

对于第一个. 来说 52 - 1 = 51

对于第一个 ww 来说 51 - 1 = 50



- 串 "ababaaabb" 的真子串个数：9*10/2 = 45



## 互质/分解质因数/容斥原理

- 求100以内和100互素（互质）的正整数个数.

$100= 2^2*5^2$
2k: 有50个
5k:有20个
10k:有10个
所以互质数的数有:
100-(50+20-10)
=100-60
=40(个)

- 求1-2999 内和 3000 互素（互质）的个数 800个

$3000 = 2^3*3^1*5^3$

2: 有 1499 个

3: 有 999 个

5: 有 599 个

6: 有 499 个 6=2*3

10: 有 299 个 10=2*5

15: 有 199 个 15=3*5

30: 有 99 个 30=2\*3\*5

所以互质数的数有:
2999-(1499+999+599-499-299-199+99)
=2999 - 3196 + 997
=800(个)



所以互质数的数有:
2999-2999/2-2999/3+2999/6 -2999/5 + 2999/10 + 2999/15 - 2999/30
=2999 - 1499 - 999 + 499 - 599 + 299 + 199 - 99
=          1500 > 501 > 1000 > 401> 700 > 899 > 80



- 求a~b之间与n互素的个数

求出 1~b 之间与n互素的个数减去 1~a-1之间与n互素的的个数即为所求。



```c++
ll fac[N], m;

//对n分解质因数，质因数个数为m
void div(ll x) {
	m = 0;
	int q = sqrt(x);
	for (int i = 2; i <= q; i++)
		if (x % i == 0) {
			fac[++m] = i;
			while (x % i == 0) x /= i;
		}

	if (x > 1) fac[++m] = x;
}

//应用容斥原理求出1~b之间含有n的质因子的数的个数，也即与n不互素的数的个数
ll co_prime(ll n) {
	ll ans = 0;
	for (ll i = 0; i < 1ll << m; i++)//i == 0的时候，t = 1， ans = n，也即是b可以含有任何质因子
	{
		int k = 0;
		ll t = 1;
		for (int j = 0; j < m; j++)
			if (i & 1ll << j) t *= fac[j + 1], k++;
		if (k & 1) ans -= n / t;
		else ans += n / t;
	}

	return ans;
}
```



---



---

# CS

## 1. 字典序

**字典序（dictionary order）**，又称 **字母序（alphabetical order）**

原意是表示英文单词在字典中的先后顺序，在计算机领域中扩展成两个任意**字符串**的**大小**关系。



英文中的 **字母表（Alphabet）** 按照如下的顺序排列：

ABCDEFG HIJKLMN OPQRST UVWXYZ

abcdefg hijklmn opqrst uvwxyz



大小关系取决于两个字符串**从左到右第一个不同字符的 ASCII 值的大小**关系



都提供了比较两个字符串大小的方法，比较的实际上就是两个字符串的字典序。例如在 C++  中：

```c++
cout << ("ah1x" < "ahb") << endl; //true
```



**字典序算法**





---

## 2. int类型在内存中的存储方式

int类型表示带有符号的整型，而unsigned int类型为无符号的整型。

|   类型名称   | 占字节数 |       取值范围        |
| :----------: | :------: | :-------------------: |
|     int      |    4B    | $-2^{31}\sim2^{31}-1$ |
| unsigned int |    4B    |   $0 \sim 2^{32}-1$   |



**1、占用的比特位数量**

在32位操作系统下，两者都是占用4个字节，每个字节有8个比特位，因此有32个0-1的二进制位数。两者的不同在于，int类型有正负号（±）的存在，需要比unsigned int类型多消耗一个位数。



**2、符号的表示方法**

在所有被int类型占用的比特位中，**左起第一个位**（即**最高位**）就是**符号位**。int类型的符号位上，**0表示正数**，**1表示负数**。在32位操作系统下，其余**后面31位是数值位**。



**3、数字0的表示方法**

按照上面提到的符号，我们有了两种0的表示方法，即 “+0” 和 “-0”。

实际上，在32位系统下int类型中，我们计算机已经强行规定了这种情况，数字0采用 “+0” 的表示方法，即0000000000000000 00000000；而 “**-0**” 这个特殊的数字被定义为了$-2^{31}$。

因此我们看到32位系统下int类型的取值范围中，负数部分比正数部分多了一个数字，正数的最大取值是 $2^{31}-1$，而负数的最小取值是 $-2^{31}$。**正数部分之所以要减去 1，是因为被数字 0 占用了 “+0”**，而负数部分不需要用来表示 0，因此原本的 “-0” 就用来表示 $-2^{31}$ 这个数字。



按照上面的理解方式，int类型的数字“-1”，在内存中32个比特位上应该是这样子的：10000000 00000000 00000001，左边第一个1表示负号，后面31位表示数值部分“1”。实际情况并不是这样。这里就需要引入“补码”这个概念了。



---

### 原码（true form）

原码，是计算机中一种对数字的二进制定点表示方法。原码表示法在数值前面前面有一位符号位（即最高位为符号位），正数该位为0，负数该位为1（0有两种表示：+0和-0），其余位表示数值的大小。

int类型数值“-1”的32位二进制就是原码，即10000000 00000000 00000001。与之对应的，正数“+1”就是00000000 00000000 00000001。

那么**为何不用原码在内存中表示数值呢**？举个例子（以8位二进制表示）

|     十进制     |   原码    |
| :------------: | :-------: |
|       1        | 0000 0001 |
|       -1       | 1000 0001 |
|  结果（原码）  | 1000 0010 |
| 结果（十进制） |    -2     |

上述结果换算成十进制为-2，这显然出错了。这是由于计算机在计算时以加法进行计算的算法更简便，**减法先转换为负数**，**再进行加法运算**。因此，**原码的符号位不能直接参与运算**。

总结：原码是有符号数的**最简单的编码方式**，便于输入输出，但作为代码加减运算时较为复杂，故计算机一般不采用这种编码方式存储符号数。



---

### 反码（ones' complement）

首先我们来了解下反码表示法的规定：“**正数的反码与其原码相同**；**负数的反码是对其原码逐位取反**，但**符号位除外**。”

①  对于正数和“+0”而言，其原码本身就是反码，例如 8位二进制“+1”，其原码与反码都是00000001；

②  对于负数和“-0”而言，符号位与原码中一样，保持不变，其余位数逐位取反，1换成0,0换成1，例如 “-1”，其8位二进制原码是10000001，其反码是1111 1110；

那么是否可以正常运算了？举个三个例子：

例一：1+2=3（以8位二进制表示）

|     十进制     |   原码    |   反码    |
| :------------: | :-------: | :-------: |
|       1        | 0000 0001 | 0000 0001 |
|       2        | 0000 0010 | 0000 0010 |
|  结果（反码）  |           | 0000 0011 |
|  结果（原码）  |           | 0000 0011 |
| 结果（十进制） |           |     3     |



例二：1+（-2）=-1

|     十进制     |   原码    |   反码    |
| :------------: | :-------: | :-------: |
|       1        | 0000 0001 | 0000 0001 |
|       -2       | 1000 0010 | 1111 1101 |
|  结果（反码）  |           | 1111 1110 |
|  结果（原码）  |           | 1000 0001 |
| 结果（十进制） |           |    -1     |



例三：1+（-1）=0

|     十进制     |   原码    |   反码    |
| :------------: | :-------: | :-------: |
|       1        | 0000 0001 | 0000 0001 |
|       -1       | 1000 0001 | 1111 1110 |
|  结果（反码）  |           | 1111 1111 |
|  结果（原码）  |           | 1000 0000 |
| 结果（十进制） |           |    -0     |

计算结果为-0 (表示为 $-2^{7}$)，问题来了，由于-0的存在，使得二进制与十进制的互换不再是一一对应的关系。

总结：由于-0这个问题的存在，会使得计算机需要增加额外的物理硬件配合运算，所以在计算机发展的早期就已经抛弃了使用反码储存数据。



---

### 补码

补码正是基于反码的**“-0”**问题诞生的，可以解决这个问题。

补码的计算方法是：**正数和+0**的补码是其**原码**，**负数**则先计算其反码，然后**反码加上1**，得到补码。

补码换算为原码的过程中，如果补码是**正数或者+0**的补码，则其原码就是**补码本身**；如果补码是负数或者-0的补码，则其原码的计算方法是，先将补码**减掉1**，得到反码，再将**反码取反**，得到原码。



**例一：1+（-1）=0**

|     十进制     |   原码    |   反码    |   补码    |
| :------------: | :-------: | :-------: | :-------: |
|       1        | 0000 0001 | 0000 0001 | 0000 0001 |
|       -1       | 1000 0001 | 1111 1110 | 1111 1111 |
|  结果（补码）  |           |           | 0000 0000 |
|  结果（反码）  |           |           |           |
|  结果（原码）  |           |           | 0000 0000 |
| 结果（十进制） |           |           |    +0     |

计算结果正确，+0即是数字0的唯一表示。



**例二：1+2=3**

|     十进制     |   原码    |   反码    |   补码    |
| :------------: | :-------: | :-------: | :-------: |
|       1        | 0000 0001 | 0000 0001 | 0000 0001 |
|       2        | 0000 0010 | 0000 0010 | 0000 0010 |
|  结果（补码）  |           |           | 0000 0011 |
|  结果（反码）  |           |           |           |
|  结果（原码）  |           |           | 0000 0011 |
| 结果（十进制） |           |           |    +3     |



**例三：1+（-2）=-1**

|     十进制     |   原码    |   反码    |   补码    |
| :------------: | :-------: | :-------: | :-------: |
|       1        | 0000 0001 | 0000 0001 | 0000 0001 |
|       -2       | 1000 0010 | 1111 1101 | 1111 1110 |
|  结果（补码）  |           |           | 1111 1111 |
|  结果（反码）  |           |           | 1111 1110 |
|  结果（原码）  |           |           | 1000 0001 |
| 结果（十进制） |           |           |    -1     |







**例四：（-1）+（-127）=-128**

|     十进制     |   原码    |   反码    |   补码    |
| :------------: | :-------: | :-------: | :-------: |
|       -1       | 1000 0001 | 1111 1110 | 1111 1111 |
|      -127      | 1111 1111 | 1000 0000 | 1000 0001 |
|  结果（补码）  |           |           | 1000 0000 |
|  结果（反码）  |           |           |           |
|  结果（原码）  |           |           |           |
| 结果（十进制） |           |           |   -128    |



我们知道8位二进制的符号数的取值范围是(-2^7)～(２^7-1),即-128～127。

由于**补码1000 0000**具有特殊性，计算机在编写底层算法时，将其规定为该取值范围中的最小数-128，其值与（-1）+(-127)的计算结果正好符合。

补充一点，**8位二进制补码1000 0000没有对应的反码和原码，其他位数的二进制补码与此类似**。



即**int类型在内存中，以补码的形式存储**。

而且我们还知道了为何int类型的取值范围中负数的最小值的绝对值比正数的最大值大1的原因，即-2^31的补码是10000000 00000000 00000000 00000000，原本-0的位置被-2^31取代了。





----

## 3. 进制

进制即进位计数制，利用固定的数学符号和统一的规则的带进位的计树方法。

任何一种进位计数制都有一个基数，基数为 $X$ 的进位计数制称为 $X$ 进制，表示每一个数位上的数运算时都是逢 X 进一。



对于 X 进制的数，具体的数值由其中的每个数码和数码所在的数位决定。整数部分从右往左的第 m 个数位表示的权重是 $X^m$，其中 m 最小为0；小数部分从左往右的第 n 个数位表示的权重是 $X^{-n}$，其中 n 最小为 1。



十进制的 123.45 可以写成
$$
123.45=1\times10^2 + 2 \times 10^1 + 3 \times 10^0 + 4 \times 10^{-1} + 5 \times 10 ^{-2}
$$
 八进制的 720.5 可以写成
$$
720.5 = 7 \times 8^2 + 2 \times 8^1 + 0 \times 8^0 + 5 \times 8^{-1}
$$


日常生活中，最常用的进制是十进制。十进制包括十个数码：0,1,2,3,4,5,6,7,8,9

计算机采用的进制是二进制。二进制包括两个数码：0,10,1。

八进制和十六进制也是常见的进制。

八进制包含八个数码：0,1,2,3,4,5,6,7

十六进制包含十六个数码，除了 0 到 9 以外，还有 $\text{A},\text{B},\text{C},\text{D},\text{E},\text{F}$，分别对应十进制下的 10,11,12,13,14,1510,11,12,13,14,1



---

### 进制间的转换

**非十转十**

将每个数位的加权和即可。
$$
720.5 = 7 \times 8^2 + 2 \times 8^1 + 0 \times 8^0 + 5 \times 8^{-1}=464.625
$$


**十转非十**

需要对整数部分和小数部分分别转换。



**整数部分**

除以 $X$ 直到变成0，并记录每次的余数，反向遍历每次的余数即可得到 X 进制表示。

例如十进制 50 转二进制
$$
50 \div 2 = 25 余0\\
25 \div 2 = 12 余1\\
12 \div 2 = 6 余0\\
6 \div 3 = 3 余0\\
3 \div 2 = 1 余1\\
1 \div 2 = 0 余1
$$
反向遍历余数， 1 1 0 0 1 0，因此十进制数的 50 转成 二进制数是 $110010_{(2)}$

**小数部分**

乘以 $X$ 直到变成 0，并记录每次的整数部分，正向遍历每次的余数即可得到 X 进制表示

例如十进制 0.6875 转二进制
$$
0.6875 \times 2 = 1.375 整1\\
0.375 \times 2 = 0.75 整0\\
0.75 \times 2 = 1.5 整1\\
0.5 \times 2 = 1 整1\\
0\times 2 = 0
$$
正向遍历余数， 1 0 1 1，因此十进制数的 0.6875 转成 二进制数是 $0.1011_{(2)}$



需要注意的是，在一种进制下的有限小数，转成另一种进制之后可能变成无限循环小数。例如，十进制数 0.2 转成二进制数是 $0.\dot{0}01\dot{1}_{(2)}$。







---

### 504. 七进制数

```c++

```



---

## 4. 位运算

| 操作         | 代码                                                   |      |
| ------------ | ------------------------------------------------------ | ---- |
| 与           | 0 & 0 = 0<br>0 & 1= 0<br/>1 & 0 = 0<br/>1 & 1 = 1      |      |
| 或           | 0 \| 0 = 0<br>0 \| 1 = 1<br/>1 \| 0 = 1<br/>1 \| 1 = 1 |      |
| 异或         | 0 ^ 0 = 0<br>0 ^ 1 = 1<br/>1 ^ 0 = 1<br/>1 ^ 1 = 0     |      |
| 取反（一元） | ~0 = 1<br/>~1 = 0                                      |      |
| 左移         |                                                        |      |
| 右移         |                                                        |      |

参与运算的数字都采用有符号的 **8 位二进制**表示。

46 的二进制表示是 00101110，51 的二进制表示是 00110011。考虑以下位运算的结果。

- $46~\&~51$ 的结果是 34，对应的二进制表示是 00100010。
- $46~|~51$ 的结果是 63，对应的二进制表示是 00111111。
- $46 \oplus 51$ 的结果是 29，对应的二进制表示是 00011101。
- $\sim 46$ 的结果是 -47，对应的二进制表示是 11010001。
- $\sim 51$ 的结果是 -52，对应的二进制表示是 11001100。



左移 << 。将全部二进制位向左移动若干位，高位丢弃，低位补 0。

右移 << 。将全部二进制位向右移动若干位，低位丢弃，高位判断

- 算术（带符号）右移，高位补最高位
- 逻辑（不带符号）右移，高位补0

>  **对于 0 和正数，算术右移和逻辑右移的结果是相同的。**因为其最高位就是0 
>
> 0和正数的补码是其本身！！！





29 的**8 位二进制**为 00011101。29 左移 2 位的结果是 01110100，十进制为 116；29 左移 3 位的结果是 11101000，-24

50 的**8 位二进制**表示是 00110010。50 右移 1 位的结果是  25，对应的二进制表示是 00011001；50 右移 2 位的结果是 12，对应的二进制表示是 00001100。

−50 的二进制表示是 11001110（原码：10110010，反码：11001101，补码：11001110）。-50 算术右移 2 位的结果是 -13，对应的二进制表示是 11110011（补码：11110011，反码：11110010，原码：10001101）；-50 逻辑右移 2 位的结果是 51，对应的二进制表示是 （补码：00110011，反码：00110011，原码：00110011）。



对于 C/C++ 而言，数据类型包含有符号类型和无符号类型，其中有符号类型使用关键字 signed 声明，无符号类型使用关键字 unsigned 声明，两个关键字都不使用时，默认是有符号类型。对于**有符号**类型，右移运算为**算术右移**；对于**无符号**类型，右移运算为**逻辑右移**。





---

### 移位运算与乘除法的关系

使用**移位运算实现乘除法**的**效率显著高于直接乘除法的效率**。



29 左移 2 位的结果 116；29 左移 3 位的结果是 -24

50 右移 1 位的结果是  25；50 右移 2 位的结果是 12。

−-50 算术右移 2 位的结果是 -13；-50 逻辑右移 2 位的结果是 51。



**左移**运算对应**乘法**运算。将一个数左移 *k* 位，等价于将这个数乘以 $2^k$。当乘数不是 2 的整数次幂时，可以将乘数拆成若干项 2 的整数次幂之和，例如，$a \times 6$ 等价于 $(a<<2)+(a<<1)$。需要注意**溢出**



**算术右移**运算对应**除法**运算。将一个数右移 k 位，相当于将这个数除以 $2^k$。例如，50 右移 2 位的结果是 12，等价于 50 / 4，结果**向下取整**。

- 对于 0 和正数，将一个数（算术）右移 k 位，和将这个数除以 $2^k$ 等价。
- 但是对于负数，上述说法就不成立了











---

## 146. LRU（最近最少使用）

缓存淘汰策略

计算机的缓存容量有限，如果缓存满了就要删除一些内容，给新内容腾位置。

LRU，Least Recently Used，认为最近使用过的数据都是有用的，很久都没用过的数据应该是无用的，内存满了就优先删除很久没用过的数据。



首先接受一个 capacity 参数作为缓存的最大容量，实现两个 API，一个是 `put(key, val)` 方法存入键值对，另一个是 `get(key)` 方法获取 `key` 对应的 `val`，如果 `key` 不存在则返回 -1。



```c++
// 缓存容量为 2
LRUCache cache = new LRUCache(2);

// cache 理解成一个队列
// 假设左边是队头， 右边是队尾
// 最近使用的排在队头，久为使用的排在队尾
// 圆括号表示键值对 (key, val)

cache.put(1, 1);
// cache = [(1, 1)]

cache.put(2, 2);
// cache = [(2, 2), (1, 1)]
// 最近使用了键 2，放队头

cache.get(1);	// 返回 1
// cache = [(1, 1), (2, 2)]
// 解释：最近访问了键 1，放队头
// 返回键 1 对应的值 1

cache.put(3, 3);
// cache = [(3, 3), (1, 1)]
// 容量满了，删除内容空出位置
// 优先删除久未使用的数据，即队尾的数据
// 然后把新的数据插入队头

cache.get(2);	// 返回 -1 没找大
 // cache = [(3, 3), (1, 1)]   

cache.put(1, 4);
// cache = [(1, 4), (3, 3)]  

```



要让 `put` 和 `get` 方法的时间复杂度为 O(1)，我们可以总结出 `cache` 这个数据结构必要的条件：

1、显然 `cache` 中的元素必须有时序，以区分最近使用的和久未使用的数据，当容量满了之后要删除最久未使用的那个元素腾位置；

2、我们要在 `cache` 中快速找某个 `key` 是否已存在并得到对应的 `val`；

3、每次访问 `cache` 中的某个 `key`，需要将这个元素变为最近使用的，也就是说 `cache` 要支持在任意位置快速插入和删除元素。





LRU 缓存算法的核心数据结构就是**哈希链表**，**双向链表**和**哈希表**的结合体。这个数据结构长这样：

![img](assets/4.jpg)

1、如果我们每次默认从链表尾部添加元素，那么显然越靠尾部的元素就是最近使用的，越靠头部的元素就是最久未使用的。

2、对于某一个 `key`，我们可以通过哈希表快速定位到链表中的节点，从而取得对应 `val`。

3、链表显然是支持在任意位置快速插入和删除的，改改指针就行。只不过传统的链表无法按照索引快速访问某一个位置的元素，而这里借助哈希表，可以通过 `key` 快速映射到任意一个链表节点，然后进行插入和删除。



为什么必须要用双向链表?

因为我们需要删除操作。删除一个节点不光要得到该节点本身的指针，也需要操作其前驱节点的指针，而双向链表才能支持直接查找前驱，保证操作的时间复杂度 O(1)。



```c++
struct DLinkedNode{
    int key, value;
    DLinkedNode* next;
    DLinkedNode* prev;
    DLinkedNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
}
```

首先使用哈希表定位，找出缓存项在双向链表中的位置，随后将其移动到双向链表的头部，即可在 $O(1)$ 的时间内完成 `get` 或者 `put` 操作。具体方法如下：

- 对于 `get` 操作，首先判断 `key` 是否存在：

  - 如果 `key` 不存在，则返回 `-1`；
  - 如果 `key` 存在，则 `key` 对应的节点是最近被使用的节点。通过哈希表定位到该节点在双向链表中的位置，并将其移动到双向链表的头部，最后返回该节点的值

- 对于 `put` 操作，首先判断 `key` 是否存在：

  - 如果 `key` 不存在，使用 `key` 和 `value` 创建一个新的节点，在双向链表头部添加该节点；并将 `key` 和该节点添加到哈希表中。然后判断双向链表的节点数是否超出容量，如果超出容量，则删除双向链表的尾部节点，并删除哈希表中对应的项；
  - 如果 `key` 存在，则与 `get` 操作类似，先通过哈希表定位，再将对应的节点的值更新为 `value`，并将该节点移到双向链表的头部。

  

在双向链表的实现中，使用一个伪头部（dummy head）和伪尾部（dummy tail）标记界限，这样在添加节点和删除节点的时候就不需要检查相邻的节点是否存在。





```c++
class LRUCache {
private:
	unordered_map<int, DLinkedNode*> _cache;
    DLinkedNode* _head;
    DLinkedNode* _tail;
    int _size;
    int _capacity;
    
public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        _head = new DLinkedNode();
        _tail = new DLinkedNode();
        _head->next = _tail;
        _tail->prev = _head;
    }
    
    void put(int key, int value) {
        if (!_cache.count(key)) { // 如果 key 不存在，添加一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            _cache[key] = node;
            addToHead(node);
            ++_size;
            
            if (_size > _capacity) {
                // 删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                _cache.erase(removed->key);
                // 防止内存泄露
                deletd removed;
                --_size;
            }
        } else {			// key 存在，修改value，并移至头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }        
    }
    
    int get(int key) {
        if (!_cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void moveToHead(DLinkedNode* node) {
    	removeNode(node);
        addToHead(node);
    }
    
    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
	void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    DLinkedNode* removeTail() {
        DLinkedNode node = tail->prev;
        removeNode(node);
        return node;
    }
    
    
}
```









---

## 460. LFU

LFU 算法是淘汰**访问频次最低**的数据，如果访问频次最低的数据有多条，需要**淘汰最旧**的数据。

`get(key)` 方法会去缓存中查询键 `key`，如果 `key` 存在，则返回 `key` 对应的 `val`，否则返回 -1。

`put(key, value)` 方法插入或修改缓存。如果 `key` 已存在，则将它对应的值改为 `val`；如果 `key` 不存在，则插入键值对 `(key, val)`。

当缓存达到容量 `capacity` 时，则应该在插入新的键值对之前，删除使用频次（后文用 `freq` 表示）最低的键值对。如果 `freq` 最低的键值对有多个，则删除其中最旧的那个。

```c++
// 构建一个容量为 2 的 LFU 缓存
LFUCache cache = new LFUCache(2);

// 插入两对 (key, val),对应的 freq 变为1
cache.put(1, 10);
cache.put(2, 20);

// 查询 key 为 1 对应的 val
// 返回 10，同时键 1 对应的 freq 变为 2
cache.get(1);

// 容量已满，淘汰 freq 最小的键 2
// 插入键值对 (3, 30)，对应的 freq 为 1
cache.put(3, 30);

// 键 2 已经被淘汰删除，返回 -1
cache.get(2);
```



- 一个 map 存储 key 到 val 的映射，可以快速计算 `get(key)`。
- 一个 map 存储 key 到 freq 的映射

```c++
unordered_map<int, int> key2Val;
unordered_map<int, int> key2Freq;
```





如果在容量满了的时候进行插入，则需要将 `freq` 最小的 `key` 删除，如果最小的 `freq` 对应多个 `key`，则删除其中最旧的那一个。

1.首先，需要 `freq` 到 `key` 的映射，用来找到 `freq` 最小的 `key`。

2.将 `freq` 最小的 `key` 删除，那你就得快速得到当前所有 `key` 最小的 `freq`是多少。用一个变量 `minFreq` 来记录当前最小的 `freq`。

3.多个 `key` 可能拥有相同的 `freq`，所以 `freq` 对 `key` 是一对多的关系，一个 `freq` 对应一个 `key` 的列表。

4.`freq` 对应的 `key` 的列表是存在时序的，便于快速查找并删除最旧的 `key`。

5.希望能够快速删除 `key` 列表中的任何一个 `key` ，因为如果频次为 `freq` 的某个 `key` 被访问，那么它的频次就会 +1，就应该从 `freq` 对应的 `key` 列表中删除，加到 `freq+1` 对应的 `key` 的列表中。 





```c++
// 缓存的节点信息
struct Node {
    int key, val, freq;
    Node(int _key,int _val,int _freq): key(_key), val(_val), freq(_freq){}
};
class LFUCache {
    int minfreq, capacity;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int _capacity) {
        minfreq = 0;
        capacity = _capacity;
        key_table.clear();
        freq_table.clear();
    }
    
    int get(int key) {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        if (it == key_table.end()) return -1;
        list<Node>::iterator node = it -> second;
        int val = node -> val, freq = node -> freq;
        freq_table[freq].erase(node);
        // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (minfreq == freq) minfreq += 1;
        }
        // 插入到 freq + 1 中
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 缓存已满，需要进行删除操作
            if (key_table.size() == capacity) {
                // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
                auto it2 = freq_table[minfreq].back();
                key_table.erase(it2.key);
                freq_table[minfreq].pop_back();
                if (freq_table[minfreq].size() == 0) {
                    freq_table.erase(minfreq);
                }
            } 
            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        } else {
            // 与 get 操作基本一致，除了需要更新缓存的值
            list<Node>::iterator node = it -> second;
            int freq = node -> freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (minfreq == freq) minfreq += 1;
            }
            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};
```





充分感受C++面向对象（OOP）和结构化设计的思想

相比于LRU缓存经典问题手撸（完全自行设计）双向链表那一道题目，这个题目我们觉得更应该将关注点转向面向对象中模板抽象和数据封装、类与对象设计的思想，这道题目我们采用的思路是利用C++set容器的特性，并且自定义一个Node结构体来表征缓存的各种信息，而不需为了设计单纯的内置类型（如int）的单一关系容器而苦恼，事实上，我们可以发现，在自定义Node结构体并利用重载、模板、封装的特性，我们的set容器和映射hash容器很好的实现了键值对的映射、对于要删除的缓存节点的自排序、以及对于单一映射实现了一对多的映射关系，这便是结构化设计和封装类与对象设计的优雅之处。我们也可以发现，在之前所做的一些问题中，比如图论中抽象信息建图、最小生成树优先队列的设计、Dijkstra算法优先队列节点的设计，我们都是通过将多种节点信息抽象封装成一个结构体来简化，这是非常优雅，同时也是非常精彩的设计思路。

另外，就本题C++解法中还需要提及的一些注意点。首先，本题还融入了一些精彩的C++设计特性，也就是迭代器设计，我们知道，C++在类与对象的抽象封装中引入了迭代器的概念，也可以理解成为一种广义指针，来模板化对各种容器的引用与访问，因此，本题利用迭代器的设计，巧妙地设计了代码，更加清晰。其次，本题还有一个重要的思路设计：时间戳的概念。我们知道，本题设计的一个难点就在于如果存在**最小频率相等的缓存，应该删除最近最久未使用的键**，而维护一个全局时间戳来记录每个键值对使用更新时对应的时间戳，我们能够极好地表示一个缓存使用的时长，于是在Node结构化我们重载<运算符的时候便方便地在结构体中抽象了本题中最难的设计所在，这是极为巧妙的！

有了基于上述的思路，我们设计代码的同时时刻记得维护你自己的数据结构和全局变量，那么整个代码时极为简洁和清晰的。



![image-20220408111726496](assets/image-20220408111726496.png)



![image-20220408111740813](assets/image-20220408111740813.png)



![image-20220408111804395](assets/image-20220408111804395.png)

![image-20220408111815280](assets/image-20220408111815280.png)

![image-20220408111828175](assets/image-20220408111828175.png)



![image-20220408111842044](assets/image-20220408111842044.png)



![image-20220408111903147](assets/image-20220408111903147.png)







---

## 位图




## 868. 二进制间距




---

## 大数相加



---

## 大数相乘



---

## 浮点数相乘













---

## 表达式计算

对于「任何表达式」而言，我们都使用两个栈 `nums` 和 `ops`：

- `nums` ： 存放所有的数字
- `ops` ：存放所有的数字以外的操作



然后从前往后做，对遍历到的字符做分情况讨论：

- 空格 : 跳过
- `(` : 直接加入 ops 中，等待与之匹配的 )
- `)` : 使用现有的 nums 和 ops 进行计算，直到遇到左边最近的一个左括号为止，计算结果放到 nums
- 数字 : 从当前位置开始继续往后取，将整一个连续数字整体取出，加入 nums

+ `+ - / ^ %` : 需要将操作放入 ops 中。**在放入之前先把栈内可以算的都算掉**（只有「栈内运算符」比「当前运算符」优先级高/同等，才进行运算），使用现有的 nums 和 ops 进行计算，直到没有操作或者遇到左括号，计算结果放到 nums





因为我们是从前往后做的，假设我们当前已经扫描到 2 + 1 了（此时栈内的操作为 + ）。

- 如果后面出现的 + 2 或者 - 1 的话，满足**「栈内运算符」比「当前运算符」优先级高/同等**，可以将 2 + 1 算掉，把结果放到 nums 中；
- 如果后面出现的是 * 2 或者 / 1 的话，不满足「栈内运算符」比「当前运算符」优先级高/同等，这时候不能计算 2 + 1。



一些细节：

- 由于第一个数可能是负数，为了减少边界判断。一个小技巧是先往 nums 添加一个 0
- 为防止 () 内出现的首个字符为运算符，将所有的空格去掉，并将 `(-` 替换为 `(0-`，`(+` 替换为 `(0+`（当然也可以不进行这样的预处理，将这个处理逻辑放到循环里去做）
- 从理论上分析，nums 最好存放的是 long，而不是 int。因为可能存在 大数 + 大数 + 大数 + … - 大数 - 大数 的表达式导致中间结果溢出，最终答案不溢出的情况





```c++
unordered_map<char, int> ump = {
    {'-', 1},
    {'+', 1},
    {'*', 2},
    {'/', 2},
    {'%', 2},
    {'^', 3},
};

stack<long long> nums;
stack<char> ops;

void eval() {
    long long b = nums.top(); nums.pop();
    long long a = nums.top(); nums.pop();
    char op = ops.top(); ops.pop();

    long long res = 0;
    switch (op) {
        case '+':   res = a + b; break;
        case '-':   res = a - b; break;
        case '*':   res = a * b; break;
        case '/':   res = a / b; break;
        case '%':   res = a % b; break;
        case '^':   res = pow(a, b); break;
    }

    nums.push(res);
}

int calculate(string s) {       
    nums.push(0);
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') continue;
        if (isdigit(s[i])) {    // 数字
            int res = 0;
            while (i < s.size() && isdigit(s[i])) {
                res = res * 10 + (s[i++] - '0');
            }
            nums.push(res);
            i--;
        } else {    // 运算符
            if (s[i] == '(') {
                ops.push(s[i]);
            } else if (s[i] == ')') {   // 计算该括号内内容
                while (ops.top() != '(') { // 找到前一个 ( 并算其中的值
                    eval();
                }
                ops.pop();
            } else {
                // 有一个新操作要入栈时，先把栈内可以算的都算了 
                // 但注意的是 只有满足「栈内运算符」比「当前运算符」优先级高/同等，才进行运算
                while (!ops.empty() && ops.top() != '(' && ump[ops.top()] >= ump[s[i]]) {
                    eval();
                }
                ops.push(s[i]);
            }
        }
    }

    while(!ops.empty() && ops.top() != '(') {
        eval();
    }

    return nums.top();
}
```





### 16.26. 计算器

**考点是栈**

用栈来保存结果， 最后把所有结果累加即可
“+ -” 都是存在栈里
”* /“ 是取栈顶数字取出来 *或/ 新的数字
第一次符号记录为+， 最后每次有符号或者最后一个字符就需要进行计算，计算取决于上一个计算的符号

1、由于运算符有优先级，所以设计一个哈希表来存储 `'+'，'-'，'*'，'/'` 优先级，我们将`'+'` 和 `'-'` 设为1级优先级，将 `'*'` 和 `'/'` 设为2级优先级。
2、考虑到表达式s的第一个数字可能为负数，因此我们给s开头添加一个字符0。



```c++

```







### 224. 基本计算器

```c++
unordered_map<char, int> ump = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
};

stack<int> nums;
stack<char> ops;

void eval() {
    int b = nums.top(); nums.pop();
    int a = nums.top(); nums.pop();
    char op = ops.top(); ops.pop();

    int res;
    switch (op) {
        case '+' : res = a + b; break;
        case '-' : res = a - b; break;
        case '*' : res = a * b; break;
        case '/' : res = a / b; break;
    }

    nums.push(res);
}

int calculate(string s) {
    nums.push(0);
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') continue;

        if (isdigit(s[i])) { //num
            int res = 0;
            while (i < s.size() && isdigit(s[i])) {
                res = res * 10 + (s[i++] - '0');
            }
            nums.push(res);
            i--;
        } else {    //ops
            if (s[i] == '(') {
                ops.push(s[i]);
                if (i+1 < s.size() && s[i+1] == '-') nums.push(0); 
            } else if (s[i] == ')') {
                while (ops.top() != '(') {
                    eval();
                }
                ops.pop();  // 弹出 (
            } else {
                while (!ops.empty() && ops.top() != '(' && ump[s[i]] <= ump[ops.top()]) {
                    eval();
                }
                ops.push(s[i]);
            }
        }
    }

    while (!ops.empty() && ops.top() != '(') {
        eval();
    }

    return nums.top();
}
```





# Design

## 6062. 设计一个 ATM 机器

```c++
using ll = long long;
class ATM {
public:
    int money[5] = {20, 50, 100, 200, 500};
    
    ATM() : vec(5) {
        
    }
    
    void deposit(vector<int> banknotesCount) {
        for (int i = 0; i < 5; ++i) 
            vec[i] += banknotesCount[i];
    }
    
    vector<int> withdraw(int amount) {
        vector<int> res(5); 
        
        for (int i = 4; i >= 0; --i) {
            ll nCnt = amount / money[i];
            ll realCnt = min(nCnt, vec[i]);
            
            res[i] = realCnt;
            amount = amount - realCnt * money[i];
            
        }
        
        if (amount != 0)  return {-1};

        for (int i = 0; i < 5; ++i)
            vec[i] -= res[i]; 
     
        
        return res;
    }
    
private:
    vector<ll> vec;
};
```

