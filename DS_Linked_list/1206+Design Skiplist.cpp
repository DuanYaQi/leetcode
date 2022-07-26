constexpr int MAX_LEVEL = 32;
constexpr double P_FACTOR = 0.25;

struct SkipListNode {
    int val;
    vector<SkipListNode*> forward;   // 存该节点每一个 level 的后继节点
    // forward.size()  表示这个值有几层, 有几个 level

    SkipListNode(int _val, int _maxLevel = MAX_LEVEL) : val(_val), forward(_maxLevel, nullptr) {};
};

class Skiplist {
public:
    Skiplist() : head(new SkipListNode(-1)), level(0), dis(0, 1) {
        
    }
    
    bool search(int target) {   
        SkipListNode *curr = this->head;
        for (int i = level - 1; i >= 0; i--) {
            /* 找到第i层小于且最接近target的元素 */
            while (curr->forward[i] && curr->forward[i]->val < target) {
                curr = curr->forward[i];
            }
        }
        curr = curr->forward[0];
        /* 检测当前元素的值是否等于 target */
        if (curr && curr->val == target) {
            return true;
        }

        // 最接近target的元素的下一个不是的话，就说明没有
        return false;
    }
    
    void add(int num) {
        vector<SkipListNode *> update(MAX_LEVEL, head);
        SkipListNode *curr = this->head;        
        for (int i = level - 1; i >= 0; i--) {  // 遍历层级
            /* 找到第 i 层小于且最接近 num 的元素 */
            while (curr->forward[i] != nullptr && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }    
            update[i] = curr;  // 保存小于且最最近 num 的元素, 即前驱节点
        }

        int lv = randomLevel();
        level = max(level, lv); // 更新最大的level
        SkipListNode *newNode = new SkipListNode(num, lv);
        for (int i = 0; i < lv; ++i) {          // 在每一层插入新节点
            newNode->forward[i] = update[i]->forward[i];  
            update[i]->forward[i] = newNode; 
        }
    }   
    
    bool erase(int num) {
        vector<SkipListNode *> update(MAX_LEVEL, nullptr); // 默认都为空
        SkipListNode *curr = this->head;        
        for (int i = level - 1; i >= 0; i--) {  // 遍历层级
            /* 找到第 i 层小于且最接近 num 的元素 */
            while (curr->forward[i] != nullptr && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }    
            update[i] = curr;  // 保存小于且最最近 num 的元素, 即前驱节点
        }

        curr = curr->forward[0];    // 最底层的 curr 的后继节点没值的话，上层肯定也没有
        /* 没有这个值 */
        if (curr == nullptr || curr->val != num) {
            return false;
        }

        for (int i = 0; i < level; ++i) {   // 从小往上找
            if (update[i]->forward[i] != curr) { // 如果该层没有值，上层也不会有了
                break;
            }
            /* 对第 i 层的状态进行更新，将 forward 指向被删除节点的下一跳 */
            update[i]->forward[i] = curr->forward[i];
        }
        delete curr;
        /* 更新当前的 level */
        while (level > 0 && head->forward[level - 1] == nullptr) { //头节点后继就是nullptr,肯定就为空了
            level--;
        }
        return true;
    }

    int randomLevel() {
        int lv = 1;  //初始节点就一层，再最低层
        /* 随机生成 lv */
        while (dis(gen) < P_FACTOR && lv < MAX_LEVEL) {
            lv++;   //有0.25的概率加1层
        }
        return lv;
    }

private:
    SkipListNode* head; // 头指针
    int level;          // 当前最大的level
    mt19937 gen{random_device{} ()};    // 生成 (-maxint,+maxint) 随机数
    uniform_real_distribution<double> dis;
};

/*
mt是指maxint（整型int最大值的缩写）, 19937是指2^19937-1
mt19937是c++11新特性，它是一种随机数算法，用法与rand()函数类似，但是mt19937具有速度快，周期长的特点（所谓周期长应该是指19937所代表的意思吧）
rand()在windows下生成的数据范围为0-32726
此时的mt19937所生成的数据范围大概为(-maxint,+maxint)（maxint整型int最大值的缩写）
*/

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */