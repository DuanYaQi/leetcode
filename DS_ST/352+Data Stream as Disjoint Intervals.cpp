class SummaryRanges {
    typedef pair<int, int> pii;
    set<pii> st;
    
public:
    SummaryRanges() {

    }
    
    void addNum(int val) {
        // 找到两个连续的区间
        int left = val, right = val;
        auto it = st.lower_bound(pii(left-1, -1e9));

        while (it != st.end()) {
            if (it->second > right+1) break;
            left = min(left, it->second);
            right = max(right, it->first);
            st.erase(it++);
        }


        st.insert(pii(right, left));

        /*合并相连的区间*/

    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> ans;
        for (auto p : st) {
            ans.push_back({p.second, p.first});
        }
        return ans;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */