#include "sequence.h"
#include <iostream>

int main() {
    coen70_lab3::sequence seq1;
    coen70_lab3::sequence seq2;
    
    seq1.insert(12);
    seq1.insert(17);
    seq1.insert(52);
    seq1.insert(45);
    
    seq2.insert(2);
    seq2.insert(3);
    seq2.insert(5);
    seq2.insert(7);
    
    coen70_lab3::sequence seq3;
    seq1 += seq2;
    
    for(int i = 0; i < 8; i++) {
        std::cout << seq1.current() << std::endl;
        seq1.advance();
    }
    
    return 0;
    }