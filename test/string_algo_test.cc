#include "../string_algo.h"
#include <iostream>

using namespace std;


void FindStringTest(){
    String s1 = "helloworld";
    String s2 = "ld";
    cout << "Test function FindString" << endl;
    cout << "Find \"ld\" from \"helloworld\"" << endl;
    cout << FindString(s1, s2) << endl;
}

void FindStringOptimizingTest(){
    String s1 = "helloworld";
    String s2 = "ld";
    cout << "Test function FindStringOptimizing" << endl;
    cout << "Find \"ld\" from \"helloworld\"" << endl;
    cout << FindStringOptimizing(s1, s2) << endl;
}

void KmpTest(){
    String s1 = "helloworld";
    String s2 = "ld";
    cout << "Test function Kmp:" << endl;
    cout << "Find \"ld\" from \"helloworld\"" << endl;
    cout << Kmp(s1, s2) << endl;
}

int main(){
    FindStringTest();
    FindStringOptimizingTest();
    KmpTest();

    return 0;
}
