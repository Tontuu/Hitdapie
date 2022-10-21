#include "engine.h"
#include <iomanip>
#include <sstream>

// Static declaration
sf::RenderWindow Engine::window;

// Constructors and initialization
void Engine::initWindow() {
    window.create(sf::VideoMode(1280, 720), "HitDaPie", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
}

void Engine::initBox(Box &box, int size, int posX, int posY, sf::Color color, double velocity, double mass) {
    box.shape.setPosition(sf::Vector2f(posX, posY + (window.getSize().y - floor.getSize().y - size - 2)));
    box.shape.setSize(sf::Vector2f(size, size));
    box.shape.setFillColor(color);
    box.v = velocity;
    box.m = mass;
}


void Engine::initVariables() {
    pause = false;

    // Manage the decimals numbers of PI increasing scale:timesteps.
    count = 0;
    scale = 7;
    timesteps = pow(10, scale-3);

    boxSize1 = 200;
    boxPosX1 = 400;
    boxPosY1 = 0;
    boxColor1 = sf::Color(181, 31, 20,255);
    box.shape.setOutlineColor(sf::Color(97, 16, 11));
    box.shape.setOutlineThickness(2);
    velocity1 = 1.0 / timesteps;
    mass1 = pow(100, scale-1);

    boxSize2 = 50;
    boxPosX2 = 50;
    boxPosY2 = 0;
    boxColor2 = sf::Color(20, 157, 181,255);
    box2.shape.setOutlineColor(sf::Color(11, 93, 107));
    box2.shape.setOutlineThickness(2);
    velocity2 = 0.0;
    mass2 = 1;

    floorSize = sf::Vector2f(window.getSize().x, 100/2);
    floorPos = sf::Vector2f(0, window.getSize().y - floorSize.y);
    floorColor = sf::Color(106, 106, 106, 255);

    floor.setSize(floorSize);
    floor.setPosition(floorPos);
    floor.setFillColor(floorColor);

    backgroundColor = sf::Color(50,50,50,255);
}

void Engine::initGui() {


    // Font rendering
    font.loadFromFile("fairfax.ttf");
    countTxt.setFont(font);
    countTxt.setString(std::to_string(0));
    countTxt.setCharacterSize(48);
    countTxt.setPosition(10, 0);
    
    int characterSize;
    characterSize = (scale > 5) ? 16 : 24;

    boxMassTxt1.setFont(font);
    boxMassTxt1.setString(std::to_string(mass1).substr(0, std::to_string(mass1).length()-5).append("kg"));
    boxMassTxt1.setCharacterSize(characterSize);
    boxMassTxt1.setOrigin(boxMassTxt1.getLocalBounds().width/2,boxMassTxt1.getLocalBounds().height);
    boxMassTxt1.setFillColor(sf::Color(255, 0, 50));
    boxMassTxt1.setOutlineColor(sf::Color::Black);
    boxMassTxt1.setOutlineThickness(1);

    boxMassTxt2.setFont(font);
    boxMassTxt2.setString(std::to_string(mass2).append("kg"));
    boxMassTxt2.setCharacterSize(characterSize);
    boxMassTxt2.setOrigin(boxMassTxt2.getLocalBounds().width/2,boxMassTxt2.getLocalBounds().height);
    boxMassTxt2.setFillColor(sf::Color::Cyan);
    boxMassTxt2.setOutlineThickness(1);
    boxMassTxt2.setOutlineColor(sf::Color::Black);
}

Engine::Engine()
{
    initWindow();
    initVariables();
    initGui();

    initBox(box, boxSize1, boxPosX1, boxPosY1, boxColor1, velocity1, mass1);
    initBox(box2, boxSize2, boxPosX2, boxPosY2, boxColor2, velocity2, mass2);

}

void Engine::updateTexts() {
    boxMassTxt1.setPosition(
	box.shape.getPosition().x + boxSize1/2,
	box.shape.getPosition().y + boxSize1/2);

    boxMassTxt2.setPosition(
	box2.shape.getPosition().x + boxSize2/2,
	box2.shape.getPosition().y + boxSize2/2);
}

// Functions
void Engine::update() {
    box.update();
    box2.update();
    updateTexts();

    if (box.collide(box2)) {
	sound.play();
	box.bounce(box2);
	count++;
	countTxt.setString(std::to_string(count));
    }

    if (box2.hitWall()) {
	sound.play();
	count++;
	box2.reverse();
	countTxt.setString(std::to_string(count));
    }
    
}

void Engine::render() {

    window.clear(backgroundColor);

    window.draw(floor);
    window.draw(box2.shape);
    window.draw(boxMassTxt2);
    window.draw(box.shape);
    window.draw(boxMassTxt1);
    window.draw(countTxt);


    window.display();
}

void Engine::checkEvents() {
    while(window.pollEvent(event)) {
	if (event.type == sf::Event::Closed)
	    window.close();

	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	    window.close();

	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	    pause = !pause;
    }
}

const sf::RenderWindow & Engine::getWindow(){
    return window;
}
