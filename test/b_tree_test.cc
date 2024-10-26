#include "../b_tree.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    std::cout << "=================> Testing 4 Order B Tree" << std::endl;
    BTree<int> btree(4);    // 4阶B树
    btree.Insert(10);
    btree.Insert(20);
    btree.Insert(5);
    btree.Insert(6);
    btree.Insert(12);
    btree.Insert(30);
    btree.Insert(7);
    btree.Insert(17);

    std::cout << "B-Tree:" << std::endl;
    btree.Print();
    std::cout << std::endl;

    std::cout << "Contains 6: " << (btree.Find(6) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 15: " << (btree.Find(15) ? "Yes" : "No") << std::endl;

    std::cout << "Removing 6 and 20." << std::endl;
    btree.Remove(6);
    btree.Remove(20);

    std::cout << "B-Tree after deletions:" << std::endl;
    btree.Print();

    std::cout << "Tree size: " << btree.Size() << std::endl;
    std::cout << "Is tree empty: " << (btree.Empty() ? "Yes" : "No") << std::endl;


    return 0;
}