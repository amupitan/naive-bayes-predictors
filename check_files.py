#!/bin/python

import os.path
import sys

path = "20newsgroups/"

if os.path.exists(path) == False:
    sys.stderr.write("ERR: You need to place " + path + " in this directory\n")
    sys.exit(-1)

files = [
    "map.csv",
    "test_label.csv",
    "train_data.csv",
    "train_label.csv",
    "vocabulary.txt",
]

for f in files:
    file_path = path + f
    if os.path.isfile(file_path) == False:
        sys.stderr.write("ERR: " + f + " is missing in the " + path +
                         " directory. Please include it\n")
        sys.exit(-1)

print "All files are placed correctly!"
