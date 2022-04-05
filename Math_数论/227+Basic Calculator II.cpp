class Solution {
public:
    unordered_map<char, int> ump = {
        {'-', 1},
        {'+', 1},
        {'*', 2},
        {'/', 2},
        {'%', 2},
        {'^', 3},
    };

    stack<long long> nums;
    stack<char> ops;

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
        nums.push(0);
        replace(s.begin(),s.end(),' ','');
        
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') continue;
            if (isdigit(s[i])) {    // 数字
                int res = 0;
                while (i < s.size() && isdigit(s[i])) {
                    res = res * 10 + (s[i++] - '0');
                }
                nums.push(res);
                i--;
            } else {    // 运算符
                if (s[i] == '(') {
                    ops.push(s[i]);
                } else if (s[i] == ')') {   // 计算该括号内内容
                    while (ops.top() != '(') { // 找到前一个 ( 并算其中的值
                        eval();
                    }
                    ops.pop();
                } else {
                    // 有一个新操作要入栈时，先把栈内可以算的都算了 
                    // 但注意的是 只有满足「栈内运算符」比「当前运算符」优先级高/同等，才进行运算
                    while (!ops.empty() && ops.top() != '(' && ump[ops.top()] >= ump[s[i]]) {
                        eval();
                    }
                    ops.push(s[i]);
                }
            }
        }

        while(!ops.empty() && ops.top() != '(') {
            eval();
        }

        return nums.top();
    }
};