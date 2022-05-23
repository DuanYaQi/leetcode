typedef pair<int, int> pii;
class MinStack {
    stack<pii> st;

public:
    MinStack() {

    }
    
    void push(int val) {
        if (!st.size()) {
            st.push(pii{val, val});
            return;
        } 

        auto [tmp, minn] = st.top(); 
        if (minn > val) {
            st.push(pii{val, val});
        } else {
            st.push(pii{val, minn});
        }
        return;
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {  
        return st.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */