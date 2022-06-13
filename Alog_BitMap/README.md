# 位图



## 原理

bitmap，使用每个位表示某种状态，适合处理整型的海量数据。本质上是哈希表的一种应用实现



原理：给定一个 int 整形数据，将该 int 整数映射道对应的位上，并将该位由 0 改为 1

![img](assets/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI5MTE5NTgx,size_16,color_FFFFFF,t_70.png)





有两组数据分别是40亿个QQ号码和60亿个QQ号码，需要查找它们之间重合的数据。如果使用暴力查找一一匹配的话，时间和空间是都吃不消，时间和空间的复杂度很高，很不适用；如果使用分治法分批处理的话，内存可以降低，但是时间复杂度依然很高，也不太适用。如果使用位图的话，就可以很好的解决这个问题，时间空间上都吃的消。

在 C++ 中，整型占 32 位 4 个字节。如果使用暴力查找和分治法的话，每个数据都需要占这么多内存，但是如果使用位图，每 32 个数据只需要占一个整型的内存，在整型的**每个位上存储某个数据是否存在的状态**，存在为 1， 不存在则为 0，用第一个整型保存 id 是 0-31 的qq号的状态，第二个整型保存 id是 32-63 的qq号的状态，直接节省 32 倍的内存空间，而查找单个元素的时间复杂度只有 $O(1)$

存储数据的大小应该为 `size/32 + 1`, 

`num/32` 是数据访问下标

`num%32` 是数据所在的比特位

插入数据把对应位比特值置 1

删除数据把对应位比特值置 0

查找就是判断对应位比特值是否是 1



```c++
class BitMap {
public:
    BitMap(const size_t &range) {
        if (bits != nullptr) {
            delete[] bits;
        }
        
        count = range;
        size = range / 32 + 1;
        bits = new unsigned int[size];
    }
    
    ~BitMap() {
        delete[] bits;
    }
    
    void init() {
        for (int i = 0; i < size; ++i) bits[i] = 0;
    }
    
    void add(const size_t &num) {
        if (num > count)
            return;
       	int idx = num / 32;
        int bitIdx = num % 32;
        bist[idx] |= 1 << bitIdx;
    }
    
private:
    unsigned int* bits = nullptr;
    int size;
    int count;
}
```









----

## 模板

```c++
class BitMap {
    char bytes[];
    int nBits;
    
    BitMap(int _nBits) {
        this.nBits = _nBits;
		this.bytes = new char(_nBits / 16  + 1);	// 一个字符占2字节
    } 
}
```







## 应用场景

查询统计、定位查询、排序、去重

取两个集合的交集、并集







## 287. 寻找重复数

```c++
int findDuplicate(vector<int>& nums) {
    bitset<100001> a;
    for(auto& i:nums){
        if(a[i])  return i;
        else      a[i]=1;
    }
    return 0;
}
```



```c++
class Solution {
public:
    bool isBitZero(vector<int> &flag,int bit){
        int t = 1<<(bit%32);
        int res = flag[bit/32]&t;
        return res == 0;
    }
    void setBit(vector<int> &flag,int bit){
        int t = 1<<(bit%32);
        flag[bit/32] |= t;
    }
    int findDuplicate(vector<int>& nums) {
        int x = nums.size();
        vector<int>flag(x+1,0);
        int res = 0;
        for(int i=0;i<nums.size();i++){
            if(isBitZero(flag, nums[i])){
                setBit(flag,nums[i]);
            }
            else{
                res = nums[i];
                break;
            }
        }
        return res;
    }
};
```







----

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

# 位运算

| 操作         | 代码                                                   |      |
| ------------ | ------------------------------------------------------ | ---- |
| 与           | 0 & 0 = 0<br>0 & 1= 0<br/>1 & 0 = 0<br/>1 & 1 = 1      |      |
| 或           | 0 \| 0 = 0<br>0 \| 1 = 1<br/>1 \| 0 = 1<br/>1 \| 1 = 1 |      |
| 异或         | 0 ^ 0 = 0<br>0 ^ 1 = 1<br/>1 ^ 0 = 1<br/>1 ^ 1 = 0     |      |
| 取反（一元） | ~0 = 1<br/>~1 = 0                                      |      |
| 左移         |                                                        |      |
| 右移         |                                                        |      |

