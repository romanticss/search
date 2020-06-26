//
// Created by MaoyingYan on 2020/6/16.
//

#ifndef INVERT_SEARCH_INVERT_SEARCH_H
#define INVERT_SEARCH_INVERT_SEARCH_H

#include <iostream>
#include <string>
#include <vector>
#include "trie.h"
#include "../library_3rd/include/cppjieba/Jieba.hpp"
#include <unordered_set>
using namespace std;


class InvertSearch{
public:
    InvertSearch();
    bool loadStopWords(const string& path);
    bool loadDataFromFile(const string& path);
    void makeInvertIndex(const string& sea_str,int index);
    void searchDoc(const string& sea_str,vector<string>& doc_vec);
private:
    vector<string> doc_vec_;
    Trie* root_;
    cppjieba::Jieba *jieba_;
    unordered_set<string> stop_word_set_;

};

#endif //INVERT_SEARCH_INVERT_SEARCH_H
