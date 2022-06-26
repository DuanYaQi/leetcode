class Solution {    
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // init
        edges.resize(numCourses);
        indeg.resize(numCourses);

        for (auto info : prerequisites) {
            edges[info[1]].push_back(info[0]);  // 注意顺序 后边是需要先修的
            ++indeg[info[0]];                   // 前者入度+1,因为有先修课
        }

        queue<int> q;
        // 将所有入度为 0 
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();

            result.push_back(u);
            
            for (int v : edges[u]) {
                indeg[v]--;

                // 如果有入度变为0的, 表示可以选了, 放入队列
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        if (result.size() != numCourses) {
            return {};
        }

        return result;
    }

private:
    // 存储有向图
    vector<vector<int>> edges;  // 把下标i修了才能修的其他课程 当下标i修了，这些课程入度都-1

    // 存储每个节点的入度
    vector<int> indeg;

    // 存储答案    
    vector<int> result;
};



// dfs
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited; 
    bool gValid = true;    

public:
    void dfs(int u) {
        visited[u] = 1;

        for (auto &v : edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!gValid) return;
            } else if (visited[v] == 1) {
                gValid = false;
                return;
            }
        }
        visited[u] = 2;
    }


    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);

        for (auto &p : prerequisites) {
            edges[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses && gValid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        return gValid;
    }    
};


// dfs2
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> isVisit; 
    bool gValid = true;    

public:
    bool dfs(int u) {
        if (isVisit[u] == 1) return false;
        if (isVisit[u] == 2) return true;

        isVisit[u] = 1;
        for (auto v : edges[u]) {
            if (!dfs(v)) return false;
        }
        isVisit[u] = 2;

        return true;
    }


    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        isVisit.resize(numCourses);

        for (auto &p : prerequisites) {
            edges[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses; ++i) {
            if (!dfs(i)) {
                return false;
            }
        }

        return true;
    }    
};