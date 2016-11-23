/*
 * mystring.cpp
 * Written by: Stephen Pacwa and Ronak Gajrawala
 * 10/18/2016
 * Implementation of the string class.
 */

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <algorithm>

#include "mystring.h"

namespace coen70_lab5 {
    string::string(const char str[]) {
        // Initialize private member variables.
        allocated = 0;
        current_length = 0;
        sequence = NULL;
        
        // Reserve sequence and copy the argument to this class's sequence.
        
        reserve(strlen(str));
        strncpy(sequence, str, strlen(str));
        
        current_length = strlen(sequence);
    }
    
    string::string(const string& source) {
        // Initialize private member variables.
        allocated = 0;
        current_length = 0;
        sequence = NULL;
        
        // Reserve sequence and copy the argument to this class's sequence.
        
        reserve(source.allocated);
        strncpy(sequence, source.sequence, source.allocated);
        
        current_length = strlen(sequence);
    }
    
    string::~string() {
        // Make sure sequence is actually allocated before deleting.
        
        if (sequence != NULL) {
            delete sequence;
        }
    }
    
    void string::operator +=(const string& addend) {
        // Reserve additional space as needed.
        if (strlen(addend.sequence) + current_length >= allocated) {
            reserve(strlen(addend.sequence) + current_length);
        }
        
        // Concat the addend to this class's sequence and update length.
        
        strncat(sequence, addend.sequence, strlen(addend.sequence));
        
        current_length = strlen(sequence);
    }
    
    void string::operator +=(const char addend[]) {
        string newstr(addend);
        
        // Piggy-back off of `+=(const string&)`.
        
        *this += newstr;
    }
    
    void string::operator +=(char addend) {
        // Construct c-string array to piggy-back off of `+=(const char)`.
        char newadd[] = { addend, '\0' };
        
        *this += newadd;
    }
    
    void string::reserve(size_t n) {
        // If n is 0, allocate at least 1.
        if (n == 0) {
            n++;
        }
        
        // Do nothing if we have correct size already.
        if(n == allocated) {
            return;
        }
        
        // Allocate the new sequence and delete the old one (if it exists).
        // Then set the new sequence to the old one and update relevant metainfo.
        
        char *newstr = new char[n];
        if (sequence != NULL) {
            std::copy(sequence, sequence + n, newstr);
            delete sequence;
        }
        sequence = newstr;
        allocated = n;
    }
    
    string& string::operator =(const string& source) {
        // Set all private member variables from source to `this`.
        
        reserve(source.allocated);
        allocated = source.allocated;
        current_length = source.current_length;
        strncpy(sequence, source.sequence, current_length);
        
        return *this;
    }
    
    char string::operator [](size_t position) const {
        assert(position < length());
        
        return sequence[position];
    }
    
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.sequence;
        
        return outs;
    }
    
    bool operator ==(const string& s1, const string& s2) {
        return strcmp(s1.sequence, s2.sequence) == 0;
    }
    
    bool operator !=(const string& s1, const string& s2) {
        return !(s1 == s2);
    }
    
    bool operator > (const string& s1, const string& s2) {
        return strcmp(s1.sequence, s2.sequence) > 0;
    }
    
    bool operator < (const string& s1, const string& s2) {
        return strcmp(s1.sequence, s2.sequence) < 0;
    }
    
    bool operator >=(const string& s1, const string& s2) {
        return strcmp(s1.sequence, s2.sequence) >= 0;
    }
    
    bool operator <=(const string& s1, const string& s2) {
        return strcmp(s1.sequence, s2.sequence) <= 0;
    }
    
    string operator +(const string& s1, const string& s2) {
        // Create a new string from s1 and use += operator.
        
        string newstr(s1);
        newstr += s2;
        return newstr;
    }
    
    string operator +(const string& s1, const char addend[]) {
        // Create a new string from s1 and use += operator.
        
        string newstr(s1);
        newstr += addend;
        return newstr;
    }

    std::istream& operator >>(std::istream& ins, string& target) {
        // Remove all prepended whitespace.
        
        char check;
        while((check = ins.peek()) != EOF) {
            if(!isspace(check))
                break;
            
            ins.get();
        }
        
        // Overwrite target.
        
        string tmp;
        while((check = ins.get()) != EOF) {
            if(isspace(check))
                break;
            
            tmp += check;
        }
        
        target = tmp;
        
        return ins;
    }
    
}
