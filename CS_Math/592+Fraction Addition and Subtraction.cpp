typedef long long ll;

class Solution {             // 线段树不一定满二叉树，也不一定是完全二叉树，但一定是平衡二叉树
public:
    string fractionAddition(string expression) {
        string res;

        queue<int> signQ;
        queue<ll> upN, downN;


        // 单独处理首元素
        if (isdigit(expression[0])) 
            signQ.push(1);

        for (int i = 0; i < expression.size(); ) {
            char c = expression[i];
            if (c == '-' || c == '+') {
                signQ.push(c == '+' ? 1 : -1);
            } else if (isdigit(c)) {
                ll upNum = 0;

                /* 找数字 */
                do {
                    upNum = upNum * 10 + expression[i] - '0';
                    i++;
                } while (isdigit(expression[i]));
                
                i++; // 跳过 '/'

                ll downNum = 0;
                /* 找数字 */
                do {
                    downNum = downNum * 10 + expression[i] - '0';
                    i++;
                } while (isdigit(expression[i]));

                upN.push(upNum);
                downN.push(downNum);
                continue;
            }
            ++i;
        }

        ll denominator = 0, numerator = 1;              // 累乘的基分子，分母
        ll sign = 1, denominatorT = 0, numeratorT = 1;   // 获取到的分子和分母
        while (signQ.size()) {
            sign = signQ.front(); signQ.pop();
            denominatorT = upN.front(); upN.pop();
            numeratorT = downN.front(); downN.pop();

            denominator = denominator * numeratorT + sign * denominatorT * numerator;
            numerator *= numeratorT;
        }   

        if (denominator == 0) {
            return "0/1";
        }

        long long g = __gcd(abs(denominator), numerator); // 获取最大公约数
        return to_string(denominator / g) + "/" + to_string(numerator / g);
    }

};