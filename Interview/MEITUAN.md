# 美团

https://www.nowcoder.com/discuss/868085?type=post&order=create&pos=&page=0&ncTraceId=&channel=-1&source_id=search_post_nctrack&gio_id=4FEE4FDA855579AB1F800A97289B01DC-1647677146425



## 3.19 笔试

### 第一题 折扣价还是用满减

点外卖用折扣价还是用满减，直接模拟就行。唯一的坑是满减只能用最接近的券，比如商品总原价100，我有满100减10的券和满50-30的券，则只能用前者。

找到最大的满足折扣的券，然后判断即可。

```c++
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e5 + 10;

int a[N], b[N], c[N], d[N], n, m;

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> d[i];
  }
  int sum = 0, cur = 0;
  for (int i = 1; i <= n; i++) {
    sum += a[i], cur += b[i];
    int p = 0;
    for (int j = 1; j <= m; j++) {
      if (sum >= c[j]) {
        p = j;
      }
    }
    int ans = sum - d[p];
    if (ans == cur) {
      putchar('B');
    } else if (ans < cur) {
      putchar('M');
    } else {
      putchar('Z');
    }
  }
  return 0;
}
```









### 第二题 加解密

加解密，直接模拟就行。

容易发现从中间向两边延伸即可。

```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

char str[N], ans[N];

int n, m;

void solve1() {
    int p = 0, l, r;
    if (n & 1) {
        ans[++p] = str[n / 2 + 1];
        l = n / 2, r = n / 2 + 2;
    } else {
        l = n / 2, r = n / 2 + 1;
    }
    while (l) {
        ans[++p] = str[l--];
        ans[++p] = str[r++];
    }
}

void solve2() {
    int p = 1, l, r;
    if (n & 1) {
        ans[n / 2 + 1] = str[p++];
        l = n / 2, r = n / 2 + 2;
    } else {
        l = n / 2, r = n / 2 + 1;
    }
    while (l) {
        ans[l--] = str[p++];
        ans[r++] = str[p++];
    }
}

int main() {
    cin >> n >> m >> str + 1;
    if (m == 1) {
        solve1();
    } else {
        solve2();
    }
    cout << ans + 1 << endl;
    return 0;
}


```





### 第三题 （离散化、差分前缀和）

区间覆盖，双重循环，判断任意两个区间有无交集即可。注意，一台机器上本身的区间之间可能有重合，可以先进行区间合并，也可以直接用set记录。

```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int l1[N], r1[N], l2[N], r2[N], a[N], b[N], len[N], sum1[N], sum2[N], T, n, m, cnt, tot;

int main() {
    cin >> T >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> l1[i];
        a[++cnt] = l1[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> r1[i];
        a[++cnt] = r1[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> l2[i];
        a[++cnt] = l2[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> r2[i];
        a[++cnt] = r2[i];
    }
    a[++cnt] = 1;
    a[++cnt] = T;
    sort(a + 1, a + 1 + cnt);
    cnt = unique(a + 1, a + 1 + cnt) - (a + 1);
    b[++tot] = a[1];
    len[tot] = 1;
    for (int i = 2; i <= cnt; i++) {
        if (a[i] != a[i - 1] + 1) {
            b[++tot] = a[i] - 1;
            len[tot] = a[i] - a[i - 1] - 1;
        }
        b[++tot] = a[i];
        len[tot] = 1;
    }
    for (int i = 1; i <= n; i++) {
        int p1 = lower_bound(b + 1, b + 1 + tot, l1[i]) - b;
        int p2 = lower_bound(b + 1, b + 1 + tot, r1[i]) - b;
        sum1[p1]++, sum1[p2 + 1]--;
    }
    for (int i = 1; i <= m; i++) {
        int p1 = lower_bound(b + 1, b + 1 + tot, l2[i]) - b;
        int p2 = lower_bound(b + 1, b + 1 + tot, r2[i]) - b;
        sum2[p1]++, sum2[p2 + 1]--;
    }
    int ans = 0;
    for (int i = 1; i <= tot; i++) {
        sum1[i] += sum1[i - 1];
        sum2[i] += sum2[i - 1];
        if (sum1[i] && sum2[i]) {
            ans += len[i];
        }
    }
    cout << ans << endl;
    return 0;
}
```











### 第四题

给定n个元素的集合，从集合中选k个元素求和，使其和能被k1整除，不能被k2整除。（1 <= k <= n）   

​    参考力扣78. 子集，直接回溯遍历所有可能的和，再依次判断。不能全a，但能快速拿一些分支的分。

（DP计数）





