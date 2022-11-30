#include "cup.h"

Cup::Cup(int x, int y, int w, int h, SDL_Color color) : rect{x, y, w, h}, _color{color}
{
}

void Cup::have_touch()
{
    rect.x += 5;
    // rect.w += 20;
}

// bool Cups::render(float x, float y)
// {
// }