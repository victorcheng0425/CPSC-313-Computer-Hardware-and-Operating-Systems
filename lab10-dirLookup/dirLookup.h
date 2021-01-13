#ifndef DIR_LOOKUP_H
#define DIR_LOOKUP_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>


#define BLOCK_SIZE 1024
#define MAX_NAME_LEN 256
#define BAD_DIR_ENTRY_INODE_NUMBER 0

// For more information about this structure, visit https://wiki.osdev.org/Ext2#Directories
typedef struct dir_entry
{
    uint32_t de_inode_no;       // inode number
    uint16_t de_rec_len;        // displacement to find next entry
    uint8_t de_name_len;        // string length of the file name field
    uint8_t de_file_type;       // file type of file (not used in rev #0)
    char de_name[MAX_NAME_LEN]; // name string
} dir_entry_t;

ino_t dirLookup(const char *filename, const char *component);

#endif
