#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include "test.h"

void branchUpdate(int seed);

const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];

enum class side {LEFT, RIGHT, NONE};
side branchPoisition[NUM_BRANCHES];

void branchUpdate(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; --j)
    {
        branchPoisition[j] = branchPoisition[j - 1];
    }
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r)
    {
    case 0:
        branchPoisition[0] = side::LEFT;
        break;
    case 1:
        branchPoisition[0] = side::RIGHT;
        break;
    default:
        branchPoisition[0] = side::NONE;
        break;

    }
}

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
    //Branches
    sf::Texture branchTex;
    branchTex.loadFromFile("Graphics/branch.png");
    //changes clouds to this
    for (int i = 0; i < NUM_BRANCHES; ++i)
    {
        branches[i].setTexture(branchTex);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }
    //Player
    sf::Texture playerTex;
    playerTex.loadFromFile("Graphics/player.png");
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTex);
    playerSprite.setPosition(580, 720);
    side playerSide = side::LEFT;
    //Gravestone
    sf::Texture graveTex;
    graveTex.loadFromFile("Graphics/rip.png");
    sf::Sprite graveSprite;
    graveSprite.setTexture(graveTex);
    graveSprite.setPosition(600, 860);
    //Axe
    sf::Texture axeTex;
    axeTex.loadFromFile("Graphics/axe.png");
    sf::Sprite axeSprite;
    axeSprite.setTexture(axeTex);
    axeSprite.setPosition(700, 830);
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;
    //Log
    sf::Texture logTex;
    logTex.loadFromFile("Graphics/log.png");
    sf::Sprite logSprite;
    logSprite.setTexture(logTex);
    logSprite.setPosition(810, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    //Sound
    sf::SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("Audio/chop.wav");
    sf::Sound chop;
    chop.setBuffer(chopBuffer);

    sf::SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("Audio/death.wav");
    sf::Sound death;
    death.setBuffer(deathBuffer);

    sf::SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("Audio/out_of_time.wav");
    sf::Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    bool acceptInput = false;
    bool gamePaused = true;
    int score = 0;
    //Font setup
    sf::Font font;
    font.loadFromFile("Font/KOMIKAP_.ttf");
    //Message when player starts the game
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setString("Press Enter to begin");
    displayText.setCharacterSize(75);
    displayText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = displayText.getLocalBounds();
    displayText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    displayText.setPosition(1920 / 2.f, 1080 / 2.f);
    //Players score
    sf::Text scoreText;   
    scoreText.setFont(font);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 20);
    //Time bar
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    sf::Time gameTime;
    float timeLeft = 6.f;
    float timeBarWidthChange = timeBarStartWidth / timeLeft;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && !gamePaused)
            {
                acceptInput = true;
                axeSprite.setPosition(2000, axeSprite.getPosition().y);
            }
        }
        //input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            gamePaused = false;
            score = 0;
            timeLeft = 6.f;
            for (int i = 1; i < NUM_BRANCHES; ++i)
            {
                branchPoisition[i] = side::NONE;
            }
            graveSprite.setPosition(675, 2000);
            playerSprite.setPosition(580, 720);
            acceptInput = true;
            
        }
        if (acceptInput)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerSide = side::RIGHT;
                score++;
                timeLeft += (2 / score) + .15;
                axeSprite.setPosition(AXE_POSITION_RIGHT, axeSprite.getPosition().y);
                playerSprite.setPosition(1200, 720);
                branchUpdate(score);
                logSprite.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;

                acceptInput = false;
                chop.play();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerSide = side::LEFT;
                score++;
                timeLeft += (2 / score) + .15;
                axeSprite.setPosition(AXE_POSITION_LEFT, axeSprite.getPosition().y);
                playerSprite.setPosition(580, 720);
                branchUpdate(score);
                logSprite.setPosition(810, 720);
                logSpeedX = 5000;
                logActive = true;

                acceptInput = false;
                chop.play();
            }
        }
        //update
        sf::Time deltaTime = clock.restart();
        if (!gamePaused)
        {
            timeLeft -= deltaTime.asSeconds();
            timeBar.setSize(sf::Vector2f(timeBarWidthChange * timeLeft, timeBarHeight));

            if (timeLeft <= 0.f)
            {
                gamePaused = true;
                displayText.setString("Time up!");
                sf::FloatRect textRact = displayText.getLocalBounds();
                displayText.setOrigin(textRact.left + textRact.width / 2.f, textRact.top + textRact.height / 2.f);
                displayText.setPosition(1920 / 2.f, 1080 / 2.f);
                outOfTime.play();

            }

            if (!isBeeMoving)
            {
                srand(time(NULL));
                beeSpeed = (rand() & 200) + 20;
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
            if (!isCloud1Moving)
            {
                srand(time(NULL));
                cloud1Speed = (rand() % 200) + 200;
                float cloud1Height = (rand() % 150);
                cloudSprite1.setPosition(-200, cloud1Height);
                isCloud1Moving = true;
            }
            else
            {
                cloudSprite1.setPosition(cloudSprite1.getPosition().x + (cloud1Speed * deltaTime.asSeconds()), cloudSprite1.getPosition().y);
                if (cloudSprite1.getPosition().x > 1920)
                {
                    isCloud1Moving = false;
                }
            }
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            for (int i = 0; i < NUM_BRANCHES; ++i)
            {
                float height = i * 150;
                if (branchPoisition[i] == side::LEFT)
                {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                }
                else if (branchPoisition[i] == side::RIGHT)
                {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                }
                else
                {
                    branches[i].setPosition(3000, height);
                }
            }
            if (logActive)
            {
                logSprite.setPosition(logSprite.getPosition().x + (logSpeedX * deltaTime.asSeconds()), logSprite.getPosition().y + (logSpeedY * deltaTime.asSeconds()));
                if (logSprite.getPosition().x < -100 || logSprite.getPosition().x > 2000)
                {
                    logActive = false;
                    logSprite.setPosition(810, 720);
                }

            }
            if (branchPoisition[5] == playerSide)
            {
                gamePaused = true;
                acceptInput = false;
                graveSprite.setPosition(525, 760);
                playerSprite.setPosition(2000, 660);
                displayText.setString("Squashed!");
                displayText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
                displayText.setPosition(1920 / 2.f, 1080 / 2.f);
                death.play();
            }
        }
        

        //draw
        window.clear();
        window.draw(bgSprite);
        window.draw(treeSprite);
        window.draw(playerSprite);
        window.draw(axeSprite);
        window.draw(logSprite);
        window.draw(graveSprite);
        window.draw(beeSprite);
        window.draw(cloudSprite1);
        window.draw(cloudSprite2);
        window.draw(cloudSprite3);
        for (int i = 0; i < NUM_BRANCHES; ++i)
        {
            window.draw(branches[i]);
        }
        window.draw(scoreText);
        window.draw(timeBar);
        window.draw(logSprite);
        
        if (gamePaused)
        {
            window.draw(displayText);
        }
        window.display();
    }

    return 0;
}