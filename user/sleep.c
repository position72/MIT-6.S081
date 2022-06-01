//
// Created by ghu9999 on 6/1/22.
//

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(2, "the number of argument must be 1\n");
        exit(1);
    }
    int time = atoi(argv[1]);
    printf("(nothing happens for a little while)\n");
    sleep(time);
    exit(0);
}