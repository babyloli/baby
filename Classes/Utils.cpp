#include "Utils.h"

void split(const std::string& s, const std::string& delim, std::vector<std::string>* ret){
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (std::string::npos != index)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last > 0){
		ret->push_back(s.substr(last, index - last));
	}
}