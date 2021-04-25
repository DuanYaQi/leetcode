class Solution {
public:
    void getNext(int* next, const string& s) {
        int j = -1;
        next[0] = -1;

        for (int i = 1; i < s.size(); i++) { ///注意是从1开始
            while (j > -1 && s[i] != s[j + 1]) {
                j = next[j];
            }
            if (s[i] == s[j + 1]) {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern(string s) {
        int nSize = s.size();
        int next[nSize];

        getNext(next, s);

        /*
        for (int i = 0; i < nSize; i++) {
            cout << next[i] << " ";
        }
        */
        
        // (nSize % (nSize - next[nSize - 1] - 1)) == 0  由子串多次构成的判定
        // len = next(n - 1) + 1 存放的是s减去子字符串的长度值，nSize - len 就是子字符串的长度值，必须要能整除
        if (next[nSize - 1] != -1 && (nSize % (nSize - next[nSize - 1] - 1)) == 0) {
            return true;
        }

        return false;
    }
};