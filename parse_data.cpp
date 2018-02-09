#include "parse_data.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "document.h"
#include "naive_bayes.h"
#include "newsgroup.h"
#include "utils.h"

using std::string;
using std::vector;

namespace naive_bayes {

int get_training_data(vector<newsgroup>& newsgroups,
                      std::map<document, string>& train_docs,
                      std::map<document, string>& train_pred_docs,
                      const string& path) {
  int total_words = 0;
  std::ifstream map_file(path + "map.csv");
  string line;

  // create news groups
  while (std::getline(map_file, line)) {
    vector<string> in;
    tokenize(line, in);
    newsgroups.push_back(newsgroup(in[1].c_str(), stoi(in[0])));
  }

  std::ifstream train_label(path + "train_label.csv");
  std::ifstream train_data(path + "train_data.csv");
  string label_line;

  // read first doc id
  if (!std::getline(train_data, line)) {
    std::cerr << "DEBUG: no first doc id" << std::endl;
    return -1;
  }

  int prev_doc_id = stoi(line.substr(0, line.find(",")));
  train_data.clear();
  train_data.seekg(0, std::ios::beg);

  vector<word> words;
  int doc_id;

  while (std::getline(train_data, line)) {
    vector<string> doc_row;
    tokenize(line, doc_row);
    doc_id = stoi(doc_row[0]);
    int word_id = stoi(doc_row[1]);
    int word_count = stoi(doc_row[2]);
    total_words += word_count;

    if (prev_doc_id != doc_id) {
      document doc(prev_doc_id, words);
      prev_doc_id = doc_id;
      words.clear();
      if (!std::getline(train_label, label_line)) {
        std::cerr << "DEBUG: no label line" << std::endl;
        return -1;
      }
      auto& ng = newsgroups[stoi(label_line) - 1];

      const auto& added_doc = ng.add_document(doc);

      train_pred_docs[added_doc] = "";
      train_docs[added_doc] = ng.get_name();
    }

    words.push_back(word(word_id, word_count));
  }

  document doc(doc_id, words);
  if (!std::getline(train_label, label_line)) {
    std::cout << "DEBUG: no final label line" << std::endl;
    return -1;
  }
  auto& ng = newsgroups[stoi(label_line) - 1];
  const auto& added_doc = ng.add_document(doc);
  train_pred_docs[added_doc] = "";
  train_docs[added_doc] = ng.get_name();

  return 0;
}

int get_test_data(vector<newsgroup>& newsgroups,
                  std::map<document, string>& test_docs,
                  std::map<document, string>& test_pred_docs,
                  const string& path) {
  string line;

  std::ifstream label(path + "test_label.csv");
  std::ifstream data(path + "test_data.csv");
  string label_line;

  // read first doc id
  if (!std::getline(data, line)) {
    std::cerr << "DEBUG: no first doc id" << std::endl;
    return -1;
  }

  int prev_doc_id = stoi(line.substr(0, line.find(",")));
  data.clear();
  data.seekg(0, std::ios::beg);

  vector<word> words;
  int doc_id;

  while (std::getline(data, line)) {
    vector<string> doc_row;
    tokenize(line, doc_row);
    doc_id = stoi(doc_row[0]);
    int word_id = stoi(doc_row[1]);
    int word_count = stoi(doc_row[2]);

    if (prev_doc_id != doc_id) {
      document doc(prev_doc_id, words);
      prev_doc_id = doc_id;
      words.clear();
      if (!std::getline(label, label_line)) {
        std::cerr << "DEBUG: no label line" << std::endl;
        return -1;
      }
      auto& ng = newsgroups[stoi(label_line) - 1];

      ng.add_test_document();
      test_pred_docs[doc] = "";
      test_docs[doc] = ng.get_name();
    }

    words.push_back(word(word_id, word_count));
  }

  document doc(doc_id, words);
  if (!std::getline(label, label_line)) {
    std::cout << "DEBUG: no final label line" << std::endl;
    return -1;
  }
  auto& ng = newsgroups[stoi(label_line) - 1];
  ng.add_test_document();
  test_pred_docs[doc] = "";
  test_docs[doc] = ng.get_name();

  label.close();
  data.close();

  return 0;
}

}  // namespace naive_bayes