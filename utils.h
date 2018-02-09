#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <string>
#include <vector>

/**
 * Tokenizes a string into a vector of tokens based on the delimeter
 * \param str the string
 * \param tokens the resulting vector of tokens
 * \param delimiters the delimeter
 */
void tokenize(const std::string& str, std::vector<std::string>& tokens,
              const std::string& delimiters = ",");

/**
 * Returns the first token from the string before the delimeter
 * \param str the string
 * \param delim delimeter
 */
int first_token(const std::string& str, const std::string& delim);

#endif