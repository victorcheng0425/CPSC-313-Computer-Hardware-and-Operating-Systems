#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h> 
#include "copy.h"

/**
 * copy content from infile to outfile
 * 1. return 1 if success, and 0 otherwise
 * 2. infile should never be modified
 * 3. outfile should not be created if infile does not exist
 */
int copy(const char * infile, const char * outfile) {
    // fd_in = open infile for reading
    // fd_out = open outfile for writing
    // while (there is data left to read):
    //     read data from fd_in
    //     write data to fd_out
    // close fd_in
    // close fd_out

    int fd_in = open(infile, O_RDONLY);
    if(fd_in < 0){
        return 0;
    }
    int fd_out = open(outfile, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IWOTH);
    //exit(0);
    //printf("%d, %d\n", fd_in, fd_out);
    if(fd_out < 0) {
        return 0;
    }
    char buffer[100];
    ssize_t rd = read(fd_in, buffer, 100);
    // printf("rd: %d", rd);
   if( rd < 0) {
       return 0;
   }
    while(rd) {
        ssize_t wr = write(fd_out, buffer, rd);
        //printf("%d\n", wr);
        rd = read(fd_in, buffer, 100);
       // printf("Testing\n");
        if(wr < 0  || rd < 0) {
            return 0;
        }
    }
    close(fd_in);
    close(fd_out);

    return 1;
}