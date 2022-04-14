class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // 先修课程，grpah[i][j] = 1 表示 i 是 j 的先修课程
        bool graph[numCourses][numCourses];
        memset(graph, 0, sizeof(bool)*numCourses*numCourses);
		
         // 构建图
        for (const auto &data : prerequisites) {
            graph[data[0]][data[1]] = true;
        }
	
        
        // Floyd算法的本质是DP，而k是DP的阶段，因此要写最外面
        for (int k = 0; k < numCourses; ++k) {
            for (int i = 0; i < numCourses; ++i) {
                for (int j = 0; j < numCourses; ++j) {
                    // i 是 k 的先导课程，k 是 j 的先导课程
                    if (graph[i][k] && graph[k][j]) {
                        graph[i][j] = true;
                    }
                }
            }
        }
       
        // 遍历quries直接从graph得到结果
        vector<bool> res;
        for (const auto &q : queries) {
            if (graph[q[0]][q[1]]) res.push_back(true);
            else res.push_back(false);
        }

        return res;
    }

     
};