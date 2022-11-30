#pragma once

// colors code
#define BLUE_COLOR SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
#define YELLOW_COLOR SDL_SetRenderDrawColor(render, 255, 191, 0, 255);

struct SDL_colors_t
{
    SDL_Color dark{0, 0, 0, 0};
    SDL_Color green{127, 255, 0, 0};
    SDL_Color orange{255, 140, 0, 0};
    SDL_Color red{255, 0, 0, 0};
    SDL_Color blue{0, 0, 255, 0};
    SDL_Color yellow{255, 255, 0, 0};
    SDL_Color a{255, 0, 0, 0};
    SDL_Color grey{128, 128, 128, 0};
    SDL_Color aqva{0, 255, 255, 0};
    SDL_Color list[9] = {dark,green,orange,red,blue,yellow,a,grey,aqva};
};


