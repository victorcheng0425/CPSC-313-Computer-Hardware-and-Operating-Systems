#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "hexdump.h"

/**
 * Generate the hexdump of infile, and write result to outfile
 * 1. return 1 if success, and 0 otherwise
 * 2. outfile should not be created if infile does not exist
 */
int hexdump(const char * infile, const char * outfile) {
    //printf("Hello1!\n");
    int fd_in = open(infile, O_RDONLY);
    if(fd_in < 0){
        return 0;
    }
    //printf("Hello1!\n");
    int fd_out = open(outfile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IWOTH);
    if(fd_out < 0) {
        return 0;
    }
    //printf("Hello1!\n");
    int memory = 0;
    int offset = 0;
    char mem[20] = "\0";
    //printf("Hello1!\n");
    sprintf(mem, "%08x  ", memory);
    printf("%s", mem);
    unsigned char temp[16] = "\0";
    printf("In: %d, out: %d\n", fd_in, fd_out);
    fd_in = 3;
    fd_out = 4;
    offset = read(fd_in, temp, 16);

    while(offset > 0) {
        //printf("Hello2!\n");
        unsigned char line[100] = "\0";
        int fileoffset = offset*3;

        write(fd_out, mem, 10);
        int i;

        for (i = 0; i < offset;i++){
            printf("value: %x\n", temp[i]);
        }

        for(i = 0; i < offset; i++) {
            //printf("Hello3!\n");
            unsigned char buff[3];
            if(temp[i] == 10 && i != 0) {
                //printf("1!\n");
                fileoffset = fileoffset - 3;
                //offset -= 1;
                memory -= 1;
                //printf("i: %d\n", i);
                sprintf(mem, "%08x  ", memory);
                //printf("i: %d\n", i);
            }else if(temp[i] < 16) {
                //printf("2!\n");
                sprintf(buff, "0%x ", temp[i]);
                strcat(line, buff);

            }else{
                //printf("3!\n");
                sprintf(buff, "%x ", temp[i]);
                strcat(line, buff);
            }
            if( i >= offset-1) {
                //printf("5!\n");
                sprintf(buff, "\n");
                fileoffset+=1;
                strcat(line, buff);
            }else if(i==7) {
                //printf("4!\n");
                sprintf(buff, " ");
                fileoffset++;
                strcat(line, buff);
            }
            //printf("In: %d, out: %d, offset: %d, i: %d\n", fd_in, fd_out, offset, i);
        }
        fd_in = 3;
        fd_out = 4;
        //printf("HelloHello!\n");
        //fd_out = 4;

        //printf("HelloHello!\n");
        write(fd_out, line, fileoffset);
        memory += offset;
        fd_in = 3;
        offset = read(fd_in, temp, 16);
        sprintf(mem, "%08x  ", memory);
        //fd_out = 4;
        //printf("Hello!\n");
    }
    write(fd_out, mem, 8);
    write(fd_out, "\n", 1);
    close(fd_in);
    close(fd_out);

    return 1;
}