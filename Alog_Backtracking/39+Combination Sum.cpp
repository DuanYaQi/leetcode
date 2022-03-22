class Solution {
public: 
    vector<vector<int>> res;
    vector<int> resT;
    
    void dfs(int sum, int target, vector<int>& candidates, int start){
        if (sum == target) {
            res.push_back(resT);
            return;
        }


        for (int i = candidates[start]; i < candidates.size(); ++i) {
            if (sum + candidates[i] <= 7) {
                resT.push_back(candidates[i]);
                sum += candidates[i];
                dfs(sum, target, candidates, i);
                sum -= candidates[i];
                resT.pop_back();
            }
        }

        return;
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {


        dfs(0, target, candidates, 0);
        return res;
    }
};