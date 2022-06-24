class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int top = 0, i = -1;

        /*找到有效数字的结束位置i*/
        while (top < n) {
            i++;
            if (arr[i] != 0) {
                top++;
            } else {
                top += 2;
            }
        }

        /*倒着来移动值*/
        int j = n - 1;

        /*若 top == n + 1 说明修改后的数组的末尾的值正好是 0
        这个 0 复写后的 0 应该位于 arr[n] 的位置
        但这超出了范围 因此此种情况需要特判*/
        if (top == n + 1) {
            arr[j] = 0;
            j--;
            i--;
        }

        while (j >= 0) {
            arr[j] = arr[i];
            j--;
            if (arr[i] == 0) {
                arr[j] = arr[i];
                j--;
            }
            i--;
        } 

        return;
    }
};


class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int fast = 0, slow = 0;

        /*找到有效数字的结束位置i*/
        while (fast < n) {
            fast += arr[slow] == 0 ? 2 : 1;
            ++slow;            
        }

        /*倒着来移动值*/
        int i = n - 1, j = slow - 1;

        /*若 top == n + 1 说明修改后的数组的末尾的值正好是 0
        这个 0 复写后的 0 应该位于 arr[n] 的位置
        但这超出了范围 因此此种情况需要特判*/
        if (fast == n + 1) {
            arr[i] = 0;            
            i--;
            j--;
        }

        while (i >= 0) {
            arr[i] = arr[j];
            i--;
            if (arr[j] == 0) {  //是0的话再把前一位也赋值了
                arr[i] = arr[j];
                i--;
            }
            j--;
        } 

        return;
    }
};