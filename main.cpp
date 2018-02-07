#include "main.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "document.h"
#include "naive_bayes.h"
#include "newsgroup.h"

using namespace naive_bayes;
using std::string;
using std::vector;

int main(int argc, char** argv) {
  string path = "20newsgroups/";
  int total_words = 0;
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

  //   for (const auto& ng : newsgroups) {
  //     std::cout << ng.get_name() << ng.prior() << std::endl;
  //   }
  predict(newsgroups, naive_bayes_be, train_pred_docs);
  //   for (auto it = train_docs.begin(); it != train_docs)
  return 0;
}

unsigned int count_lines(FILE* fp) {
  unsigned int num_lines = 0;
  int ch = 0;
  do {
    ch = fgetc(fp);
    if (ch == '\n') num_lines++;
  } while (ch != EOF);
  return num_lines;
}

void tokenize(const string& str, vector<string>& tokens,
              const string& delimiters) {
  // Skip delimiters at beginning.
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  string::size_type pos = str.find_first_of(delimiters, lastPos);

  while (string::npos != pos || string::npos != lastPos) {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of(delimiters, lastPos);
  }
}

inline int first_token(const string& str, const string& delim) {
  return stoi(str.substr(0, str.find(delim)));
}
