#ifndef DEF_DISPLAY_EXCEPTIONS_H
#define DEF_DISPLAY_EXCEPTIONS_H

#include <exception>
#include <string>
namespace SDLRPG
{
    /**
     * Classe générique pour les exceptions de SDLRPG
     * @version 1.0
     * @author ars3nic
     **/
    class Exception : public std::exception
    {
        protected :
            int m_numero;
            std::string m_phrase;
            int m_niveau;

        public :
            Exception(int numero = 0, std::string const &message = "", int niveau = 1) throw()
            : m_numero(numero), m_phrase(message), m_niveau(niveau)
            {}

            virtual const char* what() const throw()
            {
                return m_phrase.c_str();
            }

            int getNiveau() const throw()
            {
                return m_niveau;
            }

            virtual ~Exception() throw()
            {}


    };

    class IOException : public Exception
    {
        public :
            IOException(std::string const &message) : Exception(2, message, 0) {}
    };

    class UnimplementedException : public Exception
    {
        public :
            UnimplementedException(std::string const &message) : Exception(1, message, 1) {}
    };

    /**
     * Exception lancée lors d'utilisation de coordonnées invalides
     **/
    class DisplayInvalidCoordinatesException : public Exception
    {
        public :
            DisplayInvalidCoordinatesException(std::string const &message) throw() : Exception(0, message, 1)
            {

            }
    };

    class ConfigKeyNotFoundException : public Exception
    {
        public :
            ConfigKeyNotFoundException(std::string const &message) throw() : Exception(2, message, 0) {}
    };

    /**
     * Exception lors d'une erreur d'initialisation
     **/
    class DisplayInitException : public Exception
    {
        public :
            DisplayInitException(std::string const &message) throw () : Exception(0, message, 0)
            {}
    };

    class DisplayRenderingException : public Exception
    {
        public :
            DisplayRenderingException(std::string const &message) throw() : Exception(0, message, 1)
            {}
    };

    class DisplayEntityNotFoundException : public Exception
    {
        public :
            DisplayEntityNotFoundException(std::string const &message) throw () : Exception(0, message, 0)
            {}
    };


    class DisplayTextRenderingException : public Exception
    {
      public :
          DisplayTextRenderingException(std::string const &message) throw() : Exception(0, message, 1)
          {}
    };

    class GameException : public Exception
    {
      public :
          GameException(std::string const& message) throw() : Exception(1, message, 1)
          {}
    };
}

#endif
