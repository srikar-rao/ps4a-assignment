#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    std::string input_path;
    if (argc > 1) {
        input_path = argv[1];
    }

    if (!input_path.empty()) {
        std::ifstream input(input_path);
        if (input) {
            try {
                nlohmann::json data = nlohmann::json::parse(input);
                const unsigned int width = data.value("width", 800u);
                const unsigned int height = data.value("height", 600u);
                std::cout << "Loaded scene metadata: " << width << "x" << height << '\n';
            } catch (const std::exception& ex) {
                std::cerr << "JSON parse error: " << ex.what() << '\n';
            }
        } else {
            std::cerr << "Could not open JSON file: " << input_path << '\n';
        }
    }

    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "AniPlayer Boot");
    std::cout << "Window opened: " << window.isOpen() << '\n';
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape background(sf::Vector2f(800.f, 600.f));
    background.setFillColor(sf::Color(1, 1, 1));

    sf::RectangleShape panel(sf::Vector2f(220.f, 80.f));
    panel.setFillColor(sf::Color(40, 40, 40));
    panel.setPosition({290.f, 260.f});

    sf::Font font;
    const bool font_loaded = font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
    sf::Text title(font, "AniPlayer", 28);
    title.setFillColor(sf::Color::White);
    title.setPosition({320.f, 280.f});
    if (!font_loaded) {
        std::cerr << "Warning: Arial font unavailable; continuing with default text rendering.\n";
    }

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

        window.clear(sf::Color(1, 1, 1));
        window.draw(background);
        window.draw(panel);
        window.draw(title);
        window.display();
    }

    return 0;
}
