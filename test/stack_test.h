#ifndef _STACK_TEST_H_
#define _STACK_TEST_H_

#include "../stack.h"
#include <iostream>

using namespace std;

class StackTest{
public:
    IStack<int>* stack_;
    StackTest(IStack<int>* stack){
        stack_ = stack;
        IsEmptyTest();
        PushTest();
        TopAndPopTest();
        OtherTest(stack);
    }
    
    void IsEmptyTest(){
        cout << "Test method IsEmpty:" << endl;
        cout << "IsEmpty: " << stack_->IsEmpty() << endl;
    }

    void PushTest(){
        cout << "Test method Push:" << endl;
        stack_->Push(3);
        stack_->Push(2);
        cout << "Length: " << stack_->Length() << endl;
    }

    void TopAndPopTest(){
        cout << "Test method Top and Pop" << endl;
        cout << "length: " << stack_->Length() << endl;
        int t = stack_->Top();
        int t2;
        stack_->Pop(t2);
        cout << "Top: "<< t << endl;
        cout << "Pop: " << t2 << endl;
        cout << "length: " << stack_->Length() << endl;
    }

    void OtherTest(IStack<int>* stack);
};

#endif
