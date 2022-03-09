class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        _qu1.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int res = _qu1.back();
        int size = _qu1.size(); 
        while ( size - 1 != 0 ) { //要留最后一个元素去除
            _qu2.push(_qu1.front());
            _qu1.pop();
            size--;
        }

        _qu1.pop();
        _qu1 = _qu2;

        while (!_qu2.empty()) {
            _qu2.pop();
        }
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return _qu1.back();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return _qu1.empty();
    }

private:
    queue<int> _qu1;
    queue<int> _qu2;
};