class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<pair<int, int>> st; //存当前的函数调用的 起始时间，因为一定是配对的，所以不用存 function_id

        vector<int> res(n, 0);
        for (auto &s : logs) {
            int func_id, time;
            char str[6];
            sscanf(s.c_str(), "%d:%[^:]:%d", &func_id, str, &time);


            if (str[0] == 's') { // start
                if (!st.empty()) {  // 如果栈不为空, 说明是函数1里又调用了函数2, 需要计算时间函数1的前半部分的时间
                    res[st.top().first] += time - st.top().second;
                }
                st.emplace(func_id, time);      // start time
            } else {        // end
                auto [curFuncId, startTime] = st.top(); st.pop();
                res[curFuncId] += time - startTime + 1; 
                if (!st.empty()) {  // 如果栈不为空, 说明是函数1里调用的函数2完毕, 需要计算时间函数1的后半部分的时间，因此需要将时间更新为后半部分的起始时间
                    st.top().second = time + 1;
                }
            }
        }
    
        return res;
    }
};