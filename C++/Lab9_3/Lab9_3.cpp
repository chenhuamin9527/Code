// Lab9_3.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
const int Max = 11;

void Insert(int ht[],int x)
{
	int index = x % Max;
	if (ht[index] == 0)
	{
		ht[index] = x;
		cout << "元素" << x << "插入位置为下标" << index << endl;
	}
	else
	{
		while (ht[index] != 0)
		{
			index++;
		}
		ht[index] = x;
		cout << "元素" << x << "插入位置为下标" << index << endl;
	}
}
void Search(int ht[], int x)
{
	int i, j = x % Max;
	i = j;
	int n = 1;
	while (ht[i] != 0&&i<=Max)
	{
		if (ht[i] == x)
		{
			cout << "查找成功！元素" << ht[i] << "的下标为" << i << "共比较" << n << "次";
			return;
		}
		else
		{
			i = (i + 1) % Max;
			n++;
		}
	}
	cout << "元素" << x << "不在散列表中" << endl;
}
int main()
{
	int s[9] = { 47, 7, 29, 11, 16, 92, 22, 8, 3 };
	int ht[Max] = { 0 };
	int temp, i = 0, index = 0, count = 0;
	
	cout << "散列表中的元素为:" << endl;
	for (i = 0; i < 9; i++)
	{
		Insert(ht, s[i]);
	}
	for (i = 0; i < Max; i++)
		cout << ht[i] << "   ";
	cout << endl;
	srand(time(NULL));
	temp = s[rand() % 9];
	cout << "查找元素 " << temp << endl;
	Search(ht, temp);
	return 0;
}
