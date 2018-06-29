#ifndef __FAM

#define __FAM

#include <string>
#include <vector>

//Выполняет поиск образца P в тексте T
std::vector<int> finiteAutomatonMatcher(const std::string & P, const std::string & T, bool debug_write = false);

#endif