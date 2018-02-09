#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>

namespace naive_bayes {

/**
 * Represents a word in a document
 */
struct word {
  /**
   * the id of the word
   */
  int id;

  /**
   * The number of times a word occurs in a document
   */
  int count;

  /**
   * Constructs a word
   * \param id the id of the word
   * \param count the occurrence of the word
   */
  word(int id, int count) : id(id), count(count) {}
};

/**
 * Represents a document
 */
struct document {
  /**
   * The id of the document
   */
  int id;

  /**
   * The words in the document
   */
  std::vector<word> words;

  /**
   * Constructs a document
   * \param the id of the document
   * \param the words to be added to be document
   */
  document(int id, const std::vector<word>& words) : id(id), words(words) {}

  /**
   * Compares a document to another
   * \param rhs the document being compared to this
   * \return true if this document has a lower id than the one being compared
   * to
   */
  inline bool operator<(const document& rhs) const { return id < rhs.id; }
};
}  // namespace naive_bayes

#endif
