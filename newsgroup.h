#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "document.h"

namespace naive_bayes {
class newsgroup {
  /**
   * the id of the newsgroup
   */
  int id;

  /**
   * the name of the newsgroup
   */
  const std::string name;

  /**
   * the list of documents in the newsgroup
   */
  std::vector<document> documents;

  /**
   * mapping of word id to the count of words
   */
  std::map<int, int> words;

  /**
   * the number of words in the newsgroup
   */
  int num_words;

  /**
   * number of words being tested
   */
  int num_test_docs;

  /**
   * the number of times a word occurs
   * \param id the word id
   */
  int word_frequency(int id) const;

  /**
   * set of all words in the classification
   */
  static std::set<int> all_words;

 public:
  /**
   * the total number of documents in the classification
   */
  static int TOTAL_DOCS;

  /**
   * the total number of test documents
   */
  static int TOTAL_TEST_DOCS;

  /**
   * Constructs a new newsgroup as a class
   * \param name the name of the newsgroup
   * \param the id of the newsgroup
   */
  newsgroup(std::string name, int id);

  /**
   * adds a document to the training model of the newsgroup
   * \param d the document being added
   */
  const document& add_document(const document& d);

  /**
   * adds a test document to the newsgroup
   */
  void add_test_document();

  /**
   * returns the prior of the newsgroup
   */
  double prior() const;

  /**
   * returns the maximum likelyhood estimate of the word in the newsgroup
   * \param id the word id
   */
  double max_likelyhood_estimator(int id) const;

  /**
   * returns the bayesian estimate of the word in the newsgroup
   * \param id the word id
   */
  double bayesian_estimator(int id) const;

  /**
   * returns the number of documents
   */
  int get_num_docs() const;

  /**
   * returns the number of test documents
   */
  int get_num_test_docs() const;

  /**
   * returns the name of the newsgroup
   */
  std::string get_name() const;

  /**
   * returns the id of the newsgroup
   */
  int get_id() const;
};
}  // namespace naive_bayes

#endif