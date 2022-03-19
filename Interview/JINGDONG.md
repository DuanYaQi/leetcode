# 京东 



## 3.19 第一题 分鸡蛋

简化来说就是 $t$ 组询问，每次给出两个数 $x,y(1<=x,y<=1e^{18})$，有两种操作：

- x+1
- 如果 x%3==0，也可以选择将 x=x/3

问将 x 变为 y 的最小操作次数。

**思路**

贪心。

首先明确两种操作的本质，第一种是增大 x，第二种是减少 x

那么如果 x<y 的话，肯定是直接选择第一种操作，答案就是 y-x

如果是 x>y 的话，想减少 x 会选择第二种操作，但是要看 x 是否被 3 整除，如果没有被 3 整除的话就先+1。然后执行第二种操作，直到 x<y。再执行第一种操作，让 x+1直到 x==y。
这样操作次数就是最优的。



```C++
/*  Input
	3
	4 1
	2 2
	1000000000000000000 5
	Output
	5
	0
	76
*/

int main() {
    int T;
    long long x, y;

    cin >> T;

    for (int i = 0; i < T; ++i) {
        int cnt = 0;
        cin >> x >> y;

        while (x > y) {
            if (x % 3LL == 0LL) {
                x /= 3LL;
            } else {
                x++;
            }
            cnt++;
        }

        if (x == y) {
            cout << cnt << endl;
        } else {
            cout << cnt + y - x << endl;
        }
    }
    
    return 0;
}
```



---

## 3.19 第一题 攻城战

小七正在玩一款名为“攻城战”的策略游戏。现在，小七正在率领自己的军队攻打一座城池。

通过一段时间的游玩，小七的军队目前有a辆坦克。而“攻防战”是一个回合制游戏，一个回合如下：

1.小七的军队中的每辆坦克攻击所选择的一座碉堡，这座碉堡损失一点生命值。当一座碉堡失去所有生命值时，它就被摧毁了。小七可以为每辆坦克独立选择碉堡。

2.小七的对手进攻。炸毁k*c辆坦克，其中：k是剩余的碉堡的数量，每个碉堡可以炸毁c辆坦克。

通过侦察兵，小七探明了敌情：战场上有d座敌方碉堡，每一座碉堡都有b点生命值。摧毁所有的碉堡后，小七就攻下了这座城池（即使小七没有坦克了，也算攻下了这座城池）。反之如果小七没有坦克了，敌方还有碉堡，小七就失败了。现在小七想提前知道自己能否获胜，你能帮帮小七吗？

一行四个空格隔开的整数a,b,c,d，其中1<=a<=1000000, 1<=b,c,d<=10000

输出一个数，如果小七可以获胜，输出所需的最小回合数。否则输出-1。

样例输入:
10 6 8 2

样例输出:
2

```java
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int a = in.nextInt(); //坦克
        int b = in.nextInt(); //碉堡血量
        int c = in.nextInt(); //一个碉堡炸c
        int d = in.nextInt(); //碉堡数量
        int cur = b;
        int count = 0;
        while (a != 0 && d != 0) {
            count++;
            int tank = a;
            if (tank < cur) {
                cur -= tank;
            } else {
                while (tank >= cur && d != 0) {
                    d--;
                    tank -= cur;
                    cur = b;
                }
                if (d == 0) break;
                cur -= tank;
            }
            if (a - d * c > 0) {
                a = a - d * c;
            } else {
                a = 0;
                break;
            }
        }
        if (a == 0 && d != 0) {
            System.out.println(-1);
        } else {
            System.out.println(count);
        }
    }
}



```

坦克炸碉堡，用碉堡总血量算的，一开始没想过总血量会一次扣成负的，卡了好久。。。

```java
public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int a = in.nextInt(), b = in.nextInt(), c = in.nextInt(), d = in.nextInt();
    long time = 0, total = d * b;
    while (d > 0) {
        if (a == 0)
            break;
        total -= a;
        if (total <= 0)
            d = 0;
        else
            d = (int) total / b + (total % b == 0 ? 0 : 1);
        a -= d * c;
        ++time;
    }
    System.out.println(d == 0 ? time : -1);
}
```





根据题意模拟即可。

```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int a, b, c, d;
int hp[N];

int main() {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int i = 1; i <= d; ++i) hp[i] = b;
    int ans = 0;
    while (a > 0 && d > 0) {
        int cnt = a;
        while (cnt > 0 && d >= 1) {
            if (cnt >= hp[d]) {
                cnt -= hp[d];
                hp[d] = 0;
                --d;
            } else {
                hp[d] -= cnt;
                cnt = 0;
            }
        }
        a -= d * c;
        ++ans;
    }
    if (d > 0) puts("-1");
    else printf("%d\n", ans);
    return 0;
}
```



## 3.19 第二题 最大承重装载机

小明在玩一款建造类的游戏。他需要为一段未开荒的地段设计路段的规划，以便起重机通过。

游戏里每段路径都有能承重的级别，小明现在希望尽可能让能承重更大的起重机通过，这样他就可以比较快地完成建造了。

游戏规定小明只能选一种起重机机型，小明想知道这个起重机最高的承重级别应该是多少，使得在该承重条件下，起重机可以从任何一个点出发去向任何一个点而不会损坏道路（损坏道路指的是路段上行驶了超过承重能力的起重机）。

为了方便，我们将需要规划的建造点抽象成N个点，有M条边将他们相连。

第一行是两个空格隔开的正整数n,m。n代表点数，我们将点从1到n编号，m指边的数量

接下来m行，每行3个空格隔开的正整数u, v, p，代表节点u和节点v之间有一条承重能力为p的路径。

1 <= n <= 1000, 1 <= m <= 10000, 1 <= p <= 10000

