#include "../sort.h"
#include <iostream>
#include <functional>
#include <vector>

using namespace std;


void TestSort(function<void(int[],int)> func, int arr[], int n, const string& info){

    cout << "Test sorting algorithm: " 
        << info 
        << " ===========>" 
        << endl;
    cout << "original array:" << endl;
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    int* temp = new int[n];
    memcpy(temp, arr, sizeof(int)*n);
    func(temp, n);

    cout << "ordered array:" << endl;
    for(int i=0; i<n; i++){
        cout << temp[i] << " ";
    }
    cout << endl << endl;
    delete temp;
}


int main(){
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    TestSort(InsertSort<int>,  arr, n, "Insert Sorting");
    TestSort(BubbleSort<int>,  arr, n, "Bubble Sorting");
    TestSort(QuickSort<int>,   arr, n, "Quick Sorting");
    TestSort(ShellSort<int>,   arr, n, "Shell Sorting");
    TestSort(MergeSort<int>,   arr, n, "Merge Sorting");
    TestSort(SelectionSort<int>, arr, n, "Selection Sorting");

    return 0;
}
