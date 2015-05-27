/*
 * Tools.hpp
 *
 *  Created on: Dec 8, 2012
 *      Author: ars3nic
 */

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <iostream>
#include <sstream>

namespace SDLRPG
{
	class Formatter
	{
		private :
			std::stringstream m_sbuf;

		public :
			template<class T> Formatter& operator<< (const T& value)
			{
				m_sbuf << value;
				return *this;
			}
			operator std::string () const { return m_sbuf.str().c_str(); }
	};
}

#endif /* TOOLS_HPP_ */
