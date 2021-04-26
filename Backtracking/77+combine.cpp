class Solution {
public:
    void backtracking(int n, int k, int start) {
        if (tmp.size() == k) {
            res.push_back(tmp);
            return;
        }

        for (int i = start; i <= n; i++) {
            tmp.push_back(i);
            backtracking(n, k, i + 1);
            tmp.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return res;
    }

private:
    vector<vector<int>> res;    
    vector<int> tmp;
};