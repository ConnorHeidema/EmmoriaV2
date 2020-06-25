#ifndef __ISYSTEM__
#define __ISYSTEM__

class ISystem
{
public:
	ISystem() {};
	virtual void Update() = 0;
	virtual ~ISystem() {};
};

#endif