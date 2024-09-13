#ifndef _QUEUE_TEST_H_
#define _QUEUE_TEST_H_
#include "../queue.h"
#include <iostream>

using namespace std;

class QueueTest{
public:
    IQueue<int>* queue_;
    QueueTest(IQueue<int>* queue){
        queue_ = queue;
        IsEmptyTest();
        PushTest();
        TopTest();
        PopTest();
        OtherTest(queue_);
    }
    
    void IsEmptyTest(){
        cout << "Test method IsEmpty: " << endl;
        cout << "Is empty: " << queue_->IsEmpty() << endl;
    }

    void PushTest(){
        cout << "Test method Push" << endl;
        queue_->Push(3);
        queue_->Push(2);
        cout << "Length: " << queue_->Length() << endl;
    }

    void PopTest(){
        cout << "Test method Pop" << endl;
        int t = 0;
        queue_->Pop(t);
        cout << "Poped elem is " << t << endl;
        cout << "Length: " << queue_->Length() << endl;
    }

    void TopTest(){
        cout << "Test method Top" << endl;
        int t = queue_->Top();
        cout << "Top elem is " << t << endl;
    }
    
    void LengthTest(){
        cout << "Test method Length" << endl;
        cout << "Queue length is " << queue_->Length() << endl;
    }

    
    void OtherTest(IQueue<int>* queue);
};


#endif

