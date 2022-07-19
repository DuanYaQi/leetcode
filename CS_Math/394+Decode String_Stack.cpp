class Solution {
public:
    int getDigit(string &src, size_t &ptr) {
        int res = 0;
        while (ptr < src.size() && isdigit(src[ptr])) {
            res = res * 10 + src[ptr] - '0';
            ptr++;
        }
        return res;
    }

    string decodeString(string s) {        
        stack<int> numSt;
        stack<string> stringSt;
        string res;
        int numT;
        size_t ptr = 0; 

        while (ptr < s.size()) {
            char cur = s[ptr];

            if (cur == '[') {
                ptr++;
                numSt.push(numT);
                stringSt.push(res);
                res = "";
            } else if (cur == ']') {
                ptr++;
                string tmpSrc;
                int times = numSt.top(); numSt.pop();
                while (times--) //复制字符串res
                    tmpSrc += res;
                res = stringSt.top() + tmpSrc; stringSt.pop(); //把他拼到前一个字符串上，并且重新赋值给 res，相当于解耦]右括号
            } else if (isdigit(cur)) {
                numT = getDigit(s, ptr);
            } else if (isalpha(cur)) {
                ptr++;
                res += cur;
            }  
        } 

        return res;
    }
};