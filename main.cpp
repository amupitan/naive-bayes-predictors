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

int main(int argc, char** argv) {
  string path = "20newsgroups/";
  srand((unsigned)time(0));

  // get vocabulary length
  if ((newsgroup::VOCAB_LEN = vocab_len(path)) == -1) {
    return -1;
  }
  vector<newsgroup> newsgroups;
  std::map<document, string> train_docs;
  std::map<document, string> train_pred_docs;

  if (get_training_data(newsgroups, train_docs, train_pred_docs, path) == -1) {
    return -1;
  }

  std::map<string, double> accuracy;

  // predict(newsgroups, naive_bayes_be, train_pred_docs);

  // std::cout << overall_accuracy(accuracy, newsgroups, train_docs,
  //                               train_pred_docs)
  //           << std::endl;

  std::map<document, string> test_docs;
  std::map<document, string> test_pred_docs;
  if (get_test_data(newsgroups, test_docs, test_pred_docs, path) == -1) {
    return -1;
  }

  predict(newsgroups, naive_bayes_mle, test_pred_docs);

  std::cout << overall_accuracy(accuracy, newsgroups, test_docs, test_pred_docs,
                                true)
            << std::endl;

  return 0;
}