// Lab9_4.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int Max = 10;
void Creat(int r[], int n);
void InsertSort(int r[], int n);
void ShellSort(int r[], int n);

void InsertSort(int r[],int n)
{
	int i, j, temp;
	for (i = 1; i <= Max; i++)
	{
		temp = r[i];
		for (j = i - 1; j >= 0 && temp < r[j]; j--)
		{
			r[j + 1] = r[j];
		}
		r[j + 1] = temp;
	}
}

void ShellSort(int r[], int n)
{
	int d, i, j, temp;
	for (d = Max / 2; d >= 1; d = d / 2)
	{
		for (i = d; i < Max+1; i++)
		{
			temp = r[i];
			for (j = i - d; j >= 0 && temp < r[j]; j = j - d)
			{
				r[j + d] = r[j];
			}
			r[j + d] = temp;
		}
	}
}

int main()
{
	int a[Max + 1] = { 0 }, b[Max + 1] = { 0 };
	int i = 0;
	Creat(a, Max);
	for (i = 1; i <= Max; i++)
		b[i] = a[i];
	cout << "对于无序序列：";
	for (i = 1; i <= Max; i++)
		cout << b[i] << "  ";
	cout << endl;
	InsertSort(b, Max);
	cout << "执行直接插入排序后，元素为：";
	for (i = 1; i <= Max; i++)
		cout << b[i] << "  ";
	cout << endl;
	cout << "对于无序序列：";
	for (i = 1; i <= Max; i++)
		cout << a[i] << "  ";
	cout << endl;
	ShellSort(a, Max);
	cout << "执行希尔排序后，元素为：";
	for (i = 1; i <= Max; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}

void Creat(int r[], int n)
{
	int i = 0;
	srand(time(NULL));
	for (i = 1; i <= n; i++)
		r[i] = 1 + rand() % 100;
}



