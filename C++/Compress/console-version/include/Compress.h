#ifndef COMPRESS_H
#define COMPRESS_H

#include"Huffman.h"
#include<fstream>
#include<assert.h>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdio>
#include<cstdlib>
//ASCII有256位
const int CharSize=256;
class Compress
{
    public:
        Compress();
        //读文件
        void ReadFile();
        //执行压缩
        void start();
        virtual ~Compress();
    protected:

    private:
        string inName;
        //输入文件名
        string outName;
        //每种字符个数
        int *CharNum;
        //出现的字符及个数
        int HaveNum;
        int *HaveName;
        int *HaveTimes;
        //字符编码信息
        string *CodeInfo;
        //数据长度
        int length;
        //统计各种字符数
        void CountNum();
        //二进制转十进制
        char TranToNum(string data);
        //哈夫曼编码
        void BuildCode();
        //输出压缩的文件
        void Write(string fileName);
        int binSearch(int k,int a[],int l,int d);
};

#endif // COMPRESS_H
