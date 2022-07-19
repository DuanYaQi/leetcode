typedef pair<int, string> pis;

class Solution {
public:
    int getDigit() {
        int res = 0;
        while (ptr < src.size() && isdigit(src[ptr])) {
            res = res * 10 + src[ptr] - '0';
            ptr++;
        }
        return res;
    }

    string getString() {    
        if (ptr == src.size() || src[ptr] == ']') {
            return "";  //String -> eps
        }

        string res;             // 最后返回的结果
        char cur = src[ptr];    // ptr下标的字符

        if (isdigit(cur)) {
            // String -> Digits[String] String
            // 解析 Digits 
            int times = getDigit(); //字符串乘的次数
            // 过滤左括号
            ++ptr;
            // 解析 string
            string str = getString();
            // 过滤右括号
            ++ptr;
            // 字符串累乘
            while(times--) 
                res += str;
        } else if (isalpha(cur)) {
            // String -> Alpha String
            // 解析 Alpha
            res = src[ptr++];
        }

        return res + getString();       
        // 能走到这一步说明完成了一个k[]表达式
        // 但后边可能还有k[]表达式, 所以要继续递归并且把后边的结果拼接起来
    }

    string decodeString(string s) {
        src = s;
        ptr = 0;
        return getString();
    }

private:
    string src;
    size_t ptr;
};