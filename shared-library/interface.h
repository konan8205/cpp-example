
class IClass {
protected:
	IClass() {
	}

public:
	virtual ~IClass() {
	}

	virtual int GetVar() = 0;
	virtual void SetVar(int arg) = 0;
	virtual int Pow(int base, int exp) = 0;
};

using PFN_CreateClass = IClass *(*)();
using PFN_DestroyClass = void (*)(IClass *);
