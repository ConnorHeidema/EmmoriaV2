#ifndef __IADAPTER__
#define __IADAPTER__

#include <string>
#include <fstream>
#include <sstream>

/**
 * Purpose:
 * This is used to convert a stream of data before it is loaded so the user doesn't need to input an exact thing initially into the loading sys
 */
class IAdapter
{
public:
	virtual std::istringstream TransformData(std::string inData) = 0;
	virtual ~IAdapter() {};
};

#endif
