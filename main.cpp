#include <iostream>
#include "cups_board.h"

// nedd to trasfer to enum class settings
const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Cupboards", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    //set cups board with parametr-level

    // Check that the window was successfully created
    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    Cups_Board cups_board_stage {1};
    SDL_Event windowEvent;
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    while (true)
    {
        // set general color or texture (white or similar)
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF,  0xFF,  0xFF);
        SDL_RenderClear(render);
        //pass render to update 
       std::cout<<"addr"<<cups_board_stage.get_array_addr()<< std::endl;
        cups_board_stage.cups_board_render_update(render);
        std::cout<<"SDL_RenderPresent"<< std::endl;
        //std::cout<<"addr"<<cups_board_stage.get_array_addr()<< std::endl;

        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
        //render
        SDL_RenderPresent(render);
        std::cout<<"SDL_RenderPresent"<< std::endl;

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
}
