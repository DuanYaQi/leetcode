class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> ump;

        for (int i = 0; i < nums.size(); ++i) {
            ump[nums[i]]++;
        }

        vector<pair<int, int>> vecs(ump.begin(), ump.end());
        sort(vecs.begin(), vecs.end(), cmp);

        vector<int> res;
        for (int i = 0; i < k; i++) {
            res.push_back(vecs[i].first);
        }

        return res;
    }
private:
    static bool cmp(pair<int, int> &p1, pair<int, int> &p2) {
        return p1.second > p2.second;
    }    
};