#include <iostream>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>

#include "AniPlayer.hpp"

int main(int argc, char** argv) {
    std::string input_path = argc > 1 ? argv[1] : "../videos/hello-world.json";

    try {
        AP::AniPlayer player(input_path);
        sf::RenderWindow window(sf::VideoMode(player.windowSize()), "AniPlayer");
        window.setVerticalSyncEnabled(true);

        sf::Clock clock;
        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
                if (event->is<sf::Event::KeyPressed>() &&
                    event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }

            const sf::Time elapsed = clock.getElapsedTime();
            player.tween(elapsed);
            window.clear(sf::Color(1, 1, 1, 1));
            window.draw(player);
            window.display();
        }
    } catch (const std::exception& ex) {
        std::cerr << "AniPlayer error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
