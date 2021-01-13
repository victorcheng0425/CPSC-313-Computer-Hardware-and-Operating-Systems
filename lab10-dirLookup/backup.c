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

void closefile() {
    close(temp_input);
    close(fd_in);
}

int readFileLength(int fileDescriptor, char* array, int length) {

}
ino_t dirLookup(const char *filename, const char *component) {
    int fd_in = open(filename, O_RDONLY);
    int temp_input = open(filename, O_RDONLY);
    if (fd_in < 0 || temp_input < 0) {
        return 0;
    }
    unsigned char temp[270] = "\0";
    unsigned char reclen[4] = "\0";
    //move offset to d_reclen
    if (lseek(temp_input, 4, SEEK_CUR) == -1) {
        return 0;
    }

    //get reclen from memory
    if (read(temp_input, reclen, 2) == -1) {
        return 0;
    }
    printf("reclen: %x %x\n", reclen[0],reclen[1]);
    //transfer the reclen to buffer len
    int a = convertCharToInt(reclen, 2);
    printf("a before loop: %d\n", a);


    dir_entry_t dir;
    while (read(fd_in, temp, a) != 0) {
        ino_t inode = convertCharToInt(temp, 4);
        printf("inode: %d\n", inode);
        char *ptr = temp + 4;
        a = convertCharToInt(ptr, 2);
        if (lseek(temp_input, a, SEEK_CUR) == -1) {
            return 0;
        }
        //get reclen from memory
        if (read(temp_input, reclen, 2) == -1) {
            return 0;
        }
        a = convertCharToInt(reclen, 2);
        ptr = temp + 6;
        uint8_t namlen = convertCharToInt(ptr, 1);
        ptr = temp + 8;
        unsigned char *name;
        printf("Temp: %x%x%x%x %x%x %x %x ", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]);
        int j;
        for(j = 0; j < namlen; j++) {
            printf("%x ", temp[j+8]);
        }
        printf("\n");

        printf("namlen: %d\n", namlen);
        strncpy(name, ptr, namlen);
        if (inode == 0) {
            continue;
        } else if (strstr(name, component)) {
            closefile();
            return inode;
        }

        closefile();
        return BAD_DIR_ENTRY_INODE_NUMBER;
    }
}

