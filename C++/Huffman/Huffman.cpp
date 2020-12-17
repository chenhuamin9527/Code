// Huffman.cpp: 定义应用程序的入口点。
//

#include "Huffman.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <queue>
#include <map>
#include "OutPut.h"
#include "Code.h"

using  namespace std;

void TxtZip()
{
    char key;  //txt文件字符，map中的关键字
    map<char, int> data_b;  //文件中的字符以及对应的出现次数
    pair<char, string> code; //字符及对应编码
    vector<pair<char, string>> codeorder;  //字符编码集
    fstream file(TXT_NAME);
    if (!file)
    {
        cout << "fail to open the file" << endl;
        exit(0);
    }
    while (true)  //填充map
    {
        file.read(&key, 1);
        if (file.peek() == EOF)
            break;
        data_b[key] += 1;
    }
    file.close();
    HuffManTree Htree(data_b);  //构建哈弗曼树
//    Htree.PreOrder(Htree.root);
    StructuralCoding(&codeorder, Htree.root);  //构建字符编码集
    OutToBinFile(&codeorder, &data_b);
    codeorder.clear();
}

void BinUnzip()  //获取编码流和01串
{
    char c, o, p, q;
    bitset<8> a;
    string strline, codestream;  //strline存储二进制文件中的字符及对应权值，codestream存储01串
    fstream infile_b(BIN_NAME, ios::in | ios::binary);
    while (true)         //从二进制文件中获取字符及对应权值
    {
        if (infile_b.peek() == EOF)
            break;
        infile_b.read(&o, 1);
        if (o == '*')
        {
            infile_b.read(&p, 1);
            infile_b.read(&q, 1);
            if (p == '@' && q == '#')
                break;
            else infile_b.seekg(-2, ios::cur);
        }
        strline += o;
    }
    while (true)       //读取字符转化为01串
    {
        if (infile_b.peek() == EOF)
            break;
        infile_b.read(&c, 1);
        a = c;   //字符赋值给bitset<8>可直接转化为二进制
        codestream += a.to_string();
    }
    cout << "Decompression, please wait..." << endl;
    OutToTxt(&strline, &codestream);
}

int main(int argc, char* argv[]) {
    if (argc == 2 && !strcmp(argv[1], "-zip")) {
        TxtZip();
    }
    else if (argc == 2 && !strcmp(argv[1], "-unzip"))
        BinUnzip();
    else cout << "please input legal parameters!!";
    return 0;
}