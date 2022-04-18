class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        // 一旦你走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。 这句话的意思就是必须连续

        int n = fruits.size();
        unordered_map<int, int> ump;

        int lo = 0, cnt = 0, len = 0;
        
        for (int hi = lo; hi < n; ++hi) {            
            ump[fruits[hi]]++;
            len++;

            while (ump.size() > 2) {
                ump[fruits[lo]]--;
                if (ump[fruits[lo]] == 0) ump.erase(fruits[lo]);
                lo++;
                len--;
            }
            cnt = max(cnt, len);
        }

        return cnt;
    }
};