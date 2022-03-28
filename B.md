## 14. 最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 `""`。



```
输入：strs = ["flower","flow","flight"]
输出："fl"
```



分治

```c++

```











---

# 滑动窗口/双指针

## 76. 最小覆盖子串

给你一个字符串 `s` 、一个字符串 `t` 。返回 `s` 中涵盖 `t` 所有字符的最小子串。如果 `s` 中不存在涵盖 `t` 所有字符的子串，则返回空字符串 `""` 。



**注意：**

- 对于 `t` 中重复字符，我们寻找的子字符串中该字符数量必须不少于 `t` 中该字符数量。
- 如果 `s` 中存在这样的子串，我们保证它是唯一的答案。

 

**示例 1：**

```
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
```





```c++
unordered_map<char, int> umaps, umapt;

bool check() {
    for (auto c : umapt) {
        if (umaps[c.first] < c.second) {
            return false;
        }
    }
    return true;
}

string minWindow(string s, string t) {
 	for (auto c : t)
        umapt[c]++;
    
    int left = 0, right = 0;
    int len = INT_MAX, resL = -1;
    
    for (; right < t.size(); ++right) {
        char c = s[right];
        
        if (umapt.find(c) != umapt.end())
            umaps[c]++;
                
        while (check() && left <= right) {	//一旦满足 就移动 left 缩小
            if (right - left + 1 < len) {	//保存结果在里边
                len = right - left + 1;
                resL = left;
            }
            
            if (umapt.find(s[left]) != umapt.end()) {
                umaps[s[left]]--;
            }
            
            left++;
        }
        
    }
    
    return resL == -1 ? string() : s.substr(left, len);
}
```





---

# 二分

## 69.x 的平方根

二分查找第一个 res^2 大于x的元素，然后再减一



给你一个非负整数 `x` ，计算并返回 `x` 的 **算术平方根** 。

由于返回类型是整数，结果只保留 **整数部分** ，小数部分将被 **舍去 。**

**注意：**不允许使用任何内置指数函数和算符，例如 `pow(x, 0.5)` 或者 `x ** 0.5` 。

 

**示例 1：**

```
输入：x = 4
输出：2
```



```c++
int mySqrt(int x) {
    int left = 1, right = x;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if ((long long)mid * mid > x) {
            right = mid - 1;
        } else {
            left  = mid + 1; 
        } 
    }

    return left - 1;
}
```



### 牛顿迭代(补)

快速求解函数零点的方法。借助泰勒级数，从初始值开始快速向零点逼近。

```c++
int mySqrt(int x) {				//16
    if (x == 0) return 0;

    double C = x, x0 = x;		//16.0 16.0
    while (true) {
        double xi = 0.5 * (x0 + C / x0);	//
        if (fabs(x0 - xi) < 1e-7) break;
        x0 = xi;
    }
    return int(x0);
}
```









---

## 367.有效的完全平方数

给定一个 **正整数** `num` ，编写一个函数，如果 `num` 是一个完全平方数，则返回 `true` ，否则返回 `false` 。

**进阶：不要** 使用任何内置的库函数，如 `sqrt` 。

 

```
输入：num = 16
输出：true
```



```c++
bool isPerfectSquare(int num) {
    if (num == 1) return true;
    if (num == 2 | num == 3) return false;

    int left = 0, right = num / 2;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long tmp = (long long) mid * mid;
        if (tmp > num) {
            right = mid - 1;
        } else if (tmp < num) {
            left = mid + 1;
        } else {
            return true;
        }
    }

    return false;
}
```







# 排序

## 315. 计算右侧小于当前元素的个数

给你一个整数数组 `nums` ，按要求返回一个新数组 `counts` 。数组 `counts` 有该性质： `counts[i]` 的值是 `nums[i]` 右侧小于 `nums[i]` 的元素的数量。



```
输入：nums = [5,2,6,1]
输出：[2,1,1,0] 
解释：
5 的右侧有 2 个更小的元素 (2 和 1)
2 的右侧仅有 1 个更小的元素 (1)
6 的右侧有 1 个更小的元素 (1)
1 的右侧有 0 个更小的元素
```













# 回溯

----

## 71. 组合

给定两个整数 `n` 和 `k`，返回范围 `[1, n]` 中所有可能的 `k` 个数的组合。

你可以按 **任何顺序** 返回答案。

```
输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```



```c++
vector<vector<int>> res;
vector<int> resT;

void dfs(int start, int cnt, int n, int k) {
    if (cnt == k) {
        res.push_back(resT);
    }

    for (int i = start + 1; i <= n; ++i) {
        resT.push_back(i);
        dfs(i, cnt + 1, n, k);
        resT.pop_back();
    }

    return;
}

vector<vector<int>> combine(int n, int k) {
    vector<int> resT;
    dfs(0, 0, n, k);    

    return res;
}
```







