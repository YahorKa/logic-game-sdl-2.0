#pragma once

// colors code
#define BLUE_COLOR SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
#define YELLOW_COLOR SDL_SetRenderDrawColor(render, 255, 191, 0, 255);

struct SDL_colors_t
{
    //cups colors
    SDL_Color dimGray{105, 105, 105, 0};
    SDL_Color green{0, 128, 0, 0};
    SDL_Color gold{255, 215, 0, 0};
    SDL_Color red{139, 0, 0, 0};
    SDL_Color blue{0, 0, 255, 0};
    SDL_Color yellow{255, 255, 0, 0};
    SDL_Color magenta{255, 0, 255, 0};
    SDL_Color aqva{0, 255, 255, 0};
    SDL_Color list[9] = {dimGray, green, gold, red, blue, magenta, magenta, aqva};

    // More brightness colors
    SDL_Color Gray{220, 220, 220, 0};
    SDL_Color SpringGreen{0, 255, 127, 0};
    SDL_Color Yellow{255, 255, 0, 0};
    SDL_Color Tomato{255, 99, 71, 0};
    SDL_Color LightSkyBlue{135, 206, 250, 0};
    SDL_Color LightYellow{173, 255, 47, 0};
    SDL_Color Violet{255, 150, 255, 0};
    SDL_Color light_list[9] = {Gray, SpringGreen, Yellow, Tomato, LightSkyBlue, Violet, Violet};

};
