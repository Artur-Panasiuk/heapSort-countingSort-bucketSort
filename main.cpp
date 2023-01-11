#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template<class T>
class bheap{
public:
    T *arr;
    int arrSize{16};
    int arrSizeMultipl{2};
    int usedSize{0};
    bheap(){
        arr = new T[arrSize];
    }
    bheap(T* arry, int siz){
        arr = arry;
        usedSize = siz;
    }
    ~bheap(){
        delete[]arr;
    }
    void expand(){
        arrSize *= arrSizeMultipl;
        T* temp = new T[arrSize];
        for(int i = 0; i < usedSize; i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    int getParent(int index){
        return (index - 1) / 2;
    }

    int getLChild(int index){
        return 2*index + 1;
    }

    int getRChild(int index){
        return 2*index + 2;
    }

    void swapPtr(int *a, int *b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapify(int siz, int index){
        int temp = index;

        int l = getLChild(index);
        int r = getRChild(index);

        if(l < siz && arr[l] > arr[temp])
            temp = l;
        if(r < siz && arr[r] > arr[temp])
            temp = r;
        if(temp != index){
            swapPtr(&arr[index], &arr[temp]);
            heapify(siz, temp);
        }
    }
    void add(T data){
        if(usedSize >= arrSize){
            expand();
            add(data);
        }

        int temp = usedSize;

        arr[usedSize] = data;
        usedSize++;

        while(temp != 0 && arr[getParent(temp)] < arr[temp]){
            swapPtr(&arr[getParent(temp)], &arr[temp]);
            temp = getParent(temp);
        }

    }

    void print(){
        for(int i = 0; i < usedSize; i++){
            cout<<arr[i]<< " ";
        }
        cout<<endl;
    }

    void heapSort(){
        for(int i = usedSize / 2 - 1; i >= 0; i--){
            heapify(usedSize, i);
        }
        for(int i = usedSize - 1; i > 0; i--){
            swapPtr(&arr[0], &arr[i]);
            heapify(i, 0);
        }
    }
};

void countSort(int *arr, int siz, int m){
    int maxv = m;

    int *temp = new int[maxv];
    int *out = new int[siz];

    for(int i = 0; i < maxv; i++){
        temp[i] = 0;
    }

    for(int i = 0; i < siz; i++){
        temp[arr[i]]++;
    }

    for(int i = 1; i <= maxv; i++){
        temp[i] += temp[i-1];
    }

    for(int i = siz -1; i >= 0; i--){
        out[temp[arr[i]] - 1] = arr[i];
        temp[arr[i]]--;
    }
    for(int i = 0; i < siz; i++){
        arr[i] = out[i];
    }
    delete[] temp;
    delete[] out;
}

void bucktSort(int *arr, int siz){
    int temp = 0;
    int index = 0;
    int maxv = 0;

    for(int i = 0; i < siz; i++){
        maxv = (maxv < arr[i]) ? arr[i] : maxv;
    }

    vector<int> bucket[siz];



    for(int i = 0; i < siz; i++){
        index = siz * arr[i];
        bucket[index].push_back(arr[i]);
    }
    for(int i = 0; i < maxv; i++){
        sort(bucket[i].begin(), bucket[i].end());
    }

    for(int i = 0; i < siz; i++){
        for(int j = 0; j < bucket[i].size(); j++){
            arr[temp++] = bucket[i][j];
        }
    }
}

void bucketSort(int arr[], int n)
{

    // 1) Create n empty buckets
    vector<int> b[n];

    // 2) Put array elements
    // in different buckets
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

int main()
{

    int arr[]
        = { 8, 5, 6, 1, 6, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);

    cout << "Sorted array is \n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    /*
    int siz = 6;

    int *b = new int[siz];

    b[0] = 1;
    b[1] = 5;
    b[2] = 3;
    b[3] = 6;
    b[4] = 8;
    b[5] = 1;

    for(int i = 0; i < siz; i++){
        cout << b[i] << " ";
    }

    cout<<endl;

    bucketSort(b, );


    for(int i = 0; i < siz; i++){
        cout << b[i] << " ";
    }

    delete[]b;

    /*
    int siz = 6;

    int *a = new int[siz];

    a[0] = 3;
    a[1] = 6;
    a[2] = 4;
    a[3] = 5;
    a[4] = 7;
    a[5] = 4;

    for(int i = 0; i < siz; i++){
        cout << a[i] << " ";
    }
    cout<<endl;

    countSort(a, siz, 8);

    for(int i = 0; i < siz; i++){
        cout << a[i] << " ";
    }

    delete[]a;
    */

    /*
    bheap<int> test;

    test.add(10);
    test.add(5);
    test.add(8);
    test.add(12);
    test.add(9);
    test.add(9);
    test.print();

    test.heapSort();

    test.print();
    */

    return 0;
}
