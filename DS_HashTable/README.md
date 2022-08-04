# 哈希表

## 基础

### 哈希表

哈希表（英文名为Hash table，国内也有一些算法书籍翻译为**散列表**）。

> 哈希表是根据**关键码**的值而**直接进行访问**的数据结构。

**一般哈希表都是用来快速判断一个元素是否出现集合里**





### **哈希函数**

哈希函数如下图所示，通过hashCode把名字转化为数值，一般hashcode是通过特定**编码方式**，可以将其他数据格式转化为不同的数值，这样就把学生名字映射为哈希表上的索引数字了。

![图片](assets/hashfunction)

如果hashCode得到的数值大于 哈希表的大小了，也就是大于tableSize了，怎么办呢？

此时为了保证映射出来的索引数值都落在哈希表上，我们会在再次对数值做一个**取模**的操作，就要我们就保证了学生姓名一定可以映射到哈希表上了。

如果学生的数量大于哈希表的大小怎么办，此时就算哈希函数计算的再均匀，也避免不了会有几位学生的名字同时映射到哈希表 同一个索引下表的位置。接下来**「哈希碰撞」**登场

---

### 哈希碰撞

如图所示，小李和小王都映射到了索引下表 1的位置，**「这一现象叫做哈希碰撞」**。

![图片](assets/hashcollision)

一般哈希碰撞有两种解决方法， 拉链法和线性探测法。

---

#### 拉链法

发生冲突的元素都被存储在**链表中**。

![图片](assets/hashcollisionsolutioni)

其实拉链法就是要选择适当的哈希表的大小，这样既不会因为数组空值而浪费大量内存，也不会因为**链表太长**而在查找上浪费太多时间。（数据规模是 dataSize， 哈希表的大小为 tableSize）



---

#### 线性探测法

使用线性探测法，一定要保证 tableSize 大于 dataSize。我们需要依靠哈希表中的**空位**来解决碰撞问题。

例如冲突的位置，放了小李，那么就**向下找一个空位**放置小王的信息。所以要求tableSize一定要大于dataSize ，要不然哈希表上就没有空置的位置来存放 冲突的数据了。如图所示：

![图片](assets/hashcollisionsolutionii)



---

### 哈希结构

当我们想使用哈希法来解决问题的时候，我们一般会选择如下三种数据结构。

- 数组
- set （集合）
- map（映射）

在C++语言中，实现在C++中，`set` 和 `map` 分别提供了以下三种数据结构，其底层实现以及优劣如下表所示：

![图片](assets/setmapi)

`std::unordered_set` 底层实现为哈希表，`std::set` 和 `std::multiset` 的底层实现是红黑树，红黑树是一种平衡二叉搜索树，所以key值是有序的，但key不可以修改，改动key值会导致整棵树的错乱，所以**只能删除和增加**。



![图片](assets/setmapii)

`std::unordered_map` 底层实现为哈希表，`std::map` 和 `std::multimap` 的底层实现是红黑树。同理，`std::map` 和 `std::multimap` 的 `key` 也是有序的。



解决哈希问题的时候，优先使用 `unordered_set` ，因为它的查询和增删效率是最优的，如果需要集合是有序的，那么就用 `set`，如果要求不仅有序还要有重复数据的话，那么就用 ` multiset` 。



 `map` 是一个 `key value` 的数据结构，`map` 中，对 `key` 是有限制，对 `value` 没有限制的，因为 `key` 的存储方式使用红黑树实现的。



虽然 `set`、`multiset` 的底层实现是红黑树，不是哈希表，但是 `set、multiset` 依然使用哈希函数来做映射，只不过底层的符号表使用了红黑树来存储数据，所以使用这些数据结构来解决映射问题的方法，我们依然称之为哈希法。`map` 也是一样的道理。



`unordered_set` 在C++11的时候被引入标准库了，而 `hash_set` 并没有，所以建议还是使用 `unordered_set` 比较好，这就好比一个是官方认证的，`hash_set，hash_map` 是 C++11 标准之前民间高手自发造的轮子。实际上功能都是一样的



---



**当我们遇到了要快速判断一个元素是否出现集合里的时候，就要考虑哈希法**。

但是哈希法也是**牺牲了空间换取了时间**，因为我们要使用额外的数组，set或者是map来存放数据，才能实现快速的查找。



### pair<int, int> 的 hash 函数

