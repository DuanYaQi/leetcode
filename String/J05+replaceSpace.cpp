class Solution {
public:
    string replaceSpace(string s) {
        //先扩充大小
        int count = 0;
        int oldSize = s.size();
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                count++;
            }
        }

        s.resize(s.size() + count * 2);
        int newSize = s.size();
        // 双指针,从后往前移动,并填充空格
        for (int i = oldSize - 1, j = newSize - 1; i < j; i--, j--) {
            if (s[i] == ' ') {
                s[j] = '0';
                s[j - 1] = '2';
                s[j - 2] = '%';
                j -= 2;
            } else {
                s[j] = s[i];
            }
        }
        return s; 
    }
};