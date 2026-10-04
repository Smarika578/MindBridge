#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "MindBridge GUI Test"
    );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(235, 245, 240));
        window.display();
    }

    return 0;
}
