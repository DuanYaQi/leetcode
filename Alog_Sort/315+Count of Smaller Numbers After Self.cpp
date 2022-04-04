const int maxn = 1e5 + 10;
class Solution {
public:
    struct Pair {
        int val; // 记录数组的元素值
        int id;  // 记录元素在数组中的原始索引
        Pair(): val(), id() {}
        Pair(int val, int id): val(val), id(id) {}
    } arr[maxn], tmp[maxn];     // 注意这里是tmp结构体数组记录，要连着id一起转换，不要只转换val
    
    int cnt[maxn];
    void merge(int l1, int r1, int l2, int r2) {
        int i = l1, j = l2, index = 0;

        while (i <= r1 && j <= r2) {
            if (arr[i].val <= arr[j].val) { // 这里是 <= !!!!!!!!!!!!!!!!!!!!!!!!
                tmp[index++] = arr[i];
                cnt[arr[i++].id] += (j - r1 - 1);
            } else {
                tmp[index++] = arr[j++];
            }
        }

        while (i <= r1) {
            tmp[index++] = arr[i];            
            cnt[arr[i++].id] += (j - r1 - 1);
        }
        while (j <= r2) tmp[index++] = arr[j++];
        
        for (int i = 0; i < index; ++i)
            arr[i+l1] = tmp[i];

        return;
    }

    void mergeSort(int lo, int hi) {
        if (lo >= hi) return;

        int mid = lo + (hi- lo) / 2;

        mergeSort(lo, mid);
        mergeSort(mid+1, hi);

        merge(lo, mid, mid+1, hi);
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        
        for (int i = 0; i < n; ++i) {
            arr[i].val = nums[i];
            arr[i].id  = i;
        }

        mergeSort(0, n-1);

        vector<int> res;
        for (int i = 0; i < n; ++i)
            res.push_back(cnt[i]);

        return res;
    }

private:
    vector<int> count;

};