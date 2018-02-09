#include "newsgroup.h"

namespace naive_bayes {
int newsgroup::TOTAL_DOCS;
int newsgroup::TOTAL_TEST_DOCS;
std::set<int> newsgroup::all_words;

newsgroup::newsgroup(std::string name, int id)
    : id(id), name(name), num_words(0) {}

const document& newsgroup::add_document(const document& d) {
  documents.push_back(d);
  TOTAL_DOCS++;

  for (const word& w : d.words) {
    num_words += w.count;
    all_words.insert(w.id);
    if (words.find(w.id) == words.end()) {
      words[w.id] = w.count;
    } else {
      words[w.id] += w.count;
    }
  }
  return documents[documents.size() - 1];
}

void newsgroup::add_test_document() {
  TOTAL_TEST_DOCS++;
  num_test_docs++;
}

int newsgroup::word_frequency(int id) const {
  auto found = words.find(id);
  if (found != words.end()) {
    return found->second;
  }
  return 0;
}

double newsgroup::prior() const {
  return (double)documents.size() / TOTAL_DOCS;
}

double newsgroup::max_likelyhood_estimator(int id) const {
  return (double)word_frequency(id) / num_words;
}

double newsgroup::bayesian_estimator(int id) const {
  return (double)(word_frequency(id) + 1) / (num_words + all_words.size());
}

int newsgroup::get_num_docs() const { return documents.size(); }

int newsgroup::get_num_test_docs() const { return num_test_docs; }

std::string newsgroup::get_name() const { return name; }

int newsgroup::get_id() const { return id; }

}  // namespace naive_bayes