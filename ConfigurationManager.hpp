#ifndef DEF_CONFIGURATION_MANAGER
#define DEF_CONFIGURATION_MANAGER

#include <string>
#include <vector>
#include <libconfig.h++>

#include "DisplayExceptions.hpp"

using namespace libconfig;

#define SDLRPG_DEFAULT_CONFIG_FILE  "default.cfg"
#define SDLRPG_WINDOW_KEY           "SDLRPG.window"
#define SDLRPG_WIN_HEIGHT_KEY       SDLRPG_WINDOW_KEY << ".size.h"
#define SDLRPG_WIN_WIDTH_KEY        SDLRPG_WINDOW_KEY << "size.w"

namespace SDLRPG
{
    class ConfigurationManager
    {
        public :
            std::vector<std::string> &getConfigVector(const std::string &key) throw(IOException);
            std::string getConfigKey(const std::string &key) const;
            bool hasConfigKey(const std::string &key) const;
            void writeConfigKey(const std::string &key ,const std::string &value);

            ConfigurationManager() throw (ParseException);
            ConfigurationManager(const std::string &filename) throw (ParseException);
            ~ConfigurationManager();

        protected :
            Config m_config;
            std::string m_filename;
            std::vector<std::string> m_lastList;
    };
}
#endif
