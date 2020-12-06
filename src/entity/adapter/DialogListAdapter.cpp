#include "entity/adapter/DialogListAdapter.hpp"

#include <iostream>

std::istringstream DialogListAdapter::TransformData(std::string data)
{
	// latest work here
	if (data.find("BottomDialog") == 0)
	{
		auto dataStream =  std::istringstream(data);
		std::string currentToken;
		while(dataStream >> currentToken)
		{
			std::cout << currentToken << std::endl;
		}
	}
	return std::istringstream(data);;
}
