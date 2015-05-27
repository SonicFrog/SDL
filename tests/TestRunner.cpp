#include <cppunit/TextTestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/ui/text/TestRunner.h>

#include "DisplayEngineTest.hpp"
#include "TextRendererTest.hpp"
#include "ConfiguratorTest.hpp"

using namespace SDLRPG;

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TextRendererTest::suite());
    runner.addTest(DisplayTest::suite());
    runner.addTest(ScreenConfiguratorTest::suite());
    runner.run();
    return 0;
}
