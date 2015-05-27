#include "ConfigurationManager.hpp"
#include "DisplayExceptions.hpp"
#include "ErrorPrinter.hpp"
#include "Tools.hpp"

namespace SDLRPG
{
    ConfigurationManager::ConfigurationManager() throw (ParseException) : m_config()
    {
        m_filename = SDLRPG_DEFAULT_CONFIG_FILE;
        m_config.readFile(SDLRPG_DEFAULT_CONFIG_FILE);
    }

    ConfigurationManager::ConfigurationManager(const std::string &filename) throw (ParseException): m_config()
    {
        m_filename = filename;
        m_config.readFile(filename.c_str());
    }

    std::vector<std::string> &ConfigurationManager::getConfigVector(const std::string &key) throw(IOException)
    {
        Setting &out = m_config.lookup(key);
        std::string buffer;
        if(out.getLength() == 0)
            throw IOException(Formatter() << key << " is not a group in " << m_filename);
        m_lastList.clear();
        for(int i = 0 ; i < out.getLength() ; i++)
        {
            buffer = out[i].c_str();
            m_lastList.insert(m_lastList.end(), buffer);
        }
        return m_lastList;
    }

    std::string ConfigurationManager::getConfigKey(const std::string &key) const
    {
        std::string out;
        if(!m_config.lookupValue(key, out))
        {
            throw ConfigKeyNotFoundException(Formatter() << "The key " << key << " was not found in " << m_filename);
        }
        return out;
    }

    bool ConfigurationManager::hasConfigKey(const std::string &key) const
    {
        std::string dummy;
        return m_config.lookupValue(key, dummy);
    }

    void ConfigurationManager::writeConfigKey(const std::string &key, const std::string &value)
    {
        std::string buffer;
        int lastDot = key.find_last_of('.');
        Setting &node = m_config.lookup(key.substr(0, lastDot));
        if(!node.lookupValue(key.substr(lastDot, lastDot - key.length()), buffer))
        {
            ErrorPrinter::printInternalDebug(Formatter() << key << " does not exist in " << m_filename);
            Setting& added = node.add(key.substr(lastDot, lastDot - key.length()), Setting::Type::TypeString);
            added = value;
        }
        Setting& added = m_config.lookup(key);
        added = value;
    }

    ConfigurationManager::~ConfigurationManager()
    {
        ErrorPrinter::printInternalDebug(Formatter() << "Writing config file to " << m_filename);
        m_config.writeFile(m_filename.c_str());
    }
}
