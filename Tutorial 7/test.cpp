#include "catch.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

extern "C"
{
#include "copy.h"
}

using namespace std;
string readFile(string path)
{
    ostringstream buf;
    ifstream input(path.c_str());
    buf << input.rdbuf();
    return buf.str();
}

TEST_CASE("test", "[weight=1][part=test]")
{
    int success = copy("original.txt", "copied.txt");
    REQUIRE(success == 1);

    string original = readFile("original.txt");
    string copied = readFile("copied.txt");
    remove("copied.txt");

    // The original file should not be modified
    REQUIRE(original == "some very interesting text here.");

    // The new file should have the same content
    REQUIRE(copied == "some very interesting text here.");
}

TEST_CASE("testBad", "[weight=1][part=test]")
{
    // Copy an existing file should fail
    int success = copy("does_not_exist", "destination");
    REQUIRE(success == 0);
};