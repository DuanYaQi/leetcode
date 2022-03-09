class Solution {
public:
    bool isValid(string s) {
        stack<int> st;

        for (int i = 0; i < s.size(); i++) {
            // 三个左
            if (s[i] == '(') st.push(')');
            else if (s[i] == '{') st.push('}');
            else if (s[i] == '[') st.push(']');
            // 三个右
            else if (st.empty() || s[i] != st.top()) return false; // 为右括号且不为空 返回false； 为右括号且与栈顶元素不同，即不对应
            else if (s[i] == st.top()) st.pop(); //为右且前一个为对应的左，pop出
            else st.push(s[i]);
        }

        return st.empty();
    }
};