class Solution {
public:
    string digitSum(string s, int k) {
        
        while (s.size() > k) {
            string tmp;
            for (int i = 0; i < s.size(); i+=k) {
                string t = s.substr(i, k);
                int x = 0;
                for (char c : t) {
                    x += c - '0';
                }
                tmp += to_string(x);
            }
            
            s = tmp;            
        }
        
        return s;
    }
};