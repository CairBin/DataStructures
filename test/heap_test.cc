#include "../heap.h"
#include <iostream>

using namespace std;

int main(){
    cout << "Testing Min-Heap ----------------->" << endl;
    Heap<int> h1;
    cout << "Insert 2" << endl;
    h1.Insert(2);
    cout << "Insert 1" << endl;
    h1.Insert(1);
    cout << "Insert 3" << endl;
    h1.Insert(3);


    cout << "Output: 1 2 3" << endl;
    cout << "Result: " ;
    while(!h1.Empty()){
        cout << h1.Peek() << " ";
        h1.Pop();
    }

    cout << endl << endl;

    cout << "Testing Max-Heap ----------------->" << endl;
    Heap<int, greater<int> > h2;
    cout << "Insert 2" << endl;
    h2.Insert(2);
    cout << "Insert 1" << endl;
    h2.Insert(1);
    cout << "Insert 3" << endl;
    h2.Insert(3);


    cout << "Output: 3 2 1" << endl;
    cout << "Result: ";
    while(!h2.Empty()){
        cout << h2.Peek() << " ";
        h2.Pop();
    }
    cout << endl;
    
    return 0;
}