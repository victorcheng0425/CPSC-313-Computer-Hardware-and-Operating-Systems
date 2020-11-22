#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "hexdump.h"

/**
 * Generate the hexdump of infile, and write result to outfile
 * 1. return 1 if success, and 0 otherwise
 * 2. outfile should not be created if infile does not exist
 */
int hexdump(const char * infile, const char * outfile) {

    int fd_in = open(infile, O_RDONLY);
    if(fd_in < 0){
        return 0;
    }
    int fd_out = open(outfile, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IWOTH);
    if(fd_out < 0) {
        return 0;
    }

    int memory = 0;
    int offset = 0;
    char mem[10];
    sprintf(mem, "%08x  ", memory);
    unsigned char temp[16];
int outout = open("test.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU|S_IRWXO);
    offset = read(fd_in, temp, 16);

    while(offset > 0) {
        unsigned char line[100] = "\0";
        int fileoffset = offset*3;
        printf("memory: %d\n", memory);
        printf("memory: %s\n", mem);
        write(outout, mem, 10);
        printf("value: %x\n", temp[15]);
        int i;
        for (i = 0; i < offset;i++){
            printf("value: %x\n", temp[i]);
        }

        for(i = 0; i < offset; i++) {
            unsigned char buff[3];
            if(temp[i] <= 16) {
                sprintf(buff, "0%x ", temp[i]);
            }else{
                sprintf(buff, "%x ", temp[i]);
            }
            printf("buff1: %s , i: %d\n", buff, i);
            strcat(line, buff);

            printf("first cat: %s\n", line);
            if(i==7) {
                sprintf(buff, " ");
                fileoffset++;
                strcat(line, buff);
            } else if( i == offset-1) {
                sprintf(buff, " \n");
                fileoffset+=2;
                strcat(line, buff);
            }
            //printf("buff2: %s\n", buff);
            //printf("second cat: %s\n", line);
        }
        write(outout, line, fileoffset);
        printf("%d\n", outout);
        memory += offset;
        printf("%d\n", outout);
        offset = read(fd_in, temp, 16);
        printf("%d\n", outout);
        sprintf(mem, "%08x  ", memory);
        //outout = 5;
        printf("%d\n", outout);
    }
    write(outout, mem, 8);
    close(fd_in);
    close(outout);

    return 0;
}