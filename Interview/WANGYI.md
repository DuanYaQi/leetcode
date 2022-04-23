# 网易







## 4.21

https://leetcode-cn.com/circle/discuss/gGavIU/

https://leetcode-cn.com/circle/discuss/Spt89H/



### t1

> 打印风车



```c++
#include <iostream>
#include <vector>

using namespace std;

int main () {
    int n;
    cin >> n;

    vector<string> answer;
    string temporary;
    for (int i = 1; i <= n; ++i) {
        // 第 1 行
        if (i == 1) {
            string line(2 * n - 1, ' ');
            line[0] = '*';
            for (int j = 2 * n - 2; j >= n - 1; --j) {
                line[j] = '*';
            }
            answer.push_back(line);
            temporary = line;
        }else if (i == n) {
            string line(2 * n - 1, '*');
            answer.push_back(line);
        }else {
            string line(2 * n - 1, ' ');
            for (int j = 0; j < n; ++j) {
                if (j == 0) {
                    line[j] = '*';
                }else if (j == n - 1) {
                    line[j] = '*';
                }else {
                    if (i == j + 1) {
                        line[j] = '*';
                    }
                }
            }
            for (int j = n * 2 - 2; j > n - 1; --j) {
                if (j == n * 2 - 2) {
                    continue;
                }else {
                    if (i == n * 2 - 1 - j) {
                        line[j] = '*';
                    }
                }
            }
            answer.push_back(line);
            temporary = line;
        }
    }
    
    for (const auto& s : answer) {
        cout << s << endl;
    }
    const int row = answer.size();
    const int column = answer[0].size();
    for (int i = row - 2; i >= 0; --i) {
        for (int j = column - 1; j >= 0; --j) {
            cout << answer[i][j];
        }
        if (i != 0) {
            cout << endl;
        }
    }
    return 0;
}
```







### t2

> 给定 n，p，x和长度为n的数组（都是正整数），你可以修改数组中某一个数，取不大于p的值，不能等于原来的值，有几种改法



```c++
int main(){
    int n,p,x;
    cin>>n>>p>>x;

    vector<int> a(n);
    long long s=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        s+=a[i];
    }

    long long res=0;
    for(int i=0;i<n;i++){
        long long cur=s-a[i];   //去掉a[i]之后的和
        long long yux=cur%x;   //取余x的值
        long long yuTarget=(x-yux)%x;    //替换的数字取余x应该为多少

        //找从1-p有几个数组取余x为yuTarget
        if(p>=yuTarget){
            res+=(p-yuTarget)/x+1;

            if(a[i]<=p&&a[i]%x==yuTarget)  //本身包含在里面
                res--;
            if(yuTarget==0)    //0包含在里面
                res=res-1;
        }
    }
    cout<<res<<endl;
    return 0;
}
```











### t3

> 给n个节点和一个长度为m数组{x,y,z}格式，表示x到y的有向路径的权值为z，你可以且仅可以不多于一次将一个有向路径改成无向路径，问最短长度是多少，不能到达返回1



T3用Dijkstra就过了10%，最后也没查出来哪错，用的也是long long



**用(节点编号, 是否使用修改功能) 来表示一个点也就是你现在有了2n个点, 把这2n个点用图表示,**
**2个起点,2个终点, 跑一次dijkstra就行了.**



```c++
#include <bits/stdc++.h>
using namespace std;
struct edge {
    long long int u, v, w;
    edge() {};
    edge(int _u, int _v, int _w) {u = _u, v = _v, w = _w;};
};
long long int n, m, inq[100005][2], d[100005][2], state[100005];
vector<edge> g[100005][2];

int main() {
    memset(d, 0x3f, sizeof(d));
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        edge e;
        cin >> e.u >> e.v >> e.w;
        g[e.u][0].push_back(e);
        g[e.v][1].push_back(e);
    }
    queue<pair<int, int>> q;
    q.push(make_pair(1, 0));
    d[1][0] = 0;
    inq[1][0] = 1;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        inq[p.first][p.second] = 0;
        for (auto i : g[p.first][0]) {
            if (d[i.u][p.second] + i.w < d[i.v][p.second]) {
                d[i.v][p.second] = d[i.u][p.second] + i.w;
                if (!inq[i.v][p.second])
                    inq[i.v][p.second] = 1, q.push(make_pair(i.v, p.second));
            }
        }
        if (p.second == 0)
            for (auto i : g[p.first][1]) {
                swap(i.u, i.v);
                if (d[i.u][0] + i.w < d[i.v][1]) {
                    d[i.v][1] = d[i.u][0] + i.w;
                    if (!inq[i.v][1])
                        inq[i.v][1] = 1, q.push(make_pair(i.v, 1));
                }
            }
    }
    cout << (min(d[n][0], d[n][1]) < d[0][0] ? min(d[n][0], d[n][1]) : -1);
    return 0;
}
```





