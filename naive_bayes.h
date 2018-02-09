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

/**
 * Predicts the class of each document
 * \param newsgroup classes
 * \param estimator the estimator used for classifying
 * \param docs the predicted document-class pair
 */
void predict(const std::vector<naive_bayes::newsgroup>& newsgroups,
             estimator_t estimator, std::map<naive_bayes::document, int>& docs);

/**
 * Runs an estimator on all data in all classes and returns the class with the
 * highest probability
 * \param newsgroup classes
 * \param in_words the list of all words
 * \param estimator the estimator used
 */
int naive_bayes_classify(const std::vector<newsgroup>& newsgroups,
                         const std::vector<word>& in_words,
                         estimator_t estimator);

/**
 * Calculates the accuracy of a classification
 * \param accuracy the list of accuracies per classification
 * \param newsgroups the classes
 * \param train_docs the actual documents
 * \param train_pred_docs the predicted documents
 * \param confusion_matrix confusion_matrix to be generated
 * \param is_test true if the train_docs is test data
 */
double overall_accuracy(std::vector<double>& accuracy,
                        const std::vector<newsgroup>& newsgroups,
                        const std::map<document, int>& train_docs,
                        const std::map<document, int>& train_pred_docs,
                        std::vector<std::vector<int>>& confusion_matrix,
                        bool is_test = false);
}  // namespace naive_bayes

#endif