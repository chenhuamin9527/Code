// Huffman.h: interface for the Huffman class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUFFMAN_H__08A1863A_6641_4FE9_9596_5EEBE76B53F7__INCLUDED_)
#define AFX_HUFFMAN_H__08A1863A_6641_4FE9_9596_5EEBE76B53F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;



//¹þ¸¥ÂüÊ÷½Úµã
typedef struct 
{
	float weight;
	int parent;
	int lchild;
	int rchild;
}HuffTreeNode,*HuffTree;

//×Ö·û-È¨Öµ-±àÂëÓ³Éä
typedef struct
{
	char c;
	float weight;
	char *code;
}CharMapNode,*CharMap;


class Huffman  
{
private:
	void select(int n, int &s1, int &s2);
	HuffTree huffTree;	//¹þ¸¥ÂüÊ÷
	CharMap chars;		//×Ö·û±í
	int n;				//×Ö·ûÊý
	string text;		//Ô­ÎÄ
	string code;		//±àÂë
public:	

	void InputCharsWeight();
	void CountCharsWeight();
	void Decode();
	void ReadTextFromFile(char *filename);
	void ReadCodeFromFile(char *filename);
	void SaveTextToFile(char *filename);
	void SaveCodeToFile(char *filename);
	void PrintCode();
	void MakeCharMap();
	void PrintText();	
	void PrintCharCode();
	void PrintCharWeight();
	void Encode();
	int FileSize(char* path);
	
	Huffman();
	virtual ~Huffman();

};

#endif // !defined(AFX_HUFFMAN_H__08A1863A_6641_4FE9_9596_5EEBE76B53F7__INCLUDED_)
