#include "Unpack.h"
#include<iostream>
using namespace std;
Unpack::Unpack()
{
    //ctor
    HaveName = new int[CharSize1];
    HaveTimes = new int[CharSize1];

    memset(HaveTimes,0,sizeof(int)*CharSize1);
    memset(HaveName,0,sizeof(int)*CharSize1);
}
void Unpack::ReadFile()
{
    cout<<"Enter file name:";
    cin>>inName;
    if((read=fopen(inName.data(),"rb"))==NULL){
        cout<<"open file error!"<<endl;
        exit(0);
    }
    char ch;
    int step=1,t=0;
    HaveNum=preLen=0;
    while(!feof(read)&&step!=4)
    {
        if(step!=3)ch=fgetc(read);
        switch(step)
        {
            //1.����preLen
            case 1:
                if(ch=='\n'){
                    step++;
                }
                else{
                    preLen = preLen*10 + ch-'0';
                }
                break;
            //2.��������С
            case 2:
                if(ch=='\n'){
                    step++;
                }
                else{
                    HaveNum = HaveNum*10 + ch-'0';
                }
                break;
            //3.��ȡ���뷽ʽ
            case 3:
                if(t==HaveNum){
                    step++;
                }
                else{
                    for(int i=0;i<HaveNum;i++)
                    {
                        //�����ַ�
                        ch=fgetc(read);
                        HaveName[i]=ch;
                        //����ո�
                        ch = fgetc(read);
                        while((ch=fgetc(read))&&ch!='\n')
                        {
                            HaveTimes[i]=HaveTimes[i]*10+ch-'0';

                        }
                        t++;
                    }
                }
                break;
            //4.�����ļ�
            case 4:
                break;
            default:
                break;
        }
    }
}
void Unpack::BuildCode()
{
    Huffman tree(HaveTimes,HaveNum);
    tree.compile();
    //���ɱ�����Ϣ
    CodeInfo = new string[HaveNum];
    for(int i=0;i<HaveNum;i++)
        CodeInfo[i]=tree.getCode(i);
    for(int i=0;i<2*HaveNum;i++)
        packTree[i]=tree.getNode(i);
}
string Unpack::TranToBit(int aim)
{
    string a="";
    int sum=aim;
    char temp[10];
    int i=0;
    while(sum)
    {
        temp[i++]=sum%2+'0';
        sum/=2;
    }
    for(;i<8;i++)temp[i]='0';
    temp[i]='\0';
    for(int i=7;i>=0;i--)a+=temp[i];
    return a;
}
void Unpack::TransCode(string fileName)
{
    FILE *fp;
    if((fp=fopen(fileName.data(),"wb"))==NULL){
        cout<<"open file error!"<<endl;
        exit(0);
    }
    //01�����ƴ�
    string code="";
    //Դ�ļ��ַ���
    int charNum=0;
    char cRead;
    while(!feof(read)){
        cRead=fgetc(read);
        code+=TranToBit(cRead+128);
        while(code.length()>20&&charNum<preLen)
        {
            int start = 2*HaveNum-2;
            while(packTree[start].lchild!=-1&&packTree[start].rchild!=-1)
            {
                if(code[0]=='0')start=packTree[start].lchild;
                else start=packTree[start].rchild;
                code=code.substr(1);
            }
            int ch=HaveName[start];
            fputc(ch,fp);
            charNum++;
        }
    }
    cout<<charNum<<"/"<<preLen<<endl;
    while(charNum<preLen)
    {
        int start = 2*HaveNum-2;
        while(packTree[start].lchild!=-1&&packTree[start].rchild!=-1)
        {
            if(code[0]=='0')start=packTree[start].lchild;
            else start=packTree[start].rchild;
            code=code.substr(1);
        }
        int ch=HaveName[start];
        fputc(ch,fp);
        charNum++;
    }
    fclose(fp);
    fclose(read);
}
void Unpack::start()
{
    cout<<"Outer file name:";
    cin>>outName;
    cout<<"-------��ѹ��-------"<<endl;
    BuildCode();
    TransCode(outName);
    cout<<"------��ѹ���------"<<endl;
}
Unpack::~Unpack()
{
    //dtor
    delete HaveName;
    delete HaveTimes;
    delete CodeInfo;
}
