#include <iostream>
#include "cups_board.h"
#include "file_manager.h"

// nedd to add to enum class settings
const int WIDTH = 800, HEIGHT = 600;
int mouse_cord_x, mouse_cord_y, button_click = 0;
SDL_Event windowEvent;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        cout << "Can't init SDL: " << SDL_GetError() << endl;
        return false;
    }
    SDL_Window *window = SDL_CreateWindow("Cupboards", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    // Check that the window was successfully created
    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    Cups_Board cups_board_stage{};
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    while (true)
    {
        float fps = SDL_GetTicks();
        // set general color or texture (white or similar)
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(render);
        // pass render to update
        cups_board_stage.cups_board_render_update(render);
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
            if (windowEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                cups_board_stage.handle_mouse(windowEvent.button.x, windowEvent.button.y);
            }
        }
        // render
        SDL_RenderPresent(render);
        fps = 1000/(SDL_GetTicks()-fps);
        //cout<<fps<<endl;
    }
    // SDL_Delay(500);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
}
