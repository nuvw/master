#ifndef UTILITY_CONSOLE_HPP
#define UTILITY_CONSOLE_HPP

#include <iostream>
#include <string>
#include <boost/format.hpp>

namespace utility
{
  namespace console
  {
    template <typename Format>
    void insert( Format& format )
    {

    }
 
    template <typename Format, typename Arg, typename ... Args>
    void insert( Format& format, Arg && arg, Args && ... args )
    {
      format % arg;
      insert( format, std::forward<Args>( args ) ... );
    }
     
    template <typename ... Args>
    void write_line( const std::string& str, Args && ... args )
    {
      auto format = boost::format( str );
      insert( format, std::forward<Args>( args ) ... );
      std::cout << format.str() << std::endl;
    }
  }
}

#endif

