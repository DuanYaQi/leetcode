# 字符串

## 题目：344. 反转字符串

```c++
void reverseString(vector<char>& s) {
    reverse(s.begin(), s.end());
}

void reverseString(vector<char>& s) {
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
        swap(s[i], s[j]);
    }
}
```



## 题目：541. 反转字符串II

让 `i += (2 * k)`，i 每次移动 2 * k 就可以了，然后判断是否需要有反转的区间。

因为要找的也就是每 `2 * k ` 区间的**起点**，这样写程序会高效很多。

**「所以当需要固定规律一段一段去处理字符串的时候，要想想在在for循环的表达式上做做文章。」**

```c++
string reverseStr(string s, int k) {
    for (int i = 0; i < s.size(); i += k*2) {
        //正常反转,  包括剩余字符小于2k,大于k个的前k个字符反转
        if (i + k <= s.size()) {
            reverse(s.begin() + i, s.begin() + i + k);
            continue;
        }
        //剩余字符小于k个，全部反转
        reverse(s.begin() + i, s.begin() + s.size());
    }

    return s;
}
```



## 题目：剑指Offer 05.替换空格

```c++
string replaceSpace(string s) {
    //先扩充大小
    int count = 0;
    int oldSize = s.size();
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            count++;
        }
    }

    s.resize(s.size() + count * 2);
    int newSize = s.size();
    // 双指针,从后往前移动,并填充空格
    for (int i = oldSize - 1, j = newSize - 1; i < j; i--, j--) {
        if (s[i] == ' ') {
            s[j] = '0';
            s[j - 1] = '2';
            s[j - 2] = '%';
            j -= 2;
        } else {
            s[j] = s[i];
        }
    }
    return s; 
}
```





## 题目：151.翻转字符串里的单词

```c++
class Solution {
public:
    void removeExtraSpace(string &s) {
        int slowIndex = 0, fastIndex = 0;
        while (s[fastIndex] == ' ' && fastIndex < s.size()) {  
            fastIndex++;
        }
        
        // 去除中间多余的空格 和 末尾多余的空格
        for (; fastIndex < s.size(); fastIndex++) {
            //如果当前是空格,前一位置也是空格,什么也不操作,继续循环
            if (s[fastIndex] == ' ' && s[fastIndex] == s[fastIndex - 1] ) { 
                continue;
            } else {
                s[slowIndex++] = s[fastIndex];
            }
        }

        // slowIndex - 1 指向string的最后的一位置
        if (s[slowIndex - 1] == ' ') {
            s.resize(slowIndex - 1);
        } else {
            s.resize(slowIndex);
        }
    }

    string reverseWords(string s) {
        removeExtraSpace(s);
        reverse(s.begin(), s.end());
        int left = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                reverse(s.begin() + left, s.begin() + i);
                left = i + 1;
            }
        }
        reverse(s.begin() + left, s.end());
        return s;
    }
};
```



## 题目：剑指Offer58-II.左旋转字符串

通过**局部反转+整体反转**



具体步骤为：

1. 反转区间为前n的子串
2. 反转区间为n到末尾的子串
3. 反转整个字符串

```c++
string reverseLeftWords(string s, int n) {
    reverse(s.begin(), s.begin() + n);
    reverse(s.begin() + n, s.end());
    reverse(s.begin(), s.end());
    return s;
}
```



---

## KMP算法

### 理论

knuth Morris Pratt O(n+m)

字符串匹配问题

文本串 `aabaabaaf`

模式串 `aabaaf`

判断文本串中是否出现过模式串，暴力解法 O(nm)



#### 关键概念

前缀表：各字串的最长相等前后缀

前缀：包含首字母不包含尾字母的所有字串。`aabaaf` 前缀有 `a, aa, aab, aaba, aabaa`

后缀：只包含尾字母不包含首字母的所有字串。`aabaaf` 后缀有 `f, af, aaf, baaf, abaaf`

最长相等前后缀：

`a` 的相等前后缀为 0

`aa` 的相等前后缀为 1，前缀 `a`，后缀 `a`

`aab` 的相等前后缀为 0

`aaba` 的相等前后缀为 1，前缀 `a`*（位置1的a），后缀 `a`（位置4的a）

`aabaa` 的相等前后缀为 2，前缀 `aa`（位置1-2的a），后缀 `aa`（位置4-5的a）

`aabaaf` 的相等前后缀为 0

`[0 1 0 1 2 0]` 即为模式串 `aabaaf` 的前缀表，也称为 next 数组 / perfix 数组（有时会把数组减1，`[-1 0 -1 0 1 -1]` ，或者把数组右移动，`[-1 0 1 0 1 2]` ）



---

### 实战

字符串匹配问题

文本串 `aabaabaaf`

模式串 `aabaaf`

next 数组为 `[0 1 0 1 2 0]` ，与模式串一一对应

```c++

```







----

## 28. 实现 strStr()





## 459. 重复的子字符串























