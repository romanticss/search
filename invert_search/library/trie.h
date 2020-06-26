//
// Created by MaoyingYan on 2020/5/31.
//

#ifndef PREFIX_SEARCH_TRIE_H
#define PREFIX_SEARCH_TRIE_H
#include <unordered_map>
#include <string>
#include <vector>
#include <set>

class TrieNode {
public:
	std::set<int> index_set;
    //存储后续节点
    std::unordered_map<std::string,TrieNode*> str2next_node_map;
};

class Trie {
public:
    Trie();
    //检索文档
    bool searchTrieDoc(const std::string& sea_str,std::set<int>& res_set);
    //主动插入构建trie
    bool insertStr(const std::string& ins_str,const int index);
public:
    TrieNode* root_;
};


#endif //PREFIX_SEARCH_TRIE_H
