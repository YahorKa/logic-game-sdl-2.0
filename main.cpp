#include <iostream>
#include "cups_board.h"
#include "file_manager.h"

// nedd to trasfer to enum class settings
const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    File_Manager level_manager;
    SDL_Window *window = SDL_CreateWindow("Cupboards", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    //set cups board with parametr-level

    // Check that the window was successfully created
    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    Cups_Board cups_board_stage {};

    SDL_Event windowEvent;
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    try
    {
        level_manager.get_data(1);
    }
    catch(...)
    {
        std::cout << "cath ext :: "<<std::endl;
    }
    
    while (true)
    {

        // set general color or texture (white or similar)
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF,  0xFF,  0xFF);
        SDL_RenderClear(render);
        //pass render to update 
        cups_board_stage.cups_board_render_update(render);
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
        //render
        SDL_RenderPresent(render);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
}
