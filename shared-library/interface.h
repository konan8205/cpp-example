
class IClass {
public:
	int var;
	IClass() : var(6){};
	virtual ~IClass(){};
	virtual int Square(int num) = 0;
};
