//
// Created by MaoyingYan on 2020/5/31.
//

#include "trie.h"
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <unordered_set>


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

//加载数据
void Trie::loadDataFromVec(const std::vector<std::string>& str_vec) {
    for(const auto& str : str_vec) {
        if(str.size() > 0) {
            insertStr(str);
        }
    }
}

bool Trie::loadDataFromFile(const std::string& path){
    std::ifstream infile;
    infile.open(path);
    if(!infile.is_open()) {
        std::cerr<<"open "<<path<<" file error"<<std::endl;
        return false;
    }

    std::string str;
    while (getline(infile,str)) {
        insertStr(str);
    }
    infile.close();
    return true;
}

//查找当前串是否存在
bool Trie::searchStr(const std::string& sea_str) {
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

	//该串存在,但是不成词
	if(!now_node->flag)
		return false;
	return true;
}

//遍历检索
void searchList(const std::string& sea_str,std::unordered_map<std::string,TrieNode*>& str2next_node_map,std::vector<std::string>& res_vec) {
	for(auto it = str2next_node_map.begin(); it != str2next_node_map.end(); ++it ) {
		if(it->second->flag){
			res_vec.push_back(sea_str + it->first);
		}
		searchList(sea_str + it->first,it->second->str2next_node_map,res_vec);
	}
}

//基于前缀检索全量词
bool Trie::searchPrefixStr(const std::string& sea_str,std::vector<std::string>& res_vec) {
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

	if(now_node->flag){
		res_vec.push_back(sea_str);
	}
	searchList(sea_str,now_node->str2next_node_map,res_vec);

	std::sort(res_vec.begin(),res_vec.end(),[](const std::string& a, const std::string& b){return a.size() < b.size();});
	return true;
}


//主动插入构建trie
bool Trie::insertStr(const std::string& ins_str) {
	if(ins_str.size() == 0){
		return false;
	}
    TrieNode *now_node = this->root_;
    for (size_t i = 0, len = 0; i != ins_str.length(); i += len) {
        unsigned char byte = (unsigned) ins_str[i];
        len = getByteLen(byte);
        const std::string &buf_str = ins_str.substr(i, len);

        auto it = now_node->str2next_node_map.find(buf_str);
        if (it == now_node->str2next_node_map.end()) {
            now_node->str2next_node_map[buf_str] = new TrieNode();
        }
        now_node = now_node->str2next_node_map[buf_str];
    }
	now_node->flag = true;
	return true;
}
