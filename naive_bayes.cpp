#include "naive_bayes.h"
#include <cmath>
#include <limits>

using std::string;
using std::vector;

namespace naive_bayes {

std::pair<string, double> naive_bayes_classify(
    const vector<newsgroup>& newsgroups, const vector<word>& in_words,
    double (*estimator)(const newsgroup& ng, const vector<word>& in_words)) {
  std::map<string, double> nb_vals;
  std::pair<string, double> prediction("", -std::numeric_limits<double>::max());
  for (const auto& ng : newsgroups) {
    nb_vals[ng.get_name()] = estimator(ng, in_words);
    if (nb_vals[ng.get_name()] != 0 &&
        nb_vals[ng.get_name()] > prediction.second) {
      prediction.first = ng.get_name();
      prediction.second = nb_vals[ng.get_name()];
    }
  }
  if (prediction.first == "") {
    const auto& ng = newsgroups[(rand() % 19)];
    prediction.first = ng.get_name();
  }
  return prediction;
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
             std::map<document, string>& docs) {
  for (auto it = docs.begin(); it != docs.end(); it++) {
    auto doc = it->first;
    auto res = naive_bayes_classify(newsgroups, doc.words, estimator);
    docs[doc] = res.first;
  }
}

double overall_accuracy(std::map<string, double>& accuracy,
                        const vector<newsgroup>& newsgroups,
                        const std::map<document, string>& train_docs,
                        const std::map<document, string>& train_pred_docs,
                        bool is_test) {
  for (const newsgroup& ng : newsgroups) {
    accuracy[ng.get_name()] = 0;
  }
  double overall = 0;

  for (auto it = train_docs.begin(); it != train_docs.end(); it++) {
    auto& doc = it->first;
    auto& train_name = it->second;
    auto& pred_name = train_pred_docs.at(doc);
    if (train_name == pred_name) {
      accuracy[train_name]++;
      overall++;
    }
  }
  for (const newsgroup& ng : newsgroups) {
    auto divisor = is_test ? ng.get_num_test_docs() : ng.get_num_docs();
    accuracy[ng.get_name()] = accuracy[ng.get_name()] / divisor;
  }
  auto divisor = is_test ? newsgroup::TOTAL_TEST_DOCS : newsgroup::TOTAL_DOCS;
  return overall / divisor;
}

}  // namespace naive_bayes