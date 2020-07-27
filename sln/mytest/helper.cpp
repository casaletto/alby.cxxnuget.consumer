#include <windows.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <regex>

#include "helper.h"

namespace mytest
{
    std::string helper::trim( const std::string& str )
    {
        auto str2 = str;

        str2.erase(
            str2.begin(),
            std::find_if(
                str2.begin(),
                str2.end(),
                [](int ch)
                {
                    return !std::isspace(ch);
                }));


        str2.erase(
            std::find_if(
                str2.rbegin(),
                str2.rend(),
                [](int ch)
                {
                    return !std::isspace(ch);
                }).base(),
            str2.end() );

        return str2;
    }

    std::string helper::slurp( const std::string& file )
    {
        std::ifstream      instream(file);
        std::ostringstream ss;

        ss << instream.rdbuf() ;

        return trim( ss.str() ) ;
    }

    std::string helper::findFile( const std::string& folder, const std::string& file )
    {
        auto pattern = std::regex_replace( file, std::regex( R"(\.)" ), R"(\.)" ) ;
        auto target  = "(.*)" + pattern + "$" ;

        std::regex regex( target )   ;

        auto it    = std::filesystem::recursive_directory_iterator( folder ) ;
        auto itend = std::filesystem::end(it) ;

        auto result = std::find_if(
                            std::filesystem::begin( it ),
                            itend,
                            [ &regex ] ( auto& x )
                            {
                                return std::regex_match(
                                            x.path().string(),
                                            regex ) ;
                            } ) ;

        if ( result == itend )
             return "" ;

        return result->path().string() ;
    }

    std::vector<std::string> helper::findFiles( const std::string& folder, const std::string& file )
    {
        auto pattern = std::regex_replace( file, std::regex( R"(\.)" ), R"(\.)" ) ;
        auto target  = "(.*)" + pattern + "$" ;

        std::regex regex( target ) ;

        std::vector<std::string> list ;

        for ( auto& p : std::filesystem::recursive_directory_iterator(folder ) )
        {
            auto file = p.path() ;

            if ( std::regex_match( p.path().string(), regex ) )
                 list.push_back( p.path().string() ) ;
        }

        return list ;
    }

}

