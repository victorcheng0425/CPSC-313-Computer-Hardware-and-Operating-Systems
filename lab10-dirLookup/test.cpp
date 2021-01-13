#include "catch.hpp"
extern "C"
{
#include "dirLookup.h"
}

TEST_CASE("test1", "[weight=1][part=test]")
{
    REQUIRE(dirLookup("tests/test1.out", "file_23945") == 13);
    REQUIRE(dirLookup("tests/test1.out", "dir_25792") == 14);
    REQUIRE(dirLookup("tests/test1.out", "link_to_dir_25792") == 15);
    REQUIRE(dirLookup("tests/test1.out", "file_20121") == 55);
    REQUIRE(dirLookup("tests/test1.out", "bad_component") == BAD_DIR_ENTRY_INODE_NUMBER);
}

TEST_CASE("test2", "[weight=1][part=test]")
{
    REQUIRE(dirLookup("tests/test2.out", "file_6738") == 13);
    REQUIRE(dirLookup("tests/test2.out", "link_to_dir_31455") == 16);
    REQUIRE(dirLookup("tests/test2.out", "dir_21860") == 29);
    REQUIRE(dirLookup("tests/test2.out", "file_27306") == 48);
    REQUIRE(dirLookup("tests/test2.out", "bad_component") == BAD_DIR_ENTRY_INODE_NUMBER);
}

TEST_CASE("test3", "[weight=1][part=test]")
{
    REQUIRE(dirLookup("tests/test3.out", "file_10765") == 29);
    REQUIRE(dirLookup("tests/test3.out", "link_to_file_10765") == 30);
    REQUIRE(dirLookup("tests/test3.out", "file_698") == 31);
    REQUIRE(dirLookup("tests/test3.out", "link_to_file_698") == 32);
    REQUIRE(dirLookup("tests/test3.out", "bad_component") == BAD_DIR_ENTRY_INODE_NUMBER);
}