class MyStack {
public:
    MyStack() {

    }
    
    void push(int x) {
        mqT = mqO;
        mqO = queue<int>();     // 置空
        mqO.push(x);            // 把x加入队首
        while (mqT.size()) {    // 把原来的结点，再加进去
            int num = mqT.front(); mqT.pop();
            mqO.push(num);
        }
    }
    /*只用一个队列*/
    void push2(int x) { 
        int size = mqO.size();

        mqO.push(x);
        for (int i = 0; i < size; ++i) {
            mqO.push(mqO.front()); mqO.pop();
        }
        return;
    }
    
    int pop() {
        int num = mqO.front(); mqO.pop();
        return num;
    }
    
    int top() {
        return mqO.front();
    }
    
    bool empty() {
        return mqO.empty();
    }

private:
    queue<int> mqT;
    queue<int> mqO;    
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */