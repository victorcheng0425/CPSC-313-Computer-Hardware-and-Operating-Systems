#include <stdio.h>
#include <stdint.h>

#include "lbnToPbn.h"

#define BAD_PBN ((uint32_t)-1)

/**
 * A simple helper function. You do not have to use this.
 * @arg block: a indirect / double-indirect / triple-indirect block
 * @arg index: the index to access the block
 * @returns a block pointer located at the "index"th location inside "block"
 */
static inline uint32_t get_pointer(block_t block, uint32_t index)
{
    return ((uint32_t *)&block.data)[index];
}

/**
 * @arg inode: an inode of a file
 * @arg lbn: a logical block number of the file
 * @arg block_size: the block size of the entire ext2 file system
 * @arg getBlock: a function that takes a block number (block pointer) and returns the block itself
 * @returns the physical block number, translated from the logical block number using the inode
 *          0 if lbn is a block beyond the end of a file
 *          BAD_PBN if lbn is larger than the theoretical limit of a single file in ext2
 */
uint32_t lbnToPbn(inode_t *inode, uint32_t lbn, uint32_t block_size, block_t(*getBlock)(uint32_t block_no))
{
    if(lbn<=EXT2_MAX_BLOCK_SIZE){
        int pointerPerBlock = block_size / 4;
        int doubleLevelBlockSum = pointerPerBlock*pointerPerBlock;
        //1) check if lbn can be accesed, ie lbn>max idx of the file
        if(lbn * block_size>=inode->i_size){
            printf("test\n");
            return 0;
        }
        if(lbn<=11){
            printf("Direct block\n");
            return inode->i_block[lbn];
        }
        lbn -=12;
        if(lbn<pointerPerBlock){//1-indirect pointer
            block_t tempBlock = getBlock(inode->i_block_1ind);
            return get_pointer(tempBlock,lbn);
        }
        lbn -= pointerPerBlock;
        if(lbn< doubleLevelBlockSum&& lbn>=0){//2-indirect pointer
            block_t level1BlockD = getBlock(inode->i_block_2ind);
            uint32_t level2IdxD = get_pointer(level1BlockD, lbn/pointerPerBlock);
            block_t level2BlockD = getBlock(level2IdxD);
            return get_pointer(level2BlockD, lbn%pointerPerBlock);
        }
        lbn -= doubleLevelBlockSum;
        if( lbn >= 0  ){ //3-indirect pointer
            // printf("NEW a: %d\n", 'a');
            // block_t level1BlockT = getBlock(inode->i_block_3ind);
            // // uint32_t level2IdxT = get_pointer(level1BlockT, lbn/doubleLevelBlockSum);
            // uint32_t* temp = (uint32_t *)&level1BlockT.data;
            // block_t level2BlockT = getBlock(temp[lbn/doubleLevelBlockSum]);
            // lbn -= (lbn/(pointerPerBlock*pointerPerBlock))*(pointerPerBlock*pointerPerBlock);
            // temp = (uint32_t *)&level2BlockT.data;
            // // uint32_t level3Idx = get_pointer(level2BlockT,lbn/pointerPerBlock);
            // block_t level3Block = getBlock(temp[lbn/pointerPerBlock]);
            // temp = (uint32_t *)&level3Block.data;
            // return temp[lbn%pointerPerBlock];
            return 0;
        }

        //else if(lbn==13){

        //    } else if(lbn==14){ //3-indirect pointer

        //    }


    }
    return BAD_PBN;
}