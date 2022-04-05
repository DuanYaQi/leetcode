class Solution {
public:
    unordered_map<char, int> ump = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };

    stack<int> nums;
    stack<char> ops;
    
    void eval() {
        int b = nums.top(); nums.pop();
        int a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();

        int res;
        switch (op) {
            case '+' : res = a + b; break;
            case '-' : res = a - b; break;
            case '*' : res = a * b; break;
            case '/' : res = a / b; break;
        }

        nums.push(res);
        return;
    }

    int calculate(string s) {
        nums.push(0);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') continue;

            if (isdigit(s[i])) {    // NUM
                int res = 0;
                while (i < s.size() && isdigit(s[i]) ){
                    res = res * 10 + (s[i++] - '0');
                }
                i--;
                nums.push(res);
             } else {    //op
                if (s[i] == '(') {
                    ops.push(s[i]);
                } else if (s[i] == ')') {
                    while (ops.top() != '(') {
                        eval();
                    }
                    ops.pop();
                } else {
                    while (!ops.empty() && ops.top() != '(' && ump[ops.top()] >= ump[s[i]]) {
                        eval();
                    }
                    ops.push(s[i]);
                }
            }
        }

        while (!ops.empty() && ops.top() != '(') {
            eval();
        }
        return nums.top();
    }   
};