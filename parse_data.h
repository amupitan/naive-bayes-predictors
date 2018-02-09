#ifndef PARSE_DATA_H
#define PARSE_DATA_H

#include "document.h"
#include "newsgroup.h"

namespace naive_bayes {

/**
 * Parses the training data into proper groups
 * \param newsgroups the list of newsgroups to be created
 * \param train_docs a map of document to the name of newsgroup it belongs to
 * \param train_pred_docs an empty map containing documents mapped to nothing
 * \param path the path to the training data
 */
int get_training_data(std::vector<newsgroup>& newsgroups,
                      std::map<document, std::string>& train_docs,
                      std::map<document, std::string>& train_pred_docs,
                      const std::string& path);

/**
 * Parses the test data into proper groups
 * \param newsgroups the list of newsgroups to be created
 * \param train_docs a map of document to the name of newsgroup it belongs to
 * \param train_pred_docs an empty map containing documents mapped to nothing
 * \param path the path to the test data
 */
int get_test_data(std::vector<newsgroup>& newsgroups,
                  std::map<document, std::string>& test_docs,
                  std::map<document, std::string>& test_pred_docs,
                  const std::string& path);

}  // namespace naive_bayes

#endif