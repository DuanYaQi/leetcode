class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;


        sort(points.begin(), points.end(), [] (vector<int> &a1, vector<int> &a2) {
            return a1[1] < a2[1];
        });

        int pos = points[0][1]; // 第一个的右边界
        int res = 1;
        for (auto &vec : points) {
            if (vec[0] > pos) { // 如果这个球的左边界大于已知的右边界 只能来一根新的箭
                pos = vec[1];   // 设置新的右边界，这跟新箭 能移动端范围
                res++;  
            }
        }

        return res;
    }
};