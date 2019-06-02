/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <chrono>
#include <iostream>
#include <string>

#include <cstdio>

using namespace std;
using namespace std::chrono;

string str = "abcdefghijklnmopqrstuvwxyz";
duration<double> t[4];

int main()
{
	/*
	If you set ios_base::sync_with_stdio(false),
	std::cout is fast enough.
	*/

	high_resolution_clock::time_point st, ed;

	// cout
	cout.flush();
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e4; ++i) {
		cout << str << endl;
	}

	ed = high_resolution_clock::now();
	t[0] = ed - st;

	// cout optimized
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout.flush();
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e4; ++i) {
		cout << str << endl;
	}

	ed = high_resolution_clock::now();
	t[1] = ed - st;

	// prepare for c functions
	ios_base::sync_with_stdio(true);

	// printf
	fflush(stdout);
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e4; ++i) {
		printf("%s\n", str.data());
	}

	ed = high_resolution_clock::now();
	t[2] = ed - st;

	// puts
	fflush(stdout);
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e4; ++i) {
		puts(str.data());
	}

	ed = high_resolution_clock::now();
	t[3] = ed - st;

	/* print all results */

	// Optimization
	ios_base::sync_with_stdio(true);

#if _WIN32
	system("cls");
#else
	system("clear; clear");
#endif

	cout.precision(2);
	cout.setf(ios::fixed);

	cout.flush();

	cout << endl
	     << "cout:\t\t\t" << t[0].count() << endl
	     << "cout optimized:\t\t" << t[1].count() << endl
	     << "printf:\t\t\t" << t[2].count() << endl
	     << "puts:\t\t\t" << t[3].count() << endl
	     << endl
	     << "cout/printf:\t\t" << t[0].count() / t[2].count() << endl
	     << "cout optimized/printf:\t" << t[1].count() / t[2].count() << endl
	     << "puts/printf:\t\t" << t[2].count() / t[3].count() << endl;

	return 0;
}
