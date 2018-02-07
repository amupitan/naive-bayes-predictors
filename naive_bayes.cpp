#include "naive_bayes.h"
#include <cmath>

using std::string;
using std::vector;

namespace naive_bayes {

std::pair<string, double> naive_bayes_classify(
    const vector<newsgroup>& newsgroups, const vector<word>& in_words,
    double (*estimator)(const newsgroup& ng, const vector<word>& in_words)) {
  std::map<string, double> nb_vals;
  std::pair<string, double> prediction("", 0);
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
  return sum;
}

double naive_bayes_mle(const newsgroup& ng, const vector<word>& words) {
  double sum = 0;
  for (const auto& w : words) {
    auto est = ng.max_likelyhood_estimator(w.id);
    if (!est) {
      sum = 0;
      break;
    }
    sum += log(est);
  }

  return sum != 0 ? log(ng.prior() + sum) : 0;
}

void predict(const vector<newsgroup>& newsgroups, estimator_t estimator,
             std::map<document, string>& docs) {
  for (auto it = docs.begin(); it != docs.end(); it++) {
    auto doc = it->first;
    auto res = naive_bayes_classify(newsgroups, doc.words, estimator);
    docs[doc] = res.first;
  }
}

}  // namespace naive_bayes