## 39. 组合总和

给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。



```
输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
7 也是一个候选， 7 = 7 。
仅有这两种组合。
```





```c++
vector<vector<int>> res;
vector<int> resT;

void dfs(int sum, int target, vector<int>& candidates, int start){
    if (sum == target) {
        res.push_back(resT);
        return;
    }

    for (int i = start; i < candidates.size(); ++i) {
        if (sum + candidates[i] <= target) {
            resT.push_back(candidates[i]);
            sum += candidates[i];
            dfs(sum, target, candidates, i);
            sum -= candidates[i];
            resT.pop_back();
        }
    }

    return;
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {


    dfs(0, target, candidates, 0);
    return res;
}
```







---

## 40. 组合总和II

本题的难点在于区别2中：集合（数组candidates）有重复元素，但还不能有重复的组合。

给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用 一次 。

注意：解集不能包含重复的组合。 

 

```
输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
```





```c++
vector<vector<int>> res;
vector<int> resT;

void dfs(vector<int>& candidates, int target, int sum, int start) {
    if (sum == target) {
        res.push_back(resT);
        return;
    }

    for (int i = start; i < candidates.size(); ++i) {
        if (i > 0 && candidates[i] == candidates[i-1]  && i > start) {
            continue;
        }
        if (sum + candidates[i] <= target) {
            sum += candidates[i];
            resT.push_back(candidates[i]);
            dfs(candidates, target, sum, i+1);
            resT.pop_back();
            sum -= candidates[i];
        }
    }

    return;
}


vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    dfs(candidates, target, 0, 0);

    return res;
}
```



## 216题. 组合总和III

找出所有相加之和为 `n` 的 `k` 个数的组合，且满足下列条件：

- 只使用数字1到9
- 每个数字 **最多使用一次** 

返回 *所有可能的有效组合的列表* 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。

 

```
输入: k = 3, n = 7
输出: [[1,2,4]]
解释:
1 + 2 + 4 = 7
没有其他符合的组合了。
```



```c++
vector<vector<int>> res;
vector<int> resT;

void dfs(int k, int n, int start, int sum) {
    if (resT.size() == k && sum == n) {
        res.push_back(resT);
        return;
    }

    for (int i = start; i <= 9; ++i) {
        if (sum + i <= n) {		//这里不剪枝 也不会降低效率
            resT.push_back(i);
            sum += i;
            dfs(k, n, i+1, sum);
            sum -= i;
            resT.pop_back();
        }
    }


    return;
}

vector<vector<int>> combinationSum3(int k, int n) {
    dfs(k, n, 1, 0);

    return res;
}
```



---

## 78. 子集

集合中元素是不同的

给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。



```
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```



```c++
vector<vector<int>> res;
vector<int> resT;
void dfs(vector<int>& nums, int start){
    if (start >= nums.size()) {
        return;
    }
    res.push_back(resT);


    for (int i = start; i < nums.size(); ++i) {
        resT.push_back(nums[i]);
        dfs(nums, i + 1);
        resT.pop_back();
    }

    return;
}

vector<vector<int>> subsets(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    dfs(nums, 0);
    return res;
}
```







---

## 90. 子集II

集合中元素可以相同



给你一个整数数组 `nums` ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。返回的解集中，子集可以按 **任意顺序** 排列。

 

**示例 1：**

```
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
```



```c++
    vector<vector<int>> res;
    vector<int> resT;

    void dfs(vector<int>& nums, int start) {
        res.push_back(resT);

        unordered_set<int> uset;
        for (int i = start; i < nums.size(); ++i) {
            if (uset.find(nums[i]) != uset.end()) {
                continue;
            }
            uset.insert(nums[i]);
            resT.push_back(nums[i]);
            dfs(nums, i+1);
            resT.pop_back();
        }

        return;
    }


    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // ！！！！！！！！！！！！
        dfs(nums, 0);
        return res;
    }

```





## 491. 递增子序列

在图中可以看出，同⼀父节点下的同层上使用过的元素就不能在使用了



给你一个整数数组 `nums` ，找出并返回所有该数组中不同的递增子序列，递增子序列中 **至少有两个元素** 。你可以按 **任意顺序** 返回答案。

数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。



```
输入：nums = [4,6,7,7]
输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
```



```c++
vector<vector<int>> res;
vector<int> resT;
void dfs(vector<int>& nums, int start) {
    if (resT.size() >= 2) {
        res.push_back(resT);
    }

    unordered_set<int> uset;

    for (int i = start; i < nums.size(); ++i) {
        if (uset.find(nums[i]) != uset.end()) {
            continue;
        }

        if (resT.size() == 0 || nums[i] >= resT.back()) {
            uset.insert(nums[i]);
            resT.push_back(nums[i]);
            dfs(nums, i+1);
            resT.pop_back();
        }
    }

    return;
}

vector<vector<int>> findSubsequences(vector<int>& nums) {

    dfs(nums, 0);
    return res;
}
```





## 46. 全排列

给定一个不含重复数字的数组 `nums` ，返回其 *所有可能的全排列* 。你可以 **按任意顺序** 返回答案。



```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```



```c++
vector<vector<int>> res;
vector<int> resT;  
unordered_set<int> uset;

void dfs(vector<int>& nums) {
    if (resT.size() == nums.size()) {
        res.push_back(resT);
        return;
    }


    for (int i = 0; i < nums.size(); ++i) {
        if (uset.find(nums[i]) == uset.end()) {
            uset.insert(nums[i]);
            resT.push_back(nums[i]);
            dfs(nums);
            resT.pop_back();
            uset.erase(nums[i]);
        }
    }


    return;
}

vector<vector<int>> permute(vector<int>& nums) {
    //sort(nums.begin(), nums.end());
    dfs(nums);

    return res;
}   
```





## 47. 全排列 II

给定一个可包含重复数字的序列 `nums` ，***按任意顺序*** 返回所有不重复的全排列。

 

```
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
```



```c++
vector<vector<int>> res;
vector<int> resT;
unordered_set<int> uset;  // 存下标

void dfs(vector<int>& nums) {
    if (resT.size() == nums.size()) {
        res.push_back(resT);
        return;
    }

    unordered_set<int> uuset; // 存数字

    for (int i = 0; i < nums.size(); ++i) {
        if (uuset.find(nums[i]) != uuset.end())
            continue;

        if (uset.find(i) == uset.end()) {
            uuset.insert(nums[i]);
            uset.insert(i);
            resT.push_back(nums[i]);
            dfs(nums);
            resT.pop_back();
            uset.erase(i);
        }

    }

    return;
}


vector<vector<int>> permuteUnique(vector<int>& nums) {
    dfs(nums);
    return res;
}
```





## 51. N皇后

**放 Queen，更新 Attack数组**

```c++
void putQueen(int x, int y, vector<vector<int>> &attack) {
    int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    attack[x][y] = 1;

    for (int i = 1; i < attack.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            int ax = x + i * dx[j];
            int ay = y + i * dy[j];

            if (ax >= 0 && ax < attack.size() && ay >=0 && ay < attack.size()) {
                attack[ax][ay] = 1;
            }
        }
    }

}
```



**递归 + 回溯**

```c++
void bt(int cnt, int n, vector<string> &queen, vector<vector<int>> &attack, vector<vector<string>> &solve) {

    if (cnt == n) {     //放皇后的数目, 也表示行数
        solve.push_back(queen);
        return;
    }

    for (int i = 0; i < n; ++i) {
        if(attack[cnt][i] == 0) {
            queen[cnt][i] = 'Q';
            vector<vector<int>> tmp = attack;
            putQueen(cnt, i, attack);
            bt(cnt+1, n, queen, attack, solve);
            attack = tmp;
            queen[cnt][i] = '.';
        }
    }
}
```



**主函数**

```c++
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> solve;
    vector<vector<int>> attack;
    vector<string> queen;
	
    for (int i = 0; i < n; ++i) {	
        attack.push_back(vector<int>());
        for (int j = 0; j < n; ++j) {
            attack[i].push_back(0);
        }
        queen.push_back("");
        queen[i].append(n, '.');
    }


    bt(0, n, queen, attack, solve);


    return solve;
}
```





## 37. 解数独

**判断棋盘是否合法有如下三个维度**：

同行是否重复
同列是否重复
9宫格里是否重复

```c++
bool isValid(int row, int col, char val, vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) { // 判断行里是否重复
        if (board[row][i] == val) {
        	return false;
        }
    }
    
    for (int j = 0; j < 9; j++) { // 判断列里是否重复
        if (board[j][col] == val) {
            return false;
        }
    }
    
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    
    for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == val ) {
                return false;
            }
        }
    }
    return true;
}
```



```c++
 bool backTracking(vector<vector<char>>& board) {
     for (int i = 0; i < board.size(); ++i) {
         for (int j = 0; j < board.size(); ++j) {

             if (board[i][j] != '.') continue;

             for (char k = '1'; k <= '9'; k++) {
                 if (isValid(i, j, k, board)) {
                     board[i][j] = k;
                     if (backTracking(board)) return true;
                     board[i][j] = '.';
                 }
             }

             return false;
         }
     }

     return true;
 }
```

