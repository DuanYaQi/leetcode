class CountIntervals {
    typedef pair<int, int> pii; //先存right 再存left

    int ans = 0;
    set<pii> st;    // 存（右端点，左端点）    因为主要是为了找右端点进行比较

public:
    CountIntervals() {

    }
    
    void add(int left, int right) {
        // 只有满足下面条件才能插入并计算
        // 存在两个相邻集合A(ALeft, ARight)和B(BLeft, BRight) 
        // 条件一: left > ARight
        // 条件二: right < BLeft

        auto it = st.lower_bound(pii(left, -1e-9)); // 找到第一个 A 满足 ARight 比 left 大  满足条件一 (10, 7)
        while (it != st.end()) {             // 如果找到了
            if (right < it->second) break;   // 判断 right 是否小于 BLeft，及要求满足条件二跳出 

            /*合并区间*/
            left = min(left, it->second);    // min(5, 7) = 5
            right = max(right, it->first);   // max(8, 10) = 10
            ans -= (it->first - it->second + 1);
            st.erase(it++);
        }        

        st.insert(pii(right, left));
        ans += right - left + 1;

        return;
    }        
    
    int count() {
        return ans;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */