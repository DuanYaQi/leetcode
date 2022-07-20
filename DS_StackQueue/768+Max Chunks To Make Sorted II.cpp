class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        stack<int> st;
        st.push(arr[0]);

        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] >= st.top()) {
                st.push(arr[i]);
            } else {
                int head = st.top(); st.pop();  // 先把头部取出来
                while (st.size() != 0 && arr[i] < st.top()) { // 合并比他大的数
                    st.pop();
                }
                st.push(head);
            }
        }

        return st.size();
    }
};