class Solution {
public:
    unordered_map<char, int> umaps, umapp;

    bool check() {
        for (auto c : umapp) {
            if (umaps[c.first] < c.second) {
                return false;
            }
        }
        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        if (p.size() > s.size()) return {};
        vector<int> res;
        for (auto c : p)
            umapp[c]++;

        int left = 0, right = 0;
        int size = p.size();
        
        for (; left < s.size() - size + 1; ++left) {
            if (left == 0) {
                for (right = left; right <= left + size - 1; ++right) {
                    char c = s[right];
                    if (umapp.find(c) != umapp.end()) 
                        umaps[c]++;
                }

                if (check())
                    res.push_back(left);

            } else {
                right = left + size - 1;
                if (umapp.find(s[left - 1]) != umapp.end()) 
                    umaps[s[left - 1]] = max(umaps[s[left - 1]] - 1, 0);
                
                if (umapp.find(s[right]) != umapp.end()) 
                    umaps[s[right]]++;
                
                if (check())
                    res.push_back(left);
            }
            
        }

        return res;
    }
};





class Solution {
public:
    unordered_map<char, int> umaps, umapp;

    bool check() {
        for (auto c : umapp) {
            if (umaps[c.first] < c.second) {
                return false;
            }
        }
        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        if (p.size() > s.size()) return {};
        vector<int> res;
        for (auto c : p)
            umapp[c]++;

        int left = 0;
        int size = p.size();    //r-l+1 = size
        int right = left + size - 1;// r = l + size - 1

        for (int i = 0; i <= right; i++) {
            char c = s[i];
            if (umapp.find(c) != umapp.end()) 
                umaps[c]++;

            if (check())
                res.push_back(left);
        }

        left++;
        right++;
        while (right < s.size()) {
            if (umapp.find(s[left - 1]) != umapp.end())                 // 减前一个窗口
                umaps[s[left - 1]] = max(umaps[s[left - 1]] - 1, 0);
            
            if (umapp.find(s[right]) != umapp.end())                    // 加后一个窗口
                umaps[s[right]]++;
            
            if (check())
                res.push_back(left);
            
            left++;
            right++;
        }

        return res;
    }
};