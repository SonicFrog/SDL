#ifndef DEF_TEST_CONFIGURATION_HPP
#define DEF_TEST_CONFIGURATION_HPP

#include <cppunit/Test.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace SDLRPG
{
    class AbstractConfiguratorTest : public CppUnit::TestFixture
    {
        public :
            virtual void DialogTest() = 0;
            virtual void ChangesTest() = 0;
    };

    class ScreenConfiguratorTest : public AbstractConfiguratorTest
    {
        CPPUNIT_TEST_SUITE (ScreenConfiguratorTest);
        CPPUNIT_TEST (DialogTest);
        CPPUNIT_TEST (ChangesTest);
        CPPUNIT_TEST_SUITE_END ();
        public :
            virtual void DialogTest();
            virtual void ChangesTest();

    };
}

#endif
