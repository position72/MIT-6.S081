//
// Created by ghu9999 on 6/1/22.
//

#include "kernel/types.h"
#include "user/user.h"

int main() {
    // p1[0]: 子进程从父进程的读端，p1[1]: 父进程向子进程的写端
    // p2[0]: 父进程从子进程的读端，p2[1]: 子进程向父进程的写端
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    char buf[1] = {'a'};
    if (fork() == 0) { // 子进程
        close(p1[1]);
        close(p2[0]);
        read(p1[0], buf, sizeof(buf));
        printf("%d: received ping\n", getpid());
        write(p2[1], buf, sizeof(buf));
    } else { // 父进程
        close(p1[0]);
        close(p2[1]);
        write(p1[1], buf, sizeof(buf));
        read(p2[0], buf, sizeof(buf));
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}