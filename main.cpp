#include <iostream>
#include <cstdlib>

#include "DisplayEngine.hpp"
#include "ErrorPrinter.hpp"
#include "ScreenConfiguration.hpp"
#include "Tools.hpp"

#define MENU_SPRITE     "sprites/back.jpg"
#define DEMO_DELAY      100

using namespace SDLRPG;

void demo(DisplayEngine *engine);

int main(int argc, char** argv)
{
    DisplayEngine *engine = NULL;
    int pos;
    ErrorPrinter::printInternalDebug(Formatter() << "Running as " << argv[0]);
    pos = std::cout.tellp();
    std::cout.seekp(pos - 2);
    for(int i = 1 ; i < argc ; i++) {
    	std::cout << argv[i];
    }
    std::cout << std::endl;
    try {
        engine = new DisplayEngine();
        engine->printInfo();
        demo(engine);
    }
    catch (std::exception &e)
    {
        ErrorPrinter::printDisplayError(Formatter() << "An error occured : " << e.what());
    }
    delete engine;
    return EXIT_SUCCESS;
}

int delay(int last)
{
    int wait = DEMO_DELAY - SDL_GetTicks() - last;
    if(wait < 0)
        wait = 0;
    ErrorPrinter::printInternalDebug(Formatter() << "Waiting " << wait << " msecs");
    return wait;
}

void demo(DisplayEngine *engine)
{
    bool running = true;
    int last_update = SDL_GetTicks();
    SDL_Surface* menu = IMG_Load(MENU_SPRITE);
    ScreenEntityID text;
    if(engine->hasAcceleration())
    {
         text = engine->renderText("Demo");
    }
    else
    {
        text = engine->renderText("Your OS does not support Hardware Acceleration", {255, 255, 255});
    }
    ScreenConfiguration sc;
    engine->setBackground(new ScreenEntity(menu));
    engine->drawEntity(text, menu->w/2, menu->h/2);
    engine->resizeScreen(menu->w, menu->h);
    engine->updateScreen();
    SDL_Event event;
    while(running)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_o :
                        engine->saveEngineState();
                        sc.showConfigDialog(engine);
                        engine->restoreEngineState();
                        break;

                    case SDLK_q :
                        running = false;
                        break;

                    default :
                        continue;
                }
                break;

            case SDL_QUIT :
                running = false;
                break;

            case SDL_MOUSEBUTTONDOWN :
            	engine->drawEntity(text, event.button.x, event.button.y);
                break;

            default:
                continue;
        }
        engine->updateScreen();
        SDL_Delay(delay(last_update = SDL_GetTicks()));
    }
}
