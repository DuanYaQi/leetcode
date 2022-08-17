const int maxn = 2e3 + 5;
struct UF {
    int fa[maxn];

    void init(int n) { for (int i = 0; i < n; ++i) { fa[i] = i; } }

    int find(int x) {
        if (x == fa[x]) return x;
        else return find(fa[x]);
    }

    void merge(int x, int y) { fa[find(y)] = find(x); }

} uf;

class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        uf.init(n + 1);
        vector<vector<int>> g(n + 1);

        for (auto &dis : dislikes) {
            g[dis[0]].push_back(dis[1]);
            g[dis[1]].push_back(dis[0]);
        }

        for (int i = 1; i <= n; ++i) {
            for (auto &e : g[i]) {
                if (uf.find(e) == uf.find(i)) return false;
                uf.merge(g[i][0], e);
            }
        }

        return true;
    }
};