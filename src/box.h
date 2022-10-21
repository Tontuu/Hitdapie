#pragma once
#ifndef box_h
#define box_h

#include "SFML/Graphics.hpp"
#include <iostream>

class Box {
private:
    // Objects
    sf::RenderWindow window;
    sf::Color color;

public:
    // Constructor
    Box();

    // Variables
    double m;
    double v;
    int vScale;

    // Objects
    sf::RectangleShape shape; 

    // Functions
    void update();
    bool hitWall();
    bool collide(Box &other);
    void bounce(Box &other);
    void reverse();

};

#endif
