# alby.cxxnuget.consumer


![](https://github.com/casaletto/alby.cxxnuget.consumer/workflows/.github/workflows/main.yml/badge.svg)


This repo just is a very simple C++ unit test dll that consumes a C++ static library, alby.cxxnuget, which is versioned and packaged as a github nuget package.


The only useful function of the library is myclass::version() 


```
#include <alby.mylibrary/alby.myclass.h>

auto version = alby::mylibrary::myclass::version() ;
```


Command line build


```
msbuild sln\build.proj /t:clean,source,restore,upgrade,build,test "/p:SourceKey=xxx" "/p:SourceUser=xxx"
```
