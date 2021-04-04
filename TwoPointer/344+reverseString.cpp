class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0;
        int size = s.size() - 1;
        char tmp;
        while (i <= size) {
            tmp = s[i];
            s[i] = s[size];
            s[size] = tmp;
            size--;
            i++;
        }
    }
};