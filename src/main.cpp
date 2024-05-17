#include <SDL2/SDL.h>
#include "Player.h"
#include "Map.h"
#include "Raycaster.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Raycaster::screenWidth, Raycaster::screenHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player player(3.0, 3.0, 0.0);
    Map map;
    Raycaster raycaster;

    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            player.moveForward(0.1);
                            break;
                        case SDLK_s:
                            player.moveBackward(0.1);
                            break;
                        case SDLK_a:
                            player.turnLeft(0.1);
                            break;
                        case SDLK_d:
                            player.turnRight(0.1);
                            break;
                    }
                    break;
            }
        }

        raycaster.render(renderer, player, map);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
