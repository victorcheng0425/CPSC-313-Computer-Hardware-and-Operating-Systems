#ifndef LBN_TO_PBN_H
#define LBN_TO_PBN_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

#define EXT2_MAX_BLOCK_SIZE 8192

// To understand this structure, visit: https://wiki.osdev.org/Ext2#Inodes
typedef struct inode {
  uint16_t i_mode;        // Mode (type of file and permissions)
  uint16_t i_uid;         // Owner's user ID
  uint32_t i_size;        // File size (least significant 32 bits)
  uint32_t i_atime;       // Last access time
  uint32_t i_ctime;       // Creation time
  uint32_t i_mtime;       // Last modification time
  uint32_t i_dtime;       // Deletion time
  uint16_t i_gid;         // Owner's group ID
  uint16_t i_links_count; // Reference counter (number of hard links)
  uint32_t i_blocks;      // Number of 512-byte blocks reserved for this inode
  uint32_t i_flags;       // Flags
  uint32_t i_osd1;        // OS-dependant value
  union {
    struct {
      uint32_t i_block[12];   // Direct block numbers
      uint32_t i_block_1ind;  // 1-indirect block number
      uint32_t i_block_2ind;  // 2-indirect block number
      uint32_t i_block_3ind;  // 3-indirect block number
    };
    char i_symlink_target[60]; // Symbolic link target, if smaller than 60 bytes
  };
  uint32_t i_generation;  // File version (used for NFS)
  uint32_t i_file_acl;    // Block number for extended attributes
  uint32_t i_dir_acl;     // File size (most significant 32 bits)
  uint32_t i_faddr;       // Location of file fragment (deprecated)
  union {
    uint8_t i_osd2[12]; // OS-dependant value
    struct {
      uint8_t  l_i_frag;      // Linux only: fragment number (deprecated)
      uint8_t  l_i_fsize;     // Linux only: fragment size (deprecated)
      uint16_t l_i_reserved;  // Reserved for future use
      uint16_t l_i_uid_high;  // Linux only: high 16 bits of owner's user ID
      uint16_t l_i_gid_high;  // Linux only: high 16 bits of owner's group ID
      uint32_t l_i_reserved2; // Reserved for future use
    };
  };
} inode_t;

typedef struct block {
  uint32_t is_valid;
  uint8_t data[EXT2_MAX_BLOCK_SIZE]; 
} block_t;

uint32_t lbnToPbn(inode_t *inode, uint32_t lbn, uint32_t block_size, block_t(*getBlock)(uint32_t block_no));

#endif
