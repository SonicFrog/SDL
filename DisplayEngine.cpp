#include <iostream>
#include "DisplayEngine.hpp"
#include "ErrorPrinter.hpp"
#include "Tools.hpp"

namespace SDLRPG
{
    /**
     * Constructeur par défaut du DisplayEngine
     **/
    DisplayEngine::DisplayEngine()
    {
        init(SDLRPG_DEFAULT_FLAGS);
        loadScreen(SDLRPG_DEFAULT_WIDTH, SDLRPG_DEFAULT_HEIGHT, SDLRPG_DEFAULT_COLOR, SDLRPG_DEFAULT_SCREEN_FLAGS);
    }

    /**
     * Constructeur avec paramètres pour initialiser certains sous systèmes de la SDL
     *
     * @param flags
     *      Un entier 32 bits contenant les flags d'initialisation
     **/
    DisplayEngine::DisplayEngine(Uint32 flags)
    {
        init(flags);
        loadScreen(SDLRPG_DEFAULT_WIDTH, SDLRPG_DEFAULT_HEIGHT,
                   SDLRPG_DEFAULT_COLOR, SDLRPG_DEFAULT_SCREEN_FLAGS);
    }

    /**
     * Constructeur avec paramètres pour initialiser certains sous systèmes SDL
     * et permettant de choisir les paramètres graphiques
     * @param flags
     *      Entier 32 bits contenant les flags SDL
     * @param width
     *      Largeur de la fenêtre SDL
     * @param height
     *      Hauteur de la fenêtre SDL
     * @param bit
     *      Profondeur de la couleur
     * @param screenFlags
     *      Flags pour le rendu de l'écran (Double buffering, HW ou SW rendering, Fullscreen, etc ...)
     **/
    DisplayEngine::DisplayEngine(Uint32 flags, int width, int height, int bit,
                                 Uint32 screenFlags)
    {
        init(flags);
        loadScreen(width, height, bit, screenFlags);
    }

    /**
     * Initialise la SDL
     * @param flags
     *      Flags d'initialisation SDL
     */
    void DisplayEngine::init(Uint32 flags) throw (DisplayInitException)
    {
        ErrorPrinter::printDisplayDebug(Formatter() << "Compiled against libSDL " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL);
        ErrorPrinter::printDisplayDebug(Formatter() << "Compiled against libSDL_image " << SDL_IMAGE_MAJOR_VERSION <<  "." << SDL_IMAGE_MINOR_VERSION << "." << SDL_IMAGE_PATCHLEVEL);
        ErrorPrinter::printDisplayDebug("Initializing display engine ..");
        m_version = SDLRPG_DISPLAY_ENGINE_NAME " " SDLRPG_DISPLAY_ENGINE_VERSION;
        m_background = NULL;
        m_LastID = 0;
        if(SDL_Init(flags) < 0)
        {
            throw DisplayInitException(SDL_GetError());
        }
        m_renderer = new TextRenderer();
    }

    /**
     * Charge le mode vidéo SDL
     * @param width
     *      Largeur de la fenêtre
     * @param height
     *      Hauteur de la fenêtre
     * @param bit
     *      Profondeur de la couleur
     * @param flags
     *      Flags SDL
     **/
    void DisplayEngine::loadScreen(int width, int height, int bit, Uint32 flags)
        throw (DisplayInitException)
    {
        SDL_WM_SetIcon(IMG_Load(SDLRPG_DISPLAY_ENGINE_ICON), NULL);
        m_screen = SDL_SetVideoMode(width, height, bit, flags);
        SDL_WM_SetCaption(getVersion().c_str(), NULL);
        m_size.x = width;
        m_size.y = height;

        if(m_screen == NULL)
        {
            throw DisplayInitException(Formatter() << "Unable to load video mode : " << SDL_GetError());
        }
    }

    /**
     * Enregistre une entité dans le moteur d'affichage
     * @param entity
     *      Pointeur vers l'entité à enregistrer
     **/
    ScreenEntityID DisplayEngine::registerEntity(ScreenEntity* entity)
    {
        if(entity == NULL || entity->getTexture() == NULL)
        {
            ErrorPrinter::printDisplayError("Loading invalid entity into display engine (NULL)");
            throw DisplayEntityNotFoundException("Loading NULL entity");
        }
        m_EntityList.insert(std::pair<int, ScreenEntity*>(m_LastID++, entity));
        ErrorPrinter::printDisplayDebug("Registered entity.");
        return m_LastID - 1;
    }

