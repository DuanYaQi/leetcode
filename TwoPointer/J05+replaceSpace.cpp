class Solution {
public:
    string replaceSpace(string s) {
        int count = 0; // 记录要扩充的内存大小
        int oldSize = s.size();
        for (int i = 0; i < oldSize; i++) {
            if (s[i] == ' ') {
                count++;
            }
        }
        s.resize(s.size() + count * 2);
        int newSize = s.size();
        //反向填充
        for (int i = newSize - 1, j = oldSize - 1; j < i; i--, j--) {
            if (s[j] != ' ') {
                s[i] = s[j];
            } else {
                s[i] = '0';
                s[--i] = '2';
                s[--i] = '%';
            }
        }
        
        return s;
    }
};