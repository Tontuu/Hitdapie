#include <iostream>
#include "engine.h"


int main() {
    Engine engine;

    if (!engine.buffer.loadFromFile("sound.wav")) {
	std::cerr << "Error while loading sound file" << std::endl;
	return -1;
    }

    engine.sound.setBuffer(engine.buffer);

    engine.sound.setVolume(10.f);

    while(Engine::getWindow().isOpen()) {

	if (engine.pause == false) {
	    for (double i = 0; i < engine.timesteps; i++) {
		engine.update();
	    }
	}

	engine.checkEvents();
	engine.render();
    }

    return EXIT_SUCCESS;
}
