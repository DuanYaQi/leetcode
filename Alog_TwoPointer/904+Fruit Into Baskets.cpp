class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int left = 0, right = 0;
        int len = 0, res = 0;
        unordered_map<int, int> umap;
        
        for(; right < fruits.size(); right++) {
            umap[fruits[right]]++;
            len++;
            while (umap.size() > 2) {
                umap[fruits[left]]--;
                if (umap[fruits[left]] == 0) umap.erase(fruits[left]);
                left++;
                len--;
            }

            res = max(res, len);
        }

        return res;
    }
};