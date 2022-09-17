#include <iostream>
#include <algorithm>

using namespace std;

const int maxn=100;
//heap为堆,n为元素个数
int heap[maxn], n=10;

// 对heap数组在[low, high]范围进行向下调整   O(logN)
void downAdjust(int lo, int hi){
    int i = lo, j = i * 2;  // i 为欲调整结点，j 为其左孩子
    while (j <= hi) {
        if (j + 1 <= hi && heap[j + 1] > heap[j]) {
            j++;
        }

        if (heap[j] > heap[i]) {
            swap(heap[i], heap[j]);
            i = j;
            j = i * 2;
        } else break;
    }
}

void createHeap() {
    for (int i = n / 2; i >= 1; i--) {
        downAdjust(i, n);
    }
}

void heapSort() {
    createHeap();
    // 排序过程
    for (int i = n; i > 1; --i) {
        swap(heap[i], heap[1]);
        downAdjust(1, i - 1);
    }
}

int main () {
    for (int i = 1; i <= n; ++i) {
        int r = rand() % 10;
        heap[i] = r;
    } 

    heapSort();
    return 0;
}