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
//ASCII��256λ
const int CharSize=256;
class Compress
{
    public:
        Compress();
        //���ļ�
        void ReadFile();
        //ִ��ѹ��
        void start();
        virtual ~Compress();
    protected:

    private:
        string inName;
        //�����ļ���
        string outName;
        //ÿ���ַ�����
        int *CharNum;
        //���ֵ��ַ�������
        int HaveNum;
        int *HaveName;
        int *HaveTimes;
        //�ַ�������Ϣ
        string *CodeInfo;
        //���ݳ���
        int length;
        //ͳ�Ƹ����ַ���
        void CountNum();
        //������תʮ����
        char TranToNum(string data);
        //����������
        void BuildCode();
        //���ѹ�����ļ�
        void Write(string fileName);
        int binSearch(int k,int a[],int l,int d);
};

#endif // COMPRESS_H
