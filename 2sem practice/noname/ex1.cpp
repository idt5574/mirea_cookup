#include <iostream>
#include <string>

#include "usefull_functions.hpp"

int main()
{
	std::string str;

	std::getline(std::cin, str);
	
	int countOfUpper = str_count(upper, str), 
	    countOfLower = str_count(lower, str), 
	    countOfDigits = str_count(digits, str), 
	    countOfSpaces = str_count(spaces, str);

	printf("Counted values:\n- upper: %d\n- lower: %d\n- digits: %d\n- spaces: %d\n", 
			countOfUpper, countOfLower, countOfDigits, countOfSpaces);

	std::string transformedString = transform_string(str); // Changes the letter case, removes spaces, replaces any "Hello" combination with Hi

	std::cout << "Transformed string: " << transformedString << std::endl;

	return 0;
}
