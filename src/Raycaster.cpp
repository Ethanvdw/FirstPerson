#include "Raycaster.h"
#include <cmath>
#include <iostream>

void Raycaster::render(SDL_Renderer* renderer, const Player& player, const Map& map) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    const double fov = 60.0 * M_PI / 180.0; // Field of view (60 degrees)
    const double rayAngleStep = fov / screenWidth;

    for (int x = 0; x < screenWidth; x++) {
        double rayAngle = (player.angle - fov / 2.0) + (x * rayAngleStep);

        double rayDirX = cos(rayAngle);
        double rayDirY = sin(rayAngle);

        int mapX = int(player.x);
        int mapY = int(player.y);

        double sideDistX, sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist;

        int stepX, stepY;
        bool hit = false;
        int side = 0;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
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

            if (map.isWall(mapX, mapY)) {
                hit = true;
            }
        }

        if (side == 0) {
            perpWallDist = (sideDistX - deltaDistX);
        } else {
            perpWallDist = (sideDistY - deltaDistY);
        }

        int lineHeight = int(screenHeight / perpWallDist);

        int color = int(255 / (1 + perpWallDist));
        if (color < 0) {
            color = 0;
        }
        if (color > 255) {
            color = 255;
        }

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }

        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) {
            drawEnd = screenHeight - 1;
        }

        SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }

    SDL_RenderPresent(renderer);
}
