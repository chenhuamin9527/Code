#ifndef UNPACK_H
#define UNPACK_H

#include"Huffman.h"
#include<fstream>
#include<assert.h>
#include<cstring>
#include<cstdio>
#include<cstdlib>
//ASCII��256λ
const int CharSize1=256;
class Unpack
{
    public:
        Unpack();
        //���ļ�
        void ReadFile();
        //ִ�н�ѹ
        void start();
        virtual ~Unpack();

    protected:

    private:
        FILE *read;
        string inName;
        string outName;
        Node packTree[2*CharSize1];
        //Դ�ļ���С
        int preLen;
        //���ֵ��ַ�������
        int HaveNum;
        int *HaveName;
        int *HaveTimes;
        //�ַ�������Ϣ
        string *CodeInfo;
        //����������
        void BuildCode();
        //����תΪ01����
        void TransCode(string fileName);
        string TranToBit(int aim);
        //���ѹ�����ļ�
};

#endif // UNPACK_H
