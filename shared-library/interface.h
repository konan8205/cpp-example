
class IClass {
public:
	int var;
	IClass() : var(2){};
	virtual ~IClass(){};
	virtual int Pow(int base, int exp) = 0;
};
