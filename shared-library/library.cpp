
#include "interface.h"

class Class : public IClass {
private:
	int var;

public:
	Class() : var(0){};
	~Class(){};

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
#define LIB_API __declspec(dllexport)
#else
#define LIB_API
#endif

extern "C" {
extern LIB_API Class *CreateClass() {
	return new Class;
}

extern LIB_API void DestroyClass(Class *ptr) {
	delete ptr;
}
}
