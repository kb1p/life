#include "lifeboard.h"

#include <SDL2/SDL.h>
#include <string>

int main(int argc, char *argv[])
{
    int rc = 0;
    SDL_Window *win = { };
    SDL_Renderer *g = { };
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
            throw "SDL initialization failed";

        win = SDL_CreateWindow("Life game",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (!win)
            throw "failed to create SDL window";

        g = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        if (!g)
            throw "failed to create renderer";

        LifeBoard board;
        board.init(100, 100);

        const int cellWidth = 640 / 100,
                  cellHeight = 480 / 100;

        bool runLoop = true;
        while (runLoop)
        {
            SDL_Event evt;
            while (SDL_PollEvent(&evt) != 0)
            {
                if (evt.type == SDL_QUIT)
                    runLoop = false;
                // Handle other events...
            }

            // Update game area state
            board.update();

            // Render the area
            SDL_SetRenderDrawColor(g, 0, 0, 0, 0xFFu);
            SDL_RenderClear(g);

            SDL_Rect rCell;
            rCell.w = cellWidth;
            rCell.h = cellHeight;
            for (int r = 0; r < board.height(); r++)
                for (int c = 0; c < board.width(); c++)
                {
                    const int v = board.cell(r, c);
                    if (v != LifeBoard::EMPTY_CELL)
                    {
                        rCell.x = c * cellWidth;
                        rCell.y = r * cellHeight;
                        SDL_SetRenderDrawColor(g, 0xFF, 0x00, 0x00, 0xFF);        
                        SDL_RenderFillRect(g, &rCell);
                    }
                }

            SDL_RenderPresent(g);
        }
    }
    catch (const char *msg)
    {
        std::string fullMsg = "Initialization error: ";
        fullMsg += msg;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Error",
                                 fullMsg.c_str(),
                                 win);
        rc = 1;
    }

    if (g)
        SDL_DestroyRenderer(g);
    if (win)
        SDL_DestroyWindow(win);
    SDL_Quit();

    return rc;
}
