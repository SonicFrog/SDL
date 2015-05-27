#include "ScreenConfiguration.hpp"
#include "Tools.hpp"
#include "ErrorPrinter.hpp"

namespace SDLRPG
{
    Configurator::Configurator()
    {

    }

    ScreenConfiguration::ScreenConfiguration()
    {

    }

    void ScreenConfiguration::showConfigDialog(DisplayEngine* engine)
    {
        int starting_y = 50;
        int selected = 0, i;
        ScreenEntityID text_id, res_id;
        bool done = false;
        SDL_Event event;
        SDL_Rect** modes = SDL_ListModes(engine->getFormat(), SDLRPG_DEFAULT_SCREEN_FLAGS);
        ErrorPrinter::printInternalDebug(Formatter() << "VideoMode = " << modes);
        if(modes == NULL)
        {
            text_id = engine->renderText("No resolution available!!", {255, 255, 255, 0});
            engine->drawEntity(text_id, engine->getWidth() / 2, engine->getHeight() / 2);
            return;
        }
        else if(modes == (SDL_Rect**) -1)
        {
            text_id = engine->renderText("Every resolution accepted!!", {255, 255, 255, 0});
            engine->drawEntity(text_id, engine->getWidth() / 2, engine->getHeight() / 2);
            engine->updateScreen();
            while(!done)
            {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                    case SDL_KEYDOWN :
                    case SDL_QUIT :
                        ErrorPrinter::printDisplayDebug("Leaving configurator ...");
                        done = true;
                        break;
                }
            }
            return;
        }
        engine->clearScreen();
        text_id = engine->renderText("Resolution :", {0, 0, 0} );
        engine->drawEntity(text_id, engine->getWidth() / 2, starting_y += 60);
        for(i = 0 ; modes[i] ; ++i)
        {
            ErrorPrinter::printInternalDebug(Formatter() << "Pointer to 0x" << modes[i]);
            res_id = engine->renderText(Formatter() << (i + 1) << ". " << modes[i]->x << "x" << modes[i]->y);
            engine->drawEntity(res_id, engine->getWidth() / 2, starting_y);
            while(!done)
            {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                    case SDL_KEYDOWN :
                        done = true;
                        break;
                }
            }
        }
        engine->updateScreen();
        while(!done)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_KEYDOWN :
                    selected = event.key.keysym.sym - SDLK_0;
                    if(selected < 0 || selected > i)
                        selected = 0;
                    done = true;
                    break;
            }
        }
        m_engine = engine;
        engine->eraseEntity(text_id);
        doConfig(modes[selected]);
    }

    void ScreenConfiguration::doConfig(void* data)
    {
        SDL_Rect* resolution = (SDL_Rect*) data;
        m_engine->resizeScreen(resolution->w, resolution->h);
     }
}
