class Solution {
public:
    int minimumLines(vector<vector<int>>& stockPrices) {
        if (stockPrices.size() == 1) {
            return 0;
        }
        
        auto cmp = [](vector<int> &x, vector<int> &y)->bool { 
            return x[0] < y[0];
        };
        
        sort(stockPrices.begin(), stockPrices.end(), cmp);                
        vector<long double> diff(stockPrices.size(), -1);
        
        for (int i = 1; i < stockPrices.size(); ++i) {
            long double diffx = (long double)(stockPrices[i][0]) - (long double)(stockPrices[i-1][0]);
            long double diffy = (long double)(stockPrices[i][1]) - (long double)(stockPrices[i-1][1]);
            
            long double diffT = diffy == 0 ? 0 : (long double)(diffy / diffx);
            diff[i] = diffT;
        }
        
        int ans = 1;
        for (int i = 2; i < diff.size(); ++i) {
            if (diff[i] == diff[i-1]) continue;
            ans++;
        }
        
        return ans;
    }
};