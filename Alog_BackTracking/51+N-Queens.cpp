class Solution {
public:
    void putQueen(int x, int y, vector<vector<int>> &attack) {
        int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        attack[x][y] = 1;
        
        for (int i = 1; i < attack.size(); ++i) {
            for (int j = 0; j < 8; ++j) {
                int ax = x + i * dx[j];
                int ay = y + i * dy[j];

                if (ax >= 0 && ax < attack.size() && ay >=0 && ay < attack.size()) {
                    attack[ax][ay] = 1;
                }
            }
        }

    }

    void bt(int cnt, int n, vector<string> &queen, vector<vector<int>> &attack, vector<vector<string>> &solve) {

        if (cnt == n) {     //放皇后的数目, 也表示行数
            solve.push_back(queen);
            return;
        }

        for (int i = 0; i < n; ++i) {
            if(attack[cnt][i] == 0) {
                queen[cnt][i] = 'Q';
                vector<vector<int>> tmp = attack;
                putQueen(cnt, i, attack);
                bt(cnt+1, n, queen, attack, solve);
                attack = tmp;
                queen[cnt][i] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solve;
        vector<vector<int>> attack;
        vector<string> queen;

        for (int i = 0; i < n; ++i) {
            attack.push_back(vector<int>());
            for (int j = 0; j < n; ++j) {
                attack[i].push_back(0);
            }
            queen.push_back("");
            queen[i].append(n, '.');
        }


        bt(0, n, queen, attack, solve);


        return solve;
    }
};