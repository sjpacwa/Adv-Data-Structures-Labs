#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>

//INVARIANT FOR STRING
// 1. current_length is the number of characters in the string, not including the null character.
// 2. allocated is the amount of space reserved for the dynamic string array.
// 3. sequence is a dynamic array of chars that stores a string terminated with a null character ('\0').

// For ops on char*
#include "string.h"

// My string header
#include "mystring.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;

// To enter debug mode, change DEBUGMODE to 1.  This
// is handy when you need to convince yourself exactly
// which of the methods is being called when
#define DEBUGMODE 0
#define DEBUG(s) if (DEBUGMODE) cerr << s << endl;

namespace coen70_lab6
{
	// Some of below implementation is copied from:
	// http://www-cs-students.stanford.edu/~wolfe/cpp/Mystring.cpp
	// and then modified.

	// CONSTRUCTORS AND DESTRUCTORS

	//
	// Constructor called when a string is constructed
	// with a char*.
	//
	string::string(const char str[])
	{
		DEBUG("Char* constructor")

		// Allocate enough space for the char*
		current_length = strlen(str);
		sequence = NULL;
        allocated = 0;
        reserve(current_length+1);
		sequence[0] = '\0';

		// Copy the char* into the internal string data
		strncpy(sequence, str, allocated);
	}

	//
	// Copy constructor.
	//
	string::string(const string& source)
	{
		DEBUG("string constructor")

		// Allocate enough space for the new string
		current_length = source.length();
        allocated = 0;
        reserve(current_length+1);

		// Copy the string buffer from the new string into
		// myself (I can access the private sequence in str
		// because I am also a member of string
		strncpy(sequence, source.sequence, allocated);
	}

	string::string(char c)
	{
		//Explicitly set all variables
        current_length = 1;
        allocated = 0;
        
        //Resere enough space for char
        reserve(2);
		sequence[0] = c;
		sequence[1] = '\0';
	}

	//
	// Destructor
	//
	string::~string()
	{
		DEBUG("Delete a str (" << sequence << ")")
		delete [] sequence;
	}

	// MODIFICATION MEMBER FUNCTIONS

	void string::operator +=(const string& addend)
	{
		DEBUG("String += operator string& parameter.")

		// Temp string to old the original data

		// Allocate enough space for both string
		reserve(current_length + addend.length() + 1);

		// Concat the strings
		strncat(sequence, addend.sequence, allocated - current_length);
		current_length += addend.length();
	}

	void string::operator +=(const char addend[ ])
	{
		DEBUG("String += operator char[] parameter.")
		string temp(addend);
		(*this) += temp;
	}

	void string::operator +=(char addend)
	{
		DEBUG("String += operator char parameter.")
		char temp[2];
		temp[0] = addend;
		temp[1] = '\0';
		(*this) += temp;
	}

	//
	// Increases size of sequence array if n > current size.
	//
	void string::reserve(size_t n)
	{
		DEBUG("Attempting to reserve " << n)
		// Only increase size with this function.
		if (n == allocated)
			return;

		if (n < current_length+1)
			n = current_length+1;

		char *temp = sequence;
		sequence = new char[n];
		assert(sequence != NULL);
		if (temp != NULL) {
			strncpy(sequence, temp, n);
			delete [] temp;
		}
		allocated = n;
	}

	void string::insert(const string& source, unsigned int position)
	{
		assert(position <= length());

        //reserve memory
		reserve(length() + source.length() + 1);

        //Shift old datato make space
		for (size_t i = length(); i >= position; --i)
		{
			sequence[i + source.length()] = sequence[i];
		}

        //Insert new data in position
		for (size_t j = 0; j < source.length(); ++j)
		{
			sequence[position + j] = source.sequence[j];
		}
        
        //update
		current_length += source.length();
	}

	void string::dlt(unsigned int position, unsigned int num)
	{
		assert( position + num <= length() );
		
        //Move data past deleted data left
		for (size_t i = position; i < length() - num; ++i)
		{
			sequence[i] = sequence[i + num];
		}
        
        //Add null character
		sequence[length() - num] = '\0';

        //Update
		current_length -= num;
	}

	void string::replace(char c, unsigned int position)
	{
		assert(position < length());

		sequence[position] = c;
	}

	void string::replace(const string& source, unsigned int position)
	{
		assert(position + source.length() <= length());

		//Replace data with new data
        for(size_t i = 0; i < source.length(); ++i)
		{
			sequence[i + position] = source.sequence[i];
		}
	}

