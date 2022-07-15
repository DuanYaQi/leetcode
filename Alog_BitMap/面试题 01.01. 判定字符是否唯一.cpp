class Solution {
public:
    bool isUnique(string astr) {
        int flag = 0;

        for (auto &ch : astr) {
            int idx = ch - 'a';
            int mask = 1 << idx;    
            // 往左移idx位 比如是字符是'c'的话，往左移2位 00000000000000000000000000000100

            int res = flag & mask;            
            //cout << bitset<32>(mask) << " " << bitset<32>(flag) << " " << bitset<32>(res) << endl;
            if (res == mask) 
                return false;
            else 
                flag |= mask;

        }

        return true;
    }
};