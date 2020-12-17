#include<iostream>         //引入输入输出流
#include <time.h>
#include <stdlib.h>

using namespace std;
const int Max = 11;

int main()
{
	int s[9]={47, 7, 29, 11, 16, 92, 22, 8, 3};
	int ht[Max] = {0};
	int temp, i = 0, index = 0, count = 0;

	cout<<"散列表中的元素为:"<<endl;
	for(i = 0; i < Max; i++)
		cout<<ht[i]<<"   ";
	cout<<endl;
	srand(time(NULL));
	temp = s[rand() % 9];
	cout<<"查找元素 "<<temp<<endl;

	return 0;
}
