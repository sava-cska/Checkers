#include "model.h"
#include "./UI/include/draw_smf.hpp"
#include <iostream>
#include <string>

int main()
{
	Game Game_state;

	sf::RenderWindow window;
    window.setFramerateLimit(60);
    window.create(sf::VideoMode(1280, 720), "Chess");

    while (window.isOpen()) {
        sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        std::list<sf::RectangleShape> rendrer_list;

        sf::Event event;

        window.clear();
        draw_background(rendrer_list);
        draw_table(rendrer_list);
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
                if(event.key.code == sf::Mouse::Left) {
                    int count = -1;
                    int count1 = -1;
                    for (auto& elem : rendrer_list) {
                        if ((elem.getPosition() < pos) && (elem.getPosition() + elem.getSize()) > pos) {
                            count = count1;
                        }
                        count1++;
                    }
                    
                    int x = count % 8;
					int y = count / 8;
                }
        }

        for (auto& elem : rendrer_list) {
            window.draw(elem);
        }
        

        window.display();
    }
	
	return 0;
}
