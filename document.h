#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>

namespace naive_bayes {
struct word {
  int id;
  int count;
  word(int id, int count) : id(id), count(count) {}
};

struct document {
  int id;
  std::vector<word> words;
  document(int id, const std::vector<word>& words) : id(id), words(words) {}
  inline bool operator<(const document& rhs) const { return id < rhs.id; }
};
}  // namespace naive_bayes

#endif

// class Word:
//     def __init__(self, id, count):
//         self.id = id
//         self.count = count

//     def __str__(self):
//         return "id: " + str(self.id) + " count: " + str(self.count)

// class Document:

//     def __init__(self, id, words):
//         self.id = id
//         self.words = words
