int findPairs(vector<int>& nums, int k) {
    /*负数映射到正数区间*/
    int minn = *min_element(nums.begin(), nums.end());

    if (minn < 0) {
        for (auto &n : nums) {
            n += abs(minn);
        }
    }

    sort(nums.begin(), nums.end());
	/* k == 0 用 hashmap */
    if (k == 0) {
        unordered_map<int, int> ump;
        for (int i = 1; i < nums.size(); ++i) {
            if (ump.count(nums[i]) == 0) {
                if (nums[i] == nums[i-1]) ump[nums[i]] = 1;
            }
        } 
        return ump.size();
    } 
	
    /*k != 0 用二分找*/
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    int cnt = 0;
    for (int j = 1; j < nums.size(); ++j) {
        auto find = lower_bound(nums.begin(), nums.end(), nums[j] - k);
        if (find != nums.end()) {
            int idx = find - nums.begin();
            if (nums[idx] == nums[j] - k) cnt++;
        }
    }

    return cnt;
}