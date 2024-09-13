#include "queue_test.h"

void QueueTest::OtherTest(IQueue<int>* queue){
    try{
    CircularQueue<int>* q = (CircularQueue<int>*)queue;
    cout << "Test method ExtendSize(1)" << endl;
    q->ExtendSize(1);
    cout << "Now maxsize is " << q->GetMaxsize() << endl;
    cout << "Length: " << q->Length() << endl;
    q->Push(789);
    cout << "first push ok" << endl;
    q->Push(642);
    cout << "second push ok" << endl;
    q->Push(999);
    cout << "third push ok" << endl;
    cout << "Length: " << q->Length() << endl;
    int t;
    q->Pop(t);
    q->Push(888);
    cout << q->Top() << endl;
    }catch(const char* e){
            cout << "Error: " << e << endl;
    }
}

int main(){
    cout << "SqQueue maxsize is 3" << endl;
    CircularQueue<int> sq(3);
    QueueTest t((IQueue<int>*) &sq);

}
