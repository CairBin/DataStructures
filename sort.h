#ifndef _SORT_H_
#define _SORT_H_

#include <algorithm>
#include <iostream>
#include <numeric>

/// @brief 插入排序
/// @tparam T 数组元素类型
/// @param arr 排序数组
/// @param n 数组长度
template <class T>
void InsertSort(T arr[], int n){
    
    for(int i=1; i<n; i++){
        T temp = arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>temp){
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = temp;
    }
}


/// @brief 冒泡排序
/// @tparam T 数组元素类型
/// @param arr 排序数组
/// @param n 数组长度
template <class T>
void BubbleSort(T arr[], int n){
    bool flag = false;
    for(int i= n-1; i>=1; i--){
        for(int j=1; j<=i; j++){
            if(arr[j-1]>arr[j]){
                std::swap(arr[j-1], arr[j]);
                flag = true;
            }
        }

        if(!flag) return;
    }
}


/// @brief 快速排序
/// @tparam T 数组元素类型
/// @param arr 排序数组
/// @param n 数组长度
template <class T>
void QuickSort(T arr[], int n){
    if(n<=1) return;
    
    int pivot = arr[0];
    int low = 0;
    int high = n-1;
    while(low<high){
        while(low<high && pivot<=arr[high]) --high;
        arr[low] = arr[high];
        while(low<high && pivot>=arr[low])  ++low;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    QuickSort(arr, low);
    QuickSort(arr+low+1, n-low-1);
}

/// @brief 希尔排序
/// @tparam T 数组元素类型
/// @param arr 排序数组
/// @param n 数组长度
template <class T>
void ShellSort(T arr[], int n){
   int gap = n;
   while(gap>>=1){
    for(int i=gap; i<n; i++){
        T temp = arr[i];
        int j = i-gap;
        while(j>=0 && arr[j]>temp){
            arr[j+gap] = arr[j];
            j-=gap;
        }
        arr[j+gap] = temp;
    }
   }
}



/// @brief 归并排序
/// @tparam T 数组元素类型
/// @param arr 排序数组
/// @param n 数组长度
template <class T>
void MergeSort(T arr[], int n){
    T* temp = new T[n];
    auto Merge = [temp](T arr[], int low, int mid, int high){
        int i,j,k;
        for(k=low; k<=high; ++k) temp[k] = arr[k];
        for(i=low,j=mid+1, k=i; i<=mid&& j<=high; ++k)
            arr[k] = temp[i]<=temp[j] ? temp[i++] : temp[j++];

        while(i<=mid)   arr[k++] = temp[i++];
        while(j<=high)  arr[k++] = temp[j++];
    };

    std::function<void(T[], int)> InternalSort = 
    [&,Merge](T arr[], int n){
        if(n<=1) return;

        int mid = n>>2;
        InternalSort(arr, mid+1);
        InternalSort(arr+mid+1, n-mid-1);

        Merge(arr, 0, mid, n-1);
    };

    InternalSort(arr, n);

    delete temp;
}

/// @brief 选择排序（同时选最大值、最小值）
/// @tparam T 数组元素类型
/// @param arr 排序数组
/// @param n 数组长度
template <class T>
void SelectionSort(int arr[], int n){
    for(int i=0; i<n; i++,n--){

        int max_index = i;    //最大值元素索引
        int min_index = i;    //最小值元素索引
        // 遍历数组来寻找最大值、最小值
        for(int j=i; j<n;j++){
            if(arr[j] < arr[min_index]) min_index = j;
            if(arr[j] > arr[max_index]) max_index = j; 
        }

        // 交换最小值和第一个元素
        std::swap(arr[i], arr[min_index]);
        // 如果上面这个交换，第一个元素为最大值
        // 那么在接下来交换最大值的时候
        // 就把已经交换好的最小值放到末尾而乱序，因此要判断下
        if(max_index == i) max_index = min_index;
        // 交换最大值和最后一个元素(此时交换就没有任何问题了)
        std::swap(arr[n-1], arr[max_index]);
    }
}



#endif