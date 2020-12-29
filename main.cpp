#include "core/Application.hpp"

#include <iostream>

int main(int argc, char ** argv)
{
	Application app;
    app.Start() ?
        std::cout << "Successfully exited game." :
        std::cout << "Error occurred while exiting game";
    std::cout << std::endl;
}
