// Lab9_1.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <stdlib.h>  
#include <time.h>

using namespace std;
const int Max = 10;

int a[Max + 1] = { 0 };
void Creat();

void Creat()
{
	srand(time(NULL));
	for (int i = 1; i <= Max; i++)
		a[i] = 1 + rand() % Max;
}

void SeqSearch(int x)
{
	int count = 0;
	for (int i = 1; i <= Max; i++)
	{
		count++;
		if (x == a[i])
		{
			cout << "元素" << x << "在序列中的序号是" << i << "，共比较" << count << "次" << endl;
			return;
		}
	}
	cout << "元素" << x << "不存在序列中" << endl;
}

int main()
{
	int k;
	Creat();
	for (int i = 1; i <= Max; i++)
		cout << a[i] << "  ";
	cout << endl;
	k = 1 + rand() % Max;
	SeqSearch(k);
	return 0;
}