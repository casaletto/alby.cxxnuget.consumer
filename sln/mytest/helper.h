#pragma once

namespace mytest
{
    class helper
    {
    public:
        static std::string trim    ( const std::string& str  ) ;
        static std::string slurp   ( const std::string& file ) ;
        static std::string findFile( const std::string& folder, const std::string& pattern ) ;

    } ;
};


