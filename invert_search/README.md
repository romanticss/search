## 项目目录
	bin		存储二进制文件
	library	trie树的定义和方法
	library_3rd 第三方依赖
	build	编译相关
	data	测试语料
	build.sh	编译脚本
	start.sh	启动脚本
	main.cpp	main文件

## 环境
	gcc/clang 要求支持c++11
	cmake3.15以上版本	
	linux或mac环境
	
## 算法原理
	基于trie树实现的倒排索引
## 主要思路
	1. 使用cpp的结巴分词,对文档分词,建立词对文档的trie
	2. 额外对一元词做一层索引
	3. 检索文档时候,先基于结巴分词分词,然后基于分词结果查找文档,取最终的交集,就是最终匹配的文档
