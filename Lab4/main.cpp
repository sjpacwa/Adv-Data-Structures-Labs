#include <iostream>
#include "poly.h"

using namespace coen70_lab6;

int main() {
    polynomial p1, p2, p3;
    
    
    p1.assign_coef(-5.0, 3);
    p1.assign_coef(2.0, 2);
    p1.assign_coef(3.0, 1);
    p1.assign_coef(4.0, 0);
    
    p2.assign_coef(10.0, 3);
    p2.assign_coef(5.0, 2);
    p2.assign_coef(-1.0, 1);
    p2.assign_coef(7.0, 0);
    
    
    std::cout << p2.derivative() << std::endl;
    std::cout << p2 << "TEST" << std::endl;
    std::cout << p1 << "TEST2" << std::endl;
    std::cout << p1.derivative() << "TEST3" << std::endl;
    std::cout << p1.antiderivative() << "TEST4" << std:: endl;
    std::cout << p2.is_zero() << "TEST5" << std::endl;
    
    
    return 0;
}
