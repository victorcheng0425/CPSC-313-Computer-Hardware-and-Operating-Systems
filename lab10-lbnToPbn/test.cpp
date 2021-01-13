#include "catch.hpp"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

extern "C"
{
#include "lbnToPbn.h"
}

#define TEST_BLOCK_SIZE 1024
#define VERY_LARGE_NUMBER 0xFFFFFFFF

static block_t valid_block = {1};

TEST_CASE("test_direct_block_pointers", "[weight=1][part=test]")
{
    // block_size
    uint32_t block_size = TEST_BLOCK_SIZE;

    // inode
    inode_t inode;
    inode.i_size = VERY_LARGE_NUMBER;
    inode.i_dir_acl = 0;

    for (uint32_t i = 0; i < 12; i++)
    {
        inode.i_block[i] = i + 0xFF;
    }

    // getBlock
    auto getBlock = [](uint32_t block_no) {
        return valid_block;
    };

    // test lbn -> pbn
    for (uint32_t lbn = 0; lbn < 12; lbn++)
    {
        uint32_t expected_pbn = lbn + 0xFF;
        uint32_t actual_pbn = lbnToPbn(&inode, lbn, block_size, getBlock);
        REQUIRE(actual_pbn == expected_pbn);
    }
}

TEST_CASE("test_indirect_block_pointer", "[weight=1][part=test]")
{
    // block_size
    uint32_t block_size = TEST_BLOCK_SIZE;

    // inode
    inode_t inode;
    inode.i_size = VERY_LARGE_NUMBER;
    inode.i_dir_acl = 0;

    // getBlock
    auto getBlock = [](uint32_t block_no) {
        block_t block = valid_block;
        uint32_t *pointers = (uint32_t *)&block.data;

        // fill the block with bad data
        for (uint32_t i = 0; i < TEST_BLOCK_SIZE / 4; i++)
        {
            pointers[i] = 0xBADBAD;
        }

        // if the input is good, fill the right index with the right data
        if (block_no == 0xFF)
        {
            pointers[25] = 0x100;
        }

        return block;
    };

    // notice how these numbers are similar to the ones in the definition of getBlock
    inode.i_block_1ind = 0xFF;
    uint32_t lbn = 12 + 25;
    uint32_t expected_pbn = 0x100;

    uint32_t actual_pbn = lbnToPbn(&inode, lbn, block_size, getBlock);
    REQUIRE(actual_pbn == expected_pbn);
}

TEST_CASE("test_double_indirect_block_pointer", "[weight=1][part=test]")
{
    // block_size
    uint32_t block_size = TEST_BLOCK_SIZE;

    // inode
    inode_t inode;
    inode.i_size = VERY_LARGE_NUMBER;
    inode.i_dir_acl = 0;

    // getBlock
    auto getBlock = [](uint32_t block_no) {
        block_t block = valid_block;
        uint32_t *pointers = (uint32_t *)&block.data;

        // fill the block with bad data
        for (uint32_t i = 0; i < TEST_BLOCK_SIZE / 4; i++)
        {
            pointers[i] = 0xBADBAD;
        }

        // if the input is good, fill the right index with the right data
        switch (block_no)
        {
        case 0xFF:
            pointers[25] = 0x100;
            break;
        case 0x100:
            pointers[26] = 0x102;
            break;
        }

        return block;
    };

    uint32_t num_pointers_per_block = TEST_BLOCK_SIZE / sizeof(uint32_t);

    // notice how these numbers are similar to the ones in the definition of getBlock
    inode.i_block_2ind = 0xFF;
    uint32_t lbn = 12 + 26 + num_pointers_per_block + 25 * num_pointers_per_block;
    uint32_t expected_pbn = 0x102;

    uint32_t actual_pbn = lbnToPbn(&inode, lbn, block_size, getBlock);
    REQUIRE(actual_pbn == expected_pbn);
}

TEST_CASE("test_triple_indirect_block_pointer", "[weight=1][part=test]")
{
    // block_size
    uint32_t block_size = TEST_BLOCK_SIZE;

    // inode
    inode_t inode;
    inode.i_size = VERY_LARGE_NUMBER;
    inode.i_dir_acl = 0;

    // getBlock
    auto getBlock = [](uint32_t block_no) {
        block_t block = valid_block;
        uint32_t *pointers = (uint32_t *)&block.data;

        // fill the block with bad data
        for (uint32_t i = 0; i < TEST_BLOCK_SIZE / 4; i++)
        {
            pointers[i] = 0xBADBAD;
        }

        // if the input is good, fill the right index with the right data
        switch (block_no)
        {
        case 0xFF:
            pointers[25] = 0x100;
            break;
        case 0x100:
            pointers[26] = 0x102;
            break;
        case 0x102:
            pointers[27] = 0x103;
            break;
        }

        return block;
    };

    uint32_t num_pointers_per_block = TEST_BLOCK_SIZE / sizeof(uint32_t);

    // notice how these numbers are similar to the ones in the definition of getBlock
    inode.i_block_3ind = 0xFF;

    uint32_t lbn = 12 + 27 +
                   num_pointers_per_block + 26 * num_pointers_per_block +
                   num_pointers_per_block * num_pointers_per_block + 25 * num_pointers_per_block * num_pointers_per_block;

    uint32_t expected_pbn = 0x103;

    uint32_t actual_pbn = lbnToPbn(&inode, lbn, block_size, getBlock);
    REQUIRE(actual_pbn == expected_pbn);
}

TEST_CASE("test_overflow", "[weight=1][part=test]"){
    // We have only used a block size of 1024 bytes so far
    // The ext2 file system supports block sizes of 1024, 2048, 4096, and 8192 bytes
    // Notably the 8192-byte block size may cause an overflow in your calculation.
    // Write your own test here.

    // block_size
    uint32_t block_size;

    // inode
    inode_t inode;
    
    // getBlock
    auto getBlock = [](uint32_t block_no) {
        return valid_block;
    };

    uint32_t lbn;
    uint32_t expected_pbn;
    // uint32_t actual_pbn = lbnToPbn(&inode, lbn, block_size, getBlock);

    // REQUIRE(actual_pbn == expected_pbn);
}


TEST_CASE("test_too_large", "[weight=1][part=test]"){
    // We have only used the macro VERY_LARGE_NUMBER to set the inode size so far
    // When the logical block number a caller request is too large (what is too large?),
    // your lbnToPbn() should immediately return BAD_PBN without needing to do any calculation
    // Write your own test here.

    // block_size
    uint32_t block_size;

    // inode
    inode_t inode;
    
    // getBlock
    auto getBlock = [](uint32_t block_no) {
        return valid_block;
    };

    uint32_t lbn;
    uint32_t expected_pbn;
    // uint32_t actual_pbn = lbnToPbn(&inode, lbn, block_size, getBlock);

    // REQUIRE(actual_pbn == expected_pbn);
}