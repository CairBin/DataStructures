#ifndef _LINEAR_LIST_TEST_H_
#define _LINEAR_LIST_TEST_H_

#include "../linear_list.h"

using namespace std;

class LinearListTest{
public:
    LinearListTest(ILinearList<int>* lst){
        try{   
            cout << "Test method PushBack" << endl;
            lst->PushBack(18);
            lst->PushBack(20);
            cout << (lst->GetElem(1) == 20) << endl;
            lst->PrintList();

            cout << "Test method PushFront" << endl;
            lst->PushFront(32);
            cout << (lst->GetElem(0) == 32) << endl;
            lst->PrintList();

            cout << "Test method PopBack" << endl;
            int t;
            lst->PopBack(t);
            cout << (t == 20) << endl;
            lst->PrintList();

            cout << "Test method PopFront" << endl;
            lst->PopFront(t);
            cout << (t==32) << endl;
            lst->PrintList();

            cout << "Test method ListDelete and IsEmpty" << endl;
            lst->ListDelete(0,t);
            cout << lst->IsEmpty() << endl;
            lst->PrintList();

            cout << "Test method ListInsert" << endl;
            lst->PushBack(2);
            lst->PushBack(32);
            lst->ListInsert(1,33);
            lst->PrintList();
            cout << "Test method Length" << endl;
            cout << "length: " << lst->Length() << endl;
            cout << "Test method LocateElem" << endl;
            cout << "The index of elem 33 is " << lst->LocateElem(33) << endl;
        
            OtherTest(lst);
        }catch(const char* e){
            std::cout << "Error:" << e << std::endl;
        }
    }

    void OtherTest(ILinearList<int>* lst);
};

#endif

