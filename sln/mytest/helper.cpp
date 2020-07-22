#include <windows.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm> 
#include <cctype>
#include <locale>

#include "helper.h"

namespace mytest
{
    std::string helper::trim( const std::string& str )
    {
        auto str2 = str;

        str2.erase(
            str2.begin(),
            std::find_if(str2.begin(), str2.end(), [](int ch)
        {
            return !std::isspace(ch);
        }));


        str2.erase(
            std::find_if(str2.rbegin(), str2.rend(), [](int ch)
        {
            return !std::isspace(ch);
        }).base(),
            str2.end());

        return str2;
    }

    std::string helper::slurp( const std::string& file )
    {
        std::ifstream      instream(file);
        std::ostringstream ss;

        ss << instream.rdbuf();
        return trim(ss.str());
    }
}

