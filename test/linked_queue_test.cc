#include "queue_test.h"

void QueueTest::OtherTest(IQueue<int>* queue){

}

int main(){
    LinkedQueue<int> queue;
    QueueTest((IQueue<int> *) &queue);
}
