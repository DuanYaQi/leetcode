class Solution {
public:
    unordered_map<char, int> umaps, umapt;

    bool check() {
        for (auto c : umapt) {
            if (umaps[c.first] < c.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        for (auto c : t)
            umapt[c]++;
        
        int left = 0, right = 0;
        int len = INT_MAX, resL = -1;
        
        for (; right < s.size(); ++right) {
            char c = s[right];
            
            if (umapt.find(c) != umapt.end())
                umaps[c]++;
                    
            while (check() && left <= right) {
                if (right - left + 1 < len) {
                    len = right - left + 1;
                    resL = left;
                }
                
                if (umapt.find(s[left]) != umapt.end()) {
                    umaps[s[left]]--;
                }
                
                left++;
            }
            
        }
        
        return resL == -1 ? string() : s.substr(resL, len);
    }
};