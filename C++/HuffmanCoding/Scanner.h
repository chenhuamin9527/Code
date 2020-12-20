#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Node
{
	char Code;//该字符
	double Rate;//该字符出现频率
	string coding;//哈夫曼编码
	Node* Next;
	Node* parent;//父指针
	Node* left;//左指针
	Node* right;//右指针
};

class Scanner
{
public:
	string text;
	ifstream in;
	string filename;
	Node* Character;
	int num;
	Scanner() :num(0){}
	void Run()
	{
		cout << "请输入文件名：";
		cin >> filename;
		in.open(filename);
		while (!in)
		{
			cout << "读取文件出错。请重新输入：" << endl;
			getline(cin, filename, '\n');
			in.open(filename);
		}
		Character = new Node();
		Node* p1; Node* p2;
		char temp;
		p1 = p2 = Character;
		num = 0;
		//读入文件
		while (!in.eof())
		{
			in.read(&temp, 1);
			if (in.eof())
				break;
			num++;
			if (num == 1)
			{
				Character->Code = temp;
				Character->Rate = 0;
				Character->Rate++;
				Character->right = Character->left = Character->parent = nullptr;
				Character->Next = nullptr;
			}
			else
			{
				if (IsANew(temp))
				{
					p2 = new Node();
					p2->Code = temp;
					p2->Rate = 0;
					p2->Rate++;
					p2->left = p2->right = p2->parent = nullptr;
					p1->Next = p2;
					p1 = p1->Next;
					p1->Next = nullptr;
				}
			}
		}
		in.close();
		cout << endl;

		GetRate(num);
		Sort();
		cout << endl << "              读入文件完毕                   " << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
		for (Node* temp = Character; temp != nullptr; temp = temp->Next)
		{
			if (temp->Code == 10 || temp->Code == 13)
			{
				cout << "◇ " << (char)14 << "  ";
				printf("%.4f\t\t\t", temp->Rate);
			}
			else if (temp->Code == 32)
			{
				cout << "◇ " << (char)1 << "  ";
				printf("%.4f\t\t\t", temp->Rate);
			}
			else
			{
				cout << "◇ " << temp->Code << "  ";
				printf("%.4f\t\t\t", temp->Rate);
			}
			
		}
		cout << endl << "p.s 空格字符由" << (char)1 << "代替，换行字符由" << (char)14 << "代替。" << endl;
		cout <<endl<< "--------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	//判断此时读入的字符是否之前还未读入过
	bool IsANew(char temp1)
	{
		Node* temp;
		
		for ( temp = Character; temp != nullptr; temp = temp->Next)
		{
			if ((*temp).Code == temp1)
			{
				temp->Rate++;
				return false;
			}
		}
		return true;
	}
	//得到每个字符出现的频率
	void GetRate(int num)
	{
		for (Node* temp = Character; temp != nullptr; temp = temp->Next)
			temp->Rate = (double)(temp->Rate / num);
	}
	void Sort()//直接选择排序
	{
		Node* temp;
		Node* temp1;
		double Rate;
		char code;
		for (temp = Character; temp->Next != nullptr; temp = temp->Next)
		{
			temp1 = temp;// temp指向当前需要排序的元素
			int i = 1;
			Node* temp2;//temp2指向
			temp2 = temp1->Next;
			while (temp2 != nullptr)
			{
				if (temp2->Rate < temp1->Rate)
					temp1 = temp2;//temp1指向当前循环最小的结点
				temp2 = temp2->Next;
			}
			//将当前循环中最小的结点与此次循环需要排序的元素交换
			code = temp1->Code;
			Rate = temp1->Rate;
			temp1->Code = temp->Code;
			temp1->Rate = temp->Rate;
			temp->Code = code;
			temp->Rate = Rate;
		}
	}
};