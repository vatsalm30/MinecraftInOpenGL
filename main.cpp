#include <iostream>
#include <vector>

#include "SDL2/SDL.h"

#include "src/Renderer.h"

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Test SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    // cube
    std::vector<Point3D> points{
        Point3D{ -1.0f, -1.0f, -1.0f }, Point3D{ -1.0f, -1.0f, 1.0f }, 
        Point3D{ 1.0f, -1.0f, 1.0f }, Point3D{ 1.0f, -1.0f, -1.0f },
        Point3D{ -1.0f, 1.0f, -1.0f }, Point3D{ -1.0f, 1.0f, 1.0f },
        Point3D{ 1.0f, 1.0f, -1.0f }, Point3D{ 1.0f, 1.0f, 1.0f }
    };
    std::vector<Quad> quads{
        Quad{ 0, 1, 0, 3 }, // TOP NEGY 0 1 2 3
        Quad{ 4, 5, 6, 7 }, // BOTTOM POSY 4 5 6 7
        Quad{ 0, 3, 4, 6 }, // FRONT NEGZ 0 3 4 6
        Quad{ 1, 2, 5, 7 }, // BACK POSZ 1 2 5 7
        Quad{ 0, 1, 4, 5 }, // LEFT NEGX 0 1 4 5
        Quad{ 2, 6, 3, 2 }, // RIGHT POSX 2 3 6 7
    };

    if(window == NULL)
    {
        std::cout<<"Failed to create window: "<<SDL_GetError()<<std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    Renderer3D renderer3D(window, renderer, points, quads);

    while(true)
    {
        if(SDL_PollEvent(&windowEvent))
        {
            if(windowEvent.type == SDL_QUIT)
            {
                break;
            }
        }

        renderer3D.Render();

        // SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        // SDL_RenderClear( renderer );

        // SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );

        // SDL_RenderPresent( renderer );
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}