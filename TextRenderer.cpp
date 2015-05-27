#include "TextRenderer.hpp"
#include "DisplayExceptions.hpp"
#include "ErrorPrinter.hpp"

namespace SDLRPG
{
	/**
	 * Constructeur par defaut
	 **/
	TextRenderer::TextRenderer() throw (DisplayTextRenderingException)
	{
	  init(SDLRPG_TEXT_DEFAULT_FONT, SDLRPG_TEXT_DEFAULT_COLOR, SDLRPG_TEXT_DEFAULT_SIZE);
	}

	TextRenderer::TextRenderer(std::string font) throw (DisplayTextRenderingException)
	{
	  init(font, SDLRPG_TEXT_DEFAULT_COLOR, SDLRPG_TEXT_DEFAULT_SIZE);
	}

	TextRenderer::TextRenderer(std::string font, SDL_Color color) throw (DisplayTextRenderingException)
	{
	  init(font, color, SDLRPG_TEXT_DEFAULT_SIZE);
	}

	TextRenderer::TextRenderer(std::string font, SDL_Color color, int size) throw (DisplayTextRenderingException)
	{
	  init(font, color, size);
	}

	/**
	 * Destructeur du TextRenderer
	 **/
	TextRenderer::~TextRenderer()
	{
	  TTF_CloseFont(m_font);
	  TTF_Quit();
	}

	/**
	 * Initialisation du TextRenderer
	 * @param fontName
	 *      Le chemin d'acces de la police
	 * @param color
	 *      La couleur a utiliser pour faire le rendu du texte
	 * @param size
	 *      La taille du texte
	 **/
	void TextRenderer::init(std::string fontName, SDL_Color color, int size) throw (DisplayTextRenderingException)
	{
	  TTF_Init();
	  m_font = TTF_OpenFont(fontName.c_str(), size);
	  if(m_font == NULL)
	  {
		std::string message ("TTF Internal error ");
		throw DisplayTextRenderingException(message + TTF_GetError());
	  }
	  m_color = color;
	  ErrorPrinter::printDisplayDebug("Initialized text renderer!");
	}

	/**
	 * Effectue le rendu d'une chaine de caractere dans la memoire video
	 * @see SDLRPG_TextRenderer#renderText()
	 **/
	SDL_Surface* TextRenderer::renderText(std::string text) throw (DisplayTextRenderingException)
	{
	  return renderText(text, m_font, m_color);
	}

	SDL_Surface* TextRenderer::renderText(std::string text, SDL_Color color) throw (DisplayTextRenderingException)
	{
	    return renderText(text, m_font, color);
	}

	SDL_Surface* TextRenderer::renderText(std::string text, TTF_Font* font) throw (DisplayTextRenderingException)
	{
	  return renderText(text, font, m_color);
	}

	SDL_Surface* TextRenderer::renderText(std::string text, TTF_Font* font, SDL_Color color) throw (DisplayTextRenderingException)
	{
	  if(text.empty())
		throw DisplayTextRenderingException("Trying to render an empty string");
	  ErrorPrinter::printDisplayDebug((std::string) "Rendering text : " + text);
	  return TTF_RenderText_Blended(font, text.c_str(), color);
	}
}
