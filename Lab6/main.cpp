#include <iostream>
#include "mystring.h"

using namespace coen70_lab6;

int main()
{
	string s1 = "test";
	string s2('a');

	std::cout << s2 << std::endl;

	string s3 = "foo";
	s1.insert(s3, 1);

	std::cout << s1 << std::endl;

	s1.dlt(1, 3);

	std::cout << s1 << std::endl;

	s1.replace('s', 3);

	std::cout << s1 << std::endl;

	s1.replace(s3, 0);

	std::cout << s1 << std::endl;

	std::cout << s1.search('o') << std::endl;
	std::cout << s1.search('q') << std::endl;

	std::cout << s1.count('o') << std::endl;

	string s4 = "oos";

	std::cout << s1.search(s4) << std::endl;

	return 0;
}
