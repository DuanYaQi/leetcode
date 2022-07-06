enum ExprStatus {
    VALUE = 0,  //  初始状态
    NONE,       //  表达式类型未知
    LET,        //  let 表达式
    LET1,       //  let 表达式已经解析了 vi 变量
    LET2,       //  let 表达式已经解析了最后一个表达式 expr
    ADD,        //  add 表达式
    ADD1,       //  add 表达式已经解析了 e1 表达式
    ADD2,       //  add 表达式已经解析了 e2 表达式
    MULT,       //  mult 表达式
    MULT1,      //  mult 表达式已经解析了 e1 表达式
    MULT2,      //  mult 表达式已经解析了 e2 表达式
    DONE        //  解析完成
};

struct Expr {
    ExprStatus status;
    string var;         // let 的变量 vi
    int value;          // VALUE 状态的数值，或者 LET2 状态最后一个表达式的数值
    int e1, e2;         // add 或 mult 表达式的两个表达式 e1 和 e2 的数值

    Expr(ExprStatus s) {
        status = s;
    }
};

class Solution {
public:
    int calculateToken(const string &token) {
        if (islower(token[0])) {
            return scope[token].back();     // 去 scope 里找 let 赋给v的值e
        } else {
            return stoi(token);
        }
    }


    int evaluate(string expression) {
        vector<vector<string>> vars;
        int start = 0, n = expression.size();
        stack<Expr> s;
        Expr cur(VALUE);

        while (start < n) {
            if (expression[start] == ' ') {
                start++;        // 去空格
                continue;
            }
            if (expression[start] == '(') {
                start++;        // 去左括号
                s.push(cur);    // 全部放到 stack 中 完了找到右括号一个一个算回来
                cur = Expr(NONE);
                continue;
            }

            string token;

            if (expression[start] == ')') { // 本质上是把表达式转成一个 token
                start++;
                if (cur.status == LET2) {
                    token = to_string(cur.value);

                    for (auto var : vars.back())    // 清除该层的作用域
                        scope[var].pop_back();
                    
                    vars.pop_back();
                } else if (cur.status == ADD2) {
                    token = to_string(cur.e1 + cur.e2);     // add 后的值被 token 存着
                } else {
                    token = to_string(cur.e1 * cur.e2);
                }
                cur = s.top();  // 获取上层状态
                s.pop();        // 弹出现在层的状态
            } else {
                while (start < n && expression[start] != ' ' && expression[start] != ')') { //这里循环加入表达式比如 let/add/mult
                    token.push_back(expression[start]);
                    start++;
                }
            }

            switch (cur.status) {
                case VALUE:
                    cur.value = stoi(token);
                    cur.status = DONE;
                    break;
                case NONE:
                    if (token == "let") {
                        cur.status = LET;
                        vars.emplace_back();    // 记录该层作用域的所有变量，方便后续清除,该层的所有变量都在这个{}中
                    } else if (token == "add") {
                        cur.status = ADD;
                    } else if (token == "mult") {
                        cur.status = MULT;
                    }
                    break;
                case LET:
                    if (expression[start] == ')') { // let 表达式最后一个 expr 表达式
                        cur.value = calculateToken(token);
                        cur.status = LET2;
                    } else {
                        cur.var = token;                // x/y
                        vars.back().push_back(token);   // 记录该层作用域的所有变量，方便后续清除 放入#90创建的{}
                        cur.status = LET1;
                    }
                    break;
                case LET1:
                    scope[cur.var].push_back(calculateToken(token));        // 把 var 变量名的值存入 scope 中
                    cur.status = LET;
                    break;
                case ADD:
                    cur.e1 = calculateToken(token);
                    cur.status = ADD1;
                    break;
                case ADD1:
                    cur.e2 = calculateToken(token);
                    cur.status = ADD2;
                    break;
                case MULT:
                    cur.e1 = calculateToken(token);
                    cur.status = MULT1;
                    break;
                case MULT1:
                    cur.e2 = calculateToken(token); // (let x 3 y 4 (add x y)) 的结果被 token 存着，继续与x进行mult
                    cur.status = MULT2;
                    break;
            }
        }

        return cur.value;
    }
private:
    unordered_map<string, vector<int>> scope;   
    // scope 存 let 赋给 v 的值 e
    // unordered_map<string v, int e>
};