#include <SFML/Graphics.hpp>

int main() {
    sf::Window window;
    window.create(sf::VideoMode(1280, 720), "Chess");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            sf::RectangleShape block;
            block.setSize(sf::Vector2f(75, 75));
            block.setPosition(i*75, j*75);
            block.setFillColor(sf::Color(0 - (i + j % 2)));
            //window.draw(block);
        }
            
    }

    //char a = getchar();
    return 0;
}