#include "util/Size.hpp"

#include "core/Application.hpp"
#include "config/ConfigItems.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

int main() {
	Application app;
    ConfigItems::LoadConfigFile("data/Config/config.ini");
    app.Start() ?
        std::cout << "Successfully exited game." :
        std::cout << "Error occurred while exiting game";
}
