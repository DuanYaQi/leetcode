class Solution {
public:
    string convertToBase7(int num) {
        string res = "";

        bool negative = num < 0;
        num = abs(num);            

        int m;  // 余数
        do {
            m = num % 7;
            num /= 7;
            res += to_string(m);
        } while (num != 0);     // 用 do while 可以不特判零


        if (negative) res += "-";
        reverse(res.begin(), res.end());

        return res;
    }
};