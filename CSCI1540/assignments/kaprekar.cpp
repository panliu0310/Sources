/* CSCI1540
 *
 * Assignment: 3
 * Student ID: 1155127464
 * Name: Liu Hoi Pan
 * Email: 1155127464@link.cuhk.edu.hk
 */

#include <iostream>
using namespace std;

int main()
{
	long long s;
	long long n;

	cout << "Enter an integer: ";
	cin >> s;
	while (s <= 0)
	{
		cout << "Input must be +ve! Enter again." << endl << "Enter an integer: ";
		cin >> s;
	}
	cout << "How many Kaprekar numbers? ";
	cin >> n;
	while (n <= 0)
	{
		cout << "Input must be +ve! Enter again." << endl << "How many Kaprekar numbers? ";
		cin >> n;
	}

//Step 1: user input. Ensure s and n are positive.

	while (n > 0)
	{
		long long x = s * s;
		long long digit = 0;
		while (x > 0)//get digit number of x
		{
			x = x / 10;
			digit++;
		}
		x = s * s;//reset value of x
		long long tmp = 1;
		long long time = digit;
		while (time > 0)//check whether s is a kaprekar number
		{
			tmp *= 10;
			time--;
			long long a = x / tmp;//spilt s into two parts
			long long b = x % tmp;//spilt s into two parts
			if ((b != 0) && (s == (a + b)))//Output
			{
				cout << s << "^2 = " << s * s << endl;
				cout << a << " + " << b << " = " << a + b << endl;
				n--;
			}
		}
		s++;
	}
	return 0;
}