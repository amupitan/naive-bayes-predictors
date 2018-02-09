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
                  const std::map<document, string>& actual_docs,
                  const std::map<document, string>& pred_docs,
                  std::map<string, double> accuracy, bool is_test);

int main(int argc, char** argv) {
  string path = "20newsgroups/";
  srand((unsigned)time(0));

  vector<newsgroup> newsgroups;
  std::map<document, string> train_docs;
  std::map<document, string> train_pred_docs;

  if (get_training_data(newsgroups, train_docs, train_pred_docs, path) == -1) {
    return -1;
  }

  std::map<string, double> accuracy;

  predict(newsgroups, naive_bayes_be, train_pred_docs);
  std::cout << "BE training data:" << std::endl;
  print_report(newsgroups, train_docs, train_pred_docs, accuracy, false);

  // Confusion matrix BE traning

  std::map<document, string> test_docs;
  std::map<document, string> test_pred_docs;
  if (get_test_data(newsgroups, test_docs, test_pred_docs, path) == -1) {
    return -1;
  }

  predict(newsgroups, naive_bayes_be, test_pred_docs);
  std::cout << "BE test data:" << std::endl;
  print_report(newsgroups, test_docs, test_pred_docs, accuracy, true);

  predict(newsgroups, naive_bayes_mle, test_pred_docs);
  std::cout << "MLE test data:" << std::endl;
  print_report(newsgroups, test_docs, test_pred_docs, accuracy, true);

  return 0;
}

void print_report(const vector<newsgroup>& newsgroups,
                  const std::map<document, string>& actual_docs,
                  const std::map<document, string>& pred_docs,
                  std::map<string, double> accuracy, bool is_test) {
  std::cout << "Overall Accuracy: "
            << overall_accuracy(accuracy, newsgroups, actual_docs, pred_docs,
                                is_test)
            << std::endl;
  std::cout << "Class accuracy:" << std::endl;
  for (const auto& ng : newsgroups) {
    std::cout << "Group " << ng.get_id() << ": " << accuracy[ng.get_name()]
              << std::endl;
  }
  std::cout << std::endl;
}