	//
	// Assignment of a string into another string
	//
	string& string::operator=(const string& source)
	{
		DEBUG("string assignment operator")

		if (&source == this)
		{
			DEBUG("Not copying myself");
			return *this;
		}
		// Delete the old string that this class was holding.

		// Allocate enough space for the new string.
		current_length = source.length();
		reserve(current_length+1);

		// Copy the new string into myself
		strncpy(sequence, source.sequence, allocated);

		// Return myself
		return *this;
	}

	//
	// Return the character at a given position
	//
	char string::operator[](size_t pos) const
	{
		DEBUG("Calling []");
		if (pos >= length())
		{
			cerr << "Tried to access invalid string index\n";
			exit(1);
		}
		return sequence[pos];
	}

	int string::search(char c) const
	{
		int position = -1;
		
        //Break when char is found
        for (size_t i = 0; i < length(); ++i)
		{
			if (sequence[i] == c)
			{
				position = i;
				break;
			}
		}
		
        //Return updated position or -1
		return position;
	}

	int string::search(const string& substring) const
	{
		size_t current_sub_pos = 0;

		//Iterate through array
        for (size_t i = 0; i < length(); ++i)
		{
			//Check if next character in substring is found
            if (sequence[i] == substring[current_sub_pos])
			{
				//If at end, return pos of first character
                if (current_sub_pos == substring.length() - 1)
				{
					return i - substring.length() + 1;
				}
				//Increment if not at end
                else
				{
					++current_sub_pos;
				}
			}
            //If doesnt match reset
			else
			{
				current_sub_pos = 0;
			}
		}

		return -1;
	}


	unsigned int string::count(char c) const
	{
		int counter = 0;
		//Increment counter everytime c is found
        for (size_t i = 0; i < length(); ++i)
		{
			if (sequence[i] == c)
			{
				counter++;
			}
		}
		
		return counter;
	}

	// FRIEND FUNCTIONS

	//
	// Send the string to an output string.
	//
	ostream& operator<<(ostream& outs, const string& source)
	{
		DEBUG("<< operator")
		return outs << source.sequence;
	}

	//
	// Return if s2 is equal to s1 in
	// alphanumeric order
	bool operator==(const string&s1, const string& s2)
	{
		DEBUG("Calling ==");
		return (bool)(strcmp(s1.sequence, s2.sequence) == 0);
	}

	//
	// Return if s2 is not equal to s1 in
	// alphanumeric order
	bool operator !=(const string& s1, const string& s2)
	{
		DEBUG("Calling !=");
		return !(s1 == s2);
	}

	//
	// Return if s2 is before s1 in
	// alphanumeric order
	bool operator>(const string&s1, const string& s2)
	{
		DEBUG("Calling >");
		return (bool)(strcmp(s1.sequence, s2.sequence) > 0);
	}

	//
	// Return if s2 string is after s1 in
	// alphanumeric order
	bool operator<(const string&s1, const string& s2)
	{
		DEBUG("Calling <");
		return (bool)(strcmp(s1.sequence, s2.sequence) < 0);
	}

	//
	// Return if s2 is equal to or after s1 in
	// alphanumeric order
	bool operator >=(const string& s1, const string& s2)
	{
		DEBUG("Calling >=");
		return (s1 > s2 || s1 == s2);
	}

	//
	// Return if s2 is equal to or before s1 in
	// alphanumeric order
	bool operator <=(const string& s1, const string& s2)
	{
		DEBUG("Calling <=");
		return (s1 < s2 || s1 == s2);
	}

	// NON-MEMBER FUNCTIONS

	//
	// Concatenation of two strings
	//
	string operator+(const string& s1, const string& s2)
	{
		DEBUG("String + operator with 2 strings")

		// Temp string to old the original data
		string tmp;

		tmp += s1;
		tmp += s2;

		// Return the temporary string
		return tmp;
	}

	string operator+(const string& s1, const char addend[ ]) {
		DEBUG("String + operator with 1 string and 1 character array.")
		return s1 + string(addend);
	}

	// Read from an input stream
	//
	istream& operator>>(istream& ins, string& target)
	{
		DEBUG(">> operator")
		// Skip white space characters.
		while (ins && isspace(ins.peek()))
			ins.ignore();



		char tmp;

		// Clear the target string.
		target = "";

		// Read characters from the stream;
		while (ins && !isspace(ins.peek()))
		{
			ins >> tmp;
			target += tmp;
		}

		return ins;
	}
}
