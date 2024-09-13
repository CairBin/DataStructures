#include "../linked_list.h"
#include "linear_list_test.h"

using namespace std;

void LinearListTest::OtherTest(ILinearList<int>* lst){

}


int main(){
    SingleLinkedList<int> lst;    
    LinearListTest test((ILinearList<int>*)&lst);
    return 0;
}
