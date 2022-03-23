const int MAX_N = 1e5 + 5;
class Solution {
public:
    struct UF {
        int fa[MAX_N];

        void init(int n) { for (int i = 0; i < n; ++i) { fa[i] = i; } }
        int find (int x) { 
            if (x == fa[x]) return x;
            else {
                int F = find(fa[x]);
                fa[x] = F;
                return F;
            }
        }
        void merge(int x, int y) { fa[find(y)] = find(x); }
    } uf;


    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        if (pairs.size() == 0) return s;
        
        uf.init(s.size());

        for (auto pair : pairs) {
            uf.merge(pair[0], pair[1]);
        }

        vector<vector<int>> vec(pairs.size());
        vector<vector<char>> vecC(pairs.size());

        for (int i = 0; i < s.size(); ++i) {
            int tmp = uf.find(i);
            vec[uf.find(i)].push_back(i);
            vecC[uf.find(i)].push_back(s[i]);
        }

        
        for (auto& vecc : vecC) {
            sort(vecc.begin(), vecc.end());
        }

        for (auto& ve : vec) {
            sort(ve.begin(), ve.end());
        }

        string res(s.size(), 0);

        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < vec[i].size(); ++j) {
                res[vec[i][j]] = vecC[i][j];
            }
        }

        return res;
    }
};