class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int fast = 0, slow = 0;
        int res = 0;
        int cha = INT_MAX;
        for (; fast < nums.size(); fast++) {
            if (res < target) {
                res += nums[fast];
                if (res >= target) {
                    while (res >= target) {
                        if (res - nums[slow] >= target) {
                            res -= nums[slow];
                            slow++;
                        } else {
                            break;
                        }
                    }

                    cha = min(cha, fast - slow + 1);
                }
            } else {
                res += nums[fast];
                while (res >= target) {
                    if (res - nums[slow] >= target) {
                        res -= nums[slow];
                        slow++;
                    } else {
                        break;
                    }
                }

                cha = min(cha, fast - slow + 1);
            }
        }

        if (cha == INT_MAX)
            return 0;
            
        return cha;
    }
};



int main () {
    int target;
    cin >> target;
    int string;
    
    vector<int> nums(6);
    for (int i = 0; i < 6; i++) {
        cin >> nums[i];
    }

    int res = minSubArrayLen(target, nums);

    return res;
}

/***************优化后*********************/

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int fast = 0, slow = 0;
        int res = 0;
        int cha = INT_MAX;
        for (; fast < nums.size(); fast++) {
            res += nums[fast];
            while (res >= target) {
                cha = min(cha, fast - slow + 1);
                res -= nums[slow++];
            }
        }

        if (cha == INT_MAX)
            return 0;

        return cha;
    }
};