class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> preSum(n + 1, 0);
        unordered_map<int, int> ump;

        ump[0] = 1;
        int tmp, cnt = 0;
        for (int i = 1; i <= nums.size(); ++i) {
            preSum[i] = preSum[i-1] + nums[i-1];
            // 处理负数 把求余数都归到一边  sum取模后得到的区间是[-(K-1),(K-1)] 正数的同余值  
            // -7 % 3 我们希望的值是 2, 即-7=3*-3 + 2; 但实际计算是-1 我们想把3*modNum 放到-7的前边，即比-7小，这样余数是整数
            // 即坐标轴从-inf > inf  我们希望每次的 num % n 余数都是离 num 最近的左边的数字离num的差值
            tmp = (preSum[i] % k + k) % k;    
            //tmp = preSum[i] % k;            // 如果全是正数用这个
            cnt += ump[tmp];
            ump[tmp]++;
        }

        return cnt;
    }
};