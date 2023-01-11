#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;


template<class T>
class bheap {
public:
    T* arr;
    int arrSize{ 16 };
    int arrSizeMultipl{ 2 };
    int usedSize{ 0 };
    bheap() {
        arr = new T[arrSize];
    }
    bheap(T* arry, int siz) {
        arr = arry;
        usedSize = siz;
    }
    ~bheap() {
        delete[]arr;
    }
    void expand() {
        arrSize *= arrSizeMultipl;
        T* temp = new T[arrSize];
        for (int i = 0; i < usedSize; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    int getParent(int index) {
        return (index - 1) / 2;
    }

    int getLChild(int index) {
        return 2 * index + 1;
    }

    int getRChild(int index) {
        return 2 * index + 2;
    }

    void swapPtr(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapify(int siz, int index) {
        int temp = index;

        int l = getLChild(index);
        int r = getRChild(index);

        if (l < siz && arr[l] > arr[temp])
            temp = l;
        if (r < siz && arr[r] > arr[temp])
            temp = r;
        if (temp != index) {
            swapPtr(&arr[index], &arr[temp]);
            heapify(siz, temp);
        }
    }
    void add(T data) {
        if (usedSize >= arrSize) {
            expand();
            add(data);
        }

        int temp = usedSize;

        arr[usedSize] = data;
        usedSize++;

        while (temp != 0 && arr[getParent(temp)] < arr[temp]) {
            swapPtr(&arr[getParent(temp)], &arr[temp]);
            temp = getParent(temp);
        }

    }

    void print() {
        for (int i = 0; i < usedSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void heapSort() {
        for (int i = usedSize / 2 - 1; i >= 0; i--) {
            heapify(usedSize, i);
        }
        for (int i = usedSize - 1; i > 0; i--) {
            swapPtr(&arr[0], &arr[i]);
            heapify(i, 0);
        }
    }
};

void countSort(int* arr, int siz) {
    int maxv = *max_element(arr, arr + siz);

    int* temp = new int[siz];
    int* out = new int[siz];

    for (int i = 0; i < siz; i++) {
        temp[i] = 0;
    }

    for (int i = 0; i < siz; i++) {
        temp[arr[i]]++;
    }

    for (int i = 1; i < siz; i++) {
        temp[i] += temp[i - 1];
    }

    for (int i = siz - 1; i >= 0; i--) {
        out[temp[arr[i]] - 1] = arr[i];
        temp[arr[i]]--;

    }
    for (int i = 0; i < siz; i++) {
        arr[i] = out[i];
    }
    delete[] temp;
    delete[] out;
}

void main_ints() {
    srand(0);

    const int MAX_ORDER = 7;
    const int m = (int)pow(10, 7);

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = (int)pow(10, o);

        int* array1 = new int[n];

        for (int i = 0; i < n; i++) {
            int rand_val = rand() % 10;
            array1[i] = rand_val;
        }
        int* array2 = new int[n];
        //int* array3 = new int[n];
        memcpy(array2, array1, n * sizeof(int));
        //memcpy(array3, array1, n * sizeof(int));
        
        clock_t t1 = clock();
        countSort(array1, n);
        clock_t t2 = clock();

        double now = (t2 - t1) / (double)CLOCKS_PER_SEC;

        cout << "Counting sort wykonanie w sekundach: " << now << endl;

        t1 = clock();
        bheap<int>* bh = new bheap<int>(array2, n);
        bh->heapSort();
        t2 = clock();

        now = (t2 - t1) / (double)CLOCKS_PER_SEC;

        cout << "bucket sort wykonanie w sekundach: " << now << endl;

        bool check = true;

        for (int i = 0; i < n; i++) {
            if (array1[i] != array2[i]) check = false;
        }

        if (!check) {
            cout << "tablice niezgodne" << endl;
        }

        cout << "---------" << endl;

        delete[] array1;
        delete[] array2;
        //delete[] array3;
    }
}

int main(){
    main_ints();

    return 0;
}