    bool DisplayEngine::hasAcceleration() const
    {
        const SDL_VideoInfo* info = SDL_GetVideoInfo();
        return info->blit_fill && info->blit_hw && info->blit_sw && (info->hw_available > 0);
    }

    /**
     * Definit le fond du moteur de rendu
     * @param texture
     *      La texture du fond
     **/
    void DisplayEngine::setBackground(ScreenEntity* bTexture)
    {
        if(bTexture == NULL)
        {
            throw DisplayEntityNotFoundException("Setting a NULL background texture");
        }
        m_background = bTexture;
    }

    /**
     * Dessine une entité sur l'écran
     * @param id
     *      L'id de l'entité à dessiner
     * @param x
     *      La position abscisse où dessiner l'entité
     * @param y
     *      La position ordonnée où dessiner l'entité
     **/
    void DisplayEngine::drawEntity(ScreenEntityID id, int x, int y)
    {
        drawEntity(id, x, y, true);
    }

    /**
     *
     */
    void DisplayEngine::drawEntity(ScreenEntityID id, int x, int y, bool center)
    {
        if(m_EntityList.count(id) < 1)
            throw DisplayEntityNotFoundException(Formatter() << "Entity " <<
                                                 id << " was not found!");
        ScreenEntity* ent = m_EntityList[id];
        if(center) {
            x -= ent->getWidth() / 2;
            y -= ent->getHeight() / 2;
            if(x < 0)
                x = 0;
            if(y < 0)
                y = 0;
        }
        ent->setX(x);
        ent->setY(y);
        m_ScreenList.insert(std::pair<int, ScreenEntity*>(id, ent));
    }

    /**
     * Deplace l'entite selectionne de xmove pixels sur x et ymove pixels sur y
     * @param id
     *      L'id de l'entite a selectionner
     * @param xmove
     *      Le nombre de pixels de deplacement horizontal
     * @param ymove
     *      Le nombre de pixels deplacement vertical
     **/
    void DisplayEngine::moveEntity(ScreenEntityID id, int xmove, int ymove)
    {
        if(m_ScreenList.count(id) < 1)
        {
            throw DisplayEntityNotFoundException("Tried to move a non-existent entity on screen");
        }
        ScreenEntity* entity = m_ScreenList[id];
        int x, y;

        x = entity->getX() + xmove;
        y = entity->getY() + ymove;
        if(x < 0 || x > m_screen->w || y < 0 || y > m_screen->h)
        {
            ErrorPrinter::printDisplayWarning(Formatter() << "Drawing entity out of displayed screen area (" << x << ", " << y <<")");
#ifdef DEF_SDLRPG_DEBUG
            throw DisplayInvalidCoordinatesException(Formatter() << "(" << x << ", " << y << ")");
#endif
        }
        entity->setX(x);
        entity->setY(y);
    }

    /**
     * Actualise l'affichage
     **/
    void DisplayEngine::updateScreen()
    {
        clearScreen();
        blitSurfaces();
        SDL_Flip(m_screen);
        ErrorPrinter::printDisplayDebug("Screen updated!");
    }

    /**
     * Enlève une entité de l'écran
     * @param entityID
     *      L'id de l'entité à enlever
     **/
    void DisplayEngine::eraseEntity(ScreenEntityID id)
    {
        if(m_ScreenList.count(id) < 1)
        {
            ErrorPrinter::printDisplayWarning(Formatter() <<
                                              "Erasing unknown entity (ID = " <<
                                              id << ") from screen");
            return;
        }
        m_ScreenList.erase(id);
    }

    /**
     * Effectue le rendu du texte en mémoire et construit une entité graphique avec ce texte
     */
    ScreenEntityID DisplayEngine::renderText(std::string text)
    {
        SDL_Surface* text_s = m_renderer->renderText(text);
        ScreenEntity* entity = new ScreenEntity(text_s);
        return registerEntity(entity);
    }

    ScreenEntityID DisplayEngine::renderText(std::string text, SDL_Color color)
    {
        SDL_Surface* text_s = m_renderer->renderText(text, color);
        ScreenEntity* entity = new ScreenEntity(text_s);
        return registerEntity(entity);
    }

    /**
     * Retourne la version du DisplayEngine
     * @return
     *      La version du moteur chargé en mémoire
     **/
    std::string DisplayEngine::getVersion() const
    {
        return m_version;
    }

    void DisplayEngine::saveEngineState()
    {
        std::map<int, ScreenEntity*>::iterator iter;
        ErrorPrinter::printDisplayDebug("Saving engine state...");
        m_stateList.clear();
        m_ScreenList.swap(m_stateList);
        ErrorPrinter::printDisplayDebug(Formatter() << "Engine state saved ("
                                        << m_ScreenList.size() << ") !");
    }

