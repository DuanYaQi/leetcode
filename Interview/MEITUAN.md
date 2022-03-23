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





---

## 3.5 笔试

https://blog.csdn.net/qq_38649940/article/details/123292226



第一题就是贪心

第二题dp

第三题维护最长xyz片段

第四题差分数组+贪心（查询最多的点乘最大的点，依次递推）

第五题我写的dfs搜索只过了64，换成bfs过了82





### 第一题

类似leetcode 128





给出 $n$ 个数，让你选出一个最大的子集，使得任意两个数的差>1
`n <= 1e5 , a[i] <= 2e5`

显然直接用 `dp[i]`  表示现在最大的数选到 `i`，最大的子集是多少，然后直接转移即可。





给一个带有重复数字的数组，找出最长的不连续的序列的长度（好像是上升的）。

输入：1,2,3,5,6,7

输出：4，最长为【1,3,5,7】

我的思路：签到题，排序一下，然后一个个找即可。



```c++
int dp[maxn],n,a[maxn],v[maxn];

int main()
{
	n=read(); rep(i,1,n) a[i]=read(),v[a[i]+1]=1;
	rep(i,2,200001) dp[i]=max(dp[i-1],dp[i-2]+v[i]);
	cout<<dp[200001]<<endl;
	return 0;
}
```



```c++
bool IsNear(int& n1, int& n2)
{
	return abs(n1 - n2) <= 1;
}

int main()
{
	int n;
	while ( cin >> n )
	{
		vector<int>numVec(n);
		for ( auto i = 0; i < n; ++i )
		{
			cin >> numVec[i];
		}
		sort(numVec.begin(), numVec.end());
		int sum = 0;
		int length = 1;
		for ( auto i = 1; i <= n; ++i )
		{
			if ( IsNear(numVec[i - 1], numVec[i]) )
			{
				length++;
			}
			else
			{
				if ( length % 2 == 1 )
					++length;
				sum += length / 2;
				length = 1;
			}
		}
		cout << sum << endl;
	}
	return 0;
}
```



----

### 第二题

给一个数组，你可以将其中某一段翻转，然后求连续子数组的最大和

输入：-1,3,-5,2,-1,3

输出：7（将数组下标1-2的元素翻转，然后求得3+2+-1+3 = 7，另有别的翻转方法）

我的思路：瞎想了半小时，求两个数组，left[i]保存i左边的连续子数组最大和，right[i]保存右边的，然后相加即可。估计边界有问题，只过了90%。





题目大意：给出长度为n的数组，可以翻转任意一段，问翻转一段之后的数组最大子段和为多少    `n<=1e5,-1e3<=a[i]<=1e3`

可以发现：翻转操作只是相当于，我们可以选择两个子段进行统计答案。
所以我们从前往后做一遍存到 dp1，从后往前做一遍存存到 dp2，分别表示，从该位开始的最大子段和为多少。
然后我们记录一下 dp1数组的前缀 max，就可以直接统计答案了

```C++
ll n,a[maxn],dp1[maxn],dp2[maxn],ans,pmx[maxn];

int main()
{
	n=read(); rep(i,1,n) a[i]=read();
	rep(i,1,n) dp1[i]=max(0ll,dp1[i-1])+a[i],pmx[i]=max(pmx[i-1],dp1[i]);
	per(i,n,1) dp2[i]=max(dp2[i+1],0ll)+a[i];
	rep(i,1,n) ans=max(ans,pmx[i]+dp2[i+1]);
	cout<<ans<<endl;
	return 0;
}

```





----

### 第三题

切豆腐，豆腐是正方体，边长n，一共切m刀。  每刀对着x、y、z轴之一垂直切，切的轴上的坐标会告诉你。  输出每刀切完后，剩下的豆腐块中最大的豆腐体积。 

 输入： 

 2 3 

 x y z 

 1 1 1 

 输出： 

 4 

 2 

 1 







切豆腐。给定正立方体的边长n。对立方体进行若干次垂直与坐标轴（x,y,z）的切割操作，求每一次操作结束后最大切块的体积，求操作结束后的最大切块的体积。

