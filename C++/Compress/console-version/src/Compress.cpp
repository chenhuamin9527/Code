#include "Compress.h"
#include<iostream>
using namespace std;
Compress::Compress()
{
    CharNum = new int[CharSize];
    HaveName = new int[CharSize];
    HaveTimes = new int[CharSize];
    //ctor
    memset(CharNum,0,sizeof(int)*CharSize);
    memset(HaveName,0,sizeof(int)*CharSize);
    memset(HaveTimes,0,sizeof(int)*CharSize);
}
char Compress::TranToNum(string data)
{
    int sum=0,len=data.length();
    for(int i=0;i<len;i++)
        sum = sum + (data[i]-'0')*pow(2,len-i-1);
    char aim = sum;
    return aim-128;
}
void Compress::CountNum()
{
    HaveNum=0;
    for(int i=0;i<CharSize;i++)
    {
        if(CharNum[i])
        {
            HaveTimes[HaveNum]=CharNum[i];
            HaveName[HaveNum]=i-128;
            HaveNum++;
        }
    }
}
void Compress::ReadFile()
{
    //文件指针
    FILE* fp;
    //输入要读取的图像名
    cout<<"Enter file name:";
    cin>>inName;
    //以二进制方式打开图像
    if ( (fp=fopen(inName.data(), "rb" ))==NULL )
    {
        cout<<"Open file failed!"<<endl;
        exit(0);
    }
    //获取数据总长度
    fseek(fp, 0, SEEK_END);
    length=ftell(fp);
    rewind(fp);
    char ch;
    while(!feof(fp))
    {
        ch = fgetc(fp);
        CharNum[ch+128]++;
    }
    CountNum();
}
void Compress::BuildCode()
{
    Huffman tree(HaveTimes,HaveNum);
    tree.compile();
    //生成编码信息
    CodeInfo = new string[HaveNum];
    for(int i=0;i<HaveNum;i++)
        CodeInfo[i]=tree.getCode(i);
}
string NumtoStr(int n)
{
    string a="";
    char num[100];
    int i=0;
    while(n)
    {
        num[i]=n%10+'0';
        n/=10;
        i++;
    }
    for(int j=i-1;j>=0;j--)a+=num[j];
    return a;
}
int Compress::binSearch(int k,int a[],int l,int d)
{
    if(l>d)return -1;
    int r=(l+d)/2;
    if(a[r]==k)return r;
    else if(a[r]>k)binSearch(k,a,l,r-1);
    else binSearch(k,a,r+1,d);
    //return -1;
}
void Compress::Write(string fileName)
{
    outName=fileName;
    FILE *fp;
    if((fp=fopen(fileName.data(),"wb"))==NULL){
        cout<<"open file error!"<<endl;
        exit(0);
    }
    string temp;
    int l;
    //文件大小
    temp=NumtoStr(length);
    l=temp.length();
    for(int i=0;i<l;i++)
        fputc(temp[i],fp);
    fputc('\n',fp);
    //编码数量
    temp=NumtoStr(HaveNum);
    l=temp.length();
    for(int i=0;i<l;i++)
        fputc(temp[i],fp);
    fputc('\n',fp);
    //编码格式   ASCII值---空格---权值
    for(int i=0;i<HaveNum;i++)
    {
        fputc(HaveName[i],fp);
        fputc(' ',fp);
        temp = NumtoStr(HaveTimes[i]);
        l=temp.length();
        for(int i=0;i<l;i++)
            fputc(temp[i],fp);
        fputc('\n',fp);
    }
    FILE *read;
    read = fopen(inName.data(),"rb");
    char ch;
    string FinalCode = "";
    while(!feof(read))
    {
        ch = fgetc(read);
        int j=binSearch(ch,HaveName,0,HaveNum-1);
        FinalCode+=CodeInfo[j];
        while(FinalCode.length()>=8)
        {
            string temp=FinalCode.substr(0,8);
            char value = TranToNum(temp);
            fputc(value,fp);
            FinalCode=FinalCode.substr(8);
        }
    }
    if(FinalCode.length()){
        while(FinalCode.length()%8)FinalCode+="0";
        char value = TranToNum(FinalCode);
        fputc(value,fp);
    }
    fclose(fp);
    fclose(read);
}
void Compress::start()
{
    string outputName;
    cout<<"Outer file name:";
    cin>>outputName;
    cout<<"-------压缩中-------"<<endl;
    BuildCode();
    Write(outputName);
    cout<<"------压缩完成------"<<endl;
}
Compress::~Compress()
{
    //dtor
    delete CharNum;
    delete HaveName;
    delete HaveTimes;
    delete CodeInfo;
}
