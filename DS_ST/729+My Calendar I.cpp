typedef pair<int, int> pii;
class MyCalendar {
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        auto it = st.lower_bound(pii(end, -1e-9)); // 找到第一个 A 满足 ARight 比 start 大

        if (it == st.begin() || (--it)->second <= start) {
            st.insert({start, end});
            return true;
        }
        
        return false;
    }

private:
    set<pii> st;    
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */