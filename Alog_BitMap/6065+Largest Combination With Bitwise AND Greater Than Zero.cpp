#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        int ans = 0;
        for (int i = 0; i < 32; ++i) {
            int cnt = 0;
            for (int j = 0; j < candidates.size(); ++j) {
                int num = candidates[j];
                if (num & (1 << i)) cnt++;
            }
            ans = max(ans, cnt);
        }

        return ans;
    }
};


#ifdef _DEBUG
int main() {
    vector<int> candidates = {8,8};
    auto ans=Solution().largestCombination(candidates);

    return 0;
}
#endif