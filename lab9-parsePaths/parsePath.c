#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "parsePath.h"

/**
 * Parse an input string according to examples in test.cpp
 * 1. The caller is not responsible for freeing the char array you return.
 * 2. The returned char array must be writable (write your own test to verify your implementation). 
 */
char *temp;
int flag = 0;
char tem[2] = {'/','\0'};
char * parsePath(char * str) {
    //(void) str;

    if(str != NULL) {
        if(str[0] == '/'){
            flag = 1;
            temp = str+1;
            printf("%s\n", tem);
            tem[0] = '/';
            return tem;
        }
        flag = 0;
        temp = strtok(str, "/");
    } else if (flag == 1){
        flag = 0;
        temp = strtok(temp, "/");
    }else if( temp != NULL){
        temp = strtok(NULL, "/");
    }
    if(temp == NULL) {
        //printf("return NULL\n");
        return NULL;

    }
    printf("%s\n", temp);
    return temp;

}