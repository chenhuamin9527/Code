// 202009-2.cpp: 定义应用程序的入口点。
//

#include "202009-2.h"
#include <bits/stdc++.h>

using namespace std;

struct Point
{
	int location_x = 0;
	int location_y = 0;
};
int n, k, t, xl, yd, xr, yu; 
bool judge(int x, int y)
{
	if (x >= xl && x <= xr && y >= yd && y <= yu)
		return true;
	return false;
}

int main()
{
	cin >> n >> k >> t >> xl >> yd >> xr >> yu;
	Point data[30][1005];
	int stayPerson = 0;
	int passPerson = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < t; j++)
		{
			cin >> data[i][j].location_x >> data[i][j].location_y;
		}
	}
	for (int i = 0; i < n; i++)
	{
		bool pass = false;
		int max_stay = 0;
		for (int j = 0; j < t; j++)
		{
			if (judge(data[i][j].location_x, data[i][j].location_y))
			{
				pass = true;
				max_stay++;
			}
			else
				max_stay = 0;
			if (max_stay >= k)
			{
				stayPerson++;
				break;
			}

		}
		if (pass) passPerson++;
	}

	cout << passPerson << endl;
	cout << stayPerson << endl;
	return 0;
}
