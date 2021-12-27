#include <iostream>
using namespace std;

int distinct(int* p, int n);

int distinct(int* p, int n)
{
	if (n == 1)return 1;

	int frequency = 1;
	
	for (int i = 1; i < n; i++)
	{
		bool Repeated = false;
		for (int j = 0; j < i; j++)
		{
			if (p[i] == p[j])Repeated = true;
		}
		if (Repeated == false)frequency++;
	}

	return frequency;
}

int main()
{
	int x[5] = { 1, 6, 4, 6, 1 };
	cout << distinct(x, 5);
	return 0;
}