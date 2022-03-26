#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<stack>
#include<cassert>
#include<unordered_map>
#include<unordered_set>

using namespace std;

const int MAX_N = 1e5;
class Solution {
public:
    struct UF{
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

    }uf;

    vector<string> trulyMostPopular(vector<string>& names, vector<string>& synonyms) {
        /* init */
        vector<string> res;

        for(string synonym : synonyms) {
            int index = synonym.find(',');
            int endIndex = synonym.find(")");
            string s1 = synonym.substr(1, index - 1);
            string s2 = synonym.substr(index+1, endIndex - index - 1);
            uf.fa[s1] = s1;
            uf.fa[s2] = s2;
        }

        for (auto synonym : synonyms) {
            int index = synonym.find(',');
            int endIndex = synonym.find(")");
            string s1 = synonym.substr(1, index - 1);
            string s2 = synonym.substr(index+1, endIndex - index - 1);

            s1 < s2 ?  uf.merge(s1, s2) : uf.merge(s2, s1);            
        }

        //sort(names.begin(), names.end());

        unordered_map<string, int> umap;

        for (auto s : names) {
            int index = s.find('(');
            int endIndex = s.find(')');
            string sTmp = s.substr(index + 1, endIndex - index - 1);
            int num = stoi(sTmp);

            umap[s.substr(0, index)] += num;
            
        }

        unordered_map<string, int> umapT;
        for (auto ump : umap) 
            umapT[uf.find(ump.first)] += ump.second;

        for (auto ump : umapT) {
            string s = "";
            s.append(ump.first);
            s.append("(");
            s.append(to_string(ump.second));
            s.append(")");
            res.push_back(s);
        }

        return res;
    }
};
/*
5
John(15)
Jon(12)
Chris(13)
Kris(4)
Christopher(19)
4
(Jon,John)
(John,Johnny)
(Chris,Kris)
(Chris,Christopher)

*/
int main() {
    int m, n;
    cin >> m;

    vector<string> names, synonyms;

    string tmp;
    for (int i = 0; i < m; ++i) {
        cin >> tmp;
        names.push_back(tmp);
    }

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        synonyms.push_back(tmp);
    }
    
        
    vector<string> res = Solution().trulyMostPopular(names, synonyms);

    return 0;
}