#include <iostream>
#include "library/trie.h"

int main() {
    Trie* trie_root = new Trie();
    trie_root->loadDataFromFile("./data/test.txt");

    std::string str;
    while(1) {
        std::cout<<"请输入检索词"<<std::endl;
		getline(std::cin,str);
        if(str == "exit" || str.size() == 0){
            break;
        }
        std::vector<std::string> res_vec;
        trie_root->searchPrefixStr(str,res_vec);
        std::cout<<"检索"<<str<<",共"<<res_vec.size()<<"条结果."<<std::endl;
        for(auto& buf_str : res_vec){
            std::cout<<buf_str<<std::endl;
        }
    }
    return 0;
}
