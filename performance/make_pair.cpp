/*
    Shinwoo Park
    natural7530@gmail.com

    MIT License
*/

#include <chrono>
#include <iostream>
#include <utility>

using namespace std;
using namespace std::chrono;

duration<double> t, t2, t3;
pair<int, int> p;

int main()
{
	// Optimization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout.precision(2);
	cout.setf(ios::fixed);

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
	t = ed - st;
	cout << "make_pair:\t\t" << t.count() << endl;

	// pair
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p = pair<int, int>(i, i);
	}

	ed = high_resolution_clock::now();
	t2 = ed - st;
	cout << "pair:\t\t\t" << t2.count() << endl;

	// native
	st = high_resolution_clock::now();
	for (int i = 0; i < 1e8; ++i) {
		p.first = i, p.second = i;
	}

	ed = high_resolution_clock::now();
	t3 = ed - st;
	cout << "native:\t\t\t" << t3.count() << endl;

	cout << "make_pair/native:\t" << t.count() / t3.count() << endl;
	cout << "pair/native:\t\t" << t2.count() / t3.count() << endl;

	return 0;
}
