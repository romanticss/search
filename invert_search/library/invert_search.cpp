//
// Created by MaoyingYan on 2020/6/16.
//
#include "invert_search.h"
#include <unordered_set>
#include <vector>


InvertSearch::InvertSearch() {

    //初始化jieba
    string directory = "./library_3rd/dict";
    const std::string dict_path = directory + "/jieba.dict.utf8";
    const std::string hmm_path = directory + "/hmm_model.utf8";
    const std::string user_dict_path = directory + "/user.dict.utf8";
    const std::string idf_path = directory + "/idf.utf8";
    const std::string stop_word_path = directory + "/stop_words.utf8";
    if(!loadStopWords(stop_word_path)){
        std::cerr<<"[Load Stop Word Err]"<<endl;
    }
    jieba_ = new cppjieba::Jieba(dict_path, hmm_path, user_dict_path,
                                 idf_path, stop_word_path);
	//trie
	root_ = new Trie();
    //获取到索引文档
    if(!loadDataFromFile("./data/test.txt")){
        std::cerr<<"索引建立失败"<<endl;
    }
}

bool InvertSearch::loadStopWords(const string& stop_word_path){
    std::ifstream ifs(stop_word_path);
    if (!ifs.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        stop_word_set_.insert(line);
    }
    return true;
}

bool InvertSearch::loadDataFromFile(const string& path){
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        doc_vec_.push_back(line);
        makeInvertIndex(line,doc_vec_.size()-1);
    }
    return true;
}

void InvertSearch::makeInvertIndex(const string& sea_str,int index){
	std::vector<string> word_vec;
    jieba_->CutForSearch(sea_str,word_vec);
    for(auto& s: word_vec){
		if(stop_word_set_.find(s) != stop_word_set_.end()){
			continue;
		}
		root_->insertStr(s,index);
    }
}

void InvertSearch::searchDoc(const string& sea_str,vector<string>& doc_vec){
	std::vector<string> word_vec;
	jieba_->Cut(sea_str,word_vec);
	std::set<int> doc_set;

	for(auto& word : word_vec) {
		if(stop_word_set_.find(word) != stop_word_set_.end())
			continue;
		std::set<int> buf_set;
		root_->searchTrieDoc(word,buf_set);

		if(doc_set.size() == 0){
			doc_set = std::move(buf_set);
		}else{
			std::set<int> doc_buf_set;
			std::set_intersection(begin(doc_set),end(doc_set),begin(buf_set),end(buf_set),inserter(doc_buf_set,doc_buf_set.begin()));
			doc_set.clear();
			doc_set = std::move(doc_buf_set);
		}
	}
	for(auto it = doc_set.begin(); it != doc_set.end(); ++it){
		doc_vec.push_back(doc_vec_[*it]);
	}
}
