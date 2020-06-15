//
// Created by MaoyingYan on 2020/5/31.
//

#ifndef PREFIX_SEARCH_TRIE_H
#define PREFIX_SEARCH_TRIE_H
#include <unordered_map>
#include <string>
#include <vector>

class TrieNode {
public:
    //标识当前是否成词
    bool flag;
    //存储后续节点
    std::unordered_map<std::string,TrieNode*> str2next_node_map;
};

class Trie {
public:
    Trie();
    //加载数据
    void loadDataFromVec(const std::vector<std::string>& str_vec);
    bool loadDataFromFile(const std::string& path);
    //查找当前串是否存在
    bool searchStr(const std::string& sea_str);
    //基于前缀检索全量词
    bool searchPrefixStr(const std::string& sea_str,std::vector<std::string>& res_vec);
    //主动插入构建trie
    bool insertStr(const std::string& ins_str);
public:
    TrieNode* root_;
    std::vector<std::string> term_vec_;
};


#endif //PREFIX_SEARCH_TRIE_H
