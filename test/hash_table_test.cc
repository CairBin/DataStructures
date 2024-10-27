#include "../hash_table.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    
    cout << "Testing HashTable =======>" << endl;
    HashTable<string, int> table(10);
    cout << "Bucket size: " << 10 << endl;
    table.Insert("Alice", 123);
    cout << "Success to insert (\"Alice\", 123)" << endl;
    table.Insert("Bob", 456);
    cout << "Success to insert (\"Bob\", 456)" << endl;
    table.Insert("Charlie", 789);
    cout << "Success to insert (\"Charlie\", 789)" << endl;
    
    int t = -1;
    if(table.Find("Bob", t)){
        cout << "Found Bob: " << t << endl;
    }else{
        cout << "Bob not found" << endl;
    }

    table.Remove("Bob");
    cout << "Removed Bob" << endl;

    t = -1;
    if(table.Find("Bob", t)){
        cout << "Found Bob: " << t << endl;
    }else{
        cout << "Bob not found" << endl;
    }

    cout << "Hash table size: " << table.Size() << endl;
    cout << "Hash table is empty: " << table.Empty() << endl;
    
    return 0;
}