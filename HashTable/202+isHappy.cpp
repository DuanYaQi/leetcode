class Solution {
public:
    int getNum (int n) {//计算位置之和
        int sum = 0;
        int c;
        while (n) {
            c = n % 10; //余数
            n = n / 10;
            sum += c * c;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> uset;
        while (1) {
            n = getNum(n);
            if (n == 1) {
                return true;
            }
            if (uset.find(n) != uset.end()) {
                return false;
            }
            uset.insert(n);
        }
        return true;
    }
};