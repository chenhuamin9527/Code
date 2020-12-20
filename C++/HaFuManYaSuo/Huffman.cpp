#include "Huffman.h"
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

Huffman::Huffman()
{
	huffTree = NULL;
	chars = NULL;
	n = 0;
}

Huffman::~Huffman()
{

}

//对Text串进行哈弗曼编码
void Huffman::Encode()
{
	code = "";
	for (string::size_type i = 0; i != text.size(); ++i)
	{
		for (int j = 1; j <= n; ++j)
			if (chars[j].c == text[i])
				code += chars[j].code;
	}
}

void Huffman::PrintCharWeight()
{
	CharMapNode cc ;
	for(int p = 0 ; p<= n; p++){
		for(int j = 0 ;j<= n-1; j++){
			if(chars[j].weight>chars[j+1].weight){
				cc = chars[j];
				chars[j] = chars[j+1];
				chars[j+1] = cc;
			}
		}
	}

	cout << " |字符|———|权值|" << endl;
	for (int i = 1; i <= n; ++i)
	{
		switch (chars[i].c)
		{
		case '\t':
			cout <<"  |"<< "\\t"<<"|";
			break;
		case '\n':
			cout <<"  |"<< "\\n"<<"|";
			break;
		default:
			cout << "  |" << chars[i].c <<"|";
			break;
		}
			cout << "——|" << chars[i].weight <<"|" << endl;
	}
}

void Huffman::PrintCharCode()
{
	cout << " |字符|———|哈弗曼编码|" << endl;
	for (int i = 1; i <= n; ++i)
	{
		switch (chars[i].c)
		{
		case '\t':
			cout <<"  | "<< "\\t"<<" |";
			break;
		case '\n':
			cout <<"  | "<< "\\n"<<" |";
			break;
		default:
			cout << "  | " << chars[i].c <<" |";
			break;
		}
			cout << "—————| " << chars[i].code <<" |" << endl;
	}
}

void Huffman::select(int n, int &s1, int &s2)
{
	s1 = s2 = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (huffTree[i].parent != 0)// 有父节点，已经操作过
			continue;
		if (s1 == 0)
			s1 = i;
		else if (s2 == 0)
		{
			//s1恒为权值较小的那个，s1大时，s1和s2交换
			if (huffTree[i].weight < huffTree[s1].weight)
			{
				s2 = s1;
				s1 = i;
			}
			else
				s2 = i;
		}
		else
		{
			if (huffTree[i].weight < huffTree[s1].weight)
			{
				s2 = s1;
				s1 = i;
			}
			else if (huffTree[i].weight < huffTree[s2].weight)
				s2 = i;
		}
	}

}

//输出编码
void Huffman::PrintCode()
{
	cout << code << endl;
}

//根据各字符的权值建立字符-编码表
void Huffman::MakeCharMap()
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;		//哈弗曼树所需节点数
	huffTree = new HuffTreeNode[m+1];		//0号单元未使用
	//初始化
	int i;
	for (i = 1; i <= n; ++i)//n个字符，节点有权值。
	{
		huffTree[i].weight = chars[i].weight;
		huffTree[i].parent = 0;
		huffTree[i].lchild = 0;
		huffTree[i].rchild = 0;
	}
	for (i = n + 1; i <= m; ++i)//n-1个节点用来作为其他两个有权值节点的根节点
	{
		huffTree[i].weight = 0;
		huffTree[i].parent = 0;
		huffTree[i].lchild = 0;
		huffTree[i].rchild = 0;
	}
	//建哈弗曼树
	for (i = n + 1; i <= m; ++i)
	{
		int s1,s2;
		select(i - 1, s1, s2);
		huffTree[s1].parent = huffTree[s2].parent = i;
		huffTree[i].lchild = s1;
		huffTree[i].rchild = s2;
		huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;
	}

	//从节点到根节点逆向求每个字符的哈弗曼编码
	char *cd = new char[n];	//分配求编码的工作空间（每个字符编码结果最长n-1再加上'\0'）
	cd[n-1] = '\0';			//编码结束符
	for(i = 1; i <= n; ++i)		//逐个字符求哈弗曼编码
	{
		int start = n - 1;
		int c,f;
		//从叶子到根逆向求编码
		for (c = i, f = huffTree[i].parent; f != 0; c = f, f = huffTree[f].parent)
		{
			if (huffTree[f].lchild == c)	//左孩子编码为0
				cd[--start] = '0';
			else							//右孩子编码为1
				cd[--start] = '1';
		}
		chars[i].code = new char[n - start];	//为第i个字符编码分配空间
		strcpy(chars[i].code,&cd[start]);
	}
	delete cd;
}

