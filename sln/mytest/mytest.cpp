#include <windows.h>
#include <CppUnitTest.h>

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <regex>

#include "helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
// get-package
// uninstall-package alby.mylibrary
// install-package alby.mylibrary -source "github"
// update-package alby.mylibrary -source "github"
//

#include <alby.mylibrary/alby.myclass.h>

namespace mytest
{
	TEST_CLASS(mytest)
	{
	public:
		
        TEST_METHOD(CurrentFolder)
        {
            auto dir = std::filesystem::current_path() ;

            Logger::WriteMessage( dir.c_str() );
        }

        TEST_METHOD(FindFile)
        {
            std::string folder = R"(..\..\packages)" ;
            std::string file   = "alby.mylibrary.version.txt" ;

            auto result = helper::findFile( folder, file ) ;

            Logger::WriteMessage( result.c_str() ) ;

            //..\..\packages\alby.mylibrary.1.0.3\build\alby.mylibrary.version.txt

//ALBy fix me
            std::regex regex( R"(\\packages\\alby.mylibrary(.*)\\build\\alby.mylibrary.version.txt)" )   ;

            Assert::IsTrue( std::regex_match( result, regex ) ) ;
        }

        TEST_METHOD(PackagesFiles2)
        {
            auto folder = R"(..\..\packages)" ; // R"(..\packages)" ;

            //for ( auto& p : std::filesystem::recursive_directory_iterator(folder) )
            //{
            //    auto file = p.path() ;
            //    Logger::WriteMessage( file.c_str() ) ;
            //}

            std::string file = "alby.mylibrary.version.txt" ;

            auto file2 = std::regex_replace( file, std::regex( R"(\.)" ), R"(\.)" ) ;

            std::string target = "(.*)" + file2 + "$" ;

            Logger::WriteMessage( target.c_str() ) ;


            std::regex regex( target )   ;
            //std::regex regex( R"((.*)version\.txt$)" )   ;

            auto it = std::filesystem::recursive_directory_iterator(folder) ;

            auto result = std::find_if( std::filesystem::begin( it ),
                                        std::filesystem::end( it ),
                                        [ &regex] ( auto& x )
                                        {
                                            Logger::WriteMessage( x.path().c_str() ) ;
                                            //std::string str =  ;
                                            return std::regex_match( x.path().string(), regex ) ;
                                        } ) ;

            Logger::WriteMessage( "RESULT" ) ;
            if ( result != std::filesystem::end( it ) )
                 Logger::WriteMessage( result->path().c_str() ) ;
            else
                 Logger::WriteMessage( "NULL" ) ;

            //auto it = std::filesystem::recursive_directory_iterator( folder ) ;

            //while (true)
            //{
            //    auto file = it.path() ;
            //    Logger::WriteMessage( file.c_str() ) ;

            //    it++ ;
            //}




        }

        TEST_METHOD(ReadFile)
        {
            auto file = R"(..\..\..\nupkg\alby.mylibrary.version.txt)" ;

            auto txt  = helper::slurp( file ) ;
            txt = std::string( "#" ) + txt + std::string( "#" ) ;

            Logger::WriteMessage( txt.c_str() ) ;
        }

        TEST_METHOD(NugetPackageVersionTest)
        {
            auto file = R"(..\..\..\nupkg\alby.mylibrary.version.txt)" ;
            auto expectedVersion = helper::slurp( file ) ;

            alby::mylibrary::myclass m ;

            auto actualVersion = m.version() ;

            Logger::WriteMessage( expectedVersion.c_str() ) ;
            Logger::WriteMessage( actualVersion.c_str()   ) ;

            Assert::AreEqual( expectedVersion, actualVersion ) ;
        }

	} ;
}

