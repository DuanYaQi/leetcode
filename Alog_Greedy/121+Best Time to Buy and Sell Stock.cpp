class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int low = INT_MAX;
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            low = min(low, prices[i]);
            result = max(result, prices[i] - low);
        }
        return result;
    }
};