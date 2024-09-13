#include "../huffman_tree.h"
#include <iostream>


using namespace std;


int main(){
    int arr[] = {25,15,10,15,35};
    HuffmanTree huf(arr, 5);

    map<int, std::vector<vector<bool> > > res;
    huf.GetCoding(res);
    
    cout << "=======>Test huffman_tree:" << endl;
    cout << "==========>Test method GetCoding:" << endl;
    for(auto it=res.begin(); it!=res.end(); it++){
        cout << "Node weight = " << it->first << " , code is :" << endl;
        for(int i=0; i<it->second.size(); i++){
            for(int j=0; j<it->second[i].size(); j++){
                cout << it->second[i][j];
            }
            cout << endl;
        }

        cout << endl;
    }

    cout << "===========>Test method GetWpl:" << endl;
    cout << "WPL: " << huf.GetWpl() << endl;
    cout << "===========>Test static method GetWpl:" << endl;
    cout << "WPL: " << HuffmanTree::GetWpl(arr, 5) << endl;


    return 0;
}
