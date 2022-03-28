class Solution {
public:
    bool judge(vector<string>& strs, string subs) {
        for (int i = 0; i < strs.size(); ++i) {
            for (int j = 0; j < subs.size(); ++j) {
                if (strs[i][j] != subs[j]) return false;
            }
        }        

        return true;
    }

    string longestCommonPrefix(vector<string>& strs) {
        int index = 0, len = 205;

        for (int i = 0; i < strs.size(); ++i) {
            index = len > strs[i].size() ? i : index;
            len = strs[i].size();
        }

        int l = 0, r = strs[index].size() - 1;
        string subs = strs[index].substr(0, r+1);

        while (l <= r) {
            if (judge(strs, subs)) {
                break;
            } else {
                r--;
            }
            subs = strs[index].substr(0, r+1);
        }

        
        return subs; 
    }
};