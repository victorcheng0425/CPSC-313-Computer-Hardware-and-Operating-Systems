#include <stdio.h>
#include "life.h"

// You are only allowed to change the contents of this file with respect
// to improving the performance of this program



// If you need to initialize some data structures for your implementation
// of life then make changes to the following function, otherwise
// do not change this function.

void initLife() {
}



#define USE
// For each version of life you are testing duplicate the code between the
// ifdef and endif and make your changes. To use the new version, move the the #define
// just about this comment to be just in front of the ifdef for the new version.

#ifdef USE

int life(long oldWorld[N][N], long newWorld[N][N]) {

    int i, j, k, l;
    int col, row;
    //int q = -1;

    int alive = 0;
    register long a, b, c, d, e;

    for (j = 0; j < N; j++) {
        row = (j - 1 + N) % N;
        k = (j + 1 + N ) % N;
        for (i = 0; i < N; i+=2) {
            col = (i - 1 + N) % N;
            l = (i + 1 + N) % N;
            a = oldWorld[row][i];
            b = oldWorld[row][l];
            c = oldWorld[k][i];
            d = oldWorld[k][l];
            e = oldWorld[j][i];
            newWorld[j][i] = oldWorld[row][col] + a + b
                             + oldWorld[k][col] + c + d
                             + oldWorld[j][col]                  + oldWorld[j][l];
            newWorld[j][i] = checkHealth(newWorld[j][i], e);
            alive += newWorld[j][i];
            l = (i + 2 + N) % N;
            newWorld[j][i+1] = oldWorld[row][l] + b + a
                               + oldWorld[k][l] + d + c
                               + oldWorld[j][l] + e;
            newWorld[j][i+1] = checkHealth(newWorld[j][i+1], oldWorld[j][i+1]);
            alive += newWorld[j][i+1];


        }
    }

    return alive;
}
#undef USE
#endif
