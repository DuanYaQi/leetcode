using ll = long long;
class ATM {
public:
    int money[5] = {20, 50, 100, 200, 500};
    
    ATM() : vec(5) {
        
    }
    
    void deposit(vector<int> banknotesCount) {
        for (int i = 0; i < 5; ++i) 
            vec[i] += banknotesCount[i];
    }
    
    vector<int> withdraw(int amount) {
        vector<int> res(5); 
        
        for (int i = 4; i >= 0; --i) {
            ll nCnt = amount / money[i];
            ll realCnt = min(nCnt, vec[i]);
            
            res[i] = realCnt;
            amount = amount - realCnt * money[i];
            
        }
        
        if (amount != 0)  return {-1};

        for (int i = 0; i < 5; ++i)
            vec[i] -= res[i]; 
     
        
        return res;
    }
    
private:
    vector<ll> vec;
};

//[null, null, [0,0,1,0,1], null, [-1], [0,1,0,0,1]]
/**
 * Your ATM object will be instantiated and called as such:
 * ATM* obj = new ATM();
 * obj->deposit(banknotesCount);
 * vector<int> param_2 = obj->withdraw(amount);
 */