#include <windows.h>
#include <CppUnitTest.h>

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <regex>

#include <alby.mylibrary/alby.myclass.h>
#include "helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
// install: 
//   get-package
//   uninstall-package alby.mylibrary
//   install-package alby.mylibrary -source "github"
//
// upgrade: 
//   update-package alby.mylibrary -source "github"
//   or
//   msbuild build.proj /t:upgrade
//


namespace mytest
{
	TEST_CLASS(mytest)
	{
	public:
		
        TEST_METHOD( TestFolder )
        {
            auto dir = std::filesystem::current_path() ;

            Logger::WriteMessage( dir.c_str() );
        }

        TEST_METHOD( BinFolder )
        {
            std::string folder = R"(.)" ;

            for ( auto& p : std::filesystem::recursive_directory_iterator( folder ) )
            {
                auto file = p.path() ;
                Logger::WriteMessage( file.c_str() ) ;
            }
        }

        TEST_METHOD( PackagesFolder )
        {
            std::string folder = R"(..\..\packages)" ;

            for ( auto& p : std::filesystem::recursive_directory_iterator( folder ) )
            {
                auto file = p.path() ;
                Logger::WriteMessage( file.c_str() ) ;
            }
        }

        TEST_METHOD( SolutionFolder )
        {
            std::string folder = R"(..\..\..\sln)";

            for ( auto& p : std::filesystem::recursive_directory_iterator(folder) )
            {
                auto file = p.path();
                Logger::WriteMessage(file.c_str());
            }
        }

        TEST_METHOD( FindVersionFile )
        {
            std::string folder = R"(..\..\..)" ;
            std::string file   = "alby.mylibrary.version.txt" ;

            auto result = helper::findFile( folder, file ) ;

            Logger::WriteMessage( result.c_str() ) ;

            // ..\..\..\sln\mytest\bin\alby.mylibrary.version.txt 

            std::regex regex( R"((.*)\\bin\\alby\.mylibrary\.version\.txt$)" ) ;

            Assert::IsTrue( std::regex_match( result, regex ) ) ;
        }

        TEST_METHOD( FindVersionFiles )
        {
            // ..\..\..\sln\mytest\bin\alby.mylibrary.version.txt
            // ..\..\..\sln\packages\alby.mylibrary.1.0.3\build\alby.mylibrary.version.txt

            std::regex regex1( R"((.*)\\bin\\alby\.mylibrary\.version\.txt$)"            ) ;
            std::regex regex2( R"((.*)\\packages\\(.*)\\alby\.mylibrary\.version\.txt$)" ) ;

            std::string folder = R"(..\..\..)" ;
            std::string file   = "alby.mylibrary.version.txt" ;

            auto list = helper::findFiles( folder, file ) ;

            for ( auto& f : list )
                  Logger::WriteMessage( f.c_str() ) ;

            auto result1 = std::find_if( list.begin(),
                                         list.end(),
                                         [ &regex1 ] ( const auto& f )
                                         {
                                            return std::regex_match( f, regex1 ) ;
                                         } ) ;

            auto result2 = std::find_if( list.begin(),
                                         list.end(),
                                         [ &regex2 ] ( const auto& f )
                                         {
                                            return std::regex_match( f, regex2 ) ;
                                         } ) ;

            Assert::IsTrue( result1 != list.end() ) ;
            Assert::IsTrue( result2 != list.end() ) ;

            Logger::WriteMessage( result1->c_str() ) ;
            Logger::WriteMessage( result2->c_str() ) ;
        }

        TEST_METHOD( VersionFile )
        {
            auto file = R"(.\alby.mylibrary.version.txt)" ;

            auto txt  = helper::slurp( file ) ;
            txt = std::string( "#" ) + txt + std::string( "#" ) ;

            Logger::WriteMessage( txt.c_str() ) ;
        }

        TEST_METHOD( LibraryVersion )
        {
            auto file = R"(.\alby.mylibrary.version.txt)" ;
            auto expectedVersion = helper::slurp( file ) + ".0" ;

            alby::mylibrary::myclass m ;

            auto actualVersion = m.version()  ;

            Logger::WriteMessage( expectedVersion.c_str() ) ;
            Logger::WriteMessage( actualVersion.c_str()   ) ;

            Assert::AreEqual( expectedVersion, actualVersion ) ;
        }

	} ;
}

