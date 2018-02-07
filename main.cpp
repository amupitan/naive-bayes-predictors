#include "main.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "document.h"
#include "newsgroup.h"

using namespace naive_bayes;

int main(int argc, char** argv) {
  std::string path = "20newsgroups/";
  int total_words = 0;
  FILE* vocab = fopen((path + "vocaulary.txt").c_str(), "rb");
  newsgroup::VOCAB_LEN = count_lines(vocab);

  std::vector<newsgroup> newsgroups;
  std::ifstream map_file(path + "map.csv");
  std::string line;

  // create news groups
  while (std::getline(map_file, line)) {
    std::vector<std::string> in;
    tokenize(line, in);
    newsgroups.push_back(newsgroup(in[0].c_str(), stoi(in[1])));
  }

  std::ifstream train_label(path + "train_label.csv");
  std::ifstream train_data(path + "train_data.csv");
  std::string label_line;

  // read first doc id
  if (!std::getline(train_data, line)) {
    return -1;
  }
  int prev_doc_id = stoi(line.substr(0, line.find(",")));
  train_data.clear();
  train_data.seekg(0, std::ios::beg);

  std::vector<word> words;
  int doc_id;

  while (std::getline(train_data, line)) {
    std::vector<std::string> doc_row;
    tokenize(line, doc_row);
    doc_id = stoi(doc_row[0]);
    int word_id = stoi(doc_row[1]);
    int word_count = stoi(doc_row[2]);
    total_words += word_count;

    if (prev_doc_id != word_id) {
      document doc(prev_doc_id, words);
      prev_doc_id = doc_id;
      words.clear();
      if (!std::getline(train_data, label_line)) {
        return -1;
      }
      auto& ng = newsgroups[first_token(label_line, ",") - 1];
      ng.add_document(doc);
    }

    words.push_back(word(word_id, word_count));
  }

  document doc(doc_id, words);
  if (!std::getline(train_data, label_line)) {
    return -1;
  }
  auto& ng = newsgroups[first_token(label_line, ",")];
  ng.add_document(doc);
  //   newsgroups[0].get_name();
  //   for (const auto& ng : newsgroups) {
  //     std::cout << ng.get_name() << std::endl;
  //   }
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

void tokenize(const std::string& str, std::vector<std::string>& tokens,
              const std::string& delimiters) {
  // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos) {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of(delimiters, lastPos);
  }
}

inline int first_token(const std::string& str, const std::string& delim) {
  return stoi(str.substr(0, str.find(delim)));
}