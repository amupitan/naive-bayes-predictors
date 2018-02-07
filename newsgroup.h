#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <map>
#include <set>
#include <vector>
#include "document.h"

namespace naive_bayes {
class newsgroup {
  static std::set<int> all_words;
  static int TOTAL_DOCS;
  int id;
  const char* name;
  std::vector<document> documents;
  std::map<int, int> words;
  int num_words;
  int word_frequency(const word& w) const;

 public:
  static int VOCAB_LEN;
  newsgroup(const char* name, int id);

  void add_document(const document& d);
  int num_unique_words() const;
  double prior() const;
  double max_likelyhood_estimator(const word& w) const;
  double bayesian_estimator(const word& w) const;
  const char* get_name() const;
  int get_id() const;
};
}  // namespace naive_bayes

#endif