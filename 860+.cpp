class Solution {
public: 
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;

        for (int i : bills) {
            if (i == 5) {
                five++;
                continue;
            }
            if (i == 10 && five > 0) {
                five--;
                ten++;
                continue;
            } else {
                return false;
            }

            if (i == 20) {
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                    continue;
                } else if (five > 2) {
                    five -= 3;
                    continue;
                } else {
                    return false;
                }
            }
        }

        if (five < 0 || ten < 0) {
            return false;
        }
            
        return true;
    }
};