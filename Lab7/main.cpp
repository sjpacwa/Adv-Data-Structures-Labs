#include "sequence.h"
#include "node.h"
#include <iostream>

using namespace coen70_lab7;

void printseq(const sequence& seq)
{
    sequence s = seq;
    s.start();
    while(s.is_item())
          {
              std::cout << s.current() << " ";
              s.advance();
          }
          std::cout << std::endl;
    
}

int main() {
    sequence seq1, seq2;
    sequence seq3 = seq1;

    seq1.start();
    seq2.end();
    
    seq1.insert(5);
    seq1.insert(1);
    seq1.insert(7);
    seq1.insert(9);
    
    seq1.start();
    
    
    printseq(seq1);
    
    seq2.insert(4);
    seq2.attach(2);
    seq2.attach(4);
    seq2.attach(9);
    seq2.insert(10);
    
    seq1.start();
    seq2.start();
    
    printseq(seq2);
    
    seq2.end();
    
    seq1.start();
    
    seq1.remove_current();
    
    seq1.start();
    printseq(seq1);
    
    seq3 = seq2;
    
    seq3.start();
    printseq(seq3);
    
    return 0;
}