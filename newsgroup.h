#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "document.h"

namespace naive_bayes {
class newsgroup {
  static std::set<int> all_words;
  static int TOTAL_DOCS;
  int id;
  const std::string name;
  std::vector<document> documents;
  std::map<int, int> words;
  int num_words;
  int word_frequency(int id) const;

 public:
  static int VOCAB_LEN;
  newsgroup(const char* name, int id);

  void add_document(const document& d);
  int num_unique_words() const;
  double prior() const;
  double max_likelyhood_estimator(int id) const;
  double bayesian_estimator(int id) const;
  std::string get_name() const;
  int get_id() const;
};
}  // namespace naive_bayes

#endif