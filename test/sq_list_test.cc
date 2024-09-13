#include "../sq_list.h"
#include "linear_list_test.h"

using namespace std;

void LinearListTest::OtherTest(ILinearList<int>* lst){
    SqList<int>* l = (SqList<int>*)lst;
    cout << "Test method ExtendSize" << endl;
    l->ExtendSize(1);
    cout << "The size has increased to " << 4 << endl;
    l->PushBack(11);
    l->PrintList();
    cout << "Tips: throwing exception, because of maxsize" << endl;
    l->PushBack(12);
}

int main(){
    uint32_t maxsize = 3;
    cout << "Creating SqList, maxsize = " << maxsize << endl;
    SqList<int> lst(maxsize);
    
    LinearListTest test((ILinearList<int>*)&lst);
}
