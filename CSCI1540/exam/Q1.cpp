#include <iostream>
using namespace std;

void goldbach(int lo, int hi);

void goldbach(int lo, int hi)
{
	int x = lo;
	if (x % 2 == 1)x++;// to ensure x starts from even number

	for (int i = x; i <= hi; i += 2)
	{
		if (hi < 4 || lo > hi)break;// if high is smaller than 4 or low is larger than high, the function shall print nothing
		for (int y = 2; y < i - 1; y++)
		{
			int z = i - y;
			// if y and z are prime, then goldbach conjecture is true in this case
			bool yIsPrime = true, zIsPrime = true;

			for (int j = 2; j < y; j++) 
			{
				if (y % j == 0)yIsPrime = false;// if y is divisible for some integer j (1 < j < y), then y is not prime number
			}
			if (y == 2)yIsPrime = true;// 2 is a prime number

			for (int k = 2; k < z; k++)
			{
				if (z % k == 0)zIsPrime = false;// if 
			}
			if (z == 2)zIsPrime = true;// 2 is a prime number

			if (yIsPrime == true && zIsPrime == true)
			{
				cout << i << "=" << y << "+" << z << endl;
				break;
			}
		}
	}
}

int main()
{
	goldbach(3, 999);
	return 0;
}