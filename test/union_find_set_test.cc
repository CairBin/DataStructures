#include "../union_find_set.h"

using namespace std;

void TestUnionFindSet(bool is_zip){
    cout << "=======>Test union_find_set:" << endl;
    cout << "=========>is_zip: " << is_zip << endl;
    Dsu s(12, is_zip);    // 第二个参数启用路径压缩
    s.Unite(4, 3);
    s.Unite(5, 3);
    s.Unite(2, 1);
    s.Unite(3, 1);

    cout << "=========>Test Find method, Result == 1:" << endl;
    cout << s.Find(4) << endl;
    cout << "=========>Print container:" << endl;
    s.Print();
    cout << endl;
}

int main(){
    TestUnionFindSet(false);
    TestUnionFindSet(true);

    return 0;
}
