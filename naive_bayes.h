#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#include "document.h"
#include "newsgroup.h"

namespace naive_bayes {

/**
 * Signature for an estimator function
 * This could be a bayesian estimator or a maximum likelyhood estimator
 */
typedef double (*estimator_t)(const naive_bayes::newsgroup&,
                              const std::vector<naive_bayes::word>&);

/**
 * Bayesian estimator with naive bayes algorithm
 * \param ng the newsgroup being estimated
 * \param the set of words i.e. document, being considered
 */
double naive_bayes_be(const naive_bayes::newsgroup& ng,
                      const std::vector<naive_bayes::word>& words);

/**
 * Maximum likelyhood estimator with naive bayes algorithm
 * \param ng the newsgroup being estimated
 * \param the set of words i.e. document, being considered
 */
double naive_bayes_mle(const naive_bayes::newsgroup& ng,
                       const std::vector<naive_bayes::word>& words);

void predict(const std::vector<naive_bayes::newsgroup>& newsgroups,
             estimator_t estimator,
             std::map<naive_bayes::document, std::string>& docs);

std::pair<std::string, double> naive_bayes_classify(
    const std::vector<newsgroup>& newsgroups, const std::vector<word>& in_words,
    estimator_t estimator);

double overall_accuracy(std::map<std::string, double>& accuracy,
                        const std::vector<newsgroup>& newsgroups,
                        const std::map<document, std::string>& train_docs,
                        const std::map<document, std::string>& train_pred_docs,
                        bool is_test = false);
}  // namespace naive_bayes

#endif