class Solution {
public:
    static bool cmp(const vector<int> &v1, const vector<int> &v2) {
        return v1[0] < v2[0];
    }

    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);  // 按照 开始时间 对会议进行排序
        // 不能按照结束时间对会议进行排序  hack [[2,15],[36,45],[9,29],[16,23],[4,9]]
        int cnt = 1;

        priority_queue<int, vector<int>, greater<int>> pq; //小顶堆 greater大了就沉下去
        pq.emplace(intervals[0][1]);

        for (int i = 1; i < intervals.size(); ++i) {
            int start = intervals[i][0], end = intervals[i][1];
            int q = pq.top();

            if (start >= q) pq.pop();
            else cnt++;
                        
            pq.emplace(end);
        }

        return cnt;
    
    }   

};