#include"Scanner.h"
#include<queue>
#include<vector>
typedef string filename;
class HuffmanCoding
{
public:
	Scanner scanner;//将源文件读入 并整理其中字符
	Node* BinaryTree;//根节点
	ofstream out;
	ifstream in;
	filename source;//存放原文档名字
	filename objecthuf;//存放压缩后的文档名字
	filename objectbin;//解压后的文件的名字
	int CharLength; //
	int HufLength; //压缩后字符的长度
	int zero; //最后不足八位的编码需要补齐的位数
	vector<Node*> position; //中序遍历后的树 用来返回指示该输出多少空格
	vector<Node*>newline; //保存能够判断是否换行的结点
	//构造函数
	HuffmanCoding():HufLength(0)
	{
		Function();
	}
	//主功能列表
	void Function()
	{
		int Select;
		char x = (char)3;
		char xx = (char)13;
		cout << "\t\t\t" << x << "欢迎使用JLU文件压缩软件" << x << endl;
		cout << "\t\t◎请选择以下操作：" << endl;
		cout << xx << "\t① 选择打开文件并对其进行解压；" << endl;
		cout << xx << "\t② 选择压缩文件并译码成源文件；" << endl;
		cin >> Select;
		switch (Select)
		{
		case 1:
			ToHufFile();
			break;
		case 2:
			ToTxtFile();
			break;
		default:
			break;
		}
	}
	//源文件转换成压缩文档的过程
	void ToHufFile()
	{
		Preparation();
		char x = (char)1;
		char xx = (char)2;
		cout << "  " << x << " " << xx << " " << x << " " << xx << " "<< "   I' m coding....." << endl;
		cout << endl << endl;;
		//中间用来存放哈夫曼编码的两个二进制文件
		filename binary = "binary.txt";
		filename binary2 = "binary2.txt";
		char temp;
		//打开文件
		in.open(source, ios::binary);
		out.open(binary, ios::binary);
		//读取源文件的每个字符 对应转换成二进制
		while (!in.eof())
		{
			string s;
			in.read(&temp, 1);
			if (in.eof())
				break;
			//找到每个字符对应的哈夫曼编码
			CharToHufCode(temp, BinaryTree, s);
			out << s;
		}
		//关闭文件
		out.close();
		in.close();
		// 以上完成了从源文件到二位制文件的转换
		//以下完成从二进制到压缩文件的转换
		in.open(binary, ios::binary);
		out.open(objecthuf, ios::binary);
		int num = 0;
		string stemp;
		while (!in.eof())
		{

			in.read(&temp, 1);
			if (in.eof())
				break;
			num++;
			stemp = stemp + temp;
			//将每八位二进制转换成一个char字符
			if (num % 8 == 0)
			{
				HufLength++;
				char c;
				int m;
				BinaryToChar(stemp, c);
				m = (int)c;
				out << c;
				stemp = "";
			}
		}
		HufLength++;
		//将最后不足八位的剩余编码凑齐八位
		zero = 8 - stemp.size();
		char c;
		int m;
		for (int i = 0; i < zero; i++)
			stemp.push_back('0');
		BinaryToChar(stemp, c);
		m = (int)c;
		out << c;
		//关闭文件
		out.close();
		in.close();
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "                            文件压缩完成   ●ω●" << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		getchar();
		//以上完成了从二进制到char字符转换
		ShowSelection();
	}
	void ToTxtFile()
	{
		filename binary2 = "binary2.txt";
		cout << "请输入需要解压的文件名：";
		cin>>objecthuf;
		cout << endl;
		cout << "请输入解压成的文件名：";
		cin >> objectbin;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "                              正在解压。。。。。。" << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		//打开文件
		in.open(objecthuf, ios::binary);
		out.open(binary2, ios::binary);
		char temp;
		int num1 = 0;
		while (!in.eof())
		{
			string s;
			in.read(&temp, 1);
			if (in.eof())
				break;
			num1++;
			//压缩文件中的最后一个字符做特殊处理
			if (num1 == HufLength)
			{
				string ss;
				CharToBinary(temp, ss);
				for (int i = 0; i < 8 - zero; i++)
					s.push_back(ss[i]);
				out << s;
				break;
			}
			CharToBinary(temp, s);
			out << s;
		}
		//关闭文件
		out.close();
		in.close();
		//将二进制文件转换成源文件 打开文件
		in.open("binary.txt", ios::binary); //ios::binary  保证读取到文件末尾
		out.open(objectbin);
		string s;
		char c;//存放当前二进制编码对应的字符
		int flag = 0;//判断当前的二进制码是否能找到对应的字符
		while (!in.eof())
		{
			in.read(&temp, 1);
			if (in.eof())
				break;
			s = s + temp;
			//判断目前读入的二进制编码（哈夫曼编码）是否找到对应的字符
			FindCharByBinary(c, BinaryTree, s, flag);
			if (flag == 1)
			{
				s = "";
				out << c;
			}
		}
		//关闭文件
		in.close();
		out.close();
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "              解压缩文件完成。是否查看解压完的文件。" << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		char cc;
		cin >> cc;
		if (cc == 'y' || cc == 'Y')
		{
			cout << "您当前查看的文件名为：" << objectbin << "  该文件字数为：" << CharLength << endl;
			in.open(objectbin);
			char temp;
			while (!in.eof())
			{
				in.read(&temp, 1);
				cout << temp;
				if (in.eof())
					break;
			}
			in.close();
			Function();
		}
		else
			Function();
	}
	//初始化部分参数
	void Initialization()
	{
		//扫描要读入的文件 读取字符及计算频率
		scanner.Run();
		Copy();
		source = scanner.filename;
		CharLength = scanner.num;
	}
	//压缩文件的前期工作 1.初始化参数  2。调用创建哈夫曼函数 3.得到每个字符的哈夫曼编码
	void Preparation()
	{
		Initialization();
		BinaryTree = CreateHuffmanTree();
		BinaryTree->coding = "";
		Node* leaf;
		leaf = BinaryTree;
		GetCode(leaf);
		Node*temp = BinaryTree;
		SavePositionInTree(temp);
		NewLine(temp);
		cout << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << endl<<"     \t请输入压缩成的文件名：";
		cin >> objecthuf;
		cout << "-------------------------------------------------------------------------" << endl;

	}
	
