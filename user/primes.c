//
// Created by ghu9999 on 6/1/22.
//

#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[35][2], cnt = 0;

    for (int i = 2; i <= 35; i++) {
        int isPrime = 1;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (!isPrime) continue;
        cnt++;
        pipe(p[cnt]);
        if (fork() == 0) {
            int temp;
            read(p[cnt][0], (char *)&temp, 4);
            printf("prime %d\n", temp);
            close(p[cnt][0]);
            exit(0);
        } else {
            write(p[cnt][1], (char *)&i, 4);
            wait(0);
            close(p[cnt][1]);
        }
    }

    exit(0);
}