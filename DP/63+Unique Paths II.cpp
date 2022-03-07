class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int M = obstacleGrid.size();    //row
        int N = obstacleGrid[0].size(); //col

        int dp[M][N];
       
        if (obstacleGrid[0][0] == 1)
            return 0;

        int flag = 0;
        for (int i = 0; i < M; ++i) {
            if (flag) {
                dp[i][0] = INT_MAX;
                continue;
            }
            if (obstacleGrid[i][0] == 0) {
                dp[i][0] = 1;
            } else {
                dp[i][0] = INT_MAX;
                flag = 1;
            }      
        }
        

        flag = 0;
        for (int j = 0; j < N; ++j) {
            if (flag) {
                dp[0][j] = INT_MAX;
                continue;
            }
            if (obstacleGrid[0][j] == 0) {
                dp[0][j] = 1;
            } else {
                dp[0][j] = INT_MAX;
                flag = 1;
            }
        }

        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = INT_MAX;
                } else if (dp[i-1][j] == INT_MAX && dp[i][j-1] == INT_MAX) {
                    dp[i][j] = INT_MAX;//continue?
                } else if (dp[i-1][j] == INT_MAX) {
                    dp[i][j] = dp[i][j-1];
                } else if (dp[i][j-1] == INT_MAX) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }   
        }

        return dp[M-1][N-1]==INT_MAX? 0 : dp[M-1][N-1];
    }
};