#pragma once
#include"Huffman.h"
#define SIZE 256
//文件头
struct HEAD {
	char type[8];//文件类型
	int length;//文件长度
	int weight[256]; //权值数值
};
typedef char* BUFFER;
int InitHead(const char* pFilename, HEAD& sHead); //初始化文件头
int Compress(const char* pFilename);
int Str2byte(const char* pBinStr);
int Encode(const char* pFilename, const HuffmanCode pHC, char* pBuffer, const int nSize);
int WriteFile(const char* pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize);//写文件