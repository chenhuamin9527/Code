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
	/****************��һ�������ַ��Ͷ�ӦȨֵ******************/
//ѹ��
		cout<<"��������Ҫѹ�����ļ�·���Լ��ļ�����û��·��Ĭ���ļ���Ŀ¼\n"<<endl;
		cin>> loadpath;
		loadPath = const_cast<char*>(loadpath.c_str());
		huffman.ReadTextFromFile(loadPath);
		huffman.CountCharsWeight();
		cout << "�ַ�����ӦȨֵ��" << endl;
		huffman.PrintCharWeight();
		cout << endl <<endl;
		system("pause");
		huffman.MakeCharMap();
		cout << "�ַ�����Ӧ���룺" << endl;
		huffman.PrintCharCode();
		system("pause");
		cout << endl;
		huffman.Encode();
		cout<<"������ѹ���ļ��洢·���Լ��ļ�����û��·��Ĭ���ļ���Ŀ¼\n"<<endl;
		cin>> codepath;
		codePath = const_cast<char*>(codepath.c_str());
		huffman.SaveCodeToFile(codePath);
		cout<< "ѹ�����"<<endl;
		system("pause");
		//��ѹ
		cout << endl;
		cout<<"��������Ҫ��ѹ���ļ��洢��·���Լ��ļ�����û��·��Ĭ���ļ���Ŀ¼\n"<<endl;
		cin>> savepath;
		savePath = const_cast<char*>(savepath.c_str());
		cout << "�Ա�����н���.........���Ժ�" << endl;
		huffman.ReadCodeFromFile(codePath);
		huffman.Decode();
		huffman.SaveTextToFile(savePath);
		system("pause");
		cout<< endl;
		//�Ƚ�
		ifstream in1(loadPath);
    in1.seekg(0, ios::end);      //�����ļ�ָ�뵽�ļ�����β��	
    float  oldsize = in1.tellg() ;		//��ȡ�ļ�ָ���λ��
	cout<< oldsize<<endl;
    in1.close();
	ifstream in2(codePath);
    in2.seekg(0, ios::end);      //�����ļ�ָ�뵽�ļ�����β��

    float  newsize = in2.tellg() ;
			cout<< newsize<<endl;
	//��ȡ�ļ�ָ���λ��
    in2.close();
		float f= newsize/oldsize;
		cout<<f<<endl;
		cout<<"ѹ����Ϊ"<<f*100<<"%"<<endl;
	return 0;
}