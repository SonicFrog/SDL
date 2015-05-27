#include "../DisplayExceptions.hpp"
#include "TextRendererTest.hpp"
#include "../TextRenderer.hpp"

using namespace SDLRPG;

TextRendererTest::TextRendererTest()
{

}

void TextRendererTest::drawStringTest()
{
    TextRenderer *t = new TextRenderer();
    SDL_Surface* text = t->renderText("Test string");
    CPPUNIT_ASSERT_MESSAGE("Le pointeur vers la surface est nul", text != NULL);
    SDL_FreeSurface(text);
    delete t;
}

void TextRendererTest::drawNullStringTest()
{
    TextRenderer *t = new TextRenderer();
    SDL_Surface* text = NULL;
    try
    {
      text = t->renderText("");
      CPPUNIT_ASSERT_MESSAGE("Aucune exception interceptée", false);
    }
    catch (DisplayTextRenderingException &e)
    {
      CPPUNIT_ASSERT_MESSAGE("Malgre l'exception de la memoire a ete alloue pour la texture du texte", text == NULL);
    }
}

void TextRendererTest::blitOnScreenTest()
{
    ;
}

void TextRendererTest::instantiateTest()
{
  TextRenderer *t = new TextRenderer();
  CPPUNIT_ASSERT_MESSAGE("Le pointeur vers la police est nul", t->m_font != NULL);
  CPPUNIT_ASSERT_MESSAGE("La taille de la police est négative", t->m_size >= 0);
  delete t;
}
