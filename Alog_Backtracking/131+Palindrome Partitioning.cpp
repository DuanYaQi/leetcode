class Solution {
public:
    vector<vector<string>> res;
    vector<string> resT;

    bool check(string &s, int start, int end) {
        for (int i = start, j = end; i < j; ++i, --j) {
            if (s[i] != s[j])
                return false;
        }
        return true;
    }

    void dfs(string &s, int start) {
        if (start == s.size()) {
            res.push_back(resT);
            return;
        }

        for (int end = start; end < s.size(); ++end) {
            if (check(s, start, end)) {
                resT.push_back(s.substr(start, end-start+1));
                dfs(s, end+1);  // +1
                resT.pop_back();
            }
        }                  
    }

    vector<vector<string>> partition(string s) {
        dfs(s, 0);

        return res;
    }   
};