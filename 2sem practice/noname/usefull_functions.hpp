#include <string>
#include <vector>

enum cnt_parameter
{
	upper,
	lower,
	digits,
	spaces
};

/*
void iterating_over_combinations(std::vector& vct, const std::string& src)
{
	
}
*/

int str_count(cnt_parameter par, const std::string& str)
{
	int cnt = 0;

	for(int i = 0; i < str.length(); ++i)
	{
		switch(par)
		{
			case upper:
				if (isupper(str[i]))
					++cnt;
				break;
			
			case lower:
				if (islower(str[i]))
					++cnt;
				break;

			case digits:
				if (isdigit(str[i]))
					++cnt;
				break;

			case spaces:
				if (isspace(str[i]))
					++cnt;
				break;

			default:
				break;
		}
	}	

	return cnt;
}

std::string transform_string(const std::string& source)
{
	std::string newString = "";

	for(int i = 0; i < source.length(), ++i)
	{
		char c = source[i];

		if(isupper(c))
		{
			newString.append(tolower(c));
			continue;
		}

		if(islower(c))
		{
			newString.append(toupper(c));
			continue;
		}

		if(isspace(c))
			continue;
	}

	
}
