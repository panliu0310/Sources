#include <iostream>
using namespace std;

int keepsome(const char x[], const char y[], char z[], int n1, int n2);

int keepsome(const char x[], const char y[], char z[], int n1, int n2)
{
	int ReturnValue = 0;
	for (int i = 0; i < n1; i++)
	{
		int PutIntoZ = 0;
		for (int j = 0; j < n2; j++)
		{
			if (x[i] != y[j])
			{
				PutIntoZ++;
			}
		}
		if (PutIntoZ == n2)
		{
			ReturnValue++;
			z[ReturnValue - 1] = x[i];
		}
	}
	return ReturnValue;
}

int main()
{
	const char x[9] = { 'I', 'l', 'o', 'v', 'e', 'C', 'S', 'C', 'I' };
	const char y[3] = { 'e', 'I', 'C' };
	int n1 = 9, n2 = 3;
	char z[9] = { 'I', 'l', 'o', 'v', 'e', 'C', 'S', 'C', 'I' };
	cout << z[0] << z[1] << z[2] << z[3] << " " << keepsome(x, y, z, n1, n2);
	return 0;
}