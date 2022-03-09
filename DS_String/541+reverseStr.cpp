class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += k*2) {
            //正常反转,  包括剩余字符小于2k,大于k个的前k个字符反转
            if (i + k <= s.size()) {
                reverse(s.begin() + i, s.begin() + i + k);
                continue;
            }
            //剩余字符小于k个，全部反转
            reverse(s.begin() + i, s.begin() + s.size());
        }

        return s;
    }
};