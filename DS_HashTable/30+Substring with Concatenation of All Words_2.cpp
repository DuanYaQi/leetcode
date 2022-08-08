class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> ump; // 统计子串的字符个数
        for (auto &s : words) {
            ++ump[s];
        }
        
        int n = s.size(), cnt = words.size(), length = words[0].size();
        int childStrLen = cnt * length;
        vector<int> res;
        for (int i = 0; i < n - childStrLen + 1; ++i) {     // 遍历起始匹配位置
            string str = s.substr(i, childStrLen);          // 取出等长的字符串
            unordered_map<string, int> umpT;                // 看映射与之前的ump是否相同
            bool flag = true;
            for (int j = 0, prePos = 0; j < cnt; ++j, prePos += length) {   // 循环取出来
                string strT = str.substr(prePos, length);
                umpT[strT]++;
                if (ump.count(strT) == 0 || umpT[strT] > ump[strT]) {
                    flag = false;
                    break;
                }
            }
            if (flag) res.push_back(i);
        }

        return res;
    }
};