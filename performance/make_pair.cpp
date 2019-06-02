/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <chrono>
#include <iostream>
#include <utility>

using namespace std;
using namespace std::chrono;

pair<int, int> p;
duration<double> d[3];

int main()
{
	/*
	To speed up C++ STL containers like vector or deque,
	use customized allocator that reduces system call of memory allocation.
	*/

	high_resolution_clock::time_point st, ed;

	/* make_pair */
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p = make_pair(i, i);
	}

	ed = high_resolution_clock::now();
	d[0] = ed - st;

	/* pair */
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p = pair<int, int>(i, i);
	}

	ed = high_resolution_clock::now();
	d[1] = ed - st;

	/* native */
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p.first = i, p.second = i;
	}

	ed = high_resolution_clock::now();
	d[2] = ed - st;

	/* print all results */

	// Optimization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout.precision(2);
	cout.setf(ios::fixed);

	cout << "make_pair:\t\t" << d[0].count() << endl
	     << "pair:\t\t\t" << d[1].count() << endl
	     << "native:\t\t\t" << d[2].count() << endl
	     << endl
	     << "make_pair/native:\t" << d[0].count() / d[2].count() << endl
	     << "pair/native:\t\t" << d[1].count() / d[2].count() << endl;

	return 0;
}
