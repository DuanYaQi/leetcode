class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int freq[256] = {0};
        int l = 0, r = -1; //滑动窗口为s[l...r]
        int res = 0;
        // 整个循环从 l == 0; r == -1 这个空窗口开始
        // 到l == s.size(); r == s.size()-1 这个空窗口截止
        // 在每次循环里逐渐改变窗口, 维护freq, 并记录当前窗口中是否找到了一个新的最优值
        while(l < s.size()){
            if(r + 1 < s.size() && freq[s[r+1]] == 0){
                r++;
                freq[s[r]]++;
            }else {   //r已经到头 || freq[s[r+1]] == 1
                freq[s[l]]--;
                l++;
            }
            res = max(res, r-l+1);
        }
        return res;
    }
};