参与运算的数字都采用有符号的 **8 位二进制**表示。

46 的二进制表示是 00101110，51 的二进制表示是 00110011。考虑以下位运算的结果。

- $46~\&~51$ 的结果是 34，对应的二进制表示是 00100010。
- $46~|~51$ 的结果是 63，对应的二进制表示是 00111111。
- $46 \oplus 51$ 的结果是 29，对应的二进制表示是 00011101。
- $\sim 46$ 的结果是 -47，对应的二进制表示是 11010001。
- $\sim 51$ 的结果是 -52，对应的二进制表示是 11001100。



左移 << 。将全部二进制位向左移动若干位，高位丢弃，低位补 0。

右移 << 。将全部二进制位向右移动若干位，低位丢弃，高位判断

- 算术（带符号）右移，高位补最高位
- 逻辑（不带符号）右移，高位补0

>  **对于 0 和正数，算术右移和逻辑右移的结果是相同的。**因为其最高位就是0 
>
>  0和正数的补码是其本身！！！





29 的**8 位二进制**为 00011101。29 左移 2 位的结果是 01110100，十进制为 116；29 左移 3 位的结果是 11101000，-24

50 的**8 位二进制**表示是 00110010。50 右移 1 位的结果是  25，对应的二进制表示是 00011001；50 右移 2 位的结果是 12，对应的二进制表示是 00001100。

−50 的二进制表示是 11001110（原码：10110010，反码：11001101，补码：11001110）。-50 算术右移 2 位的结果是 -13，对应的二进制表示是 11110011（补码：11110011，反码：11110010，原码：10001101）；-50 逻辑右移 2 位的结果是 51，对应的二进制表示是 （补码：00110011，反码：00110011，原码：00110011）。



对于 C/C++ 而言，数据类型包含有符号类型和无符号类型，其中有符号类型使用关键字 signed 声明，无符号类型使用关键字 unsigned 声明，两个关键字都不使用时，默认是有符号类型。对于**有符号**类型，右移运算为**算术右移**；对于**无符号**类型，右移运算为**逻辑右移**。





---

## 移位运算与乘除法的关系

使用**移位运算实现乘除法**的**效率显著高于直接乘除法的效率**。



29 左移 2 位的结果 116；29 左移 3 位的结果是 -24

50 右移 1 位的结果是  25；50 右移 2 位的结果是 12。

−-50 算术右移 2 位的结果是 -13；-50 逻辑右移 2 位的结果是 51。



**左移**运算对应**乘法**运算。将一个数左移 *k* 位，等价于将这个数乘以 $2^k$。当乘数不是 2 的整数次幂时，可以将乘数拆成若干项 2 的整数次幂之和，例如，$a \times 6$ 等价于 $(a<<2)+(a<<1)$。需要注意**溢出**



**算术右移**运算对应**除法**运算。将一个数右移 k 位，相当于将这个数除以 $2^k$。例如，50 右移 2 位的结果是 12，等价于 50 / 4，结果**向下取整**。

- 对于 0 和正数，将一个数（算术）右移 k 位，和将这个数除以 $2^k$ 等价。
- 但是对于负数，上述说法就不成立了













----

## 6065. 按位与结果大于零的最长组合

```c++
int largestCombination(vector<int>& candidates) {
    int ans = 0;
    for (int i = 0; i < 32; ++i) {
        int cnt = 0;
        for (int j = 0; j < candidates.size(); ++j) {
            int num = candidates[j];
            if (num & (1 << i)) cnt++;
        }
        ans = max(ans, cnt);
    }

    return ans;
}
```








---

## 461. 汉明距离

```c++
class Solution {
public:
    int hammingDistance(int x, int y) {
        int cnt = 0;
        //cout << bitset<sizeof(int) * 8>(x) << endl;
        //cout << bitset<sizeof(int) * 8>(y) << endl;
        for (int i = 31; i >= 0; i--) {
            //cout << bitset<sizeof(int) * 8>(1 << i) << " " << (x & (1 << i)) << " " << (y & (1 << i)) << endl;
            if ((x & (1 << i)) != (y & (1 << i))) cnt++;
        }

        return cnt;
    }
};
```
