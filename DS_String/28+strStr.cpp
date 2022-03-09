class Solution {
public:
    void getNext(int* next, const string& s) {
        int j = -1;
        next[0] = -1;
        for (int i = 1; i < s.size(); i++) { //注意从1开始
            while (j > -1 && s[j + 1] != s[i]) {
                j = next[j];
            }
            if (s[j + 1] == s[i]) {
                j++;
            }
            next[i] = j;
        }

    }

    int strStr(string haystack, string needle) {
        int nSize = needle.size();
        if (nSize == 0) {
            return 0;
        }
        int next[nSize];
        getNext(next, needle);
        //cout << next[0] << ',' <<next[1];
        int j = -1;
        for (int i = 0; i < haystack.size() ; i++) {
            while (j > -1 && needle[j + 1] != haystack[i]) {
                j = next[j];
            }
            if (needle[j + 1] == haystack[i]) {
                j++;
            }
            if (j == nSize - 1) {
                return i - nSize + 1;
            }
        }
        return -1;
    }
};