class Solution {
public:
    //小顶堆比较方式
    class mycomparsion {
    public:
        bool operator () (const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.second > rhs.second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparsion> pri_que;
        for (unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
            pri_que.push(*it);
            if (pri_que.size() > k) {
                pri_que.pop();
            }
        } 
        vector<int> res(k);
        for (int i = k - 1; i >= 0; i--) {
            res[i] = pri_que.top().first;
            pri_que.pop();
        }
        return res;
    }
};