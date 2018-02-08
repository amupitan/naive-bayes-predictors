#ifndef PARSE_DATA_H
#define PARSE_DATA_H

#include "document.h"
#include "newsgroup.h"

namespace naive_bayes {

int get_training_data(std::vector<newsgroup>& newsgroups,
                      std::map<document, std::string>& train_docs,
                      std::map<document, std::string>& train_pred_docs,
                      const std::string& path);

int vocab_len(const std::string& path);

}  // namespace naive_bayes

#endif