// 202009-1.cpp: 定义应用程序的入口点。
//

#include "202009-1.h"
#include <bits/stdc++.h>

using namespace std;
struct Point
{
	int location_x = 0;
	int location_y = 0;
};

int main()
{
	int n, x, y;
	Point data[205];
	int dis[205] = { 0 };
	memset(dis, 10000, sizeof(dis));
	int shortest_index[10] = { 0 };
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++)
	{
		cin >> data[i].location_x >> data[i].location_y;
	}
	for (int i = 1; i <= n; i++)
	{
		dis[i] = (x - data[i].location_x) * (x - data[i].location_x) + (y - data[i].location_y) * (y - data[i].location_y);
	}
	for (int i = 1; i <= 3; i++)
	{
		int temp = 100000;
		int temp_index = 0;
		for (int j = 1; j <= n; j++)
		{
			if (dis[j] < temp)
			{
				temp = dis[j];
				temp_index = j;
			}
		}
		shortest_index[i] = temp_index;
		dis[temp_index] = 100000;
	}
	for (int i = 1; i <= 3; i++)
	{
		cout << shortest_index[i] << endl;
	}
	return 0;
}
