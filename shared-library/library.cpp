/*
	Shinwoo Park
	natural7530@gmail.com

	CC0 1.0 Universal
*/

#include "interface.h"

class Class : public IClass {
private:
	int var;

public:
	Class() : var(0) {
	}
	virtual ~Class() {
	}

	virtual int GetVar() override {
		return var;
	}

	virtual void SetVar(int arg) override {
		var = arg;
	}

	virtual int Pow(int base, int exp) override {
		int num = 1;
		for (int i = 0; i < exp; ++i) {
			num *= base;
		}
		return num;
	}
};

#ifdef _WIN32
#define DL_EXPORT extern __declspec(dllexport)
#else
#define DL_EXPORT extern
#endif

extern "C" {
DL_EXPORT Class *CreateClass() {
	return new Class;
}

DL_EXPORT void DestroyClass(Class *ptr) {
	delete ptr;
}
}
