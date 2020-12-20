#include <fstream>
#include <iostream>
#include "Huffman.h"
#include <string>
using namespace std;

int main()
{
	Huffman huffman;
	char* loadPath;
	char* savePath;
	char* codePath;
	string loadpath;
	string savepath;
	string codepath;
	/****************第一步输入字符和对应权值******************/
//压缩
		cout<<"请输入需要压缩的文件路径以及文件名，没有路径默认文件根目录\n"<<endl;
		cin>> loadpath;
		loadPath = const_cast<char*>(loadpath.c_str());
		huffman.ReadTextFromFile(loadPath);
		huffman.CountCharsWeight();
		cout << "字符及对应权值：" << endl;
		huffman.PrintCharWeight();
		cout << endl <<endl;
		system("pause");
		huffman.MakeCharMap();
		cout << "字符及对应编码：" << endl;
		huffman.PrintCharCode();
		system("pause");
		cout << endl;
		huffman.Encode();
		cout<<"请输入压缩文件存储路径以及文件名，没有路径默认文件根目录\n"<<endl;
		cin>> codepath;
		codePath = const_cast<char*>(codepath.c_str());
		huffman.SaveCodeToFile(codePath);
		cout<< "压缩完成"<<endl;
		system("pause");
		//解压
		cout << endl;
		cout<<"请输入需要解压后文件存储的路径以及文件名，没有路径默认文件根目录\n"<<endl;
		cin>> savepath;
		savePath = const_cast<char*>(savepath.c_str());
		cout << "对编码进行解码.........请稍后" << endl;
		huffman.ReadCodeFromFile(codePath);
		huffman.Decode();
		huffman.SaveTextToFile(savePath);
		system("pause");
		cout<< endl;
		//比较
		ifstream in1(loadPath);
    in1.seekg(0, ios::end);      //设置文件指针到文件流的尾部	
    float  oldsize = in1.tellg() ;		//读取文件指针的位置
	cout<< oldsize<<endl;
    in1.close();
	ifstream in2(codePath);
    in2.seekg(0, ios::end);      //设置文件指针到文件流的尾部

    float  newsize = in2.tellg() ;
			cout<< newsize<<endl;
	//读取文件指针的位置
    in2.close();
		float f= newsize/oldsize;
		cout<<f<<endl;
		cout<<"压缩率为"<<f*100<<"%"<<endl;
	return 0;
}