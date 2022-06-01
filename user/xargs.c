//
// Created by ghu9999 on 6/1/22.
//

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char *params[100], buf[1024] = {'\0'};
    for (int i = 1; i < argc; i++) {
        params[i - 1] = argv[i];
    }
    int n;
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        char tmp[1024] = {'\0'};
        params[argc - 1] = tmp;
        for (int i = 0; i < sizeof(buf); i++) {
            if (buf[i] == '\n') {
                if (fork() == 0) {
                    exec(argv[1], params);
                } else wait(0);
            } else tmp[i] = buf[i];
        }
    }
    exit(0);
}