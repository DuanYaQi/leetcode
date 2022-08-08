class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;

        unordered_map<string, int> ump;
        for (auto &s : words) {
            ++ump[s];
        }

        int cnt = words.size(), length = words[0].size();
        for (int i = 0; i < s.size() - cnt * length + 1; ++i) {
            unordered_map<string, int> umpT;
            int j = i, cntT = 0;
            while (j < s.size()) {
                string sT = s.substr(j, length);
                j += length;
                if (ump[sT] == 0) break;
                if (++umpT[sT] > ump[sT]) break;
                cntT++;
            }


            if (cntT == cnt) res.push_back(i);
        }

        return res;
    }
};