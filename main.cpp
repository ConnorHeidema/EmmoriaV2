#include "util/Size.hpp"

#include "core/Application.hpp"

#include <SFML/Graphics.hpp>


#include <iostream>

int main() {
	Application app;

    app.Start() ?
        std::cout << "Successfully exited game." :
        std::cout << "Error occurred while exiting game";
}