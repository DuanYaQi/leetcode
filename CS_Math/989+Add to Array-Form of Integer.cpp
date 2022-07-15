class Solution {
public:
    // 当前位 = (A 的当前位 + B 的当前位 + 进位carry) % 10    
    vector<int> addToArrayForm(vector<int>& num, int k) {
        int carry = 0;
            
        vector<int> res;
        int i = num.size() - 1;
        // 放到一起处理, 如果有一个变成 0, sumn 这里就相当于 + 0
        while (i >= 0 || k > 0) {
            int a = i < 0 ? 0 : num[i];
            int kn = k == 0 ? 0 : k % 10;
            k /= 10;

            int sumn = a + kn + carry;

            res.push_back(sumn % 10);
            if (sumn >= 10) {
                carry = 1;
            } else {
                carry = 0;
            }
            i--;
        }

        // 如果有进位
        if (carry == 1) res.push_back(1);
        reverse(res.begin(), res.end());

        return res;
    }
};