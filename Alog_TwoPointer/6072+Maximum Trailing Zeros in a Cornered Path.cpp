class Solution {
public: 
    void printinfo(vector<vector<int>> &vec) {
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < vec[0].size(); ++j) {
                cout << vec[i][j] << " ";
            }
            cout << endl;
        }           
        cout << endl;
    }
    
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int m = grid.size();        //行
        int n = grid[0].size();     //列
        vector<vector<int>> f2(m + 1), g2(m + 1), f5(m + 1),g5(m + 1);

        for (int i = 0; i <= m; ++i) {
            f2[i] = g2[i] = f5[i] = g5[i] = vector<int>(n + 1);
        }
   
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int x = grid[i-1][j-1];
                int two = 0, five = 0;
                while (x % 2 == 0) two++, x /= 2;
                while (x % 5 == 0) five++, x /= 5;
                f2[i][j] = f2[i][j-1] + two;        // 从左边界 i,0 到现在 i,j 累乘了多少个 2 水平 i不变
                g2[i][j] = g2[i-1][j] + two;        // 从上边界 0,j 到现在 i,j 累乘了多少个 2 垂直 j不变
                f5[i][j] = f5[i][j-1] + five;       // 从左边界 i,0 到现在 i,j 累乘了多少个 5 水平 i不变
                g5[i][j] = g5[i-1][j] + five;       // 从上边界 0,j 到现在 i,j 累乘了多少个 5 垂直 j不变
            }
        }
        
        /*
        printinfo(f2);
        printinfo(g2);
        printinfo(f5);
        printinfo(g5);
        */

        int ans = 0;

        /*枚举所有点作为拐点时的尾随零，从水平方向拿一个方向，从垂直方向拿一个方向*/
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                ans = max(ans, min(f2[i][j] + g2[i-1][j], f5[i][j] + g5[i-1][j]));                          // 左边出发 上边结束 
                // f2[i][j]   包括 [i][j]
                // g2[i-1][j] 不包括 [i][j]

                ans = max(ans, min(f2[i][j] + g2[m][j] - g2[i][j], f5[i][j] + g5[m][j] - g5[i][j]));        // 左边出发 下边结束
                // f2[i][j]   包括[i][j]
                // g2[m][j] - g2[i][j] 不包括 [i][j]  
 
                ans = max(ans, min(f2[i][n] - f2[i][j] + g2[i][j], f5[i][n] - f5[i][j] + g5[i][j]));        // 右边出发 上边结束
                // f2[i][n] - f2[i][j] 不包括 [i][j]
                // g2[i][j] 包括[i][j]
                
                ans = max(ans, min(f2[i][n] - f2[i][j] + g2[m][j] - g2[i-1][j], 
                                    f5[i][n] - f5[i][j] + g5[m][j] - g5[i-1][j]));                          // 右边出发 下边结束
                // f2[i][n] - f2[i][j]    不包括 [i][j]  
                // g2[m][j] - g2[i-1][j]   包括  [i][j]      
            }
        }

        return ans;
   
    }
};