//从文件读入原文
void Huffman::ReadTextFromFile(char *filename)
{
	ifstream infile(filename);//从硬盘到内存
	if(!infile)
	{
		cerr << " 无法打开文件！" <<endl;
		return;
	}
	char c;
	while(infile.get(c))
	{
		text += c;
	}
}

//将编码存入文件
void Huffman::SaveCodeToFile(char *filename)
{

	cout<<code<<endl;
	system("pause");
	FILE * f;
	f = fopen(filename,"a");
	unsigned char chars ;
	string str = code;
	int length = str.length();
	int times =  length/8;
	if(times*8<length){
		times = times +1;
	}

	cout<<"原长度大小"<<length<<endl;
//	unsigned char size = (char)length;
	fwrite(&length,sizeof(int),1,f);
//			cout<<"0,1代码大小=="<<size<<"  ********"<<endl;
	system("pause");

	int num = 0;
	for(int i = 0 ; i < times; i++){
		chars = 0;
		for(int j = 0 ; j < 8 ; j++){
			chars = (chars << 1);
			if(str[num] == '1'){
				chars += 1;
			}
			num += 1;
		}

	fwrite(&chars,sizeof(unsigned char),1,f);
	}
	fclose(f);



}

//从文件读入编码
void Huffman::ReadCodeFromFile(char *filename)
{

	ifstream in(filename);
    in.seekg(0, ios::end);      //设置文件指针到文件流的尾部
    int  size = in.tellg() ;	
	//读取文件指针的位置
	size = size -1;
    in.close();//关闭文件
	cout<<"文件字节"<< size<< endl;
	char* chars = new char[size];
	int length;
    string str = "";
	FILE * f;
	f = fopen(filename,"rb");
	fread(&length,sizeof(int),1,f);

		cout<<"0,1代码大小=="<<length<<"  ********"<<endl;
	system("pause");

	int temp[8];
	char c;
	fread(chars,sizeof(unsigned char),size,f);
	int num = 0;//查数，确保数量是原来编码数
	for(int j = 0 ; j < size ; j ++){ 
		for(int i = 0 ; i < 8 ; i ++){
			if(num == length){
				goto next;
			}
			temp[i] = (int)((chars[j]>>(7-i))%2);
			if(temp[i]<0){
				temp[i] = - temp[i];
			}
			itoa(temp[i], &c,10); 
			str += c;
			num++;
		}
		//	cout<<endl;
	}
next: 
	cout<<str<<endl;
	cout<<"大小"<<str.length()<<endl;
	system("pause");
	fclose(f);
	code = str;
}

//将0-1编码串解码
void Huffman::Decode()
{
	text = "";
	string::size_type i,count;//调用string中的size_type，用来操作string的长度 
	for (i = 0; i < code.size(); i += count)
	{
		//每个字符的编码结果最长n-1，从1至n-1依次尝试
		for (count = 1; count < n; ++count)
		{ 
			for (int j = 1; j <= n; ++j)
				if (code.substr(i, count) == chars[j].code)//从i开始截取cout个编码，看看存不存在
				{
					text += chars[j].c;
					goto next;//跳出到下一条信息开始处
				}
		}
next:
		;
	}
}

//统计原文中各字符的权值
void Huffman::CountCharsWeight()
{
	if (text.empty())
		return;
	if (chars != NULL)
		delete chars;
	int i = 0;
	n = 0;
	chars = new CharMapNode[2];
	chars[1].c = text[i];
	chars[1].weight = 1;
	++n;
	int total = 1;//chars初始值有一个
	for (i = 1; i != text.size(); ++i)
	{
		int j;

		for (j = 1; j <= n; ++j)	//遍历当前字符表，如果已存在该字符，权值+1
		{
			if (text[i] == chars[j].c)
			{	
				total++;//总数+1
				++chars[j].weight;
				break;
			}
		}
		if (j > n)		//该字符不存在，添加该字符
		{
			total++;//总数+1
			++n;
			CharMap newchars = new CharMapNode[n + 1];
			memcpy(newchars, chars, n * sizeof(CharMapNode));//原先的复制到新的chars
			delete chars;//释放
			chars = newchars;
			chars[n].c = text[i];
			chars[n].weight = 1;
		}
	}

	cout << "**************************" <<endl;
	cout << "字符总计" << total << endl;
	cout << "**************************" <<endl;
	system("pause");
	cout<<endl;
	for(int p = 0 ; p < n+1 ; p++){
		chars[p].weight = chars [p].weight / total;
	}
	
}



void Huffman::SaveTextToFile(char *filename)
{
	ofstream outfile(filename);
	if (!outfile)
	{
		cerr << "保存文件出错！" << endl;
		return;
	}
	outfile << text;
}

int Huffman::FileSize(char* path){
	  ifstream in(path);
    in.seekg(0, ios::end);      //设置文件指针到文件流的尾部
    int  i = in.tellg(); //读取文件指针的位置
    in.close();//关闭文件
	return i;
}