#include <iostream>
#include <string>
#include <vector>
#include "document.h"
#include "naive_bayes.h"
#include "newsgroup.h"
#include "utils.h"
#include "parse_data.h"

using namespace naive_bayes;
using std::string;
using std::vector;

int main(int argc, char** argv) {
  string path = "20newsgroups/";
  //   int total_words = 0;
  FILE* vocab = fopen((path + "vocabulary.txt").c_str(), "r");
  if (!vocab) {
    std::cout << "DEBUG: no vocab file" << std::endl;
    return -1;
  }
  newsgroup::VOCAB_LEN = count_lines(vocab);

  srand((unsigned)time(0));

  vector<newsgroup> newsgroups;
  std::map<document, string> train_docs;
  std::map<document, string> train_pred_docs;

  if (get_training_data(newsgroups, train_docs, train_pred_docs, path) == -1) {
    return -1;
  }

  for (const auto& ng : newsgroups) {
    std::cout << ng.get_name() << ng.prior() << std::endl;
  }
  //   predict(newsgroups, naive_bayes_be, train_pred_docs);
  //   for (auto it = train_docs.begin(); it != train_docs)
  return 0;
}