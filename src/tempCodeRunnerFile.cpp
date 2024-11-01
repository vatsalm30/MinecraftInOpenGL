        // OUTLINE
        SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointB.x, pointB.y);
        SDL_RenderDrawLine(renderer, pointC.x, pointC.y, pointD.x, pointD.y);
        SDL_RenderDrawLine(renderer, pointA.x, pointA.y, pointC.x, pointC.y);
        SDL_RenderDrawLine(renderer, pointD.x, pointD.y, pointB.x, pointB.y);