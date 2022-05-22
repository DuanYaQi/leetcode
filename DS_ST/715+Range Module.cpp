class RangeModule {
    typedef pair<int, int> pii;
    set<pii> st;
    
public:
    RangeModule() {
        /*因为插入、跟踪、删除全是半开区间，那就跟全开区间没区别*/
    }
    
    void addRange(int left, int right) {
        auto it = st.lower_bound(pii(left, -1e-9)); // 找第一个可以合并的区间

        while (it != st.end()) {        // 逐个合并
            auto [R, L] = *it;
            if (L > right)  break;      // 后面的不能合并了，提前退出循环
            left = min(left, L);
            right = max(right, R);
            st.erase(it++);
        }

        st.insert(pii(right, left));    // 把合并后的区间插入set，注意是{R, L}
    }
    
    bool queryRange(int left, int right) {
        auto it = st.lower_bound(pii(left, -1e-9)); // 找第一个可能包含[left, right)的区间

        if (it == st.end()) return false;           // 没有找到，直接返回false
        
        auto [R, L] = *it;
        if (L <= left && right <= R) return true;   // 判断这个区间是否包含所要查询的区间
        else return false;
    }
    
    void removeRange(int left, int right) { 
        auto it = st.lower_bound(pii(left, -1e-9)); // 找第一个可能包含[left, right)的区间
        int l1, r1, l2, r2; 
        bool flagL = false, flagR = false;
        while (it != st.end()) {
            auto [R, L] = *it;
            if (L > right) break;   // 后面的区间不用删了，提前退出循环
            
            if (left > L) {         // 部分区间在left的左边，此时需要添加多删除的部分区间
                flagL = true;
                l1 = L;
                r1 = left;
            }

            if (right < R) {        // 部分区间在right的右边，此时需要添加多删除的部分区间
                flagR = true;
                l2 = right;
                r2 = R;
            }
            st.erase(it++);         // 移除该区间
        }

        if (flagL) st.insert({r1, l1}); // 部分区间在left的左边，此时需要添加多删除的部分区间
        if (flagR) st.insert({r2, l2}); // 部分区间在right的右边，此时需要添加多删除的部分区间
        return;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 * 
["RangeModule","addRange","addRange","addRange","removeRange","queryRange","queryRange","queryRange"]
[[],[10,20],[20,25],[26,30],[14,16],[10,14],[13,15],[16,17]]
 */