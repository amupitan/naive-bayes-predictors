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

  // for (const auto& ng : newsgroups) {
  //   std::cout << ng.get_name() << ng.prior() << std::endl;
  // }

  predict(newsgroups, naive_bayes_mle, train_pred_docs);

  std::ofstream myfile;
  myfile.open("example.txt");
  std::map<string, double> accuracy;
  for (const newsgroup& ng : newsgroups) {
    accuracy[ng.get_name()] = 0;
  }
  for (auto it = train_docs.begin(); it != train_docs.end(); it++) {
    auto& doc = it->first;
    auto& train_name = it->second;
    auto& pred_name = train_pred_docs[doc];
    if (train_name == pred_name) {
      accuracy[train_name]++;
    }
    myfile << doc.id;
    // myfile << ", ";
    // myfile << train_name;
    myfile << ",";
    myfile << pred_name;
    myfile << "\n";
  }
  myfile.close();
  std::cout << "total docs " << newsgroup::TOTAL_DOCS << std::endl;
  std::cout << "total words " << newsgroup::all_words.size() << std::endl;
  // std::ofstream myfile("cresult.csv");
  double over = 0;
  for (const newsgroup& ng : newsgroups) {
    accuracy[ng.get_name()] = accuracy[ng.get_name()] / ng.get_num_docs();
    over += accuracy[ng.get_name()];
    std::cout << ng.get_name();
    std::cout << ", ";
    std::cout << accuracy[ng.get_name()] << std::endl;
  }
  std::cout << over / 20 << std::endl;

  return 0;
}