```c++
struct hashfunc {
    template<typename T, typename U>
    size_t operator() (const pair<T, U> &i) const
    {
        return hash<T>()(i.first) ^ hash<U>()(i.second);
    }
};
unordered_map< pair<int, int>, int, hashfunc> ump;
```





---

## 第242题. 有效的字母异位词

「数组其实就是一个简单哈希表」

定一个数组叫做record，大小为26 就可以了，初始化为0，因为字符a到字符z的ASCII也是26个连续的数值。

```c++
bool isAnagram(string s, string t) {
    int mp[26] = {0};

    for (char c : s) {
        mp[c - 'a']++;
    }
    for (char c : t) {
        mp[c - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (mp[i] != 0) {
            return false;
        }
    }
    return true;
}
```



## 第349题. 两个数组的交集

**「如果哈希值比较少、特别分散、跨度非常大，使用数组就造成空间的极大浪费。」**此时就要使用另一种结构体set ，关于set，C++ 给提供了如下三种可用的数据结构：

- std::set
- std::multiset
- std::unordered_set

`std::set` 和 `std::multiset` 底层实现都是红黑树，`std::unordered_set` 的底层实现是哈希表， 使用 `unordered_set` 读写效率是最高的，并不需要对数据进行排序，而且还不要让数据重复，所以选择 `unordered_set`。

```c++
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> uset(nums1.begin(), nums1.end());
    unordered_set<int> res;

    for (int num : nums2) {
        if (uset.find(num) != uset.end()) {
            res.insert(num);
        }
    }

    return vector<int>(res.begin(), res.end());
}
```



## 第202题. 快乐数

**「当我们遇到了要快速判断一个元素是否出现集合里的时候，就要考虑哈希法了。」**

```c++
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
```



---

## 第1题. 两数之和

**「这道题目中并不需要key有序，选择std::unordered_map 效率更高！」**

```c++
vector<int> twoSum(vector<int>& nums, int target) {
    std::unordered_map <int,int> map;
    for(int i = 0; i < nums.size(); i++) {
        auto iter = map.find(target - nums[i]);
        if(iter != map.end()) {
            return {iter->second, i};
        }
        map[nums[i]] = i;
    }
    return {};
}
```





---

## 第454题.四数相加II

本题解题步骤：

1. 首先定义一个 `unordered_map`，`key` 放 a 和 b 两数之和，`value` 放 a 和 b 两数之和出现的次数。
2. 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中。
3. 定义变量 `count`，用来统计 `a+b+c+d = 0` 出现的次数。
4. 在遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就用 `count` 把 map 中`key` 对应的 `value` 也就是出现次数统计出来。
5. 返回统计值 `count` 



```c++
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    std::unordered_map<int, int> umap;
    int count = 0;
    // 遍历a b 计算所有的 a + b 统计出现的次数
    for (int a : nums1) {
        for (int b : nums2) {
            umap[a + b]++;
        }
    }

    for (int c : nums3) {
        for (int d : nums4) {
            auto iter = umap.find(0 - c - d);
            if (iter != umap.end()) {
                count += iter->second; //加上出现的次数
            }
        }
    }
    return count;
}
```



---

## 第383题. 赎金信

本题判断第一个字符串ransom能不能由第二个字符串magazines里面的字符构成，但是这里需要注意两点

- 第一点“为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思” 这里**说明杂志里面的字母不可重复使用。**
- 第二点 “你可以假设两个字符串均只含有小写字母。” **说明只有小写字母**，这一点很重要



**「其实在本题的情况下，使用map的空间消耗要比数组大一些的，因为map要维护红黑树或者哈希表，而且还要做哈希函数。所以数组更加简单直接有效！」**



```c++
bool canConstruct(string ransomNote, string magazine) {
     int record[26] = {0};

     for (char c : magazine) {
         record[c - 'a']++;
     }

     for (char c : ransomNote) {
         record[c - 'a']--;
         if (record[c - 'a'] < 0) {
             return false;
         }
     }

     return true;
 }
```



---

