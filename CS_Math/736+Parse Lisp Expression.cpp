class Solution {
public:
    int parseInt(const string &expression, int &start) {
        int res = 0, sign = 1;
        if (expression[start] == '-') { //负号
            sign = -1;
            start++;
        }

        //不超范围并且是数字
        while (start < expression.size() && isdigit(expression[start])) { 
            res = res * 10 + (expression[start] - '0');
            start++;
        }

        return sign * res;
    }

    string parseVar(const string &expression, int &start) {
        string res;
        
        // 不超范围并且不是空格也不是右括号
        while (start < expression.size() && expression[start] != ' ' && expression[start] != ')') {
            res.push_back(expression[start]);
            start++;
        }

        return res;
    }

    // 解析结算 start 开始的解析式
    int innerEvaluate(const string &expression, int &start) {
        if (expression[start] != '(') {         // 非表达式可能为: 整数或变量
            if (islower(expression[start])) {   // 变量
                string var = parseVar(expression, start); 
                return scope[var].back();
            } else {                            // 整数
                return parseInt(expression, start);
            }
        }

        int res;
        start++;    //跳过左括号
        if (expression[start] == 'l') {     // "let" 表达式
            start += 4;                     // 移除 "let "
            vector<string> vars;
            while (true) {
                if (!islower(expression[start])) {          // 如果不是数字，也不是空格，也不是'('
                    res = innerEvaluate(expression, start); // let 表达式之后的 expr 的表达式的值
                    break;                                  // 计算后直接 break
                }
                string var = parseVar(expression, start);
                if (expression[start] == ')') {
                    res = scope[var].back();                // let 表达式的最后一个 expr 表达式的值
                    break;
                }
                vars.push_back(var);
                start++;    // 移除空格
                int e = innerEvaluate(expression, start);
                scope[var].push_back(e);
                start++;    // 移除空格
            }

            for (auto var : vars)
                scope[var].pop_back();  // 清除当前作用域的变量
        } else if (expression[start] == 'a') {              // "add" 表达式
            start += 4;     // 移除 "add "
            int e1 = innerEvaluate(expression, start);
            start++;        // 移除空格
            int e2 = innerEvaluate(expression, start);
            res = e1 + e2;
        } else {                                            // "mult" 表达式
            start += 5;     // 移除 "mult "
            int e1 = innerEvaluate(expression, start);
            start++;        // 移除空格
            int e2 = innerEvaluate(expression, start);
            res = e1 * e2;
        }   
        start++;            // 移除右括号
        return res;
    }

    int evaluate(string expression) {
        int start = 0;
        return innerEvaluate(expression, start);
    }  

private:
    unordered_map<string, vector<int>> scope;
};