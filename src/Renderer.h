#include "SDL2/SDL.h"

#include <vector>
#include <math.h>
#include <chrono>
#include <iostream>

#define print(x) \
    std::cout << x << std::endl

struct Point2D {
    float x, y;
};
struct Point3D {
    float x, y, z;
};
struct Quad {
    int pointA, pointB, pointC, pointD;
};

class Renderer3D
{
private:
    Point3D rotateX(Point3D point);
    Point3D rotateY(Point3D point);
    Point2D projection(Point3D point);

    float rotation = 0.0f;
    float FOV = 10.0f;
    float DeltaTime = 0.0f;

    int WindowSizeX;
    int WindowSizeY;
    SDL_Renderer* renderer;

    std::vector<Point3D> points;
    std::vector<Quad> quads;

public:
    Renderer3D(SDL_Window* _window, SDL_Renderer* _renderer, std::vector<Point3D>& _points, std::vector<Quad>& _quads);
    ~Renderer3D();
    void Render();
};
