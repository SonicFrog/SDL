#ifndef DEF_SCREEN_CONFIG_HPP
#define DEF_SCREEN_CONFIG_HPP

#include "DisplayEngine.hpp"

namespace SDLRPG
{
    class Configurator
    {
        public :
            Configurator();
            virtual void showConfigDialog(DisplayEngine* engine) = 0;

        protected :
            DisplayEngine* m_engine;
            virtual void doConfig(void *data) = 0;
    };

    class ScreenConfiguration : public Configurator
    {
        public :
            ScreenConfiguration();
            virtual void showConfigDialog(DisplayEngine* engine);

        protected :
            virtual void doConfig(void *data);
    };
};

#endif //DEF_SCREEN_CONFIG_HPP
