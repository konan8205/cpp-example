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

duration<double> t[3];
pair<int, int> p;

int main()
{
	/*
	To speed up C++ STL containers like vector or deque,
	use customized allocator that reduces system call of memory allocation.
	*/

	// make_pair
	auto st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p = make_pair(i, i);
	}

	auto ed = high_resolution_clock::now();
	t[0] = ed - st;

	// pair
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p = pair<int, int>(i, i);
	}

	ed = high_resolution_clock::now();
	t[1] = ed - st;

	// native
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p.first = i, p.second = i;
	}

	ed = high_resolution_clock::now();
	t[2] = ed - st;

	/* print all results */

	// Optimization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout.precision(2);
	cout.setf(ios::fixed);

	cout << "make_pair:\t\t" << t[0].count() << endl
	     << "pair:\t\t\t" << t[1].count() << endl
	     << "native:\t\t\t" << t[2].count() << endl
	     << endl
	     << "make_pair/native:\t" << t[0].count() / t[2].count() << endl
	     << "pair/native:\t\t" << t[1].count() / t[2].count() << endl;

	return 0;
}
