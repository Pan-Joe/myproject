#ifndef __READIR_H__
#define __READIR_H__
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
extern char* buf[100];
/* 
    dir:读取指定目录所有的文件加和参数
    @dir_name：指定的目录；
    return：返回读取到的数据

 */
char** dir(char *dir_name);

#endif