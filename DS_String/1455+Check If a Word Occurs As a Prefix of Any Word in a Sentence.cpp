class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int n = sentence.size(), n2 = searchWord.size();
        for (int i = 0, idx = 1; i < n; ++i, ++idx) {
            string s1 = sentence.substr(i, n2);
            if (s1 == searchWord) return idx;
            i = sentence.find(" ", i);
            if (i == string::npos) return -1;
        }
        return -1;
    }
};