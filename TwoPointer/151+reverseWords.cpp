class Solution {
public:
    void reverseS(string &s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    void removeExtraSpaces(string& s) {
        int slow = 0;
        int fast = 0;
        
        while (s[fast] == ' ') {
            fast++;
        }

        for (; fast < s.size(); fast++) {
            if (s[fast] == ' ' && s[fast - 1] == s[fast]) {
                continue;
            } else {
                s[slow] = s[fast];
                slow++;
            }
        }

        if (s[slow - 1] == ' ') {
            s.resize(slow - 1);
        } else {
            s.resize(slow);
        }
        
        
    }

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