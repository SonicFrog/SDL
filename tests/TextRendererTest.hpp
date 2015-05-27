#ifndef DEF_TEXT_RENDERER_TEST_H
#define DEF_TEXT_RENDERER_TEST_H

#include <cppunit/Test.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TextRendererTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE (TextRendererTest);
    CPPUNIT_TEST (drawStringTest);
    CPPUNIT_TEST (drawNullStringTest);
    CPPUNIT_TEST (blitOnScreenTest);
    CPPUNIT_TEST (instantiateTest);
    CPPUNIT_TEST_SUITE_END ();

    public :
        void drawStringTest();
        void drawNullStringTest();
        void blitOnScreenTest();
        void instantiateTest();
        TextRendererTest();
};

#endif
