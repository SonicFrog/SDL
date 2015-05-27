#include "ConfiguratorTest.hpp"
#include "../ScreenConfiguration.hpp"

namespace SDLRPG
{
    void ScreenConfiguratorTest::DialogTest()
    {
        ScreenConfiguration sc;
        DisplayEngine* engine = new DisplayEngine();
        sc.showConfigDialog(engine);
        delete engine;
    }

    void ScreenConfiguratorTest::ChangesTest()
    {
        ;
    }
}
