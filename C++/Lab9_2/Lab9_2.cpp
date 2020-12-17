// Lab9_2.cpp: 定义应用程序的入口点。
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
	a[0] = 0;
	for (int i = 1; i <= Max; i++)
		a[i] = a[i - 1] + rand() % Max;
}

void BinSearch(int x)
{
	int left = 1;
	int right = Max;
	int mid = 0;
	int count = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		count++;
		if (x == a[mid])
		{
			cout << "元素" << x << "在序列中序号是" << mid << "，共比较" << count << "次" << endl;
			return;
		}
		else if (x < a[mid])
		{
			right = mid;
		}
		else if (x > a[mid])
		{
			left = mid;
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
	k = a[1 + rand() % Max];
	BinSearch(k);
	return 0;
}
