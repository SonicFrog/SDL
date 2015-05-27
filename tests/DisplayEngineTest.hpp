#ifndef DEF_DISPLAY_TEST_H
#define DEF_DISPLAY_TEST_H

#include <cppunit/Test.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define TEST_SPRITE   "sprites/caisse.jpg"

namespace SDLRPG
{
    /**
     * Suite de test pour le moteur de rendu du jeu
     * @version 1.0
     * @author ars3nic
     **/
    class DisplayTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE(DisplayTest);
        CPPUNIT_TEST (OpenScreenTest);
        CPPUNIT_TEST (DrawTextureTest);
        CPPUNIT_TEST (InstantiateEngineTest);
        CPPUNIT_TEST (NullEntityTest);
        CPPUNIT_TEST (BackgroundTextureTest);
        CPPUNIT_TEST (RunningEngineTest);
        CPPUNIT_TEST (MovingEntityTest);
        CPPUNIT_TEST_SUITE_END();

      public :
        void OpenScreenTest();
        void DrawTextureTest();
        void InstantiateEngineTest();
        void NullEntityTest();
        void BackgroundTextureTest();
        void RunningEngineTest();
        void MovingEntityTest();
        DisplayTest();
    };
}

#endif
