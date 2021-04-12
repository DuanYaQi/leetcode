class Solution {
public:
    class MyQueue {//单调队列（从大到小）
        public:
            deque<int> que;// 使用deque来实现单调队列

            // 如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作   // 同时pop之前判断队列当前是否为空。
            void pop(int value) {
                if (!que.empty() && value == que.front()) {
                    que.pop_front();
                }
            }
 
            //如果push的元素value大于入口元素的数值，那么就将队列入口的元素弹出，直到push元素的数值小于等于队列入口元素的数值为止。这样就保持了队列里的数值是单调从大到小的了。
            void push(int value) {
                while (!que.empty() && value > que.back()) {
                    que.pop_back();
                }
                que.push_back(value);
            }

            // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
            int front() {
                return que.front();
            }
    };
    
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> res;
        for (int i = 0; i < k; i++) { // 先将前k的元素放进队列
            que.push(nums[i]);
        }

        res.push_back(que.front()); // result 记录前k的元素的最大值
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]); // 滑动窗口移除最前面元素
            que.push(nums[i]); // 滑动窗口前加入最后面的元素
            res.push_back(que.front()); // 记录对应的最大值
        }
        return res;
    }

};