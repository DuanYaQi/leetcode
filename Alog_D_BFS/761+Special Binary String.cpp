class Solution {
public:
    string dfs(string &str) {  // str 为一个新的山峰
        vector<string> m;
        int n = str.size(), h = 0, f = 0, l = 0;
        for (int i = 0; i < n; ++i) {                       // 分割出每个子山峰，h=0为分界点
            if (str[i] & 1) h++;        // '1' 高度加 1
            else {                      // '0' 高度减 1
                f = 1;                  // f 用来标记 h=1 是上升的，还是下降的
                h--;                    // h-- 说明已经开始下降了
            }
            if (h == 1) {               // 出现特殊子串
                if (!f) l = i + 1;      // 上升时 h=1, 标记左端点
                else {                  // 下降时 h=1, 标记右端点
                    m.push_back(str.substr(l, i - l + 1));  // 一个山峰，特殊的子串
                    l = i + 1; f = 0;                       // 更新左端点和标志位
                }
            }
        }

        // 对于每个特殊子串为一个新山峰，继续处理，处理指的是找特殊子串，排序
        for (string &s : m)
            s = dfs(s);

        // 将str的每个特殊子串排序，保证大的在前边，字典序就会更大
        sort(m.begin(), m.end(), [](string &s1, string &s2) {
            return s1 > s2;
        });

        // 排序后，将str的特殊子串重组一下，形成新的str返回
        // 除特殊子串外，开始和结尾都会剩一个字符，分别是'1'和'0', 我们加上就行了
        string ans;
        ans += str[0];
        for (string &s : m)
            ans += s;
        
        ans += str[n - 1];
        return ans;
    }

    string makeLargestSpecial(string s) {
        int h = 0, n = s.size(), l = 0;
        vector<string> m;
        for (int i = 0; i < n; ++i) {   // 分割出每个山峰，h=0为分界点
            if (s[i] & 1) h++;
            else h--;
            if (h == 0) {
                m.push_back(s.substr(l, i - l + 1)); // 一个山峰，特殊的子串
                l = i + 1;              // 更新左端点
            }
        }
        
        // 对于每个山峰(特殊子串) 的子峰排序重组，高度大的在前边，保证字典序最大
        for (string& str : m)
            str = dfs(str);
        
        // 将str的每个特殊子串排序，保证大的在前边，字典序就会更大
        sort(m.begin(), m.end(), [](string &s1, string &s2) {
            return s1 > s2;
        });

        // 排序后，将str的特殊子串重组一下，形成新的str返回
        // 除特殊子串外，开始和结尾都会剩一个字符，分别是'1'和'0', 我们加上就行了
        string ans;
        for (string &s : m)
            ans += s;

        return ans;
    }
};
//小结论：
//1. 任何一个1后边都会有特殊子串
//2. 任何特殊子串都是以1开始的
//3. 交换后还是特殊的
