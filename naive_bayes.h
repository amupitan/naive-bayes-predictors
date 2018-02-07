#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#include "document.h"
#include "newsgroup.h"

namespace naive_bayes {

typedef double (*estimator_t)(const naive_bayes::newsgroup&,
                              const std::vector<naive_bayes::word>&);

double naive_bayes_be(const naive_bayes::newsgroup& ng,
                      const std::vector<naive_bayes::word>& words);

double naive_bayes_mle(const naive_bayes::newsgroup& ng,
                       const std::vector<naive_bayes::word>& words);

void predict(const std::vector<naive_bayes::newsgroup>& newsgroups,
             estimator_t estimator,
             std::map<naive_bayes::document, std::string>& docs);

std::pair<std::string, double> naive_bayes_classify(
    const std::vector<int>& in_words, estimator_t estimator);
}  // namespace naive_bayes

#endif