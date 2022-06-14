class Solution {
private: 
    int mM, mN;
public:
    inline bool isValid(int i, int j) {
        if (i >= 0 && i < mM && j >= 0 && j < mN) return true;
        return false;
    }

    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        vector<int> res;
        mM = mat.size();
        mN = mat[0].size();
        int sum = mM * mN;

        int cnt = 0;
        int lineNo = 1;
        while(cnt != sum) {
            if (lineNo & 1) {   // 奇数
                int startI = lineNo - 1, startJ = 0;
                while (!isValid(startI, startJ)) {      //跳过非法点
                    startI--;
                    startJ++;
                }
                while (isValid(startI, startJ)) {       //进入合法点
                    res.emplace_back(mat[startI][startJ]);
                    cnt++;
                    startI--;
                    startJ++;
                }
            } else {            // 偶数
                int startI = 0, startJ = lineNo - 1;
                while (!isValid(startI, startJ)) {      //跳过非法点
                    startI++;
                    startJ--;
                }
                while (isValid(startI, startJ)) {       //进入合法点
                    res.emplace_back(mat[startI][startJ]);
                    cnt++;
                    startI++;
                    startJ--;
                }
            }
            lineNo++;
        }

        return res;
    }
};