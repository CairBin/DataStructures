#include "stack_test.h"

void StackTest::OtherTest(IStack<int>* stack){

}

int main(){
    LinkedStack<int> st;
    StackTest t((IStack<int>*) &st);

    return 0;
}
