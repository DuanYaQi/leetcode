class Solution {
public: 
    bool visited[10];
    int bestB = -1, bestM = -1;
    
    bool judge(vector<int>& material, vector<int>& cookbook) {
        for (int i = 0; i < material.size(); ++i) {
            if (material[i] - cookbook[i] < 0) return false;
        }
        return true;
    }
    
    void dfs(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit, int mei, int bao) {
        if (bao >= limit) {
            if (mei > bestM) {
                bestB = bao;
                bestM = mei;
                //return;!!!!!!!!!!!!! 注意不要有这一句，因为满足条件的有很多，我们还要找美味度最高的
            }       
            //return; !!!!!!!!!!!!!! 注意不要有这一句，因为满足条件的有很多，我们还要找美味度最高的
        }
        
        for (int i = 0; i < cookbooks.size(); ++i) {    //0 1 2
            if (visited[i]) continue;
            if (!judge(materials, cookbooks[i])) continue;
            
            visited[i] = true;//!!!!!!!!!!!!!!!注意位置不要放在judge后continue的前边
            
            vector<int> materialsTmp = materials;
            for (int j = 0; j < 5; ++j) {
                materialsTmp[j] = materialsTmp[j] - cookbooks[i][j];
            }
            
            dfs(materialsTmp, cookbooks, attribute, limit, mei + attribute[i][0], bao + attribute[i][1]);
            
            visited[i] = false;
        }
        
        return;
    }
    
    
    int perfectMenu(vector<int>& materials, vector<vector<int>>& cookbooks, vector<vector<int>>& attribute, int limit) {
        // memset(visited, 0, sizeof(visited));       
        dfs(materials, cookbooks, attribute, limit, 0, 0);
        
        return bestM;
    }
};
