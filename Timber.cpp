#include <SFML/Graphics.hpp>

int main()
{

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    //Background
    sf::Texture bgTex;
    bgTex.loadFromFile("Graphics/background.png");
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTex);
    bgSprite.setPosition(0, 0);
    //Tree
    sf::Texture treeTex;
    treeTex.loadFromFile("Graphics/tree.png");
    sf::Sprite treeSprite;
    treeSprite.setTexture(treeTex);
    treeSprite.setPosition(810, 0);
    //Bee
    sf::Texture beeTex;
    beeTex.loadFromFile("Graphics/bee.png");
    sf::Sprite beeSprite;
    beeSprite.setTexture(beeTex);
    beeSprite.setPosition(0, 800);
    bool isBeeMoving = false;
    bool beeSpeed = 0.0f;
    //Clouds
    sf::Texture CloudTex;
    CloudTex.loadFromFile("Graphics/cloud.png");
    sf::Sprite cloudSprite1;
    sf::Sprite cloudSprite2;
    sf::Sprite cloudSprite3;
    cloudSprite1.setTexture(CloudTex);
    cloudSprite2.setTexture(CloudTex);
    cloudSprite3.setTexture(CloudTex);
    cloudSprite1.setPosition(0, 0);
    cloudSprite2.setPosition(0, 175);
    cloudSprite3.setPosition(0, 350);
    bool isCloud1Moving = false;
    bool isCloud2Moving = false;
    bool isCloud3Moving = false;
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;
    sf::Time deltaTime = clock.restart();
    while (window.isOpen())
    {
        //input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (!isBeeMoving)
        {
            srand(time(NULL));
            beeSpeed = (rand() & 200) + 200;
            float beeHeight = (rand() % 1000) + 500;
            beeSprite.setPosition(2000, beeHeight);
            isBeeMoving = true;
        }
        else
        {
            beeSprite.setPosition(beeSprite.getPosition().x - (beeSpeed * deltaTime.asSeconds()), beeSprite.getPosition().y);
            if (beeSprite.getPosition().x < -100)
            {
                isBeeMoving = false;
            }
        }

        //draw
        window.clear();
        window.draw(bgSprite);
        window.draw(treeSprite);
        window.draw(beeSprite);
        window.draw(cloudSprite1);
        window.draw(cloudSprite2);
        window.draw(cloudSprite3);
        window.display();
    }

    return 0;
}