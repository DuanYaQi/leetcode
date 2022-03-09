class Solution {
public:
        // 逆转字符串
    void reverseS(string &s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    // 去除多余的空格
    void removeExtraSpaces(string& s) {
        int slow = 0;
        int fast = 0;
        
        // 去除最前方的空格
        while (s[fast] == ' ') {
            fast++;
        }
        
        
        // 去除字符串中间的空格
        for (; fast < s.size(); fast++) {
            if (s[fast] == ' ' && s[fast - 1] == ' ') { //保证字符串尾部本不可能有大于1个的空格
                continue;
            } else {
                s[slow] = s[fast];
                slow++;
            }
        }
        
        // 去除字符串最后的空格 最后可能是1个空格或者1个字母
        if (s[slow - 1] == ' ') {
            s.resize(slow - 1);
        } else {
            s.resize(slow);
        }
    }

    // 解
    string reverseWords(string s) {
        removeExtraSpaces(s);
        reverseS(s, 0, s.size() - 1);
        int start = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                reverseS(s, start, i - 1);
                start = i + 1;
            }
        }
        reverseS(s, start, s.size() - 1);
        return s;
    }
};