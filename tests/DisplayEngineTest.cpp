#include <exception>
#include "DisplayEngineTest.hpp"
#include "../ErrorPrinter.hpp"
#include "../DisplayEngine.hpp"
#include "../TextRenderer.hpp"

namespace SDLRPG
{
    DisplayTest::DisplayTest()
    {

    }

    void pauseG()
    {
      SDL_Event event;
      bool done = false;
      while(!done)
      {
        SDL_WaitEvent(&event);
        {
          switch(event.type)
          {
            case SDL_QUIT :
            case SDL_KEYDOWN :
              done = true;
              break;
            default :
              break;
          }
        }
      }
    }

    void DisplayTest::InstantiateEngineTest()
    {
      DisplayEngine* engine = new DisplayEngine();
      delete engine;
    }

    /**
     * Test le dessin d'une sprite de test dans la fenetre de l'engine
     **/
    void DisplayTest::DrawTextureTest()
    {
        ErrorPrinter::printInternalDebug("Starting DrawTextureTest");
        DisplayEngine* engine = new DisplayEngine();
        SDL_Surface* texture = IMG_Load(TEST_SPRITE);
        ScreenEntity entity(texture);
        ScreenEntityID id = engine->registerEntity(&entity);

        CPPUNIT_ASSERT_MESSAGE("Le compte d'entite dans la liste du moteur est incorrecte", engine->m_EntityList.size() == 1);

        engine->drawEntity(id, 50, 50);
        CPPUNIT_ASSERT_MESSAGE("Le compte d'entite dans la liste de dessin du moteur est incorrecte", engine->m_ScreenList.size() == 1);

        engine->updateScreen();
        pauseG();
        delete engine;
        ErrorPrinter::printInternalDebug("DrawTextureTest ended");
    }

    /**
     * Test d'insertion dans l'engine d'une entite nulle
     **/
    void DisplayTest::NullEntityTest()
    {
        ErrorPrinter::printInternalDebug("Starting NullEntityTest");
      DisplayEngine* engine = new DisplayEngine();
      ScreenEntity entity(NULL);
      try
      {
        engine->registerEntity(&entity);
        CPPUNIT_ASSERT_MESSAGE ("The engine loaded the null entity without firing an exception", false);
      }
      catch (DisplayEntityNotFoundException &e)
      {
        ErrorPrinter::printDisplayError(e.what());
      }
      CPPUNIT_ASSERT_MESSAGE("L'entite null a quand meme ete chargee en memoire", engine->m_EntityList.size() == 0);
    }

    /**
     * Test d'ouverture de la fenetre du moteur de rendu
     **/
    void DisplayTest::OpenScreenTest()
    {
        ErrorPrinter::printInternalDebug("Starting OpenScreenTest");
      DisplayEngine *engine;
      try
      {
        engine = new DisplayEngine();
        CPPUNIT_ASSERT_MESSAGE("Le pointeur vers la zone memoire de l'ecran est NULL", engine->m_screen != NULL);
        pauseG();
      }
      catch (std::exception &e)
      {
        std::string message = "An exception occured while opening the display engine ";
        message.append(e.what());
        CPPUNIT_ASSERT_MESSAGE(message.c_str(), false);
      }
      std::cerr << SDL_GetError();
      delete engine;
      ErrorPrinter::printInternalDebug("OpenScreenTestEnded");
    }

    /**
     * Test du fond d'ecran du moteur
     **/
    void DisplayTest::BackgroundTextureTest()
    {
        ErrorPrinter::printInternalDebug("Starting BackgroundTextureTest");
        DisplayEngine *engine = new DisplayEngine();
        SDL_Surface* bTexture = IMG_Load("sprites/menu.jpg");
        ScreenEntity* background = new ScreenEntity(bTexture);
        engine->setBackground(background);
        engine->updateScreen();
        CPPUNIT_ASSERT_MESSAGE("Erreur lors de l'assignation du pointeur vers la texture de fond d'ecran", engine->m_background != NULL);
        pauseG();
        delete engine;
        ErrorPrinter::printInternalDebug("BackgroundTextureTest ended");
    }

    void DisplayTest::MovingEntityTest()
    {
        short x_offset = 2, y_offset = x_offset + 3;
        short start = 100;
        short times = 50;
        ErrorPrinter::printInternalDebug("Starting MovingEntityTest");
        DisplayEngine *engine = new DisplayEngine();
        ScreenEntityID id = engine->renderText("Look at me move", {255, 255, 255, 0});
        engine->drawEntity(id, start, start);
        engine->updateScreen();
        for(int i = 0 ; i < times ; i++)
        {
            engine->moveEntity(id, x_offset, y_offset);
            engine->updateScreen();
            SDL_Delay(25);
        }
        CPPUNIT_ASSERT_MESSAGE("Erreur lors du déplacement de l'entité", engine->m_EntityList[id]->getX() != start + x_offset * times);
        CPPUNIT_ASSERT_MESSAGE("Erreur lors du déplacement de l'entité", engine->m_EntityList[id]->getY() != start + y_offset * times);
        delete engine;
        ErrorPrinter::printInternalDebug("MovingEntityTest has ended");
    }

    void DisplayTest::RunningEngineTest()
    {
        ErrorPrinter::printInternalDebug("Routine Test running ...");
        DisplayEngine* engine = NULL;
        ScreenEntityID id = 0;
        SDL_Surface* texture = NULL;
        TextRenderer* renderer = new TextRenderer();
        engine = new DisplayEngine();
        texture = renderer->renderText("Prout");
        id = engine->registerEntity(new ScreenEntity(texture));
        engine->drawEntity(id, SDLRPG_DEFAULT_WIDTH / 2, SDLRPG_DEFAULT_HEIGHT / 2);
        engine->updateScreen();
        pauseG();
        delete engine;
        ErrorPrinter::printInternalDebug("End Routine Test!");
    }
}
