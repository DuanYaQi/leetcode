# N数之和

返回下标不能排序，返回值可以排序

## 1. 两数之和

**返回的是下标**

找是否存过了

```c++
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> ump; //key-value 数值-索引

    for (int i = 0; i < nums.size(); ++i) {
        int num = target - nums[i];
        if (ump.count(num)) {
            return {ump[num], i};
        }

        ump[nums[i]] = i;
    }

    return {0, 0};
}
```







## 15. 三数之和

**返回的是值**

可以从小到大枚举 b，**同时**从大到小枚举 c，即**第二重循环和第三重循环实际上是并列的关系**。

每次 a 变了之后 要重新从尾部开始枚举c

```c++
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) break;
        if (i > 0 && nums[i] == nums[i-1])  continue;


        int j = i + 1, k = nums.size() - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum < 0) {
                j++;
            } else if (sum > 0) {
                k--;
            } else {
                res.push_back({nums[i], nums[j], nums[k]});
                j++;
                while(nums[j] == nums[j-1] && j < k) j++;// 很关键 去重
            }
        }
    }
    return res;
}
```





## 16. 最接近的三数之和

```c++
int res = 1e9;

void update(int cur, int target) {
    if (abs(cur - target) < abs(res - target)) {
        res = cur;
    }
}

int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ++i) {
        if (i > 0 && nums[i] == nums[i-1]) continue;

        int j = i + 1, k = nums.size() - 1;

        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            update(sum, target);
            if (sum - target < 0) {
                j++;
            } else if (sum - target > 0){
                k--;
            } else {
                return sum;
            }
        }
    }

    return res;
}
```







## 18. 四数之和

```c++
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> res;

    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); ++i) {
        if (i > 0 && nums[i] == nums[i-1]) continue;

        for (int j = i + 1; j < nums.size(); ++j) {
            if (j > i+1 && nums[j] == nums[j-1]) continue;

            int m = j + 1, n = nums.size() - 1;


            while (m < n) {
                long long sum = (long long)nums[i] + (long long)nums[j] + (long long)nums[m] + (long long)nums[n];
                if (sum - target < 0) {
                    m++;
                } else if (sum - target > 0) {
                    n--;
                } else {
                    res.push_back({nums[i], nums[j], nums[m], nums[n]});
                    m++;
                    while(nums[m] == nums[m-1] && m < n) m++;	// 很关键去重
                }
            }
        }
    }

    return res;
}
```







---

# 买卖股票



