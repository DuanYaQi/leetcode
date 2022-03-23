/*
        计算连通分量数的另一个方法是使用并查集。初始时，每个城市都属于不同的连通分量。
        遍历矩阵 isConnected，如果两个城市之间有相连关系，则它们属于同一个连通分量，对它们进行合并。

        遍历矩阵 isConnected 的全部元素之后，计算连通分量的总数，即为省份的总数。
    */

struct UF {
    int fa[205];

    void init(int n) { for (int i = 0; i < n; ++i) { fa[i] = i; } }

    int find(int x) {
        if (x == fa[x]) return x;
        else return find(fa[x]);
    }

    void merge(int x, int y) { fa[find(y)] = find(x); }


} uf;

int findCircleNum(vector<vector<int>>& isConnected) {
    uf.init(isConnected.size());

    for (int i = 0; i < isConnected.size(); ++i) {
        for (int j = 0; j < isConnected.size(); ++j) {
            if (isConnected[i][j] == true) {
                uf.merge(i, j);
            }
        }
    }

    unordered_set<int> set;

    for (int i = 0; i < isConnected.size(); ++i) {
        set.insert(uf.find(i));
    }

    return set.size();
}