    void DisplayEngine::restoreEngineState()
    {
        std::map<int, ScreenEntity*>::iterator iter;
        ErrorPrinter::printDisplayDebug("Restoring engine state ...");
        if(m_stateList.empty())
        {
            ErrorPrinter::printDisplayError("No state to restore engine to!");
            return;
        }
        m_stateList.swap(m_ScreenList);
        m_stateList.clear();
        ErrorPrinter::printDisplayDebug("Engine state restored");
    }

    void DisplayEngine::blitSurfaces()
    {
        std::map<int, ScreenEntity*>::iterator iter;
        SDL_Rect pos;
        SDL_Surface* surface;
        pos.x = 0;
        pos.y = 0;
        checkScreen();

        if(m_background != NULL)
        {
            ErrorPrinter::printDisplayDebug("Blitting background texture ...");
            m_background->blit(m_screen);
            ErrorPrinter::printDisplayDebug(Formatter() <<
                                            "Background blitted at (" << pos.x
                                            << ", " << pos.y << ") !");
        }

        if(m_ScreenList.empty())
            return;
        for(iter = m_ScreenList.begin() ; iter != m_ScreenList.end() ; ++iter)
        {
            surface = iter->second->getTexture();
            if(surface == NULL)
            {
                throw DisplayEntityNotFoundException("Entity with no texture was about to be drawn");
            }
            iter->second->blit(m_screen);
        }
    }

    /**
     * Nettoye l'écran en dessinant un rectangle blanc
     **/
    void DisplayEngine::clearScreen() throw (DisplayRenderingException)
    {
        checkScreen();
        ErrorPrinter::printDisplayDebug("Clearing screen ...");
        SDL_FillRect(m_screen, NULL, SDL_MapRGB(m_screen->format, 0, 0, 0));
        SDL_Flip(m_screen);
        ErrorPrinter::printDisplayDebug("Screen cleared !");
    }

    void DisplayEngine::checkScreen() const throw (DisplayRenderingException)
    {
        if(m_screen == NULL)
        {
            throw DisplayRenderingException("Screen is not loaded !");
        }
    }

    void DisplayEngine::resizeScreen(int w, int h) throw (DisplayRenderingException, DisplayInitException)
    {
        if(m_screen == NULL)
        {
            throw DisplayRenderingException("Can't resize the screen when it does not exist");
        }
        ErrorPrinter::printDisplayDebug(Formatter() <<
                                        "Setting screen size to " << w << "x"<< h);
        SDL_FreeSurface(m_screen);
        loadScreen(w, h, SDLRPG_DEFAULT_COLOR, SDLRPG_DEFAULT_SCREEN_FLAGS);
        m_size.x = w;
        m_size.y = h;
    }

    void DisplayEngine::printInfo() const
    {
        const SDL_VideoInfo* info = SDL_GetVideoInfo();
        char driver[1024];
        SDL_VideoDriverName(driver, 1024);
        ErrorPrinter::printDisplayDebug(Formatter() << "Driver : " << driver);
        ErrorPrinter::printDisplayDebug(Formatter() << "Memory Video available : " << info->video_mem << " kB");
        ErrorPrinter::printDisplayDebug(Formatter() << "Hardware -> hardware blits accelerated : " << ((info->blit_hw) ? "Yes" : "No"));
        ErrorPrinter::printDisplayDebug(Formatter() << "Software -> hardware blits accelerated : " << ((info->blit_sw) ? "Yes" : "No"));
        ErrorPrinter::printDisplayDebug(Formatter() << "Color fills accelerated : " << ((info->blit_fill) ? "Yes" : "No"));
    }

    int DisplayEngine::getWidth() const
    {
        checkScreen();
        return m_screen->w;
    }

    int DisplayEngine::getHeight() const
    {
        checkScreen();
        return m_screen->h;
    }

    SDL_PixelFormat *DisplayEngine::getFormat() const
    {
        return m_screen->format;
    }

    /**
     * Destructeur du DisplayEngine
     **/
    DisplayEngine::~DisplayEngine()
    {
        std::map<int, ScreenEntity*>::iterator iter;
        ErrorPrinter::printDisplayDebug(Formatter()
                                        << "Deallocating engine memory ... "
                                        << m_ScreenList.size());
        m_EntityList.clear();
        delete m_renderer;
        ErrorPrinter::printDisplayDebug("Engine closed !");
        SDL_Quit();
    }
}
