class Trie {
private:
    vector<Trie*> children;
    bool isEnd;         //这个主要是用来区分全字匹配和前缀匹配

    Trie* searchPrefix(string prefix) {
        Trie* node = this;
        
        for (char ch : prefix) {        
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }

        return node;
    }
    
public:
    Trie() : children(26), isEnd(false) { }
    
    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true; //这里标末尾
    }
    
    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this->searchPrefix(prefix);
        return node != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */


// 智能指针版
class Trie {
private:
    struct TrieNode {
        vector<shared_ptr<TrieNode>> children;
        bool isEnd;         //这个主要是用来区分全字匹配和前缀匹配
        TrieNode() : children(26, nullptr), isEnd(false) { }
    };

    shared_ptr<TrieNode> root;  //一个结构体指针root指向 TrieNode

    shared_ptr<TrieNode> searchPrefix(string prefix) {
        auto node = root;   //auto = shared_ptr<TrieNode>
        
        for (char ch : prefix) {        
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }

        return node;
    }    
    
public:
    Trie() { 
        root = make_shared<TrieNode>(); // make_shared创建一个shared_ptr智能指针，指向一个TrieNode对象
    }
    
    void insert(string word) {
        auto node = root;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = make_shared<TrieNode>();   
                // make_shared创建一个shared_ptr智能指针，指向一个TrieNode对象
                // 等价于 node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEnd = true; //这里标末尾
    }
    
    bool search(string word) {
        auto node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }
    
    bool startsWith(string prefix) {
        auto node = this->searchPrefix(prefix);
        return node != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */