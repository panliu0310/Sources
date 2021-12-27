/* CSCI1540
 *
 * Assignment: 2
 * Student ID: 1155127464
 * Name: Liu Hoi Pan
 * Email: 1155127464@link.cuhk.edu.hk
 */

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	cout << "Enter a year: ";

	int a, b, c, j, n;
	int y, m = 1, d = 21; //y stands for year, m stands for month, d stands for day 
	double k;

	//line 17-19: define variables

	cin >> y;

	a = int((14 - m) / 12);
	b = m + 12 * a - 3;
	c = y + 4800 - a;
	j = d + int((153 * b + 2) / 5) + 365 * c + int(c / 4) - int(c / 100) + int(c / 400) - 32045;
	k = (j - 2451551.0923611) / 29.530587981;
	n = int(29.530587981 * (ceil(k) - k));

	//line 25-30: algorithm from assignment 2

	d = d + n;

	if (d > 31)
	{
		d = d - 31;
		m++;
	}

	cout << "LNY of " << y << " is around: ";

	int mmm = ((j + n) % 7) + 1;//mmm stands for week, from Monday to Sunday
	if (mmm == 1) { cout << "Mon, "; }
	if (mmm == 2) { cout << "Tue, "; }
	if (mmm == 3) { cout << "Wed, "; }
	if (mmm == 4) { cout << "Thu, "; }
	if (mmm == 5) { cout << "Fri, "; }
	if (mmm == 6) { cout << "Sat, "; }
	if (mmm == 7) { cout << "Sun, "; }

	cout << d;

	if (m == 1) { cout << " Jan "; }
	else { cout << " Feb "; }

	cout << y;

	return 0;
}