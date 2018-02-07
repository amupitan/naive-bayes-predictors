#include <cstdio>
#include <string>
#include <vector>

unsigned int count_lines(FILE* p);

void tokenize(const std::string& str, std::vector<std::string>& tokens,
              const std::string& delimiters = ",");

int first_token(const std::string& str, const std::string& delim);
