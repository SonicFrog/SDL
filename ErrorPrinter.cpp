#include "ErrorPrinter.hpp"
#include "DisplayEngine.hpp"

namespace SDLRPG
{
	void ErrorPrinter::printDisplayEngine()
	{
		std::cerr << SDLRPG_DISPLAY_ENGINE_NAME << " " << SDLRPG_DISPLAY_ENGINE_VERSION;
	}

	void ErrorPrinter::printGameEngine()
	{
		std::cerr << SDLRPG_GAME_ENGINE_NAME << " " << SDLRPG_GAME_ENGINE_VERSION;
	}

	void ErrorPrinter::printDisplayError(std::string message)
	{
		printDisplayEngine();
		std::cerr << " error : " << message << std::endl;
	}

	void ErrorPrinter::printInternalError(std::string message)
	{
		std::cerr << " error : " << message << std::endl;
	}

	void ErrorPrinter::printUnknownError(std::string message)
	{
		std::cerr << "Unknown error : " << message << std::endl;
	}

	void ErrorPrinter::printDisplayWarning(std::string message)
	{
		printDisplayEngine();
		std::cerr << " warning : " << message << std::endl;
	}

	void ErrorPrinter::printInternalWarning(std::string message)
	{
		printGameEngine();
		std::cerr << " warning : " << message << std::endl;
	}

	void ErrorPrinter::printDisplayDebug(std::string message)
	{
		#ifdef DEF_SDLRPG_DEBUG_PRINT
		printDisplayEngine();
		std::cerr << " debug : " << message << std::endl;
		#endif
	}

	void ErrorPrinter::printInternalDebug(std::string message)
	{
		#ifdef DEF_SDLRPG_DEBUG_PRINT
		printGameEngine();
		std::cerr << " debug : " << message << std::endl;
		#endif
	}
}
