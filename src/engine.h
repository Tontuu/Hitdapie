#pragma once
#ifndef engine_h
#define engine_h


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <string>

#include "box.h"



class Engine {
private:

    // Objects
    Box box;
    Box box2;
    sf::Event event;
    sf::RectangleShape floor;

    // Variables
    int count;

    // Font:Texts
    sf::Font font;
    sf::Text countTxt;
    sf::Text boxMassTxt1;
    sf::Text boxMassTxt2;

    sf::Vector2f floorSize;
    sf::Vector2f floorPos;
    sf::Color floorColor;

    int boxSize1;
    int boxPosX1;
    int boxPosY1;
    double velocity1;
    double mass1;

    int boxSize2;
    int boxPosX2;
    int boxPosY2;
    double velocity2;
    int mass2;

    sf::Color boxColor1;
    sf::Color boxColor2;
    sf::Color backgroundColor;

    // Init Functions
    void initGui();
    void initVariables();
    void initWindow();
    void initBox(Box &box, int size, int posX, int posY, sf::Color color, double velocity, double mass);

public:
    // Constructors
    Engine();

    // Objects
    static sf::RenderWindow window;
    sf::SoundBuffer buffer;
    sf::Sound sound;

    // Variables
    double timesteps;
    int scale;
    bool pause;

    // Functions
    void update();
    void updateTexts();
    void render();
    void checkEvents();
    static const sf::RenderWindow & getWindow();
};


#endif


