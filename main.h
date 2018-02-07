#include <cstdio>
#include <string>
#include <vector>
#include "newsgroup.h"

unsigned int count_lines(FILE* p);

void tokenize(const std::string& str, std::vector<std::string>& tokens,
              const std::string& delimiters = ",");

int first_token(const std::string& str, const std::string& delim);

std::pair<std::string, double> naive_bayes_classify(
    const std::vector<int>& in_words,
    double (*estimator)(const naive_bayes::newsgroup& ng,
                        const std::vector<std::string>& in_words));

double naive_bayes_be(const std::vector<naive_bayes::newsgroup>& newsgroups,
                      const std::vector<std::string>& words);

double naive_bayes_mle(const naive_bayes::newsgroup& ng,
                       const std::vector<naive_bayes::word>& words)
