class Solution {
public:
    struct UF {
        unordered_map<string, string> fa;
        
        string find(string x) {
            if (x == fa[x]) return x;
            else {
                string F = find(fa[x]);
                fa[x] = F;
                return F;
            }
        }

        void merge(string x, string y) { fa[find(y)] = find(x); }

    } uf;


    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        /*init*/
        unordered_map<string, string> umap;
        for(auto account : accounts) {
            for (int i = 1; i < account.size(); ++i) {
                uf.fa[account[i]] = account[i];
                umap[account[i]] = account[0];
            } 
        }
       
        for (auto& account : accounts) {
            int size = account.size();
            if (size == 2) continue;

            sort(account.begin()+1, account.end());
            
            for (int i = 1;  i < account.size(); ++i) {
                uf.merge(account[1], account[i]);
            }
        }

        unordered_map<string, vector<string>> resumap;
        vector<vector<string>> res;
        for (auto ump : umap) {
            string mail = ump.first;
            string name = ump.second;
            string fa = uf.find(mail);
            resumap[fa].push_back(mail);
        }


        for (auto resump : resumap) {
            vector<string> resT;
            sort(resump.second.begin(), resump.second.end());
            for (int i = 0; i < resump.second.size(); ++i) {
                if (i == 0) {
                    resT.push_back(umap[resump.second[i]]);
                }
                resT.push_back(resump.second[i]);
            }
            res.push_back(resT);
        }

        return res;
    }
};