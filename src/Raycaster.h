#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <SDL2/SDL.h>
#include "Player.h"
#include "Map.h"

class Raycaster {
public:
    static const int screenWidth = 640;
    static const int screenHeight = 480;

    void render(SDL_Renderer* renderer, const Player& player, const Map& map) const;
};

#endif // RAYCASTER_H
