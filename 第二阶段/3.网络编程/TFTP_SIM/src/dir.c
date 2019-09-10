#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"stdlib.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
/*
	dir 目录操作函数
		@dir_name :带路径的目录名,表示要操作的目录
*/
char* buf[100] = {NULL};
char ** dir(char *dir_name)
{
    //char* buf[100] = {NULL};
	/*
		1.打开目录
	*/
	DIR* dirp = opendir(dir_name);
	if(NULL == dirp)
	{
		perror("open directory error");
		return NULL;
	}
	/*
		2.读取目录项
	*/
	struct dirent * p;
	struct stat st;
	int ret = 0;
    int  j = 0,i = 0;
	char path_file[100] = {0};
	while(1)
	{
		memset(path_file,0,100);
		p = readdir(dirp); //读取一个目录项
		if(NULL == p)
		{
			perror("read dir error");
			break;
		}
		//printf("%s\n",p->d_name);
        if((strcmp(p->d_name,"..")!= 0)&&(strcmp(p->d_name,".")!= 0))
        {
            buf[j] = (char *)malloc(sizeof(p->d_name ));
            buf[j] = p->d_name;
            //printf("2\n");
            /*判断读取到的目录项是一个普通文件,还是目录文件*/
            sprintf(path_file,"%s/%s",dir_name,p->d_name); //组合成带路径的文件名
            /*获取文件状态*/
            ret = stat(path_file,&st);
            /*判断文件类型*/
            if(-1 == ret)
            {
                perror("get status error");
            }
            else if(S_ISREG(st.st_mode))
            {
                strcat(buf[j],"  REG\n");
            }
            else if(S_ISDIR(st.st_mode))
            {
                strcat(buf[j],"  DIR\n");
            }
            
            if(j<100)
            {  
                j++;     
            }
            else
            {
                printf("数组满了!\n");
                break;
            }
        }
        else
        {
            continue;
        }
	}
	/*
		3.关闭目录
	*/
	closedir(dirp);
    return buf;
}