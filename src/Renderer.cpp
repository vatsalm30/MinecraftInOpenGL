#include "Renderer.h"

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* _renderer, std::vector<Point3D>& _points, std::vector<Quad>& _quads)
{
    SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
    renderer = _renderer;
    points = _points;
    quads = _quads;
}

Renderer3D::~Renderer3D() {}

void Renderer3D::Render() 
{
    auto time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration(0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0 , SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    rotation += 1 * DeltaTime;
    int r = 0;
    for(auto& quad : quads)
    {
        SDL_SetRenderDrawColor(renderer, r, 0, 0, SDL_ALPHA_OPAQUE);
        r+=40;
        Point3D rotationPointA = rotateX(points[quad.pointA]);
        Point3D rotationPointB = rotateX(points[quad.pointB]);
        Point3D rotationPointC = rotateX(points[quad.pointC]);
        Point3D rotationPointD = rotateX(points[quad.pointD]);

        // Point3D rotationPointA = points[quad.pointA];
        // Point3D rotationPointB = points[quad.pointB];
        // Point3D rotationPointC = points[quad.pointC];
        // Point3D rotationPointD = points[quad.pointD];

        Point2D pointA = projection(rotationPointA);
        Point2D pointB = projection(rotationPointB);
        Point2D pointC = projection(rotationPointC);
        Point2D pointD = projection(rotationPointD);

        SDL_Rect rect;

        int rectX = pointA.x < pointB.x ? pointA.x : pointB.x;
        int rectY = pointA.y < pointD.y ? pointA.y : pointD.y;
        int rectW = (pointC.x > pointB.x ? pointC.x : pointB.x) - rectX;
        int rectH = (pointC.y > pointD.y ? pointC.y : pointD.y) - rectY;

        rect.x = rectX;
        rect.y = rectY;
        rect.w = rectW;
        rect.h = rectH; 

        SDL_RenderFillRect(renderer, &rect);

        // // OUTLINE
        // SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
        // SDL_RenderDrawLine(renderer, pointC.x, pointC.y, pointD.x, pointD.y);
        // SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointC.x, pointC.y);
        // SDL_RenderDrawLine(renderer, pointD.x, pointD.y, pointB.x, pointB.y);

        // // DIAGONAL
        // SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointD.x, pointD.y);

    }
    SDL_RenderPresent(renderer);

    auto time2 = std::chrono::high_resolution_clock::now();
    duration = time2 - time1;
    DeltaTime = duration.count();
    time1 = time2;
}

Point3D Renderer3D::rotateX(Point3D point)
{
    Point3D returnPoint;

    returnPoint.x = point.x;
    returnPoint.y = cos(rotation) * point.y - sin(rotation) * point.z;
    returnPoint.z = sin(rotation) * point.y + cos(rotation) * point.z;

    return returnPoint;
}

Point3D Renderer3D::rotateY(Point3D point)
{
    Point3D returnPoint;

    returnPoint.x = cos(rotation) * point.x - sin(rotation) * point.z;
    returnPoint.y = point.y;
    returnPoint.z = sin(rotation) * point.x + cos(rotation) * point.z;

    return returnPoint;
}

Point2D Renderer3D::projection(Point3D point)
{
    return Point2D{ WindowSizeX / 2 + (FOV * point.x) / (point.z + FOV) * 100, WindowSizeY / 2 + (FOV * point.y) / (point.z + FOV) * 100 };
}