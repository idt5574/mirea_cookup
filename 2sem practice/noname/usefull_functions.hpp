#include <string>
#include <vector>

enum cnt_parameter
{
	upper,
	lower,
	digits,
	spaces
};

size_t mix(const std::string& destination, const std::string& source, unsigned short depth = 0)
{
	static std::string combination;
	
	if(depth == 0)
		combination = "";

	combination += tolower(destination[depth]);
	
	if(depth < destination.length() - 1)
	{
		size_t result = mix(destination, source, depth + 1);

		if(result != std::string::npos)
			return result;
	}
	else
	{
		size_t pos = source.find(combination);

		if(pos != std::string::npos)
			return pos;
	}

	combination.pop_back();

	combination += toupper(destination[depth]);
	
	if(depth < destination.length() - 1)
	{
		size_t result = mix(destination, source, depth + 1);

		if(result != std::string::npos)
			return result;
	}
	else
	{
		size_t pos = source.find(combination);

		if(pos != std::string::npos)
			return pos;
	}

	combination.pop_back();

	return std::string::npos;
}

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

	for(int i = 0; i < source.length(); ++i)
	{
		char c = source[i];

		if(isupper(c))
		{
			newString += tolower(c);
			continue;
		}

		if(islower(c))
		{
			newString += toupper(c);
			continue;
		}

		if(isspace(c))
			continue;
		
		newString += c;
	}

	while (true)
	{
		size_t pos = mix("hello", newString);
		
		if(pos != std::string::npos)
			newString.replace(pos, pos + 5, "hi");
		else break;
	}

	return newString;
}