```c++
#include<bits/stdc++.h>
using namespace std;
long long dp[100005][5];
int vis[100005];
struct node
{
    int x;
    int y;
    int z;
};
vector<node>q[100005];
void spfa(int x)
{
    queue<int>nh;
    nh.push(x);
    vis[x]=1;
    while(!nh.empty())
    {
        int now=nh.front();
        nh.pop();
        vis[now]=0;
        int len=q[now].size();
        for(int i=0; i<len; i++)
        {
            if(q[now][i].z==0)
            {
                int to=q[now][i].x;
                int val=q[now][i].y;
                if(dp[to][0]>dp[now][0]+val)
                {
                    dp[to][0]=dp[now][0]+val;
                    if(vis[to]=1)
                    {
                        nh.push(to);
                        vis[to]=1;
                    }
                }
                if(dp[to][1]>dp[now][1]+val)
                {
                    dp[to][1]=dp[now][1]+val;
                    if(vis[to]=1)
                    {
                        nh.push(to);
                        vis[to]=1;
                    }
                }
            }
            else
            {
                int to=q[now][i].x;
                int val=q[now][i].y;
                if(dp[to][1]>dp[now][0]+val)
                {
                    dp[to][1]=dp[now][0]+val;
                    if(vis[to]=1)
                    {
                        nh.push(to);
                        vis[to]=1;
                    }
                }
            }
        }
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1; i<=m; i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        q[x].push_back({y,z,0});
        q[y].push_back({x,z,1});
    }
    for(int i=2; i<=n; i++)
    {
        dp[i][1]=1e18;
        dp[i][0]=1e18;
    }
    spfa(1);
    if(min(dp[n][0],dp[n][1])==1e18) printf("-1\n");
    else printf("%lld\n",min(dp[n][0],dp[n][1]));
    return 0;
}
```



### t4

> 一个两面的魔方，都是白色，小红会分n步涂色，返回每一步后白色连通块的数量



T4别提了直接读错题没看懂题，考完别人一解释才明白……不过感觉应该是三维的岛屿，回溯吧，感觉挺麻烦的，唉，估计肯定G了



t4: 用并查集搞,应该能做吧, 不太看得懂题目.



T4没写出来，骗了点分。刚刚想了下觉得是先读入最后的状态，深搜初始化一下并查集，然后倒着来将红色块变成白色块直到全白，过程中用并查集维护连通块数量。



逆序并查集

三维岛屿问题

三维修改+查询联通块



逆序并查集，不过是三维的比较麻烦，三维坐标可以转化为一维.从最后状态往前推，看把一个块涂成白色时是否出现若干块的合并



求的是白色的有几堆，一个小立方体有8个面，一个面同色相通就算一堆



```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,h;
int solve(int x,int y,int z)
{
    return (n*m)*(z-1)+(x-1)*m+y;
}
bool check(int x,int y,int z)
{
    if(x<=0||x>n) return 0;
    if(y<=0||y>m) return 0;
    if(z<=0||z>h) return 0;
    return 1;
}
int a[200005];
int now;
int fa[200005];
int nh[200005];
int modify[200005][5];
int vis[200005];
int dir[6][3]= {1,0,0,-1,0,0,0,1,0,0,-1,0,0,0,1,0,0,-1};
void dfs(int x,int y,int z,int num)
{
    vis[solve(x,y,z)]=1;
    fa[solve(x,y,z)]=num;
    for(int i=0; i<6; i++)
    {
        int xx=x+dir[i][0];
        int yy=y+dir[i][1];
        int zz=z+dir[i][2];
        if(check(xx,yy,zz)&&vis[solve(xx,yy,zz)]==0&&a[solve(xx,yy,zz)]==0)
        {
            dfs(xx,yy,zz,num);
        }
    }
    return ;
}
int f(int x)
{
    while(fa[x]!=x)
    {
        x=fa[x]=fa[fa[x]];
    }
    return x;
}
int main()
{
    scanf("%d%d%d",&n,&m,&h);
    for(int i=1; i<=n*m*h; i++)
    {
        fa[i]=i;
    }
    int k;
    scanf("%d",&k);
    for(int i=1; i<=k; i++)
    {
        scanf("%d%d%d",&modify[i][1],&modify[i][2],&modify[i][3]);
        if(a[solve(modify[i][1],modify[i][2],modify[i][3])]==1)
        {
            nh[i]=1;
        }
        a[solve(modify[i][1],modify[i][2],modify[i][3])]=1;
    }
    vector<int>ans;
    now=0;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            for(int k=1; k<=h; k++)
            {
                if(vis[solve(i,j,k)]==0&&a[solve(i,j,k)]==0)
                {
                    dfs(i,j,k,solve(i,j,k));
                    now++;
                }
            }
        }
    }
    ans.push_back(now);
    for(int i=k; i>=2; i--)
    {
        if(nh[i]==1)
        {
            ans.push_back(now);
        }
        else
        {
            //printf("*********");
            a[solve(modify[i][1],modify[i][2],modify[i][3])]=0;
            vector<int>bza;
            for(int j=0; j<6; j++)
            {
                int xx=modify[i][1]+dir[j][0];
                int yy=modify[i][2]+dir[j][1];
                int zz=modify[i][3]+dir[j][2];
                if(check(xx,yy,zz)&&a[solve(xx,yy,zz)]==0)
                {
                    bza.push_back(f(solve(xx,yy,zz)));
                }
            }
            int len=bza.size();
            if(len==0) now++,fa[solve(modify[i][1],modify[i][2],modify[i][3])]=solve(modify[i][1],modify[i][2],modify[i][3]);
            else
            {
                map<int,int>q;
                for(int j=1; j<len; j++)
                {
                    if(q[bza[j]]==0&&bza[j]!=bza[0])
                    {
                        now--;
                        fa[bza[j]]=fa[bza[0]];
                        q[bza[j]]=1;
                    }
                }
                fa[solve(modify[i][1],modify[i][2],modify[i][3])]=bza[0];
            }
            ans.push_back(now);
        }
    }
    int len=ans.size();
    for(int i=len-1; i>=0; i--)
    {
        printf("%d\n",ans[i]);
    }
    return 0;
}
```





