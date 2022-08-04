class Solution {
public:
    inline int getDis(vector<int> &v1, vector<int> &v2) {
        return (v1[0] - v2[0]) * (v1[0] - v2[0]) + (v1[1] - v2[1]) * (v1[1] - v2[1]);
    }

    int numberOfBoomerangs(vector<vector<int>>& points) {
        int res = 0, n = points.size();

        
        for (int i = 0; i < n; ++i) {               // 选为拐点
            unordered_map<int, int> ump;            // k->v  距离->个数
            for (int j = 0; j < n; ++j) {           // 距离
                if (i == j) continue;
                ump[getDis(points[i], points[j])]++;
            }

            for (auto &[_, m] : ump) {              // 遍历 [距离,个数]
                res += m * (m - 1);
            }

        }

        
        return res;
    }
};