#include <iostream>
#include <cmath>
using namespace std;

void findpair(const int x[], int m, const int y[], int n, int t, int& a, int& b);

void findpair(const int x[], int m, const int y[], int n, int t, int& a, int& b)
{
	int min = abs(x[0] + y[0]) + abs(t);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int AbsoluteDiff;
			AbsoluteDiff = abs(x[i] - y[j]);
			if (AbsoluteDiff <= min && AbsoluteDiff > t)
			{
				min = AbsoluteDiff;
				a = x[i]; b = y[j];
			}
		}
	}
	cout << a << " " << b;
}

int main()
{
	int x[4] = { -99, 4, 1, 5 };
	int y[5] = { 20, 30, 10, 40, 50 };
	int a = 0, b = 0;
	findpair(x, 4, y, 5, 24, a, b);

	return 0;
}