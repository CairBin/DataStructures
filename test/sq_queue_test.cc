#include "queue_test.h"

void QueueTest::OtherTest(IQueue<int>* queue){
    SqQueue<int>* q = (SqQueue<int>*)queue;
    cout << "Test method ExtendSize(12)" << endl;
    q->ExtendSize(12);
    cout << "Now maxsize is " << q->GetMaxsize() << endl;
}

int main(){
    cout << "SqQueue maxsize is 3" << endl;
    SqQueue<int> sq(3);
    QueueTest t((IQueue<int>*) &sq);

}
