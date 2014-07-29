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

std::string itos(int i)
{
	std::string s;
	bool neg = false;
	int count = 0;
	if (i < 0)
	{
		neg = true;
		i = -i;
	}

	int a = i;
	char b = 0;
	do 
	{
		a = a/10;
		count++;
	} while (a != 0);
	char* c = new char[count+1];
	memset(c, 0, count+1);
	if (!c)
		return NULL;
	char* p = c;
	do 
	{
		a = i % 10;
		b = '0' + a;
		i = i / 10;
		*p = b;
		p++;
	} while (i != 0);
	s.assign(c);
	if (neg){
		s.push_back('-');
	}	
	std::string ret;
	ret.assign(s.rbegin(), s.rend());
	delete [] c;
	return ret;
}