#ifndef DEF_ERROR_PRINTER_H
#define DEF_ERROR_PRINTER_H

#include <string>

#define SDLRPG_DISPLAY_ERROR_MESSAGE
#define SDLRPG_INTERNAL_ERROR_MESSAGE
#define SDLRPG_UNKNOWN_ERROR_MESSAGE

#define SDLRPG_GAME_ENGINE_NAME         "SDLRPG Meka"
#define SDLRPG_GAME_ENGINE_VERSION      "0.1"

namespace SDLRPG
{
    class ErrorPrinter
    {
        public :
            static void printDisplayError(std::string message);
            static void printInternalError(std::string message);
            static void printUnknownError(std::string message);
            static void printDisplayWarning(std::string message);
            static void printInternalWarning(std::string message);
            static void printInternalDebug(std::string message);
            static void printDisplayDebug(std::string message);

        protected :
            static void printDisplayEngine();
            static void printGameEngine();
    };
}
#endif
