#include "box.h"
#include "engine.h"

Box::Box() {
    vScale = 1;
    v = 0;
}

void Box::update() {
    sf::Vector2f pos = sf::Vector2f(shape.getPosition().x, shape.getPosition().y);
    pos.x += (v * vScale) * -1;
    shape.setPosition(pos);
}

bool Box::hitWall() {
    return (shape.getPosition().x <= 0);
}

void Box::reverse() {
    v = -v;
}

bool Box::collide(Box &other) {
    sf::FloatRect boxBounding = shape.getGlobalBounds();
    sf::FloatRect otherBounding = other.shape.getGlobalBounds();

    return (boxBounding.intersects(otherBounding));
}

void Box::bounce(Box &other) {
    double newV1 = ((m - other.m) / (m + other.m) * v) + ((2 * other.m) / (m + other.m) * other.v);
    double newV2 = ((2 * m) / (m + other.m) * v) + ((other.m - m) / (m + other.m) * other.v);

    v = newV1;
    other.v = newV2;
}

