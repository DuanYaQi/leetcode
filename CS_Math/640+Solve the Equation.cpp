class Solution {
public:
    // "x+5-3+x=6+x-2"
    string solveEquation(string equation) {
        int left = 1, neg = 1, k = 0, b = 0;

        // left 表示在等号左右
        // neg 表示数字原本的正负号
        // k 表示x的系数
        // b 表示常数1的系数
        string cur = "";
        for (char e : equation) {
            if (e == 'x') {
                int num = cur.empty() ? 1 : atoi(cur.c_str()); // 取出来x前边的数字比如2x的2
                k = k + (neg * left) * num;
                cur = "";
            } else if (e == '+' || e == '-' || e == '=') {
                if (!cur.empty()) {
                    int num = atoi(cur.c_str());
                    b = b - (neg * left) * num;
                }
                neg = 1;
                if (e == '=') left = -1;    // 只变一次
                else if (e == '-') neg = -1;
                cur = "";
            } else {
                cur += e;
            }
        }

        if (!cur.empty())
            b = b - neg * left * atoi(cur.c_str());

        if (k == 0) return b == 0 ? "Infinite solutions" : "No solution";
        return "x=" + to_string(b / k);
    }
};