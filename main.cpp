#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "document.h"
#include "naive_bayes.h"
#include "newsgroup.h"
#include "parse_data.h"
#include "utils.h"

using namespace naive_bayes;
using std::string;
using std::vector;

void create_and_print_report(const vector<newsgroup>& newsgroups,
                             const std::map<document, int>& actual_docs,
                             const std::map<document, int>& pred_docs,
                             vector<double>& accuracy,
                             vector<vector<int>>& confusion_matrix,
                             bool is_test);

int main(int argc, char** argv) {
  constexpr auto path = "20newsgroups/";
  srand((unsigned)time(0));

  vector<newsgroup> newsgroups;
  std::map<document, int> train_docs;
  std::map<document, int> train_pred_docs;

  // create model from training data
  if (get_training_data(newsgroups, train_docs, train_pred_docs, path) == -1) {
    return -1;
  }

  // display priors
  for (const auto& ng : newsgroups) {
    std::cout << "Prior(" << ng.get_id() + 1 << ")  = " << ng.prior()
              << std::endl;
  }

  const int CLASS_SIZE = newsgroups.size();
  std::vector<double> accuracy(CLASS_SIZE);
  vector<vector<int>> confusion_matrix(CLASS_SIZE);
  for (auto& row : confusion_matrix) row = vector<int>(CLASS_SIZE);

  // classify training data using Bayesian Estimate
  predict(newsgroups, naive_bayes_be, train_pred_docs);
  std::cout << "BE training data:" << std::endl;
  create_and_print_report(newsgroups, train_docs, train_pred_docs, accuracy,
                          confusion_matrix, false);

  // get test data
  std::map<document, int> test_docs;
  std::map<document, int> test_pred_docs;
  if (get_test_data(newsgroups, test_docs, test_pred_docs, path) == -1) {
    return -1;
  }

  // classify test data using Bayesian Estimate
  predict(newsgroups, naive_bayes_be, test_pred_docs);
  std::cout << "BE test data:" << std::endl;
  create_and_print_report(newsgroups, test_docs, test_pred_docs, accuracy,
                          confusion_matrix, true);

  // classify test data using Maximum Likelyhood Estimate
  predict(newsgroups, naive_bayes_mle, test_pred_docs);
  std::cout << "MLE test data:" << std::endl;
  create_and_print_report(newsgroups, test_docs, test_pred_docs, accuracy,
                          confusion_matrix, true);

  return 0;
}

void create_and_print_report(const vector<newsgroup>& newsgroups,
                             const std::map<document, int>& actual_docs,
                             const std::map<document, int>& pred_docs,
                             vector<double>& accuracy,
                             vector<vector<int>>& confusion_matrix,
                             bool is_test) {
  // clear accuracy and mtrix
  std::fill(accuracy.begin(), accuracy.end(), 0);
  std::fill(confusion_matrix.begin(), confusion_matrix.end(),
            vector<int>(newsgroups.size()));

  // display accuracy
  std::cout << "Overall Accuracy: "
            << overall_accuracy(accuracy, newsgroups, actual_docs, pred_docs,
                                confusion_matrix, is_test)
            << std::endl;
  std::cout << "Class accuracy:" << std::endl;
  for (const auto& ng : newsgroups) {
    std::cout << "Group " << ng.get_id() + 1 << ": " << accuracy[ng.get_id()]
              << std::endl;
  }
  std::cout << std::endl;

  // display confusion matrix
  std::cout << "Confusion matrix:" << std::endl;
  for (const auto& i_ng : confusion_matrix) {
    for (const auto& j_ng : i_ng) {
      std::cout << std::setw(4) << j_ng;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}