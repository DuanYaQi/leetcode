struct Node {
    int key, val, freq;
    Node(int k, int v, int f) : key(k), val(v), freq(f) {}
};

class LFUCache {
private:
    int mMinFreq, mCapacity;
    unordered_map<int, list<Node>::iterator> mKey_table;    // 存迭代器 每个key
    unordered_map<int, list<Node>> mFreq_table; // 频率表，相同频率保存在一起

public:
    LFUCache(int capacity) : mCapacity(capacity), mMinFreq(0) {
        mKey_table.clear();
        mFreq_table.clear();
    }
    
    int get(int key) {
        auto it = mKey_table.find(key);
        if (it == mKey_table.end()) { return -1; }   // 没找到 -1
    
        // 找到了 更新状态
        list<Node>::iterator node = it->second; // 找到node的iter
        int val = node->val, freq = node->freq;                  // 得到它当前频率 freq
        mFreq_table[freq].erase(node);          // 删除这个node

        if (mFreq_table[freq].size() == 0) {    // 如果没有节点是这个频率 把这个频率对应的链表删除
            mFreq_table.erase(freq);        
            if (mMinFreq == freq) mMinFreq += 1;// 如果它的频率刚好是最小频率，并且已经没有其它node是最小频率，mMinFreq+1
        }
        mFreq_table[freq + 1].push_front(Node(key, val, freq + 1));
        mKey_table[key] = mFreq_table[freq + 1].begin();
        
        return val;
    }
    
    void put(int key, int value) {
        if (mCapacity == 0) return;
        auto it = mKey_table.find(key);             // 找到对应的节点
        if (it == mKey_table.end()) {               //没有该值 需要添加
            if (mKey_table.size() == mCapacity) {   // 缓存已满，需要删除
                // 通过 mMinFreq 拿到 mFreq_table[mMinFreq] 链表的末尾节点
                auto it2 = mFreq_table[mMinFreq].back();    // 尾部是最早创建的
                mKey_table.erase(it2.key);                  // 删除最早创建的node的iter
                mFreq_table[mMinFreq].pop_back();           // 把node从当前频率的list中也删除
                if (mFreq_table[mMinFreq].size() == 0) {    // 如果没有节点是这个频率 把这个频率对应的链表删除
                    mFreq_table.erase(mMinFreq);
                }
            }

            mMinFreq = 1;
            mFreq_table[mMinFreq].push_front(Node(key, value, mMinFreq)); //1是因为频率是1，front是因为它是最新的
            mKey_table[key] = mFreq_table[mMinFreq].begin();       //注意是begin() 返回的是iter 而不是front()的值
            
        } else {                                    // 该值已存在 需要更新状态
            list<Node>::iterator node = it->second;         // 得到其在 mFreq_table 里存的位置
            int freq = node->freq;                          // 得到它的频率
            mFreq_table[freq].erase(node);                  // 需要专门找到它再删除，所以要 erase() 而不是 popback()


            if (mFreq_table[freq].size() == 0) {    // 如果没有节点是这个频率 把这个频率对应的链表删除
                mFreq_table.erase(freq);
                if (mMinFreq == freq) mMinFreq += 1;
            }
            mFreq_table[freq + 1].push_front(Node(key, value, freq + 1));
            mKey_table[key] = mFreq_table[freq + 1].begin();    // 直接替换成新的node的iter就好了
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */