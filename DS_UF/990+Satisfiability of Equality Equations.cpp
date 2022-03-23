class Solution {
public:
    struct UF{
        int fa[30];

        void init() { for(int i = 0; i < 30; ++i) { fa[i] = i; } }
        
        int find(int x) {
            if (x == fa[x]) return x;
            else {
                int F = find(fa[x]);
                fa[x] = F;
                return F;
            }
        }

        void merge(int x, int y) { fa[find(y)] = find(x); }
    } uf;


    bool equationsPossible(vector<string>& equations) {
        uf.init();
        for (int i = 0; i < equations.size(); ++i) {
            if (equations[i][1] == '=') {
                uf.merge(equations[i][0] - 'a', equations[i][3] - 'a');
            }
        }

        for (int i = 0; i < equations.size(); ++i) {
            if (equations[i][1] == '!') {
                if (uf.find(equations[i][0] - 'a')  == uf.find(equations[i][3] - 'a') )
                    return false;
            }
        }

        return true;
    }
};