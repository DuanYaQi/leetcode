class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);

        for (auto info : prerequisites) {
            edges[info[1]].push_back(info[0]);
            indeg[info[0]]++;
        }

        queue<int> q;

        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int v = q.front(); q.pop();
            res.push_back(v);

            for (int e : edges[v]) {
                indeg[e]--;
                if (indeg[e] == 0) {
                    q.push(e);
                }
            }
        }

        if (res.size() == numCourses) {
            return true;
        }

        return false;
    }

private:
    vector<vector<int>> edges;
    vector<int> indeg; 
    vector<int> res;   
};