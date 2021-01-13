#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "dirLookup.h"

int convertCharToInt(char* length, int loop) {
    int i;
    int temp = 0;
    for(i = 0; i < loop; i++) {
        //printf("int: %d\n", length[i]);
        //printf("temp: %d\n", temp);
        temp += length[i] << (i*8);
    }
    return temp;
}

int readFileLength(int fileDescriptor, char* array, int length) {
    //move offset to d_reclen
    if (lseek(fileDescriptor, length, SEEK_CUR) == -1) {
        return 0;
    }
    //get reclen from memory
    if (read(fileDescriptor, array, 2) == -1) {
        return 0;
    }
    //transfer the reclen to buffer len
    return convertCharToInt(array, 2);
}

ino_t dirLookup(const char *filename, const char *component) {

    int fd_in = open(filename, O_RDONLY);
    int temp_input = open(filename, O_RDONLY);
    if (fd_in < 0 || temp_input < 0) {
        return 0;
    }
    unsigned char temp[270] = "\0";
    unsigned char reclen[4] = "\0";
    unsigned char name[MAX_NAME_LEN];
    unsigned char *ptr;
    int a = readFileLength(temp_input, reclen, 4);

    while (read(fd_in, temp, a) != 0) {
//        printf("Hello1\n");
        ino_t inode = convertCharToInt(temp, 4);
//printf("inode: %d\n", inode);
        ptr = temp + 4;
        a = convertCharToInt(ptr, 2);

//printf("OLD a: %d\n", a);
        a = readFileLength(temp_input, reclen, a-2);
//printf("NEW a: %d\n", a);
        if(a > MAX_NAME_LEN) {
            a = MAX_NAME_LEN;
        }
        ptr = temp + 6;
        int namlen = convertCharToInt(ptr, 1);
        ptr = temp + 8;

//printf("Temp: %x%x%x%x %x%x %x %x ", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]);
//int j;
//for(j = 0; j < namlen; j++) {
//    printf("%x ", temp[j+8]);
//}
//printf("\n");

//printf("namlen: %d\n", namlen);
        strncpy(name, ptr, namlen);
        if (inode == 0) {
            continue;
        }else if (strstr(name, component)) {
//printf("STRSTR END\n");
            close(temp_input);
            close(fd_in);
            return inode;
        }

        }
    //printf("FAIL END\n");
        close(temp_input);
        close(fd_in);
        return BAD_DIR_ENTRY_INODE_NUMBER;
    }


