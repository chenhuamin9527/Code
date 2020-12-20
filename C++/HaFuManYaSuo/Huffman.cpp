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

//��Text�����й���������
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

	cout << " |�ַ�|������|Ȩֵ|" << endl;
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
			cout << "����|" << chars[i].weight <<"|" << endl;
	}
}

void Huffman::PrintCharCode()
{
	cout << " |�ַ�|������|����������|" << endl;
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
			cout << "����������| " << chars[i].code <<" |" << endl;
	}
}

void Huffman::select(int n, int &s1, int &s2)
{
	s1 = s2 = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (huffTree[i].parent != 0)// �и��ڵ㣬�Ѿ�������
			continue;
		if (s1 == 0)
			s1 = i;
		else if (s2 == 0)
		{
			//s1��ΪȨֵ��С���Ǹ���s1��ʱ��s1��s2����
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

//�������
void Huffman::PrintCode()
{
	cout << code << endl;
}

//���ݸ��ַ���Ȩֵ�����ַ�-�����
void Huffman::MakeCharMap()
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;		//������������ڵ���
	huffTree = new HuffTreeNode[m+1];		//0�ŵ�Ԫδʹ��
	//��ʼ��
	int i;
	for (i = 1; i <= n; ++i)//n���ַ����ڵ���Ȩֵ��
	{
		huffTree[i].weight = chars[i].weight;
		huffTree[i].parent = 0;
		huffTree[i].lchild = 0;
		huffTree[i].rchild = 0;
	}
	for (i = n + 1; i <= m; ++i)//n-1���ڵ�������Ϊ����������Ȩֵ�ڵ�ĸ��ڵ�
	{
		huffTree[i].weight = 0;
		huffTree[i].parent = 0;
		huffTree[i].lchild = 0;
		huffTree[i].rchild = 0;
	}
	//����������
	for (i = n + 1; i <= m; ++i)
	{
		int s1,s2;
		select(i - 1, s1, s2);
		huffTree[s1].parent = huffTree[s2].parent = i;
		huffTree[i].lchild = s1;
		huffTree[i].rchild = s2;
		huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;
	}

	//�ӽڵ㵽���ڵ�������ÿ���ַ��Ĺ���������
	char *cd = new char[n];	//���������Ĺ����ռ䣨ÿ���ַ��������n-1�ټ���'\0'��
	cd[n-1] = '\0';			//���������
	for(i = 1; i <= n; ++i)		//����ַ������������
	{
		int start = n - 1;
		int c,f;
		//��Ҷ�ӵ������������
		for (c = i, f = huffTree[i].parent; f != 0; c = f, f = huffTree[f].parent)
		{
			if (huffTree[f].lchild == c)	//���ӱ���Ϊ0
				cd[--start] = '0';
			else							//�Һ��ӱ���Ϊ1
				cd[--start] = '1';
		}
		chars[i].code = new char[n - start];	//Ϊ��i���ַ��������ռ�
		strcpy(chars[i].code,&cd[start]);
	}
	delete cd;
}

//���ļ�����ԭ��
void Huffman::ReadTextFromFile(char *filename)
{
	ifstream infile(filename);//��Ӳ�̵��ڴ�
	if(!infile)
	{
		cerr << " �޷����ļ���" <<endl;
		return;
	}
	char c;
	while(infile.get(c))
	{
		text += c;
	}
}

//����������ļ�
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

	cout<<"ԭ���ȴ�С"<<length<<endl;
//	unsigned char size = (char)length;
	fwrite(&length,sizeof(int),1,f);
//			cout<<"0,1�����С=="<<size<<"  ********"<<endl;
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

//���ļ��������
void Huffman::ReadCodeFromFile(char *filename)
{

	ifstream in(filename);
    in.seekg(0, ios::end);      //�����ļ�ָ�뵽�ļ�����β��
    int  size = in.tellg() ;	
	//��ȡ�ļ�ָ���λ��
	size = size -1;
    in.close();//�ر��ļ�
	cout<<"�ļ��ֽ�"<< size<< endl;
	char* chars = new char[size];
	int length;
    string str = "";
	FILE * f;
	f = fopen(filename,"rb");
	fread(&length,sizeof(int),1,f);

		cout<<"0,1�����С=="<<length<<"  ********"<<endl;
	system("pause");

	int temp[8];
	char c;
	fread(chars,sizeof(unsigned char),size,f);
	int num = 0;//������ȷ��������ԭ��������
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
	cout<<"��С"<<str.length()<<endl;
	system("pause");
	fclose(f);
	code = str;
}

//��0-1���봮����
void Huffman::Decode()
{
	text = "";
	string::size_type i,count;//����string�е�size_type����������string�ĳ��� 
	for (i = 0; i < code.size(); i += count)
	{
		//ÿ���ַ��ı������n-1����1��n-1���γ���
		for (count = 1; count < n; ++count)
		{ 
			for (int j = 1; j <= n; ++j)
				if (code.substr(i, count) == chars[j].code)//��i��ʼ��ȡcout�����룬�����治����
				{
					text += chars[j].c;
					goto next;//��������һ����Ϣ��ʼ��
				}
		}
next:
		;
	}
}

//ͳ��ԭ���и��ַ���Ȩֵ
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
	int total = 1;//chars��ʼֵ��һ��
	for (i = 1; i != text.size(); ++i)
	{
		int j;

		for (j = 1; j <= n; ++j)	//������ǰ�ַ�������Ѵ��ڸ��ַ���Ȩֵ+1
		{
			if (text[i] == chars[j].c)
			{	
				total++;//����+1
				++chars[j].weight;
				break;
			}
		}
		if (j > n)		//���ַ������ڣ���Ӹ��ַ�
		{
			total++;//����+1
			++n;
			CharMap newchars = new CharMapNode[n + 1];
			memcpy(newchars, chars, n * sizeof(CharMapNode));//ԭ�ȵĸ��Ƶ��µ�chars
			delete chars;//�ͷ�
			chars = newchars;
			chars[n].c = text[i];
			chars[n].weight = 1;
		}
	}

	cout << "**************************" <<endl;
	cout << "�ַ��ܼ�" << total << endl;
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
		cerr << "�����ļ�����" << endl;
		return;
	}
	outfile << text;
}

int Huffman::FileSize(char* path){
	  ifstream in(path);
    in.seekg(0, ios::end);      //�����ļ�ָ�뵽�ļ�����β��
    int  i = in.tellg(); //��ȡ�ļ�ָ���λ��
    in.close();//�ر��ļ�
	return i;
}