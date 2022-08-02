class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        this->k = k;
        this->idx = -1;
        vecs.resize(k);
    }
    
    bool enQueue(int value) {
        if (idx == k - 1) return false;
        vecs[++idx] = value;
        return true;
    }
    
    bool deQueue() {
        if (idx == -1) return false;
        vector<int> vecsT = vecs;
        for (int i = 1; i <= idx; ++i) {
            vecs[i - 1] = vecsT[i];
        } 
        idx--;
        return true;
    }
    
    int Front() {
        if (idx == -1) return idx;
        return vecs[0];
    }
    
    int Rear() {
        if (idx == -1) return idx;
        return vecs[idx];
    }
    
    bool isEmpty() {
        return idx == -1;
    }
    
    bool isFull() {
        return idx == k - 1;
    }

private:    
    vector<int> vecs;
    int idx;
    int k;
};