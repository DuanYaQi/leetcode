class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int rightmax = 0;                   // 目前能跳到的最远位置
        int res = 0;
        int end = 0;                        // 上次跳跃可达范围右边界下次的最右起跳点
        for (int i = 0; i < n - 1; ++i) {   // 不遍历到最后一点 因为假设你总是可以到达数组的最后一个位置。
            if (i <= rightmax) {        
                rightmax = max(rightmax, i + nums[i]);                
                
                if (i == end) {         // 到达上次跳跃能到达的右边界了
                    end = rightmax;     // 目前能跳到的最远位置变成了下次起跳位置的右边界
                    res++;              // 进入下一次跳跃
                }
            }
        }

        return res;
    }
};



int jump(vector<int>& nums) {
    int n = nums.size();

    int cnt = 0;
    int flag = n-1;	// 当前倒推到的位置
	
    while (flag > 0) {	// = 0时倒退结束

        for (int i = 0; i <= flag; ++i) {
            if (i + nums[i] >= flag) {
                flag = i;  
                break;
            }
        }

        cnt++;
    }

    return cnt;        
}