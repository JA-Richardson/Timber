#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::Texture bgTex;
    bgTex.loadFromFile("Graphics/background.png");
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTex);
    bgSprite.setPosition(0, 0);

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        window.clear();
        window.draw(bgSprite);
        window.display();
    }

    return 0;
}