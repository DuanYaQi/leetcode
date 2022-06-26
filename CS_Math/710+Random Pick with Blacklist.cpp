/*
我们可以在初始化时，构建一个从 [0,n-m) 范围内的黑名单数到 [n-m,n) 的白名单数的映射：

将 [n-m,n) 范围内的黑名单数存入一个哈希集合 black；
初始化白名单数 w=n−m；
对于每个 [0,n-m) 范围内的黑名单数 b，首先不断增加 w 直至其不在黑名单中，然后将 b 映射到 w 上，并将 w 增加一。
*/

class Solution {
private:
    unordered_map<int, int> mB2W;
    int mBound;

public:
    Solution(int n, vector<int>& blacklist) {
        unordered_set<int> set;
        mBound = n - blacklist.size();
        
        /*把后半部分的黑名单加进去*/
        for (auto &n : blacklist) {
            if (n >= mBound) {
                set.insert(n);
            }   
        }

        /*把前半部分的黑名单加进去，并且记录与后半部分白名单的一一映射*/
        int idx = mBound;
        for (auto &n : blacklist) {
            if (n < mBound) {
                while (set.count(idx)) {
                    idx++;
                }
                mB2W[n] = idx++;
            }
        }


    }
    
    int pick() {
        int r = rand() % mBound;    //取前半部分的数字 
        
        // 如果这个数在mB2W里，说明它在黑名单，找到跟它映射的白名单的数字

        return mB2W.count(r) ? mB2W[r] : r;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */