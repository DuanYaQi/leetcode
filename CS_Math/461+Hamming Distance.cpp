class Solution {
public:
    int hammingDistance(int x, int y) {
        int cnt = 0;
        //cout << bitset<sizeof(int) * 8>(x) << endl;
        //cout << bitset<sizeof(int) * 8>(y) << endl;
        for (int i = 31; i >= 0; i--) {
            //cout << bitset<sizeof(int) * 8>(1 << i) << " " << (x & (1 << i)) << " " << (y & (1 << i)) << endl;
            if ((x & (1 << i)) != (y & (1 << i))) cnt++;
        }

        return cnt;
    }
};