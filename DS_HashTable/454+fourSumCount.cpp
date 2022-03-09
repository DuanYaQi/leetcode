class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        std::unordered_map<int, int> umap;
        int count = 0;
        // 遍历a b 计算所有的 a + b 统计出现的次数
        for (int a : nums1) {
            for (int b : nums2) {
                umap[a + b]++;
            }
        }

        for (int c : nums3) {
            for (int d : nums4) {
                auto iter = umap.find(0 - c - d);
                if (iter != umap.end()) {
                    count += iter->second; //加上出现的次数
                }
            }
        }
        return count;
    }
};