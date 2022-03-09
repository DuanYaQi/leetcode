class Solution {
public:
    void removeExtraSpace(string &s) {
        int slowIndex = 0, fastIndex = 0;
        while (s[fastIndex] == ' ' && fastIndex < s.size()) {  
            fastIndex++;
        }
        
        // 去除中间多余的空格 和 末尾多余的空格
        for (; fastIndex < s.size(); fastIndex++) {
            //如果当前是空格,前一位置也是空格,什么也不操作,继续循环
            if (s[fastIndex] == ' ' && s[fastIndex] == s[fastIndex - 1] ) { 
                continue;
            } else {
                s[slowIndex++] = s[fastIndex];
            }
        }

        // slowIndex - 1 指向string的最后的一位置
        if (s[slowIndex - 1] == ' ') {
            s.resize(slowIndex - 1);
        } else {
            s.resize(slowIndex);
        }
    }

    string reverseWords(string s) {
        removeExtraSpace(s);
        reverse(s.begin(), s.end());
        int left = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                reverse(s.begin() + left, s.begin() + i);
                left = i + 1; //i为空格, i+1为字母
            }
        }
        reverse(s.begin() + left, s.end()); //由于最后没有空格,所以要单独在反转一次
        return s;
    }
};