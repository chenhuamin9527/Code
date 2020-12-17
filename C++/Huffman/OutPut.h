#include "Huffman.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <map>

using namespace std;
#define TXT_NAME "test.txt"    //待压缩文件
#define BIN_NAME "text2.o"  //压缩后的文件

void OutToBinFile(vector<pair<char, string>>* codeorder, map<char, int>* data_b)
{
    fstream infile(TXT_NAME); //打开待压缩文件
    if (!infile)
    {
        cout << "fail to open the file" << endl;
        exit(0);
    }
    char c;
    string codestream;  //01串
    //逐位读取文件中的字符，根据编码集将其转换为01串存储在codestream中
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
    outfile.open(BIN_NAME, ios::out | ios::binary);  //打开压缩后文件
    for (auto iter : *data_b)  //字符及对应权值存储进二进制文件
    {
        outfile << iter.first << "~" << iter.second << " ";
    }
    outfile << "*@#";  //编码规则结束标记
    while (codestream.size() >= 8)   //01串转换为字符并输出
    {
        bitset<8> bits(codestream, 0, 8);
        codestream.erase(0, 8);
        outfile << static_cast<char>(bits.to_ulong());
    }
    if (!codestream.empty())   //结尾长度不够八位，用0补齐，记录剩余的长度将其放在文件末尾，在读取时转换为下标位置还原本来的字符串
    {
        unsigned long loc = codestream.size();
        bitset<8> bits(codestream, 0, loc);
        outfile << static_cast<char>(bits.to_ulong());
        outfile << static_cast<char>(loc);
    }
    outfile.close();
}

void OutToTxt(string* strline, string* codestream)   //构建map，建哈弗曼树，遍历01串输出
{
    char a;
    int b;
    unsigned long t;
    string tmp;
    map<char, int> data_b;
    fstream outfile_t(TXT_NAME, ios::out);  //打开压缩文件

    while (!strline->empty())   //读取其中存储的字符以及出现的频次，由此生成哈弗曼树
    {
        a = strline->at(0);
        strline->erase(0, 2);
        t = strline->find(' ');
        tmp = strline->substr(0, t);
        strline->erase(0, t + 1);
        b = stoi(tmp, nullptr, 10);
        data_b.insert(pair<char, int>(a, b));
    }
    HuffManTree HTree(data_b);  //建树
    Node* p = HTree.root;

    string end = codestream->substr(codestream->size() - 16, 16);  //处理末尾不够八位的情况
    bitset<8> loc(end, 8, 16);
    unsigned long add = loc.to_ulong();
    end = end.substr(8 - add, add);
    codestream->erase(codestream->size() - 16, codestream->size());
    *codestream += end;

    for (auto i : *codestream)  //用01串遍历哈弗曼树
    {
        if (i == '0')  //遇0，走左
            p = p->LeftChild;
        if (i == '1')  //遇1，走右
            p = p->RightChild;
        if (p->LeftChild == nullptr && p->RightChild == nullptr)  //遇叶子节点，提取字符并存储
        {
            outfile_t << p->key;
            p = HTree.root;
        }
    }
}