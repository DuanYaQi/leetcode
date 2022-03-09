class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int index = 0;

        for (int i = 0; i < s.size(); ++i) {
            if (index < g.size() && s[i] >= g[index]) {
                index++;
            }
        }
        
        return index;
    }
};