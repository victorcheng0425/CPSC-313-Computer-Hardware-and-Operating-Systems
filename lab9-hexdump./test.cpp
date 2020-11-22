#include "catch.hpp"
#include <fstream>
#include <sstream>
#include <string>

extern "C"
{
#include "hexdump.h"
}

using namespace std;
string readFile(string path)
{
    ostringstream buf;
    ifstream input(path.c_str());
    buf << input.rdbuf();
    return buf.str();
}

TEST_CASE("binary_1", "[weight=1][part=test]")
{
    int success = hexdump("test-files/binary_1", "output/binary_1_actual.txt");
    REQUIRE(success == 1);
    string actual = readFile("output/binary_1_actual.txt");
    string expected = readFile("test-files/binary_1_expected.txt");
    REQUIRE(actual == expected);
}

TEST_CASE("binary_2", "[weight=1][part=test]")
{
    int success = hexdump("test-files/binary_2", "output/binary_2_actual.txt");
    REQUIRE(success == 1);
    string actual = readFile("output/binary_2_actual.txt");
    string expected = readFile("test-files/binary_2_expected.txt");
    REQUIRE(actual == expected);
}

TEST_CASE("binary_3", "[weight=1][part=test]")
{
    int success = hexdump("test-files/binary_3", "output/binary_3_actual.txt");
    REQUIRE(success == 1);
    string actual = readFile("output/binary_3_actual.txt");
    string expected = readFile("test-files/binary_3_expected.txt");
    REQUIRE(actual == expected);
}

TEST_CASE("should_fail", "[weight=1][part=test]")
{
    int success = hexdump("does_not_exist", "does_not_exist.txt");
    REQUIRE(success == 0);
}

