//
// Created by ghu9999 on 6/1/22.
//

#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

// 返回路径末尾的文件的名称
char *fmtname(char *path) {
    static char buf[DIRSIZ + 1];
    char *p;
    // 找到path最后一个‘/’所在位置
    for (p = path + strlen(path); p >= path && *p != '/'; p--);
    p++;
    if (strlen(p) >= DIRSIZ) return p;
    memmove(buf, p, strlen(p));
    buf[strlen(p)] = 0;
    return buf;
}

void find(char *path, char *name) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    struct stat st;
    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        return;
    }
    if (st.type == T_FILE) {
        if (strcmp(fmtname(path), name) == 0) {
            printf("%s\n", path);
        }
    }
    else if (st.type == T_DIR) {
        char buf[512], *p;
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
            printf("ls: path too long\n");
            return;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        struct dirent de;
        // 遍历目录下所有文件
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            // de.name表示文件名
            // 禁止向"."和".."递归
            if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;
            memmove(p, de.name, strlen(de.name));
            p[strlen(de.name)] = 0; // path + "/" + de.name + '\0'
            find(buf, name);
        }
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("find: find <path> <fileName>\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}