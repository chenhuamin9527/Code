#ifndef UNPACK_H
#define UNPACK_H

#include"Huffman.h"
#include<fstream>
#include<assert.h>
#include<cstring>
#include<cstdio>
#include<cstdlib>
//ASCII有256位
const int CharSize1=256;
class Unpack
{
    public:
        Unpack();
        //读文件
        void ReadFile();
        //执行解压
        void start();
        virtual ~Unpack();

    protected:

    private:
        FILE *read;
        string inName;
        string outName;
        Node packTree[2*CharSize1];
        //源文件大小
        int preLen;
        //出现的字符及个数
        int HaveNum;
        int *HaveName;
        int *HaveTimes;
        //字符编码信息
        string *CodeInfo;
        //哈夫曼编码
        void BuildCode();
        //数据转为01编码
        void TransCode(string fileName);
        string TranToBit(int aim);
        //输出压缩的文件
};

#endif // UNPACK_H
