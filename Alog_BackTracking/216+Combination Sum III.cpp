class Solution {
public:
    vector<vector<int>> res;
    vector<int> resT;

    void dfs(int k, int n, int start, int sum) {
        if (resT.size() == k && sum == n) {
            res.push_back(resT);
            return;
        }

        for (int i = start; i <= 9; ++i) {
            if (sum + i <= n) {
                resT.push_back(i);
                sum += i;
                dfs(k, n, i+1, sum);
                sum -= i;
                resT.pop_back();
            }
        }


        return;
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        dfs(k, n, 1, 0);

        return res;
    }
};