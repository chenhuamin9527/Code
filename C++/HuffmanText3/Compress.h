#pragma once
#include"Huffman.h"
#define SIZE 256
//�ļ�ͷ
struct HEAD {
	char type[8];//�ļ�����
	int length;//�ļ�����
	int weight[256]; //Ȩֵ��ֵ
};
typedef char* BUFFER;
int InitHead(const char* pFilename, HEAD& sHead); //��ʼ���ļ�ͷ
int Compress(const char* pFilename);
int Str2byte(const char* pBinStr);
int Encode(const char* pFilename, const HuffmanCode pHC, char* pBuffer, const int nSize);
int WriteFile(const char* pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize);//д�ļ