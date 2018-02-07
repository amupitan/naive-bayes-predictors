#include <cstdio>
#include <string>
#include <vector>
#include "newsgroup.h"

unsigned int count_lines(FILE* p);

typedef double (*estimator_t)(const naive_bayes::newsgroup&,
                              const std::vector<naive_bayes::word>&);

void tokenize(const std::string& str, std::vector<std::string>& tokens,
              const std::string& delimiters = ",");

int first_token(const std::string& str, const std::string& delim);

std::pair<std::string, double> naive_bayes_classify(
    const std::vector<int>& in_words, estimator_t estimator);

double naive_bayes_be(const naive_bayes::newsgroup& ng,
                      const std::vector<naive_bayes::word>& words);

double naive_bayes_mle(const naive_bayes::newsgroup& ng,
                       const std::vector<naive_bayes::word>& words);

void predict(const std::vector<naive_bayes::newsgroup>& newsgroups,
             estimator_t estimator,
             std::map<naive_bayes::document, std::string>& docs);