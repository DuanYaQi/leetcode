struct DLinkedNode{
    int key, val;
    DLinkedNode* next;
    DLinkedNode* prev;
    DLinkedNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
	unordered_map<int, DLinkedNode*> _cache;
    DLinkedNode* _head;
    DLinkedNode* _tail;
    int _size;
    int _capacity;
    
public:
    LRUCache(int capacity): _capacity(capacity), _size(0) {
        // 使用伪头部和伪尾部节点
        _head = new DLinkedNode();
        _tail = new DLinkedNode();
        _head->next = _tail;
        _tail->prev = _head;
    }
    
    void put(int key, int val) {
        if (!_cache.count(key)) { // 如果 key 不存在，添加一个新的节点
            DLinkedNode* node = new DLinkedNode(key, val);
            _cache[key] = node;
            addToHead(node);
            ++_size;
            
            if (_size > _capacity) {
                // 删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                _cache.erase(removed->key);
                // 防止内存泄露
                delete removed;
                --_size;
            }
        } else {			// key 存在，修改val，并移至头部
            DLinkedNode* node = _cache[key];
            node->val = val;
            moveToHead(node);
        }        
    }
    
    int get(int key) {
        if (!_cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = _cache[key];
        moveToHead(node);
        return node->val;
    }
    
    void moveToHead(DLinkedNode* node) {
    	removeNode(node);
        addToHead(node);
    }
    
    void addToHead(DLinkedNode* node) {
        node->prev = _head;
        node->next = _head->next;
        _head->next->prev = node;
        _head->next = node;
    }
    
	void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    DLinkedNode* removeTail() {
        DLinkedNode* node = _tail->prev;
        removeNode(node);
        return node;
    }
    
    
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,val);
 */