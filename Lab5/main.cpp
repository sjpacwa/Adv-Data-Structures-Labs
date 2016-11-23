#include <iostream>
#include <iomanip>
#include "mystring.h"

using namespace coen70_lab5;
using std::cout;
using std::cin;

int main(void) {
    string test("hello world");
    string test2(test);
    
    cout << test << "   " << test2 << '\n';
    cout << std::boolalpha << (test == test2) << '\n';
    
    test += 'c';
    string test3 = test;
    cin >> test3;
    std::cout << '\n' << test3 << '\n';;
}

