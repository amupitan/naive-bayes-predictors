#include "naive_bayes.h"
#include <cmath>
#include <limits>

using std::string;
using std::vector;

namespace naive_bayes {

int naive_bayes_classify(const vector<newsgroup>& newsgroups,
                         const vector<word>& in_words, estimator_t estimator) {
  std::vector<double> nb_vals(newsgroups.size());
  std::pair<int, double> prediction(-1, -std::numeric_limits<double>::max());

  for (const auto& ng : newsgroups) {
    nb_vals[ng.get_id()] = estimator(ng, in_words);
    if (nb_vals[ng.get_id()] != 0 && nb_vals[ng.get_id()] > prediction.second) {
      prediction.first = ng.get_id();
      prediction.second = nb_vals[ng.get_id()];
    }
  }
  if (prediction.first == -1) {
    const auto& ng = newsgroups[(rand() % (newsgroups.size() - 1))];
    prediction.first = ng.get_id();
  }
  return prediction.first;
}

double naive_bayes_be(const newsgroup& ng, const vector<word>& words) {
  double sum = 0;
  for (const auto& w : words) {
    sum += log(ng.bayesian_estimator(w.id));
  }
  return sum + log(ng.prior());
}

double naive_bayes_mle(const newsgroup& ng, const vector<word>& words) {
  double sum = 0;
  for (const auto& w : words) {
    auto est = ng.max_likelyhood_estimator(w.id);
    if (est == 0) {
      sum = 0;
      break;
    }
    sum += log(est);
  }

  return sum != 0 ? log(ng.prior()) + sum : 0;
}

void predict(const vector<newsgroup>& newsgroups, estimator_t estimator,
             std::map<document, int>& docs) {
  for (auto it = docs.begin(); it != docs.end(); it++) {
    auto doc = it->first;
    int ng_id = naive_bayes_classify(newsgroups, doc.words, estimator);
    docs[doc] = ng_id;
  }
}

double overall_accuracy(std::vector<double>& accuracy,
                        const vector<newsgroup>& newsgroups,
                        const std::map<document, int>& train_docs,
                        const std::map<document, int>& train_pred_docs,
                        std::vector<std::vector<int> >& confusion_matrix,
                        bool is_test) {
  double overall = 0;

  for (auto it = train_docs.begin(); it != train_docs.end(); it++) {
    auto& doc = it->first;
    auto& train_ng_id = it->second;
    auto& pred_ng_id = train_pred_docs.at(doc);
    if (train_ng_id == pred_ng_id) {
      accuracy[train_ng_id]++;
      overall++;
    }
  }
  for (const newsgroup& ng : newsgroups) {
    auto divisor = is_test ? ng.get_num_test_docs() : ng.get_num_docs();
    accuracy[ng.get_id()] = accuracy[ng.get_id()] / divisor;
  }
  auto divisor = is_test ? newsgroup::TOTAL_TEST_DOCS : newsgroup::TOTAL_DOCS;
  return overall / divisor;
}

}  // namespace naive_bayes