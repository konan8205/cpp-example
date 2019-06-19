
#include "interface.h"

#ifdef _WIN32
#define LIB_API __declspec(dllexport)
#else
#define LIB_API
#endif

class Class : public IClass {
public:
	int Pow(int base, int exp) override {
		int num = 1;
		for (int i = 0; i < exp; ++i) {
			num *= base;
		}
		return num;
	};
	~Class(){};
};

extern "C" {
extern LIB_API Class *CreateClass() {
	return new Class;
}

extern LIB_API void DestroyClass(Class *ptr) {
	delete ptr;
}
}
