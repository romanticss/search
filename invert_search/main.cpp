#include <iostream>
#include "library/invert_search.h"
#include "library_3rd/include/cppjieba/Jieba.hpp"

int main() {
    InvertSearch* invert_search = new InvertSearch();

    std::string str;
    while(1) {
        std::cout<<"请输入检索词(q退出)"<<std::endl;
		getline(std::cin,str);
        if(str == "q" || str.size() == 0){
            break;
        }
        std::vector<std::string> res_vec;
        invert_search->searchDoc(str,res_vec);
        std::cout<<"检索"<<str<<",共"<<res_vec.size()<<"条结果."<<std::endl;
        for(int i = 0; i < res_vec.size(); ++i){
            std::cout<<"文档"<<i<<":"<<std::endl;
			std::cout<<res_vec[i]<<std::endl;
        }
    }
    return 0;
}