---

### t5

https://www.nowcoder.com/discuss/938612

> 一个数可以变为比自己大质数，也可以变为比自己小的质数，求整个数组变为相等元素的最小次数。
>
> 
>
> 求 一个数组里面选择一个质数作为参考，其他数字变成该质数最少的次数
>
> 
>
> 计算把一个序列的数变成同样质数的次数。 打算试试找到范围内的质数，然后模拟，没来得及写完



素筛法得到数据范围所有素数，数组排序，然后将数组中所有数换成小于等于自身的第一个素数。找到中位数，对数组中每个元素，统计中位数到自身相差几个素数。（素筛法的时候可以存下是第几个素数）。 然后对于前半段元素，如果是非1且非素数且小于中位数的话，多统计了一次（因为可以将它变为比自己大的素数），需要减掉。 这种思路过了90😂，感觉太麻烦，且没法证明。





第三题，先质数筛找到所有的质数，然后对整个数组排序，可以证明对于两个数a，b，以及a，b之间的质数集合c，a，b到c中任何质数的操作和是一样的，双指针从两边一对对的删除pair，然后最中间情况分奇数偶数考虑一下(剩一个奇质数不操作，否则加1)，a，b之间没有质数的情况也要考虑一下 (一起加一or减一就是2次操作?) (事后诸葛亮昨晚没做出来也不知道能过多少



```c++
#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 100010;
bool prime[maxn];//是素数为false；
int  mp[maxn];//使用map，key为数字时怎么使用
int arr[maxn];
int arr2[maxn];
vector<int> primes;

int main(){
    prime[1]=true;
    int cnt =0;
    for(int i = 2;i<maxn;i++){
        if(!prime[i]){
            primes.push_back(i);
            mp[i] = ++cnt;
            for(long long j = (long long)i*i;j<maxn;j+=i){
                prime[j] = true;
            }
        }
    }
    
    int n;
    scanf("%d",&n);
    for(int i =0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    sort(arr,arr+n);
    int j=0;
    long long ans = 0;
    for(int i = 0 ;i<n;i++){
        if(arr[i]==1){
            ans+=1;
            arr2[i]=2;continue;
        }
        //所有数化为小于它的最小素数
        while(primes[j+1]<=arr[i])j+=1;
        
        if(arr[i]!=primes[j])ans+=1;
        
        arr2[i] = primes[j];
    }
    int mid_prime = arr[n/2];
    for(int i = 0;i<n;i++){
        int cur_prime = arr2[i];
        // printf("%lld ", abs(mp[cur]-mp[mid]));
        int temp = abs(mp[cur_prime]-mp[mid_prime]);
        if(i<=n/2 && mp[cur_prime]==0&&arr[i]!=1)temp-=1; //对于原来不是是1的非素数多统计了一次。
        ans += temp;

    }
    
    printf("%lld",ans);
    return 0;
}
```



---

### t6

> 最远的共同祖先 最大递增子树
>
> 
>
> 树的最长递增祖先



就是简单的并查集，判断下节点关系大小就行

默认第0个节点为1  然后输入的第二行是剩下n个节点  第三行为父节点的索引😵  看了半天才看懂





```c++
n = int(input())
nums = list(map(int, input().split()))
parent = list(map(int, input().split()))
union_set = [-1 for _ in range(len(nums))]
for i in range(len(parent)):
    union_set[i + 1] = parent[i]
def findfastparent(node):
    if union_set[node - 1] == - 1:
        return node
    if nums[union_set[node - 1] - 1] >= nums[node - 1]:
        return node
    else:
        node = union_set[node - 1]
        return findfastparent(node)
res = []
for i in range(len(nums)):
    ans = findfastparent(i + 1)
    print(ans)
    res.append(ans)
print(" ".join(res))
```

