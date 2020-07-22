#include <windows.h>
#include <CppUnitTest.h>

#include <string>
#include <filesystem>

#include "helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
// get-package
// uninstall-package alby.mylibrary
// install-package alby.mylibrary -source "..\nupkg"
// update-package alby.mylibrary -source "..\nupkg"
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

