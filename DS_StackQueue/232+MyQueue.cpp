class MyQueue {
public:
    MyQueue() {

    }
    
    void push(int x) {
        mStT = stack<int>();
        while (mStO.size()) {                   // 把 mStO 里的内容翻转到 mStT 中
            int num = mStO.top(); mStO.pop();
            mStT.push(num);
        }
        
        mStO.push(x);                           // x 入栈底

        while (mStT.size()) {                   // 再翻转回来
            int num = mStT.top(); mStT.pop();
            mStO.push(num);
        }
    }
    
    int pop() {
        int num = mStO.top(); mStO.pop();
        return num;
    }
    
    int peek() {
        return mStO.top();
    }
    
    bool empty() {
        return mStO.empty();
    }

private:    
    stack<int> mStO;
    stack<int> mStT;     
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */