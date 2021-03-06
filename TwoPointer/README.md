# 双指针

**双指针法（快慢指针法）在数组和链表的操作中是非常常见的，很多考察数组和链表操作的面试题，都使用双指针法。**



## 27. 移除元素

**通过一个快指针和慢指针在一个for循环下完成两个for循环的工作。**



同向

```c++
int removeElement(vector<int>& nums, int val) {
    int slowIndex = 0; 
    for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {  
        if (val != nums[fastIndex]) { 
            nums[slowIndex++] = nums[fastIndex]; 
        }
    }
    return slowIndex;
}
```

![图片](assets/640.gif)

对向

```c++
int removeElement(vector<int>& nums, int val) {
    int i = 0;
    int size = nums.size() - 1;

    while (i <= size) {
        if (nums[i] == val) {
            nums[i] = nums[size];
            size--;
        } else {
            i++;
        }
    }
    return i;
}
```





## 344. 反转字符串

**如果题目关键的部分直接用库函数就可以解决，建议不要使用库函数。**

**如果库函数仅仅是 解题过程中的一小部分，并且你已经很清楚这个库函数的内部实现原理的话，可以考虑使用库函数。**

```c++
void reverseString(vector<char>& s) {
    for (int i = 0, j = s.size() - 1; i < s.size()/2; i++, j--) {
        swap(s[i],s[j]);
    }
}
```





## 剑指Offer 05. 替换空格

**「其实很多数组填充类的问题，都可以先预先给数组扩容带填充后的大小，然后在从后向前进行操作。」**



尽量不要用额外的辅助空间！

需要从后往前填充，从前向后填充就是 $O(n^2)$ 的算法了，因为每次添加元素都要将添加元素之后的所有元素向后移动。

```c++
string replaceSpace(string s) {
    int count = 0;
    int oldSize = s.size();
    for (int i = 0; i < oldSize; i++) {
        if (s[i] == ' ') {
            count++;
        }
    }
    s.resize(s.size() + count * 2); 
    int newSize = s.size();

    for (int i = newSize - 1, j = oldSize - 1; j < i; i--, j--) {
        if (s[j] != ' ') {
            s[i] = s[j];
        } else {
            s[i] = '0';
            s[--i] = '2';
            s[--i] = '%';
        }
    }

    return s;
}
```



---

## 151.翻转字符串里的单词

erase本来就是O(n)的操作，erase操作上面还套了一个for循环，那么以上代码移除冗余空格的代码时间复杂度为 $O(n^2)$ 。

**不要使用辅助空间**

- 移除多余空格
- 将整个字符串反转
- 将每个单词反转





使用双指针法来去移除空格，最后resize（重新设置）一下字符串的大小，就可以做到O(n)的时间复杂度。

```c++
// 逆转字符串
void reverseS(string &s, int start, int end) {
    for (int i = start, j = end; i < j; i++, j--) {
        swap(s[i], s[j]);
    }
}

// 去除多余的空格
void removeExtraSpaces(string& s) {
    int slow = 0;
    int fast = 0;
	
    // 去除最前方的空格
    while (s[fast] == ' ') {
        fast++;
    }
    
    
	// 去除字符串中间的空格
    for (; fast < s.size(); fast++) {
        if (s[fast] == ' ' && s[fast - 1] == ' ') { //保证字符串尾部本不可能有大于1个的空格
            continue;
        } else {
            s[slow] = s[fast];
            slow++;
        }
    }
	
    // 去除字符串最后的空格 最后可能是1个空格或者1个字母
    if (s[slow - 1] == ' ') {
        s.resize(slow - 1);
    } else {
        s.resize(slow);
    }
}

// 解
string reverseWords(string s) {
    removeExtraSpaces(s);
    reverseS(s, 0, s.size() - 1);
    int start = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            reverseS(s, start, i - 1);
            start = i + 1;
        }
    }
    reverseS(s, start, s.size() - 1);
    return s;
}
```



## 206. 反转链表

如果再定义一个新的链表，实现链表元素的反转，其实这是对内存空间的浪费。其实只需要**改变**链表的next指针的**指向**，直接将链表反转 ，而不用重新定义一个新的链表

![图片](assets/640-1617859633632.gif)

首先定义一个cur指针，指向头结点，再定义一个pre指针，初始化为null。

然后就要开始反转了，首先要把 cur->next 节点用tmp指针保存一下，也就是保存一下这个节点。

为什么要保存一下这个节点呢，因为接下来要改变 cur->next 的指向了，将cur->next 指向pre ，此时已经反转了第一个节点了。

接下来，就是循环走如下代码逻辑了，继续移动pre和cur指针。

最后，cur 指针已经指向了null，循环结束，链表也反转完毕了。此时我们return pre指针就可以了，pre指针就指向了新的头结点。

```c++
ListNode* reverseList(ListNode* head) {
    ListNode* cur = head;
    ListNode* tmp = nullptr;
    ListNode* res = nullptr;

    while (cur != nullptr) {
        tmp = cur;
        cur = cur->next;   // 注意它的位置，
        tmp->next = res;
        res = tmp;
    }
    return res;
}
```



## 142. 环形链表II

```c++
ListNode *detectCycle(ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    ListNode* cur = head;
    ListNode* slow = head->next;
    ListNode* fast = head->next->next;

    while (slow != fast && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if(fast == NULL || fast->next == NULL) {
        return NULL;
    }

    while (cur != slow) {
        cur = cur->next;
        slow = slow->next;
    }
    return slow;
}
```



- **解释为什么一定是慢指针跑完一圈之前被快指针追上：**

我们考虑，当慢指针第一次到入口的时候快指针的位置 



1.快指针在后：那快指针只要几步就能追上 

2.快慢指针重合，那就直接返回了，慢指针没有走的机会 

3.快指针在前，考虑极端情况，快指针就在慢指针的next



情况3其实跟赛跑一个道理，如果一个人速度是你的两倍，你们两个同是出发，相遇时候一定是在起点相遇，但是此时，比你跑的快的不讲武德，起跑点还比你靠前，所以肯定是在你跑完一圈之前他就追上你了

如果遇到一个人速度是你的两倍，你想在被抓到之前尽可能的跑长一些，那只能让跑的比你快的人起跑的时候在你的脸上（我们认为重合是还没跑就被抓了）

![图片](../Linked_list/assets/640.webp)





![图片](../Linked_list/assets/640-1617367448544.webp)





- 解释为什么是 2 倍速度/解释为什么 fast 不能跳过去呢

**fast相对于slow是一次移动一个节点，所以不可能跳过去**





- **从头结点出发一个指针，从相遇节点也出发一个指针，这两个指针每次只走一个节点， 那么当这两个指针相遇的时候就是 环形入口的节点**

把环铺开，因为速度为 2 倍关系，计算公式为

![图片](assets/640.webp)

slow 指针走过的节点数为: `x + y`， fast 指针走过的节点数：`x + y + n (y + z)`，n为fast指针在环内走了n圈才遇到slow指针， （y+z）为 一圈内节点的个数A。其中 n 必为1。

因为 fast 指针是一步走两个节点，slow 指针一步走一个节点， 所以 fast 指针走过的节点数 = slow 指针走过的节点数 * 2：

```
(x + y) * 2 = x + y + n (y + z)
```

有 n = 1，则公式就化解为 `x = z`





## 15. 三数之和

![图片](assets/640-1617860402834.gif)

时间复杂度：$O(n^2)$ 

```c++
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());

    int left,right;

    for (int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i-1]) {
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
                // 找到答案时，双指针同时收缩
                res.push_back(vector<int>{nums[i], nums[left], nums[right]});
                right--;
                left++;

                // 去重复值
                while (right > left && nums[right] == nums[right + 1]) {
                    right--;
                }
                while (right > left && nums[left] == nums[left - 1]) {
                    left++;
                }


            }
        }
    }
    return res;
}
```





---

## 18. 四数之和

多套一层循环，其实相当于四指针

```c++
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    std::sort(nums.begin(), nums.end());
    int i, j, left, right;

    for (i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (j = i + 1; j < nums.size(); j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }
            left = j + 1;
            right = nums.size() - 1;

            while (left < right) {
                if (nums[i] + nums[j] + nums[left] + nums[right] < target) {
                    left++;
                } else if (nums[i] + nums[j] + nums[left] + nums[right] > target) {
                    right--;
                } else if (nums[i] + nums[j] + nums[left] + nums[right] == target) {
                    res.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});

                    left++;
                    right--;

                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }

                    while (left < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                }
            }
        }
    }

    return res;
}
```

