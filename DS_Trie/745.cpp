struct Trie {
    unordered_map<string, Trie*> children;
    int weight; //根据 weight 来返回最大的下标
};

class WordFilter {
public:
    WordFilter(vector<string>& words) {
        trie = new Trie();
        for (int i = 0; i < words.size(); ++i) {
            string word = words[i];
            Trie* cur = trie;

            for (int j = 0; j < word.size(); ++j) {
                Trie* tmp = cur;
                for (int k = j; k < word.size(); ++k) {
                    string key({word[k], '#'});
                    if (!tmp->children.count(key)) { //没有这个值
                        tmp->children[key] = new Trie();
                    }

                    tmp = tmp->children[key];
                    tmp->weight = i;
                }

                tmp = cur;
                for (int k = j; k < word.size(); ++k) {
                    string key({'#', word[word.size() - k - 1]}); // "#e" "#l" "#p" "#p" "#a"
                    if (!tmp->children.count(key)) { //没有这个值
                        tmp->children[key] = new Trie();
                    }

                    tmp = tmp->children[key];
                    tmp->weight = i;
                }

                string key({word[j], word[word.size() - j - 1]});
                if (!cur->children.count(key)) {
                    cur->children[key] = new Trie();
                }
                
                cur = cur->children[key];
                cur->weight = i;
            }
        }
    }
    
    int f(string pref, string suff) {
        Trie* cur = trie;
        int m = max(pref.size(), suff.size());
        for (int i = 0; i < m; ++i) {
            char c1 = i < pref.size() ? pref[i] : '#';
            char c2 = i < suff.size() ? suff[suff.size() - 1 - i] : '#';
            string key({c1, c2});
            if (!cur->children.count(key)) return -1;
            cur = cur->children[key];
        }

        return cur->weight;
    }

private:
    Trie* trie;    
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(pref,suff);
 */