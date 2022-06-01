//
// Created by ghu9999 on 6/1/22.
//

#include "kernel/types.h"
#include "user/user.h"

int main() {
    char buf[64];
    int n;
    while ((n = read(0, buf, sizeof(buf))) >= 0) {
        write(1, buf, n);
    }
    exit(0);
}