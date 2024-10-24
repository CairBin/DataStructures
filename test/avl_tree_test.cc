#include "../avl_tree.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main(){
    cout << "Testing AvlMap ------------------>" << endl;
    AvlMap<int, std::string> mapper;
    mapper.Insert(10, "ten");
    string value = "";
    mapper.Get(10, value);
    cout << "size: " << mapper.Size() << endl;
    cout << "Judging (10, \"ten\") Get(10, value) value==\"ten\" --->" << endl;
    assert(value == "ten");
    cout << "-------->Success<--------------" << endl;
    cout << "Testing AvlMap Remove method ---->" << endl;
    mapper.Remove(10);
    cout << "size: " << mapper.Size() << endl;
    cout << "-------> Success <-------" << endl;
    
    return 0;
}