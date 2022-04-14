#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 10;

int heap[maxn], n = 9;

// 对heap数组在[low, high] 范围进行向下调整
// low 为欲调整结点的数组下标，high一般为堆的最后一个元素的数组下标

void downAdjust(int lo, int hi) {
    int i = lo, j = i * 2;  // i 为欲调整结点，j为其左孩子
    while (j <= hi) {   // 存在孩子结点
        if (j + 1 <= hi && heap[j + 1] > heap[j]) {
            j++;
        }

        if (heap[j] > heap[i]) {
            swap(heap[j], heap[i]);
            i = j;
            j = i * 2;
        } else {
            break;
        }
    }
}

void upAdjust(int lo, int hi) {
    int i = hi, j = i / 2;

    while (j >= lo) {
        if (heap[j] < heap[i]) {
            swap(heap[j], heap[i]);
            i = j;
            j = i / 2;
        } else {
            break;
        }
    }
}

//删除堆顶元素 O(logN)
void deleteTop(){
    heap[1] = heap[n--];
    downAdjust(1, n);
}


void insert(int x){
    heap[++n] = x;	//元素个数+1
    upAdjust(1, n);	//向上调整新加入的结点 n
}


//建堆  O(N)
void createHeap(){
    for (int i = n / 2; i >= 1; i--){
        downAdjust(i, n);
    }
}

int main() {
    for (int i = 1; i <= n; ++i) {
        heap[i] = rand() % 10;
    }
    createHeap();
    deleteTop();
    insert(rand() % 5);

    return 0;
}