#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int Max = 10;
void Creat(int r[], int n);
void SelectSort(int r[], int n);
void Sift(int r[], int k, int m);
void HeapSort(int r[], int n);

void SelectSort(int r[], int n)
{
	int i, j, index, temp;
	for (i = 0; i < Max - 1; i++)
	{
		index = i;
		for (j = i + 1; j < Max; j++)
		{
			if (r[j] < r[index]) index = j;
		}
		if (index != i)
		{
			temp = r[i];
			r[i] = r[index];
			r[index] = temp;
		}
	}
}

void Sift(int r[], int k, int m)
{
	int i, j, temp;
	i = k; j = 2 * i + 1;
	while (j <= m)
	{
		if (j < m && r[j] < r[j + 1]) j++;
		if (r[i] > r[j])break;
		else
		{
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i = j;
			j = 2 * i + 1;
		}
	}
}

void HeapSort(int r[], int n)
{
	int i, temp;
	for (i = ceil(Max / 2) - 1; i >= 0; i--)
	{
		Sift(r, i, Max - 1);
	}
	for (i = 1; i < Max; i++)
	{
		temp = r[0];
		r[0] = r[Max - i];
		r[Max - i] = temp;
		Sift(r, 0, Max - i - 1);
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
	SelectSort(b, Max);
	cout << "执行简单选择排序后，元素为：";
	for (i = 1; i <= Max; i++)
		cout << b[i] << "  ";
	cout << endl;
	cout << "对于无序序列：";
	for (i = 1; i <= Max; i++)
		cout << a[i] << "  ";
	cout << endl;
	HeapSort(a, Max);
	cout << "执行堆排序后，元素为：";
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




