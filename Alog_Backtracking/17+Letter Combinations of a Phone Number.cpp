class Solution {
public:
    vector<string> res;
    string resT;

    char a[10][4] = {{}, {}, {'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}, 
                    {'j', 'k', 'l'}, {'m', 'n', 'o'}, {'p', 'q', 'r', 's'}, {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'} };

    void dfs(string &digits, int start){
        if (resT.size() == digits.size()) {
            res.push_back(resT);
            return;
        }

        for (int i = start; i < digits.size(); ++i) {
            int number = digits[i] - '0';
            for (int j = 0; j <= 3; ++j) {
                char c = a[number][j];
                if (c != '\000') {          //char数组 没有初始化均为\000
                    resT.push_back(c);
                    dfs(digits, i+1);
                    resT.pop_back();
                }
            }
        }   


        return;     
    }

    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return res;     
          
        dfs(digits, 0);

        return res;
    }
};