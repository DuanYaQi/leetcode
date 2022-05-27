# 位图



## 💗691. 贴纸拼词

```c++
class charmap {
public:
    int nums[26] = {0};
    int& operator[](char c) {
        return nums[c - 'a'];
    }
    int& data(int i) {
        return nums[i];
    }
};


int minStickers(vector<string>& stickers, string target) {
    int m = target.size(), n = stickers.size(), s0 = (1 << m) - 1, ans = 0;

    //cout << s0;

    queue<int> q;
    unordered_set<int> uset;
    q.push(0);//000000
    uset.insert(0);

    while (q.size()) {
        int qn = q.size();
        ans++;

        for (int k = 0; k < qn; ++k) {  // 遍历此层
            int s1 = q.front(); q.pop();
            for (string s : stickers) { // 遍历每个可选字符串
                int s2 = s1;
                charmap cnt;
                for (char c : s) {
                    cnt[c]++;
                }

                for (int i = 0; i < m; ++i) {   // 遍历可选字符串
                    char cN = target[i];
                    if ((s2 >> i & 1) == 0 && cnt[cN] > 0) {    // 如果这个位置状态为0, 并且可选字符串里可以提供这一处的单词
                        cnt[cN]--;          // 字母表此位置记录数量减
                        s2 |= 1 << i;       // s2 的这个为0的位置变1
                    }
                }

                if (s2 == s0) return ans;   // 如果它变成全1了 直接返回ans答案
                if (s2 > s1 && uset.count(s2) == 0) {   // s2 > s1 表示选了这个字符串是有进展的，即更新了位数，uset防止此状态重复入队
                    q.push(s2);
                    uset.insert(s2);
                }
            }
        }
    }

    return -1;
}
```











---

## 461. 汉明距离

```c++

```