	//创建哈夫曼树
	Node* CreateHuffmanTree()
	{
		Node* p = nullptr;
		while (BinaryTree != nullptr)
		{
			//当节点的集合中只剩下两个节点的时候
			if (BinaryTree->Next->Next == nullptr)
			{
				p = new Node();
				p->right = BinaryTree;
				BinaryTree->coding = '1';
				BinaryTree->parent = p;
				BinaryTree = BinaryTree->Next;
				p->left = BinaryTree;
				BinaryTree->coding = '0';
				BinaryTree->parent = p;
				p->Rate = p->left->Rate + p->right->Rate;
				p->parent = nullptr;
				p->Code = (char)3;
				BinaryTree = p;
				break;

			}
			//每次选择按照频率排好的链表中的前两个最小的结点 组成新的结点 并把新节点插入到链表中的合适位置
			p = new Node();
			p->right = BinaryTree;
			BinaryTree->coding = '1';
			BinaryTree->parent = p;
			BinaryTree = BinaryTree->Next;
			p->left = BinaryTree;
			BinaryTree->coding = '0';
			BinaryTree->parent = p;
			BinaryTree = BinaryTree->Next;
			p->Rate = p->left->Rate + p->right->Rate;
			p->Code = (char)3;
			//将新节点插入到链表的合适位置
			InsertNewNode(p);
		}
		return p;
	}
	//将从文件中扫描过来的链表复制过来 创建新的列表
	void Copy()
	{
		Node* p1;
		Node* p2;
		Node* temp;
		BinaryTree = new Node();
		BinaryTree->Code = scanner.Character->Code;
		BinaryTree->Rate = scanner.Character->Rate;
		BinaryTree->left = BinaryTree->right =BinaryTree->parent= nullptr;
		p1 = p2 = BinaryTree;
		for ( temp = scanner.Character; temp != nullptr; temp = temp->Next)
		{
			if (temp == scanner.Character)
			{
				BinaryTree = scanner.Character;

			}
			p1 = new Node();
			p1->Code = temp->Code;
			p1->Rate = temp->Rate;
			p1->left = p1->right =p1->parent= nullptr;
			p2->Next = p1;
			p2 = p2->Next;
		}
		p1->Next = nullptr;
	}
	//将新节点插入到链表的合适位置
	void InsertNewNode(Node* p)
	{

		Node* temp = BinaryTree;
		Node* front = temp;//指向要插入的位置的前一个指针
		temp = BinaryTree->Next;
		//当新节点要插入到链表头时
		if (p->Rate < front->Rate || p->Rate == front->Rate)//小于第一个元素
		{
			p->Next = BinaryTree;
			BinaryTree = p;
		}
		else
		{
			for (; temp != nullptr; temp = temp->Next, front = front->Next)
			{
				if (p->Rate < temp->Rate || p->Rate == temp->Rate)
				{
					front->Next = p;
					p->Next = temp;
					break;
				}
			}
			if (temp == nullptr)
			{
				front->Next = p;
				p->Next = nullptr;
			}
		}
	}
	//生成每个节点的哈夫曼编码
	void GetCode(Node* leaf)
	{
		if (leaf != nullptr)
		{
			if (leaf != BinaryTree)
				leaf->coding = leaf->parent->coding + leaf->coding;
			if (leaf->right == nullptr&&leaf->left == nullptr)
				return;
			GetCode(leaf->left);
			GetCode(leaf->right);
		}
	}
	void CharToHufCode(char c, Node* leaf, string& s)
	{
		if (leaf != nullptr)
		{
			if (leaf->Code == c)
			{
				s = leaf->coding;
				return;
			}
			CharToHufCode(c, leaf->left, s);
			CharToHufCode(c, leaf->right, s);
		}
	}
	//判断目前读入的二进制编码（哈夫曼编码）是否找到对应的字符
	void FindCharByBinary(char&c, Node* leaf, string s,int& flag)
	{
		if (leaf != nullptr)
		{
			//若找到对应字符需满足的条件
			if (s.empty())
			{
				if ((leaf->left == nullptr) && (leaf->right == nullptr))
				{
					c = leaf->Code;
					flag= 1;
				}
				else
					flag= 0;	
			}
			//只要字符串还没有空就继续找
			else
			{
				if (s[0] == '0')
				{
					popfront(s);
					FindCharByBinary(c, leaf->left, s, flag);
				}
				else
				{
					popfront(s);
					FindCharByBinary(c, leaf->right, s, flag);
				}
			}
		}
		else
			flag= 0;
	}
	//弹出字符串的第一个元素
	void popfront(string&s)
	{
		for (int i = 1; i < s.size(); i++)
			s[i - 1] = s[i];
		s.pop_back();
	}
	//将八位二进制转换成ASCII编码
	void BinaryToChar(string s, char& c)
	{
		c = 0;
		int m = 1;
		for (int i = 7; i >= 0; i--)
		{
			c = (char)(c + (s[i] - '0')*m);
			m = m * 2;
		}
	}
	//将ASCII字符转换成二进制
	void CharToBinary(char c, string &s)
	{
		unsigned char k = 0x80;
		s = "";
		for (int i = 0; i < 8; i++, k >>= 1)
		{
			if (c & k)
				s = s + '1';
			else
				s=s+'0';
		}
	}
	//计算转化比率
	void CalculateRate()
	{
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "               源文件为" << CharLength << "byte"<< endl ;
		cout << "               压缩后的文件大小为" << HufLength << "byte." << endl;
		cout << "               压缩比率为：" << (double)HufLength / CharLength << endl;
		cout << "---------------------------------------------------------------------------" << endl;
	}
	//显示压缩完后的选择
	void ShowSelection()
	{
		int Select=0;
		char x = (char)5;
		cout << endl;
		cout << "\t\t\t"<<x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << endl;
		cout <<"\t\t\t请选择相关查阅功能：" << endl;
		cout <<"\t\t\t◇① 查看哈夫曼树；" << endl;
		cout << "\t\t\t◇② 查看每个字符的编码；" << endl;
		cout << "\t\t\t◇③ 查看源文档；" << endl;
		cout << "\t\t\t◇④ 查看转换后的文档；" << endl;
		cout << "\t\t\t◇⑤ 查看转换比率；" << endl;
		cout << "\t\t\t◇⑥ 返回主界面；" << endl;
		cout << "\t\t\t" << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << endl;
		while (Select<6)
		{
			cin >> Select;
			switch (Select)
			{
			case 1:
				ShowTree(BinaryTree);
				break;
			case 2:
				ShowCode(BinaryTree);
				break;
			case 3:
				ShowSource();
				break;
			case 4:
				ShowObject();
				break;
			case 5:
				CalculateRate();
				break;
			case 6:
				Function();
				break;
			default:
				Function();
				break;
			}
			getchar();
			cout << endl;
			cout << "\t\t\t" << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << endl;
			cout << "\t\t\t请选择相关查阅功能：" << endl;
			cout << "\t\t\t◇① 查看哈夫曼树；" << endl;
			cout << "\t\t\t◇② 查看每个字符的编码；" << endl;
			cout << "\t\t\t◇③ 查看源文档；" << endl;
			cout << "\t\t\t◇④ 查看转换后的文档；" << endl;
			cout << "\t\t\t◇⑤ 查看转换比率；" << endl;
			cout << "\t\t\t◇⑥ 返回主界面；" << endl;
			cout << "\t\t\t" << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << x << " " << endl;
		}//while
	}
	//显示二叉树
	void ShowTree(Node*leaf)
	{

		bool flag = true;//是否重新开始输出新的一行
		queue<int> line;//保存输出横线时需要的参数
		int space;//存放需要输出的空格数
		int lastspace;//存放上次输出的空格数
		queue<Node*> tree; //用于层次遍历输出二叉树
		if (leaf != nullptr)
			tree.push(leaf);
		cout << endl;
		cout << "------------------------------------------------------------BinaryTree------------------------------------------------------------" << endl;
		while (!tree.empty())
		{
			Node* temp = tree.front();
			if (flag)
			{
				space = ReturnThePosition(temp);
				if (temp->left != nullptr || temp->right != nullptr)
					line.push(space);
				lastspace = space;
				flag = false;
			}
			else
			{
				space = ReturnThePosition(temp);
				int i;
				i = space;
				space = space - lastspace;
				if (temp->left != nullptr || temp->right != nullptr)
					line.push(space);
				lastspace = i;
			}
			//输出空格
			while (space >1)
			{
				cout << " ";
				space--;
			}
			//输出节点
			if (temp->Code == 10 || temp->Code == 13)
				cout << (char)14;
			else if (temp->Code == 32)
				cout << (char)1;
			else
				cout << temp->Code;
			//弹出当前节点
			tree.pop();
			//压入当前结点的左右结点
			if (temp->left != nullptr)
			{
				tree.push(temp->left);
				line.push(ReturnThePosition(temp->left));
			}
			if (temp->right != nullptr)
			{
				tree.push(temp->right);
				line.push(ReturnThePosition(temp->right));
			}
			//如果是新的一行的话 换行并且输出辅助表示的横线
			if (IsNewLine(temp))
			{
				cout << endl;
				flag = true;
				PrintLine(line);
				  while (!line.empty())
				line.pop();
				cout << endl;
			}
		}
		cout <<endl<< "------------------------------------------------------------BinaryTree------------------------------------------------------------" << endl;
	}
	//输出辅助表示的横线
	void PrintLine(queue<int> line)
	{
		int i = 0;
		int space = 0;
		int lastspace = 0;
		int left, right;
		int hengxian;
		while (!line.empty())
		{
			line.pop();
			left = line.front();
			line.pop();
			right = line.front();
			line.pop();
			hengxian = right - left - 1;
			space = left;
			space = space - lastspace;
			lastspace = right;
			while (space > 0)
			{
				cout << " ";
				space--;
			}
			while (hengxian > 0)
			{
				cout << "-";
				hengxian--;
			}
			cout << " ";
		}
		cout << endl;
	}
	//保存中序遍历下的树 为了辅助输出空格
	void SavePositionInTree(Node* leaf)
	{
		if (leaf != nullptr)
		{
			SavePositionInTree(leaf->left);
			position.push_back(leaf);
			SavePositionInTree(leaf->right);
		}
		else return;
	}
	//保存辅助判断是否该还行的结点
	void NewLine(Node*leaf)
	{
		if (leaf != nullptr)
		{
			newline.push_back(leaf);
			NewLine(leaf->right);
			if (leaf->right == nullptr)
			{
				if (leaf->parent->left->right != nullptr)
				{
					newline.push_back(leaf->parent->left->right);
					NewLine(leaf->parent->left->right);
				}

			}
		}
	}
	//判断当前节点是否是该换行的结点
	bool IsNewLine(Node*leaf)
	{
		bool flag = false;
		for (Node* temp : newline)
		{
			if (temp == leaf)
			{
				flag = true;
				return flag;
			}
		}
		return flag;
	}
	//返回的值为输出当前节点前应该输出多少空格
	int ReturnThePosition(Node*leaf)
	{
		int i = 0;
		for (auto temp : position)
		{
			i++;
			if (temp == leaf)
				return i;
		}
	}
	void ShowCode(Node * leaf)
	{
		if (leaf != nullptr)
		{
			if (leaf->right == nullptr&&leaf->left == nullptr)
			{
				if (leaf->Code == 10 || leaf->Code == 13)
					cout << "      "<<(char)14<<"  换行" " ---->" << leaf->coding <<endl;
				else if (leaf->Code == 32)
					cout << "      " << (char)1<<"  空格" << " ----> " << leaf->coding << endl;
				else
					cout << "      "<<leaf->Code << " ----> " << leaf->coding << endl;
				return;
			}
			ShowCode(leaf->left);
			ShowCode(leaf->right);
		}
	}
	void ShowSource()
	{
		cout << endl<<"----------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t您当前查看的文件名为：" << source << "\t  该文件字数为：" << CharLength << endl;
		in.open(source);
		char temp;
		while (!in.eof())
		{
			in.read(&temp, 1);
			if (in.eof())
				break;
			cout << temp;
		}
		in.close();
		cout << endl<<"----------------------------------------------------------------------------------------" << endl;
	}
	void ShowObject()
	{
		cout <<endl<< "-----------------------------------------------------------------------------------------" << endl;
		cout << "您当前查看的文件名为：" << objecthuf << "  该文件字数为：" << HufLength << endl;
		in.open(objecthuf, ios::binary);
		char temp;
		while (!in.eof())
		{
			in.read(&temp, 1);
			if (in.eof())
				break;
			cout << temp;
		}
		in.close();
		cout <<endl<< "--------------------------------------------------------------------------------------------" << endl;
	}

};