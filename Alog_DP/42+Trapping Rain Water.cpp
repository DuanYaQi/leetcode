class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> leftMax(n), rightMax(n);

        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = max(leftMax[i-1], height[i]);
        }

        rightMax[n-1] = height[n-1];
        for (int i = n-2; i > -1; --i) {
            rightMax[i] = max(rightMax[i+1], height[i]);
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += min(leftMax[i], rightMax[i]) - height[i];
        }

        return res;
    }
};