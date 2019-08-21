/*
	Shinwoo Park
	natural7530@gmail.com

	CC0 1.0 Universal
*/

#include <chrono>
#include <iostream>

// Not currently used
#ifdef _WIN32
#define NO_INLINE __declspec(noinline)
#else
#define NO_INLINE __attribute__((noinline))
#endif

class IClass {
public:
	virtual ~IClass(){};
	virtual int GetVar() = 0;
	virtual void SetVar(int arg) = 0;
};

class Class : public IClass {
public:
	int var;

	Class() : var(0) {
	}
	virtual ~Class(){};
	virtual int GetVar() {
		return var;
	}
	virtual void SetVar(int arg) {
		var = arg;
	}
};

class Class2 {
public:
	int var;

	Class2() : var(0) {
	}
	int GetVar() {
		return var;
	}
	void SetVar(int arg) {
		var = arg;
	}
};

int main() {
	/*
	Despite virtual function can be optimized by compiler,
	it is 1.1X slower than non-virtual function.
	*/
	using high_resolution_clock = std::chrono::high_resolution_clock;

	high_resolution_clock::time_point st, ed;
	std::chrono::duration<double> res[2];

	/* Initialize the objects */
	int num = 0;
	IClass *object = new Class();
	Class2 *object2 = new Class2();

	/* virtual class */
	{
		st = high_resolution_clock::now();
		for (int i = 0; i < 1e8; ++i) {
			object->SetVar(i);
			num = object->GetVar();
		}
		ed = high_resolution_clock::now();
		res[0] = ed - st;
	}

	/* non-virtual class */
	{
		st = high_resolution_clock::now();
		for (int i = 0; i < 1e8; ++i) {
			object2->SetVar(i);
			num = object2->GetVar();
		}
		ed = high_resolution_clock::now();
		res[1] = ed - st;
	}

	delete object;
	delete object2;

	/* print all results */

	// Optimization
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cout.precision(4);
	std::cout.setf(std::ios::fixed);

	std::cout << "virtual:\t\t" << res[0].count() << std::endl
			  << "non-virtual:\t\t" << res[1].count() << std::endl;
	std::cout << "non-virtual/virtual:\t" << res[1].count() / res[0].count()
			  << std::endl;

	return 0;
}