有一个`n∗n∗n` 大小的立方体，进行 `m` 次操作，每次操作选择从 `x` 或 `y` 或 `z` 的一个面进行切割(给定操作,例如给 `x=4` 就是沿着 `x=4` 的面进行切割)，问 `m` 次操作时，每次操作后最大体积的立方块大小。 `n,m<=1000`

可以发现，xyz三个维度是独立的，我们每次操作就相当于，在xyz三个线段中选择一个线段从中间断开。
那么我们维护一下这个过程，每次统计答案就是最大的x\*最大的y\*最大的z了。
本人直接使用了set维护，简单暴力，当然应该有更好的维护方法。

```c++
int n,m,a[maxn],A[4];
char opt[maxn];
struct node{int l,r;};

inline bool operator < (node a,node b)
{
	if(a.l!=b.l) return a.l<b.l;
	return a.r<b.r;
}

multiset <node> sx[4];
multiset <node>::iterator it;

int main()
{
	n=read(); m=read(); rep(i,1,m) cin>>opt[i]; rep(i,1,m) a[i]=read();
	rep(i,0,2) sx[i].ins({0,n}),A[i]=n;
	rep(i,1,m)
	{
		int id;
		if(opt[i]=='x') id=0;
		else if(opt[i]=='y') id=1;
		else id=2;
		
		for(it=sx[id].begin();it!=sx[id].end();it++)
		{
			node tmp=*it;
			if(a[i]>=tmp.l&&a[i]<=tmp.r)
			{
				sx[id].ins({tmp.l,a[i]});
				sx[id].ins({a[i],tmp.r});
				sx[id].erase(it); break;
			}
		}
		A[id]=0;
		for(it=sx[id].begin();it!=sx[id].end();it++)
		{
			node tmp=*it; //cout<<tmp.l<<" "<<tmp.r<<endl;
			A[id]=max(A[id],tmp.r-tmp.l);
		}
		cout<<A[0]*A[1]*A[2]<<endl;
	}
	return 0;
}

```



```c++
int GetMaxLenth(set<int> disSet, int n)
{
	int maxx = 0;
	int last = 0;
	for ( auto i = disSet.begin(); i != disSet.end(); ++i )
	{
		if ( i == disSet.begin() )
		{
			maxx = *disSet.begin();
			last = *disSet.begin();
		}
		maxx = max(*i - last, maxx);
		last = *i;
	}
	maxx = max(n - last, maxx);
	return maxx;
}
int main()
{
	int n, m;
	while ( cin >> n >> m )
	{
		int xMax = n;
		int yMax = n;
		int zMax = n;
		vector<string> posVec;
		vector<int> disVec;
		set<int> disXVec;
		set<int> disYVec;
		set<int> disZVec;
		for ( auto i = 0; i < m; ++i )
		{
			string posStr;
			cin >> posStr;
			posVec.push_back(posStr);
		}
		for ( auto i = 0; i < m; ++i )
		{
			int dis;
			cin >> dis;
			disVec.push_back(dis);
		}
		for ( auto i = 0; i < m; ++i )
		{
			if ( posVec[i].compare("x") == 0 )
			{
				disXVec.insert(disVec[i]);
				xMax = GetMaxLenth(disXVec, n);
			}
			if ( posVec[i].compare("y") == 0 )
			{
				disYVec.insert(disVec[i]);
				yMax = GetMaxLenth(disYVec, n);
			}
			if ( posVec[i].compare("z") == 0 )
			{
				disZVec.insert(disVec[i]);
				zMax = GetMaxLenth(disZVec, n);
			}
			cout << xMax * yMax * zMax << endl;
		}
	}
}
```





### 第四题

给定一个数组rec。给定n个操作 【L,R,K】，表示对[L,R]范围内的数+K。给定m个查询【L,R】，表示求【L,R】范围内的和。在允许重新排列原始数组rec的情况下，计算经过n此操作后，m次查询的结果的最大值。







给个数组，给操作，重排后找出操作后的最大和







