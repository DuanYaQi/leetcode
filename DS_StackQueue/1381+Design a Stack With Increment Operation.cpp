class CustomStack {
public:
    CustomStack(int maxSize) : mMaxSize(maxSize) {

    }
    
    void push(int x) {
        if (mVec.size() < mMaxSize) {
            mVec.push_back(x);
        }
    }
    
    int pop() {
        if (mVec.size() == 0) return -1;
        int num = mVec.back(); mVec.erase((--mVec.end()));
        return num;
    }
    
    void increment(int k, int val) {
        for (int i = 0; i < min(k, (int)mVec.size()); ++i) 
            mVec[i] += val;
    }

private:
    int mMaxSize;
    vector<int> mVec;
};







class CustomStack {
public:
    CustomStack(int maxSize) : mMaxSize(maxSize) {
        mVec.resize(maxSize);
        mInc.resize(maxSize);
        top = -1;
    }
    
    void push(int x) {
        if (top < mMaxSize - 1) {
            ++top;
            mVec[top] = x;
        }
    }
    
    int pop() {
        if (top == -1) return -1;
        int num = mVec[top] + mInc[top]; 
        if (top > 0) {
            mInc[top - 1] += mInc[top];
        }
        mInc[top] = 0;
        --top;
        return num;
    }
    
    void increment(int k, int val) {
        int idx = min(k - 1, top); 
        
        if (idx >= 0)   // top 可能是 -1
            mInc[idx] += val;
    }

private:
    int mMaxSize;
    int top;        // 表示栈顶
    vector<int> mVec, mInc; //mInc[i] 表示下标<=i的元素的增量
};