class Solution {
public:
    vector<string> res;

    bool isValid(string s) {
        if (s.size() == 1) return true;
        if (s[0] - '0' == 0 || s.size() > 3) return false;

        long long num = 0;
        for (int i = 0; i < s.size(); ++i) {
            num = num*10L + s[i] - '0';
        }

        return num > 255 ? false : true;
    }


    void dfs(string &s, int start, string sT, int cnt) {
        if (cnt > 4) {
            return;
        }
        
        if (start == s.size() && cnt == 4) {
            sT = sT.substr(0, sT.size()-1);
            res.push_back(sT);
        }

        for (int end = start; end <= start+3 && end < s.size(); ++end) {
            if (isValid(s.substr(start, end-start+1))) {
                string tmp = s.substr(start, end-start+1);
                dfs(s, end+1, sT + tmp + '.', cnt+1);
            }
        }

        return;

    }


    vector<string> restoreIpAddresses(string s) {
        string sT;
        dfs(s, 0, sT, 0);

        return res;
    }
};