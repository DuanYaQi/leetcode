class Solution {
public:
    void eval() {
        long long b = nums.top(); nums.pop();
        long long a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();

        long long res = 0;
        switch (op) {
            case '+':   res = a + b; break;
            case '-':   res = a - b; break;
            case '*':   res = a * b; break;
            case '/':   res = a / b; break;
            case '%':   res = a % b; break;
            case '^':   res = pow(a, b); break;
        }

        nums.push(res);
    }

    int calculate(string s) {
        nums.push(0); // 从0开始计算
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] == ' ') continue;
            if (isdigit(s[i])) {    // 是数字
                int res = 0;
                do {
                    res = res * 10 + s[i++] - '0';
                } while (i < n && isdigit(s[i]));
                i--;
            } else {
                if (s[i] == '(') {
                    ops.push(s[i]);
                } else if (s[i] == ')') {   // 计算与上一个 ( 之间的值
                    while (ops.top() != '(') {
                        eval();
                    }
                    ops.pop();  // 弹出 (
                } else {        // 新计算符入栈， 要先把栈内能计算的都算掉
                    char nowOp = s[i];
                    while (!ops.empty() && ops.top() != '(' && ump[ops.top()] >= ump[nowOp]) {
                        eval();
                    }
                    ops.push(nowOp);
                }
            }
        }

        while (!ops.empty() && ops.top() != '(') {
            eval();
        }

        return nums.top();
    }

private:
    stack<long long> nums;//存数字
    stack<char> ops;    
    
    unordered_map<char, int> ump = {
        {'-', 1},
        {'+', 1},
        {'*', 2},
        {'/', 2},
        {'%', 2},
        {'^', 3},
    };
};