## 第15题. 三数之和

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int left, right;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                return res;
            }

            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            left = i + 1;
            right = nums.size() - 1;


            while (left < right) {
                if (nums[i] + nums[left] + nums[right] > 0) {
                    right--;
                } else if (nums[i] + nums[left] + nums[right] < 0) {
                    left++;
                } else {
                    res.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    left++;
                    right--;

                    while (left < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                    
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                    
                }

            }

        }

        return res;
    }
};
```



---

## 第18题. 四数之和

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        std::sort(nums.begin(), nums.end());
        int i, j, left, right;

        for (int i = 0; i < nums.size(); ++i) {
            /*这部分不能要如果为负数 则单独负数比负数之和要大
            if (nums[i] > target) {
                return res;
            }*/

            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            for (int j = i + 1; j < nums.size(); ++j) {
                /* 这部分不能要，因为j遍历到后边可以两个数加起来就够大了
                if (nums[i] + nums[j] > target) {
                    return res; 
                }
                */

                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }

                left = j + 1;
                right = nums.size() - 1;

                while (left < right) {
                    if (nums[i] + nums[j] + nums[left] + nums[right] > target) {
                        right--;
                    } else if (nums[i] + nums[j] + nums[left] + nums[right] < target) {
                        left++;
                    } else {
                        res.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        while (left < right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        left++;
                        right--;
                    }
                }
            }
        }
        return res;
    }
};
```





## 535. TinyURL 的加密与解密

- Encoder 函数

设字符串 longUrl 的长度为 n，选择两个合适的质数 $k_1 = 1117$，$k_2 = 10^9+7$，使用以下方法来计算 longUrl 和哈希值：
$$
\begin{equation}
 \operatorname{Hash}(  longUrl  )=\left( \sum_{i=0}^{n-1}\right.  longUrl  \left.[i] \times k_{1}^{i}\right) \bmod k_{2} 
\end{equation}
$$
将哈希值作为 longUrl 和 key，将键值对 (key, longUrl) 插入数据库 dataBase，然后返回带有 key 的字符串作为 shortUrl

> 发生哈希冲突时，我们采用线性探测再散列的方法，将 key 加一，直到没有冲突。相同的 longUrl 的哈希值相同，因此哈希冲突会频繁发生。为了避免这一点，我们使用一个额外的哈希表记录从 longUrl 到 key 映射。



- Decoder 函数

将 shortUrl 转换成对应的 key，然后在数据库 dataBase 中查找 key 对应的 longUrl

```c++
typedef long long ll;
const ll k1 = 1117;
const ll k2 = 1e9 + 7;

class Solution {
private:
    unordered_map<int, string> dataBase;
    unordered_map<string, int> urlToKey;

public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string res = "http://tinyurl.com/";
        
        if (urlToKey.count(longUrl) > 0) {
            return res + to_string(urlToKey[longUrl]);
        }
        
        ll key = 0, base = 1;
        for (auto c : longUrl) {
            key = (key + c * base) % k2;
            base = (base * k1) % k2;
        }        
        
        while (dataBase.count(key) > 0) {
            key = (key + 1) % k2;
        }

        dataBase[key] = longUrl;
        urlToKey[longUrl] = key;

        return res + to_string(key);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int p = shortUrl.rfind('/') + 1;    // 从字符串右侧开始匹配
        int key = stoi(shortUrl.substr(p, int(shortUrl.size()) - p));

        return dataBase[key];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
```



---

# 447. 回旋镖的数量

题目所描述的回旋镖可以视作一个 V 型的折线。我们可以枚举每个 points[i]，将其当作 V 型的拐点。设 points 中有 m 个点到 points[i] 的距离均相等，我们需要从这 m 点中选出 2 个点当作回旋镖的 2 个端点，由于题目要求考虑元组的顺序，因此方案数即为在 m 个元素中选出 2 个不同元素的排列数，即：

$$
A_m^2 = m\cdot(m-1)
$$
据此，我们可以遍历 points，计算并统计所有点到 points[i] 的距离，将每个距离的出现次数记录在哈希表中，然后遍历哈希表，并用上述公式计算并累加回旋镖的个数。

在代码实现时，我们可以直接保存距离的平方，避免复杂的开方运算



```c++
class Solution {
public:
    inline int getDis(vector<int> &v1, vector<int> &v2) {
        return (v1[0] - v2[0]) * (v1[0] - v2[0]) + (v1[1] - v2[1]) * (v1[1] - v2[1]);
    }

    int numberOfBoomerangs(vector<vector<int>>& points) {
        int res = 0, n = points.size();

        
        for (int i = 0; i < n; ++i) {               // 选为拐点
            unordered_map<int, int> ump;            // k->v  距离->个数
            for (int j = 0; j < n; ++j) {           // 距离
                if (i == j) continue;
                ump[getDis(points[i], points[j])]++;
            }

            for (auto &[_, m] : ump) {              // 遍历 [距离,个数]
                res += m * (m - 1);
            }

        }
        
        return res;
    }
};
```

