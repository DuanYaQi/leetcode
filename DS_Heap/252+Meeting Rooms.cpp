class Solution {
public: 
    static bool cmp (const vector<int> &vec1, const vector<int> &vec2) {
        return vec1[0] < vec2[0];
    }

    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return true;

        sort(intervals.begin(), intervals.end(), cmp);

        priority_queue<int, vector<int>, greater<int>> pq;  // 结束时间小顶堆
        pq.emplace(intervals[0][1]);

        for (int i = 1; i < intervals.size(); ++i) {
            int start = intervals[i][0], end = intervals[i][1];
            int p = pq.top();
            if (start < p) {
                return false;
            }

            pq.pop();
            pq.emplace(end);
        }   

        return true;

    }
};