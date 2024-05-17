#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

double playerX = 3.0; // Player's x-coordinate
double playerY = 3.0; // Player's y-coordinate
double playerAngle = 0.0; // Player's view angle (in radians)

const int mapWidth = 8;
const int mapHeight = 8;
const char map[] = {
        "########"
        "#......#"
        "#......#"
        "#......#"
        "#......#"
        "#......#"
        "#......#"
        "########"
};

void renderRaycasting(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    const double fov = 60.0 * M_PI / 180.0; // Field of view (60 degrees)
    const double rayAngleStep = fov / SCREEN_WIDTH;

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double rayAngle = (playerAngle - fov / 2.0) + (x * rayAngleStep);

        // Raycasting
        double rayDirX = cos(rayAngle);
        double rayDirY = sin(rayAngle);

        int mapX = int(playerX);
        int mapY = int(playerY);

        double sideDistX, sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist;

        int stepX, stepY;
        bool hit = false;
        int side = 0;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (playerX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (playerY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
        }

        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (map[mapY * mapWidth + mapX] == '#') {
                hit = true;
            }
        }
        if (side == 0) {
            perpWallDist = (sideDistX - deltaDistX);
        } else {
            perpWallDist = (sideDistY - deltaDistY);
        }

        int lineHeight = int(SCREEN_HEIGHT / perpWallDist);

        // Calculate the color based on the distance
        int color = int(255 / (1 + perpWallDist));
        if (color < 0) {
            color = 0;
        }
        if (color > 255) {
            color = 255;
        }

        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }

        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) {
            drawEnd = SCREEN_HEIGHT - 1;
        }

        // Use the calculated color for the wall
        SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
                            playerX += cos(playerAngle) * 0.1;
                            playerY += sin(playerAngle) * 0.1;
                            break;
                        case SDLK_s:
                            playerX -= cos(playerAngle) * 0.1;
                            playerY -= sin(playerAngle) * 0.1;
                            break;
                        case SDLK_a:
                            playerAngle -= 0.1;
                            break;
                        case SDLK_d:
                            playerAngle += 0.1;
                            break;
                    }
                    break;
            }
        }

        renderRaycasting(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}