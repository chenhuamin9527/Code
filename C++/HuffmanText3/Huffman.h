// HuffmanText3.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。


#pragma once
#include<iostream>
using namespace std;
struct HTNode
{
	int weight = 0;//权值
	int parent = 0;//父节点
	int lchild = 0;//左孩子
	int rchild = 0;//右孩子
};

typedef HTNode* Huffmantree;
typedef char** HuffmanCode;
int HuffmanTree(Huffmantree& pHT, int* w, int n);
int Select(Huffmantree pHT, int nSize);
void TestHuffmanTree(Huffmantree pHT);
int HuffmanCoding(HuffmanCode& pHC, Huffmantree& pHT);//求Huffman编码
void TestHuffmanCode(int root, Huffmantree pHT, HuffmanCode pHC);