```c++
// 可以考虑 另 p = lcm(k1, k2), f[i][j]，表示前i个数中模p余j的最大值，g[i][j]表示取到该值的方案。
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 998244353;

int f[N][110], g[N][110], a[N], n, k1, k2, p;

int main() {
    cin >> n >> k1 >> k2;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    p = k1 * k2 / __gcd(k1, k2);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            f[i][j] = -0x3f3f3f3f;
        }
    }
    f[0][0] = 0, g[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            f[i][j] = max(f[i][j], f[i - 1][j]);
            // f[i - 1][j] -> (j + a[i]) % p + p % p
            int cur = ((j + a[i]) % p + p) % p;
            if (f[i - 1][j] != -0x3f3f3f3f) {
                f[i][cur] = max(f[i][cur], f[i - 1][j] + a[i]);
            }
        }
        for (int j = 0; j < p; j++) {
            // g[i][j] = (g[i][j] + g[i - 1][j]) % mod;
            int cur = ((j + a[i]) % p + p) % p;
            if (f[i - 1][j] != -0x3f3f3f3f && f[i][cur] == f[i - 1][j] + a[i]) {
                g[i][cur] = (g[i][cur] + g[i - 1][j]) % mod;
            }
            if (f[i - 1][j] == f[i][j]) {
              g[i][j] = (g[i][j] + g[i - 1][j]) % mod;
            }
        }
    }
    int ans = -0x3f3f3f3f, sum;
    for (int i = 0; i < p; i++) {
        if (i % k1 == 0 && i % k2 != 0) {
            if (f[n][i] > ans) {
                ans = f[n][i], sum = g[n][i];
            }
        }
    }
    cout << ans << " " << sum << endl;
    return 0;
}
```






我ac了，`f[i][j][k]` 表示前i个%k1为i %k2 为k的最大值

`dp[i][j][k]` 为前i个能取到的值中 sum%k1 = j，sum%k2=k的最大值，转移时和背包一样，要么选择i放进去，要么i不放进去，（题目数据应该是把负数也可以看成可以对k1k2取模的，所以我没考虑负数也过了）



我开始的时候是转移那块写错了，应该写错`( j-num[i]%k1+k1)%k1`就过了

---

### 第五题

当时没时间写了，把题目抄了下来，然后发现这道题甚至是5道里最简单的一题。。。直接模拟。不能全a，但能拿一大半分支的分。  

> 对于一个序列A，我们定义序列(A+1)为将序列A里每个元素值都加1得到的序列。
>
> 例如：[3, 4, 2]+1=[4, 5, 3]，[1, 2, 1]+1=[2, 3, 2]。
>
> 对于序列A和B，我们定义序列C=A*B表示序列C是由序列A和序列B拼接而成（序列A在前，序列B在后）。
>
> 例如：[2, 3, 1]*[1, 2, 1]=[2, 3, 1, 1, 2, 1]； [1, 2, 3]*[2, 3]*[5, 4]=[1, 2, 3, 2, 3]*[5, 4]=[1, 2, 3, 2, 3, 5, 4]。
>
> 小团得到了一个魔法盒子。
>
> 将序列A放入魔法盒子内，将会弹出序列(A+1)*A*(A+2)。
>
> 小团先将仅由一个数0构成的序列[0]放入魔法盒子，然后不断将魔法盒子弹出的序列再次放入。现在小团想问，他这样操作第n次时魔法盒子弹出序列中第k个位置的值是多少？
>
> 
>
> 例如：一开始的序列为[0]，第1次放入后弹出的结果是[1, 0, 2]，第2次是[2, 1, 3, 1, 0, 2, 3, 2, 4]，第3次是[3, 2, 4, 2, 1, 3, 4, 3, 5, 2, 1, 3, 1, 0, 2, 3, 2, 4, 4, 3, 5, 3, 2, 4, 5, 4, 6]。
>
>  一行两个空格隔开的整数n，k，表示初始序列为[0]，小团想知道第n次弹出的序列的第k个数是多少。
>
> 输入：n  k            数据保证 ：1<=n<=35, 1<=k<=3^n    输出：一个整数，表示第n次弹出的序列的第k个数。



```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 50;

long long p[N], k, ans;

int main() {
  p[0] = 1;
  for (int i = 1; i < N; i++) {
    p[i] = p[i - 1] * 3;
  }
  int n;
  cin >> n >> k;
  while (n--) {
    if (k <= p[n]) {
      ans++;
    } else if (k <= 2 * p[n]) {
      k -= p[n];
    } else {
      ans += 2;
      k -= 2 * p[n];
    }
  }
  cout << ans << endl;
  return 0;
}
```



