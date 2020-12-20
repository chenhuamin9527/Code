#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Node
{
	char Code;//���ַ�
	double Rate;//���ַ�����Ƶ��
	string coding;//����������
	Node* Next;
	Node* parent;//��ָ��
	Node* left;//��ָ��
	Node* right;//��ָ��
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
		cout << "�������ļ�����";
		cin >> filename;
		in.open(filename);
		while (!in)
		{
			cout << "��ȡ�ļ��������������룺" << endl;
			getline(cin, filename, '\n');
			in.open(filename);
		}
		Character = new Node();
		Node* p1; Node* p2;
		char temp;
		p1 = p2 = Character;
		num = 0;
		//�����ļ�
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
		cout << endl << "              �����ļ����                   " << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
		for (Node* temp = Character; temp != nullptr; temp = temp->Next)
		{
			if (temp->Code == 10 || temp->Code == 13)
			{
				cout << "�� " << (char)14 << "  ";
				printf("%.4f\t\t\t", temp->Rate);
			}
			else if (temp->Code == 32)
			{
				cout << "�� " << (char)1 << "  ";
				printf("%.4f\t\t\t", temp->Rate);
			}
			else
			{
				cout << "�� " << temp->Code << "  ";
				printf("%.4f\t\t\t", temp->Rate);
			}
			
		}
		cout << endl << "p.s �ո��ַ���" << (char)1 << "���棬�����ַ���" << (char)14 << "���档" << endl;
		cout <<endl<< "--------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	//�жϴ�ʱ������ַ��Ƿ�֮ǰ��δ�����
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
	//�õ�ÿ���ַ����ֵ�Ƶ��
	void GetRate(int num)
	{
		for (Node* temp = Character; temp != nullptr; temp = temp->Next)
			temp->Rate = (double)(temp->Rate / num);
	}
	void Sort()//ֱ��ѡ������
	{
		Node* temp;
		Node* temp1;
		double Rate;
		char code;
		for (temp = Character; temp->Next != nullptr; temp = temp->Next)
		{
			temp1 = temp;// tempָ��ǰ��Ҫ�����Ԫ��
			int i = 1;
			Node* temp2;//temp2ָ��
			temp2 = temp1->Next;
			while (temp2 != nullptr)
			{
				if (temp2->Rate < temp1->Rate)
					temp1 = temp2;//temp1ָ��ǰѭ����С�Ľ��
				temp2 = temp2->Next;
			}
			//����ǰѭ������С�Ľ����˴�ѭ����Ҫ�����Ԫ�ؽ���
			code = temp1->Code;
			Rate = temp1->Rate;
			temp1->Code = temp->Code;
			temp1->Rate = temp->Rate;
			temp->Code = code;
			temp->Rate = Rate;
		}
	}
};