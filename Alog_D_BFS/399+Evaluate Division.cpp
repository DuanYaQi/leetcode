class Solution {
public: 
    void dfs(int idc, int idd, vector<vector<pair<int,double>>>& graph, vector<double>& ratio) {
        if (ratio[idd] > 0) return;
        for (auto [tx, tval] : graph[idc]) {
            if (ratio[tx] < 0) {
                ratio[tx] = ratio[idc]*tval;
                dfs(tx, idd, graph, ratio);
            }
        }

        return;
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 映射
        unordered_map<string, int> umap;
        int no = 0;
        for (auto equation : equations) {
            string A = equation[0]; //a
            string B = equation[1]; //b
            if (umap.find(A) == umap.end()) {
                umap[A] = no++;
            }   

            if (umap.find(B) == umap.end()) {
                umap[B] = no++;
            }
        }

        //构图
        vector<vector<pair<int,double>>> graph(no);
        for (int i = 0; i < equations.size(); ++i) {
            int ida = umap[equations[i][0]];
            int idb = umap[equations[i][1]];
            double value = values[i];
            graph[ida].push_back({idb, value});
            graph[idb].push_back({ida, 1.0 / value});
        }


        vector<double> res;
        for (auto& q : queries) {
            double ans = -1.0;
            if (umap.find(q[0]) != umap.end() && umap.find(q[1]) != umap.end()) {
                int idc = umap[q[0]];
                int idd = umap[q[1]];

                vector<double> ratio(no, -1.0);//初始化-1为没有访问到，与vis数组相似，但是正值为倍率
                ratio[idc]=1.0;
                dfs(idc, idd, graph, ratio);
                ans = ratio[idd];
            }

            res.push_back(ans);
        }

        return res;
    }



    
};