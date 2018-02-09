#include <fstream>
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

void print_report(const vector<newsgroup>& newsgroups,
                  const std::map<document, int>& actual_docs,
                  const std::map<document, int>& pred_docs,
                  vector<double> accuracy,
                  vector<vector<int>>& confusion_matrix, bool is_test);

int main(int argc, char** argv) {
  constexpr auto path = "20newsgroups/";
  srand((unsigned)time(0));

  vector<newsgroup> newsgroups;
  std::map<document, int> train_docs;
  std::map<document, int> train_pred_docs;

  if (get_training_data(newsgroups, train_docs, train_pred_docs, path) == -1) {
    return -1;
  }

  const int CLASS_SIZE = newsgroups.size();
  std::vector<double> accuracy(CLASS_SIZE);
  vector<vector<int>> confusion_matrix(CLASS_SIZE);
  for (auto& row : confusion_matrix) row = vector<int>(CLASS_SIZE);

  predict(newsgroups, naive_bayes_be, train_pred_docs);
  std::cout << "BE training data:" << std::endl;
  print_report(newsgroups, train_docs, train_pred_docs, accuracy,
               confusion_matrix, false);

  // Confusion matrix BE traning

  std::map<document, int> test_docs;
  std::map<document, int> test_pred_docs;
  if (get_test_data(newsgroups, test_docs, test_pred_docs, path) == -1) {
    return -1;
  }

  predict(newsgroups, naive_bayes_be, test_pred_docs);
  std::cout << "BE test data:" << std::endl;
  print_report(newsgroups, test_docs, test_pred_docs, accuracy,
               confusion_matrix, true);

  predict(newsgroups, naive_bayes_mle, test_pred_docs);
  std::cout << "MLE test data:" << std::endl;
  print_report(newsgroups, test_docs, test_pred_docs, accuracy,
               confusion_matrix, true);

  return 0;
}

void print_report(const vector<newsgroup>& newsgroups,
                  const std::map<document, int>& actual_docs,
                  const std::map<document, int>& pred_docs,
                  vector<double> accuracy,
                  vector<vector<int>>& confusion_matrix, bool is_test) {
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
  std::cout << "Confusion matrix:" << std::endl;
  // for (const auto& ig : newsgroups) {
  // }
}