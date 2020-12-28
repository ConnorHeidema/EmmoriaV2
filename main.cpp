#include "util/Size.hpp"

#include "core/Application.hpp"
#include "config/ConfigItems.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

int main(int argc, char ** argv)
{
	Application app;
    app.Start() ?
        std::cout << "Successfully exited game." :
        std::cout << "Error occurred while exiting game";
    std::cout << std::endl;
}
