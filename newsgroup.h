#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "document.h"

namespace naive_bayes {
class newsgroup {
  int id;
  const std::string name;
  std::vector<document> documents;
  std::map<int, int> words;
  int num_words;
  int num_test_docs;
  int word_frequency(int id) const;

 public:
  static int VOCAB_LEN;
  static int TOTAL_DOCS;
  static int TOTAL_TEST_DOCS;
  static std::set<int> all_words;
  newsgroup(const char* name, int id);

  const document& add_document(const document& d);
  void add_test_document();
  int num_unique_words() const;
  double prior() const;
  double max_likelyhood_estimator(int id) const;
  double bayesian_estimator(int id) const;
  int get_num_docs() const;
  int get_num_test_docs() const;
  void reset();
  std::string get_name() const;
  int get_id() const;
};
}  // namespace naive_bayes

#endif