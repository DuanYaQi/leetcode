class Solution {
public:
    string simplifyPath(string path) {
        vector<string> vec; //保存分解的path
        string tmp = "/";

        // 分解path 以/为分界线  1个/////分开保存为5个/
        for (int i = 1; i < path.size(); ++i) {
            if (path[i] == '/') {
                vec.push_back(tmp);
                tmp = "/";
            } else {
                tmp += path[i];
            }
        }
        // 结尾不为/时，需要把最后的tmp加进去
        if (tmp != "/") {
            vec.push_back(tmp);
        }
        
        stack<string> st;   //用来解析path
        // 处理已经分解的path
        for (int i = 0; i < vec.size(); ++i) {
            if (vec[i] == "/." || vec[i] == "/") {  // 如果为/.或者/ 直接不处理
                continue;
            } else if (vec[i] == "/.." && !st.empty()) {  // 如果为/.. 且栈不为空，则返回上一路径，即栈pop
                st.pop();
                continue;   
            } else if (vec[i] == "/.." && st.empty()) {   // 如果为/.. 且栈不为空 
                continue;   //从根目录向上一级是不可行的，因为根目录是你可以到达的最高级，什么也不执行
            }
            st.push(vec[i]);//正常情况添加路径
        }
        
        if (st.empty()) return "/"; //如果栈为空，则返回根目录

        string res;
        while (!st.empty()) {      //合并目录，栈内元素在前。
            res = st.top() + res;
            st.pop();
        }
        
        return res;
    }
};