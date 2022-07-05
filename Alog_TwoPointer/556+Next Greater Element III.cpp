class Solution {
public:
    int nextGreaterElement(int n) {
        string str = to_string(n);
        int size = str.size() - 1;

        // 找到交换点right，即从低位第一个比结尾数字小的数
        int right = size - 1;
        while (right >= 0 && str[right] >= str[right + 1]) {
            right--;
        }
        if (right == -1) return -1;

        /*把后边排序掉*/
        int offset = size - right;
        sort(str.end() - offset, str.end());
		
        // 找出第一个比它大的数字并交换
        for (int i = right + 1; i <= size; ++i) {
            if (str[i] > str[right]) {
                swap(str[i], str[right]);
                break;
            }
        }

        return stol(str) > INT_MAX ? -1 : stol(str);
    }
};