#include "Huffman.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <map>

using namespace std;
#define TXT_NAME "test.txt"    //��ѹ���ļ�
#define BIN_NAME "text2.o"  //ѹ������ļ�

void OutToBinFile(vector<pair<char, string>>* codeorder, map<char, int>* data_b)
{
    fstream infile(TXT_NAME); //�򿪴�ѹ���ļ�
    if (!infile)
    {
        cout << "fail to open the file" << endl;
        exit(0);
    }
    char c;
    string codestream;  //01��
    //��λ��ȡ�ļ��е��ַ������ݱ��뼯����ת��Ϊ01���洢��codestream��
    while (true)
    {
        if (infile.peek() == EOF)
            break;
        infile.read(&c, 1);
        for (auto iter : *codeorder)
        {
            if (c == iter.first)
                codestream += iter.second;
        }
    }
    infile.close();
    fstream outfile;
    outfile.open(BIN_NAME, ios::out | ios::binary);  //��ѹ�����ļ�
    for (auto iter : *data_b)  //�ַ�����ӦȨֵ�洢���������ļ�
    {
        outfile << iter.first << "~" << iter.second << " ";
    }
    outfile << "*@#";  //�������������
    while (codestream.size() >= 8)   //01��ת��Ϊ�ַ������
    {
        bitset<8> bits(codestream, 0, 8);
        codestream.erase(0, 8);
        outfile << static_cast<char>(bits.to_ulong());
    }
    if (!codestream.empty())   //��β���Ȳ�����λ����0���룬��¼ʣ��ĳ��Ƚ�������ļ�ĩβ���ڶ�ȡʱת��Ϊ�±�λ�û�ԭ�������ַ���
    {
        unsigned long loc = codestream.size();
        bitset<8> bits(codestream, 0, loc);
        outfile << static_cast<char>(bits.to_ulong());
        outfile << static_cast<char>(loc);
    }
    outfile.close();
}

void OutToTxt(string* strline, string* codestream)   //����map������������������01�����
{
    char a;
    int b;
    unsigned long t;
    string tmp;
    map<char, int> data_b;
    fstream outfile_t(TXT_NAME, ios::out);  //��ѹ���ļ�

    while (!strline->empty())   //��ȡ���д洢���ַ��Լ����ֵ�Ƶ�Σ��ɴ����ɹ�������
    {
        a = strline->at(0);
        strline->erase(0, 2);
        t = strline->find(' ');
        tmp = strline->substr(0, t);
        strline->erase(0, t + 1);
        b = stoi(tmp, nullptr, 10);
        data_b.insert(pair<char, int>(a, b));
    }
    HuffManTree HTree(data_b);  //����
    Node* p = HTree.root;

    string end = codestream->substr(codestream->size() - 16, 16);  //����ĩβ������λ�����
    bitset<8> loc(end, 8, 16);
    unsigned long add = loc.to_ulong();
    end = end.substr(8 - add, add);
    codestream->erase(codestream->size() - 16, codestream->size());
    *codestream += end;

    for (auto i : *codestream)  //��01��������������
    {
        if (i == '0')  //��0������
            p = p->LeftChild;
        if (i == '1')  //��1������
            p = p->RightChild;
        if (p->LeftChild == nullptr && p->RightChild == nullptr)  //��Ҷ�ӽڵ㣬��ȡ�ַ����洢
        {
            outfile_t << p->key;
            p = HTree.root;
        }
    }
}