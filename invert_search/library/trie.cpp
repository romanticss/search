//
// Created by MaoyingYan on 2020/5/31.
//

#include "trie.h"
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <set>


Trie::Trie(){
    this->root_ = new TrieNode();
}

//获取字符字节数
int getByteLen(const unsigned char& byte) {
    int len = 1;
    if (byte >= 0xFC) // lenght 6
        len = 6;
    else if (byte >= 0xF8)
        len = 5;
    else if (byte >= 0xF0)
        len = 4;
    else if (byte >= 0xE0)
        len = 3;
    else if (byte >= 0xC0)
        len = 2;
    return len;
}

bool Trie::searchTrieDoc(const std::string& sea_str,std::set<int>& index_set) {
	TrieNode* now_node = this->root_;

    for (size_t i = 0, len = 0; i != sea_str.length(); i += len) {
        unsigned char byte = (unsigned)sea_str[i];
        len = getByteLen(byte);
        const std::string& buf_str = sea_str.substr(i, len);

        auto it = now_node->str2next_node_map.find(buf_str);
        if(it  == now_node->str2next_node_map.end()) {
            return false;
        }else{
            now_node = it->second;
        }
    }
	
	index_set = now_node->index_set;
	return true;
}


//主动插入构建trie
bool Trie::insertStr(const std::string& ins_str,const int index) {
	if(ins_str.size() == 0){
		return false;
	}
    TrieNode *now_node = this->root_;
    for (size_t i = 0, len = 0; i != ins_str.length(); i += len) {
        unsigned char byte = (unsigned) ins_str[i];
        len = getByteLen(byte);
        const std::string &buf_str = ins_str.substr(i, len);

		//一元词做索引
		auto iter = this->root_->str2next_node_map.find(buf_str);
		if(iter == now_node->str2next_node_map.end()){
			root_->str2next_node_map[buf_str] = new TrieNode();
		}
		root_->str2next_node_map[buf_str]->index_set.insert(index);

        auto it = now_node->str2next_node_map.find(buf_str);
        if (it == now_node->str2next_node_map.end()) {
            now_node->str2next_node_map[buf_str] = new TrieNode();
        }
        now_node = now_node->str2next_node_map[buf_str];
    }
	now_node->index_set.insert(index);
	
	return true;
}
