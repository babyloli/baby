#ifndef __UTILS_H__
#define __UTILS_H__
#include <vector>
#include <string>

void split(const std::string& s, const std::string& delim, std::vector<std::string>* ret);
std::string itos(int i);

#endif