#ifndef PARSE_DATA_H
#define PARSE_DATA_H

#include "newsgroup.h"
#include "document.h"

namespace naive_bayes {

int get_training_data(std::vector<newsgroup>& newsgroups,
                      std::map<document, std::string>& train_docs,
                      std::map<document, std::string>& train_pred_docs,
                      const std::string& path);

}

#endif