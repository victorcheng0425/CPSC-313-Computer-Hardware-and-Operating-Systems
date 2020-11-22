#include "catch.hpp"
#include <string>
extern "C"
{
#include "parsePath.h"
}

using namespace std;

void equals(char *actual, string expected)
{
    REQUIRE(!!actual); // not null
    REQUIRE(string(actual) == expected);
}

TEST_CASE("test1", "[weight=1][part=test]")
{
    char absolutePath[] = "/this/is/an/absolute/path";
    equals(parsePath(absolutePath), "/");
    equals(parsePath(NULL), "this");
    equals(parsePath(NULL), "is");
    equals(parsePath(NULL), "an");
    equals(parsePath(NULL), "absolute");
    equals(parsePath(NULL), "path");
    REQUIRE(parsePath(NULL) == NULL);
}

TEST_CASE("test2", "[weight=1][part=test]")
{
    char relativePath[] = "this/is/a/relative/path";
    equals(parsePath(relativePath), "this");
    equals(parsePath(NULL), "is");
    equals(parsePath(NULL), "a");
    equals(parsePath(NULL), "relative");
    equals(parsePath(NULL), "path");
    REQUIRE(parsePath(NULL) == NULL);
}

TEST_CASE("test3", "[weight=1][part=test]")
{
    char pathWithDoubleSlash[] = "a//b";
    equals(parsePath(pathWithDoubleSlash), "a");
    equals(parsePath(NULL), "b");
    REQUIRE(parsePath(NULL) == NULL);
}

TEST_CASE("test4", "[weight=1][part=test]")
{
    char dotPath[] = "./myprog";
    equals(parsePath(dotPath), ".");
    equals(parsePath(NULL), "myprog");
    REQUIRE(parsePath(NULL) == NULL);
}

TEST_CASE("test5", "[weight=1][part=test]")
{
    char dotDotPath[] = "down/../down";
    equals(parsePath(dotDotPath), "down");
    equals(parsePath(NULL), "..");
    equals(parsePath(NULL), "down");
    REQUIRE(parsePath(NULL) == NULL);
}

TEST_CASE("test6", "[weight=1][part=test]")
{
    char dotDotPath[] = "/MAW.g_/WtHar2j/IKLM/wz_147AC/ortx/CBFIMOR/XZZadg/LO/";
    char *dir = parsePath(dotDotPath);
    equals(dir, "/");
    dir[0] = 'x';
    equals(dir, "x");
    equals(parsePath(NULL), "MAW.g_");
    equals(parsePath(NULL), "WtHar2j");
    equals(parsePath(NULL), "IKLM");
    equals(parsePath(NULL), "wz_147AC");
    equals(parsePath(NULL), "ortx");
    equals(parsePath(NULL), "CBFIMOR");
    equals(parsePath(NULL), "XZZadg");
    equals(parsePath(NULL), "LO");
    REQUIRE(parsePath(NULL) == NULL);
}

TEST_CASE("test7", "[weight=1][part=test]")
{
    char dotDotPath[] = "/MAW.g_/WtHar2j/IKLM/wz_147AC/ortx/CBFIMOR/XZZadg/LO/";
    char *dir = parsePath(dotDotPath);
    equals(dir, "/");
    dir[0] = 'x';
    equals(dir, "x");
    equals(parsePath(NULL), "MAW.g_");
    equals(parsePath(NULL), "WtHar2j");
    equals(parsePath(NULL), "IKLM");
    equals(parsePath(NULL), "wz_147AC");
    equals(parsePath(NULL), "ortx");
    equals(parsePath(NULL), "CBFIMOR");
    equals(parsePath(NULL), "XZZadg");
    equals(parsePath(NULL), "LO");
    REQUIRE(parsePath(NULL) == NULL);
}
