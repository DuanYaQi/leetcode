class Solution {
    //
    // 1            2 3 4 5 6 7 8 9
    // 10 11 12 13
public:
    int getCnt(long start, long end, long n) {
        long cnt = 0;
        while (start <= n) {
            // 一次性求出下一层的节点个数和，要是没满就用n来减，要是满了就用end减
            cnt += min(n - start + 1, end - start); 
            start *= 10;
            end *= 10;
        }

        return cnt;
    } 

    int findKthNumber(int n, int k) {
        long res = 1;
        
        while (k > 1) {
            int nowCnt = getCnt(res, res + 1, n);   // 得到当前res和res+1之间的数字. 即1的子树的结点个数. 包括父节点本身
            if (nowCnt >= k) {                      // k小,说明在子树里,进入下一层. 因为包括父节点本身, 所以有等号=
                res *= 10;              
                k--;
            } else {
                res += 1;
                k -= nowCnt;
            }
        }    

        return res;
    }
};