题目大意：给你q次区间加，区间求和的操作，需要你重新排列一下原数组，使得每次查询区间和的答之和最大。

`n<=1000,q<=500`

发现只需要统计一下每个位置的数对答案的贡献就ok了。
所以我们每次区间加，就是区间内每个点的贡献+1，然后区间加操作照常就好。
然后根据贪心思想，贡献越多的地方，应该放的数就越大，排个序统计贡献就做完了。

然后由于这个数据范围很小，并不需要真的写一个线段树，暴力处理就ok了。

```c++
ll n,Q,a[maxn],cnt[maxn],ans,nw[maxn];

int main()
{
	n=read(); Q=read(); rep(i,1,n) a[i]=read();
	while(Q--)
	{
		int opt=read();
		if(opt==1)
		{
			int l=read(),r=read();
			rep(i,l,r) ans+=nw[i],cnt[i]++;
		}
		else
		{
			int l=read(),r=read(),w=read();
			rep(i,l,r) nw[i]+=w;
		}
	}
	sort(cnt+1,cnt+n+1); sort(a+1,a+n+1);
	rep(i,1,n) ans+=a[i]*cnt[i];
	cout<<ans<<endl;
	return 0;
}

```





```c++
bool firstIsHigh(vector<pair<int, int>>&writeMap, int k1, int k2)
{
	int k1P = 0;
	int k2P = 0;
	for ( auto i : writeMap )
	{
		if ( i.first == k1 )
			k1P = i.second;
		if ( i.first == k2 )
			k2P = i.second;
	}
	return k1 > k2;
}
int main()
{
	int n, m;
	while ( cin >> n >> m )
	{
		vector<int>numVec(n);
		vector<vector<int>>opVec;
		vector<pair<int, int>>readMap(n);
		vector<pair<int, int>>writeMap(n);
		for ( auto i = 0; i < n; ++i )
		{
			cin >> numVec[i];
		}
		int sum = 0;
		for ( auto i = 0; i < m; ++i )
		{
			vector<int>lines(4);
			cin >> lines[0];
			if ( lines[0] == 1 )
			{
				cin >> lines[1] >> lines[2];
				for ( auto i = lines[1] - 1; i < lines[2]; ++i )
				{
					readMap[i].first = i;
					readMap[i].second++;
				}
			}
			else if ( lines[0] == 2 )
			{
				cin >> lines[1] >> lines[2] >> lines[3];
				for ( auto i = lines[1] - 1; i < lines[2]; ++i )
				{
					writeMap[i].first = i;
					writeMap[i].second++;
				}
			}
			opVec.push_back(lines);
		}
		sort(readMap.begin(), readMap.end(), [](pair<int, int>a, pair<int, int>b)->bool{return a.second > b.second; });
		sort(numVec.begin(), numVec.end(), greater<int>());
		vector<int>newVec(n);
		for ( auto i = 0; i < n; ++i )
		{
			if ( readMap[i].second > readMap[i + 1].second && i != n - 1 )
			{
				newVec[readMap[i].first] = numVec[i];
			}
			else if ( readMap[i].second == readMap[i + 1].second && i != n - 1 )
			{
				if ( firstIsHigh(writeMap, readMap[i].first, readMap[i].second) )
				{
					newVec[readMap[i].first] = numVec[i];
				}
				else
				{
					newVec[readMap[i + 1].first] = numVec[i];
					newVec[readMap[i].first] = numVec[i + 1];
					++i;
					if ( i + 1 == n )
					{
						break;
					}
				}
			}
			if ( i == n - 1 )
			{
				newVec[readMap[i].first] = numVec[i];
			}
		}
		for ( auto op : opVec )
		{
			if ( op[0] == 1 )
			{
				for ( auto i = op[1] - 1; i < op[2]; ++i )
					sum += newVec[i];
			}
			else if ( op[0] == 2 )
			{
				for ( auto i = op[1] - 1; i < op[2]; ++i )
					newVec[i] += op[3];
			}
		}
		cout << sum << endl;
	}
	return 0;
}
```



第四题 差分+前缀和能做，每次排序一下然后根据query的数量进行
