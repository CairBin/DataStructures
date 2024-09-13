#include "stack_test.h"

void StackTest::OtherTest(IStack<int>* stack){
    SqStack<int>* s = (SqStack<int>*) stack;
    s->Push(9);
    s->Push(250);

    cout << "Test method IsFull: " << endl;
    cout << "IsFull: " << s->IsFull() << endl;

    cout << "Test method ExtendSize:" << endl;
    cout << "Current maxsize: " << s->GetMaxsize() << endl;
    s->ExtendSize(3);
    cout << "Current maxsize: " << s->GetMaxsize() << endl;

    s->Push(114514);
}

int main(){
    cout << "SqStack size is 3" << endl;
    SqStack<int> st(3);
    StackTest((IStack<int>*) &st);    
}
