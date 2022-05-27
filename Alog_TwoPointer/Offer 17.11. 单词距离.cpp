class Solution {
public:
    int findClosest(vector<string>& words, string word1, string word2) {
        int idx1 = -1, idx2 = -1;
        int res = 0x3f3f3f3f;
        for (int i = 0; i < words.size(); ++i) {
            if (words[i] == word1) idx1 = i;
            if (words[i] == word2) idx2 = i;

            if (idx1 != -1 && idx2 != -1) res = min(res, abs(idx1 - idx2));
        }

        return res;
    }
};