class Solution {
public:
    vector<vector<int>> res;
    vector<int> resT;

    void dfs(vector<int>& candidates, int target, int sum, int start) {
        if (sum == target) {
            res.push_back(resT);
            return;
        }

        for (int i = start; i < candidates.size(); ++i) {
            if (i > 0 && candidates[i] == candidates[i-1] && i > start) {
                continue;
            }
            if (sum + candidates[i] <= target) {
                sum += candidates[i];
                resT.push_back(candidates[i]);
                dfs(candidates, target, sum, i+1);
                resT.pop_back();
                sum -= candidates[i];
            }
        }

        return;
    }


    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, 0);

        return res;
    }
};