一行，一个正整数，表示起重机的最重承重级别。

样例输入:
3 3
1 2 3
1 3 4
2 3 5

样例输出:
4



最大生成树，然后找最小的边

如果用克鲁斯卡尔那种方法的话 排序+并查集 时间复杂度应该只有nlogn  如果是暴力超过 n3就过不了



第二道题Prim 维护一个Visit数组 把边做【- Weight，Start，End】这样输到Graph数组 对Graph排序 然后遍历Graph 如果Start End不在Visit中 把Weigjt加到Road里 把不在的节点加入Visit 如果都在就跳过 最后输出Road里面最大值再取反



```c++
/*	Input
	3 3
	1 2 3
	1 3 4
	2 3 5
    Output
	4
*/
int main() {
    int n, m;
    
    while (cin >> n >> m) {
        vector<vector<int>> inputs(m, vector<int>(3));
        vector<vector<int>> weights(1 + n);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < 3; j++) {
                cin >> inputs[i][j];
            }
            int row = inputs[i][0], col = inputs[i][1], weight = inputs[i][2];

            weights[row].push_back(weight);
            weights[col].push_back(weight);
        }
        
        int res = INT_MAX;
        for (int i = 1; i <= n; i++) {
            sort()
        }
    }

    return 0;
}
```





``` java
import java.util.*;

class edge {
    int dst, value;
}

class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        List<List<edge>> edges = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            edges.add(new LinkedList<>());
        }
        int u, v, p;
        for (int i = 0; i < m; i++) {
            u = in.nextInt();
            v = in.nextInt();
            p = in.nextInt();
            edge e = new edge();
            e.dst = v;
            e.value = p;
            edges.get(u).add(e);
            edge e1 = new edge();
            e1.dst = u;
            e1.value = p;
            edges.get(v).add(e1);
        }
        Set<Integer> set = new HashSet<>();
        PriorityQueue<edge> pq = new PriorityQueue<>(new Comparator<edge>() { <a href="/profile/992988" data-card-uid="992988" class="js-nc-card" target="_blank" from-niu="default">@Override public int compare(edge o1, edge o2) {
                return o2.value - o1.value;
            }
        });
        set.add(1);
        pq.addAll(edges.get(1));
        int max = Integer.MAX_VALUE;
        while (!pq.isEmpty()) {
            edge e = pq.poll();
            max = Math.min(max, e.value);
            set.add(e.dst);
            for (edge edge : edges.get(e.dst)) {
                if (!set.contains(edge.dst)) {
                    pq.add(edge);
                }
            }
            if (set.size() == n) {
                break;
            }
        }
        System.out.println(max);
    }
}
```



第二题 当无向图做了，暴力居然干过去了。。。

输入的时候记录一个max和min，二分的找第一个满足条件的重量

只要能从一个节点到达所有节点就算满足条件，所以每次都是从第一个节点开始找

```java
	private static boolean[] mem; //记录节点是否已被遍历

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = 4, m = 5;
        int min = 10000, max = 1;
        int[][] opt = new int[][] {
                {1, 2, 4}, {1, 3, 5}, {1, 4, 6}, {2, 3, 5}, {3, 4, 2}
        };
        Map<Integer, List<int[]>> map = new HashMap<>(); //key存储起点编号，int[]存储边
        int k = 0;
        while (k < m) {
                        //输入构建无向图
            int u = opt[k][0], v = opt[k][1], p = opt[k][2];
            min = Math.min(min, p);
            max = Math.max(max, p);
            List<int[]> list1 = map.get(u);
            if (list1 == null) {
                list1 = new ArrayList<>();
                map.put(u, list1);
            }
            list1.add(new int[] {v, p});
            List<int[]> list2 = map.get(v);
            if (list2 == null) {
                list2 = new ArrayList<>();
                map.put(v, list2);
            }
            list2.add(new int[] {u, p});
            ++k;
        }            
        while (min < max) {  //二分查找最大的重量target
            int mid = (min + max + 1) >> 1;
            mem = new boolean[n + 1];
                        mem[1] = true;
            if (check(map, 1, n, mid) == n) //若能到达节点数为n，则mid <= target
                min = mid;
            else
                max = mid - 1;
        }
        System.out.println(min);
    }

    private static int check(Map<Integer, List<int[]>> map,
                                 int idx, int n, int weight) {
        int k = 0; //记录能到达的节点数
        for (int[] edge : map.get(idx)) {
            if (mem[edge[0]] || weight > edge[1]) //节点已被遍历或超重
                continue;
            mem[edge[0]] = true;
            k += check(map, edge[0], n - 1, weight);
        }
        return k + 1; //要算上当前节点
    }                   
```







二分 + 并查集
二分答案 x，然后对于所有边权小于等于 x 的边，将该边的两端点加入合并为一个集合，如果能合并成 1 个集合说明 x 是一个可行解。

```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 1005;
const int M = 10005;

struct Edge {
    int u, v, w;
} edges[M];

int n, m, par[N];

int find(int x) {
    if (x == par[x]) return x;
    return par[x] = find(par[x]);
}

bool check(int x) {
    for (int i = 1; i <= n; ++i) par[i] = i;
    int res = 0;
    for (int i = 0; i < m; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (x > w) continue;
        int ru = find(u);
        int rv = find(v);
        if (ru != rv) {
            ++res;
            par[ru] = rv;
        }
    }
    return res == n - 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges[i] = {u, v, w};
    }
    int le = 0, ri = M;
    while (le + 1 < ri) {
        int mid = (le + ri) >> 1;
        if (check(mid)) le = mid;
        else ri = mid;
    }
    printf("%d\n", le);
    return 0;
}
```

