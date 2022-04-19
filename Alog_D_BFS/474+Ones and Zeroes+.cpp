// 暴力
class Solution {
public:
    int dfs(const vector<vector<int>> &nums, int m, int n, int nowM, int nowN, int cnt, int i) {
        if (nowM > m || nowN > n) return 0; // 超过了 不满足
        // 以下情况为 nowM <= m 和 nowN <= n的情况
        if (i == nums.size()) return cnt;   // 最多 有 m 个 0 和 n 个 1 。

        // 要
        int i1 = dfs(nums, m, n, nowM + nums[i][0], nowN + nums[i][1], cnt + 1, i + 1);
        // 不要
        int i2 = dfs(nums, m, n, nowM, nowN, cnt, i+1);

        return max(i1, i2);
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<int>> nums(len, vector<int>(2, 0));

        for (int i = 0; i < len; ++i) {
            nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
            nums[i][1] = strs[i].size() - nums[i][0];
        } 

        int b = dfs(nums, m, n, 0, 0, 0, 0);
        return b;
    }
};

// unordered_map 优化
class Solution {
public:
    int dfs(const vector<vector<int>> &nums, int m, int n, int cnt, int i, unordered_map<long long, int> &memo) {
        if (m < 0 || n < 0) return 0;
        if (i == nums.size()) return cnt;

        long long key = cnt * (601*101*101) + i * (101*101) + m * (101)  +  n;
        if (memo.find(key) != memo.end()) return memo[key];

        // max(不要, 要) 
        return memo[key] = max(dfs(nums, m, n, cnt, i+1, memo), 
                            dfs(nums, m - nums[i][0], n - nums[i][1], cnt + 1, i + 1, memo));
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<int>> nums(len, vector<int>(2, 0));

        for (int i = 0; i < len; ++i) {
            nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
            nums[i][1] = strs[i].size() - nums[i][0];
        } 

        unordered_map<long long, int> memo;

        return dfs(nums, m, n, 0, 0, memo);
    }
};

// unordered_set 优化
class Solution {
public:
    int dfs(const vector<vector<int>> &nums, int m, int n, int nowM, int nowN, int cnt, int i, vector<unordered_set<int>> &memo) {
        if (nowM > m || nowN > n) return 0; // 超过了 不满足
        // 以下情况为 nowM <= m 和 nowN <= n的情况
        if (i == nums.size()) return cnt;   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以

        int idx = cnt * (101*101) + nowM * 110 + nowN;
        if (memo[i].find(idx) != memo[i].end()) return -9;
        memo[i].insert(idx);

        // max(要, 不要)    
        return max(dfs(nums, m, n, nowM + nums[i][0], nowN + nums[i][1], cnt + 1, i + 1, memo), dfs(nums, m, n, nowM, nowN, cnt, i+1, memo));
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<int>> nums(len, vector<int>(2, 0));

        for (int i = 0; i < len; ++i) {
            nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
            nums[i][1] = strs[i].size() - nums[i][0];
        } 

        vector<unordered_set<int>> memo(len); 

        return dfs(nums, m, n, 0, 0, 0, 0, memo);
    }
};



// 三维数组再优化
class Solution {
public:
    int dfs(const vector<vector<int>> &nums, int m, int n, int i, vector<vector<vector<int>>> &memo) {
        if (i == nums.size()) { return 0;}   // 题目要求最多 有 m 个 0 和 n 个 1 。 因此不==也可以,这里也相当于剪枝，要求i不越界

        if (memo[i][m][n] != -1) return memo[i][m][n];
        
        int i1 = dfs(nums, m, n, i+1, memo);
        int i2 = 0;
        if (m - nums[i][0] >= 0 && n - nums[i][1] >= 0) {
            i2 = 1 + dfs(nums, m - nums[i][0], n - nums[i][1], i + 1, memo);
        }
        // max(要, 不要)    
        return memo[i][m][n] = max(i1, i2);
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        vector<vector<int>> nums(len, vector<int>(2, 0));

        for (int i = 0; i < len; ++i) {
            nums[i][0] = count(strs[i].begin(), strs[i].end(), '0');
            nums[i][1] = strs[i].size() - nums[i][0];
        } 

        vector<vector<vector<int>>> memo(len, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        return dfs(nums, m, n, 0, memo);
    }
};
