#include <sys/types.h>   
#include <sys/stat.h>       /* See NOTES */	
#include <fcntl.h>	   
#include <sys/socket.h>		   
#include <netinet/in.h>			   
#include <arpa/inet.h>
#include <linux/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "readir.h"
//#include "protocol.h"
#define FTP_ROOT_DIR "."
char sendbuf[1024] = {0};
char recvbuf[1024] = {0};
// int readfile(char * path,int connfd)
// {
//     FILE * opf = fopen(path,"r");
// 	struct stat st;
//     int a,b,c;
// 	stat(path,&st);
// 	if(NULL == opf)
// 	{
// 		perror("open file error");
// 	}
//     a = st.st_size/1024;
//     if((st.st_size%1024 )!= 0)
//     {
//         a++;
//     }
//     char sendfile[1024] ;
//     int i[a],t;
//     c = 0;
//     while(c<a)
//     {
//         memset(sendfile,0,1024);
//         i[c] = fread(sendfile,1,1020,opf);  
//         sendfile[1020] = c;
//         sendfile[1021] = a;
//         sendfile[1022] = ((i[c] )& 255);
//         sendfile[1023] = (i[c] >>8 )& 255;
//         //printf("%d\n",i[c]);  
//         if(i[c]<0)
//         {
//             perror("readfile error");
//         }
//         puts(sendfile);
//         printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
//         printf("%d %d\n",sendfile[1020],sendfile[1021]);
//         t = send(connfd,sendfile,1024,0);
//         printf("%d %d\n",__LINE__,t);
//         if(t<0)
//         {
//             perror("send file error");
//             return -1;
//         }
//         c++;
//     }
// 	//return buf;
//     fclose(opf);
//     return 0;
// }
// int write_file(char *pathname,char * data)
// {
//     FILE *fd =fopen(pathname,"w+");
//     if(fd == NULL)
//     {
//         perror("open file error");
//         return -1;
//     }
//     int num = data[1021],i,ret;
//     ret = fwrite(data,1,(data[1022]|(data[1023]<<8)),fd);
//     if (ret <0)
//     {
//         perror("write error");
//     }
    
//     fclose(fd);
//     return 0;
// }
// int recv_buf(int connfd)
// {
//     memset(recvbuf,0,1024);
//     recv(connfd,recvbuf,1024,0);
//     puts(recvbuf);
//     char path[100]={0};
//     printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
//     sprintf(path,"%s/%s",FTP_ROOT_DIR,recvbuf);
//     int c = 0,i = 0;
//     memset(recvbuf,0,1024);
//     i = recv(connfd,recvbuf,1024,0);
//     printf("%d\n",i);
//     if(i < 0 )
//     {
//         perror("recv error!");
//         return -1;
//     }
//     if(c>recvbuf[1021])
//     {
//         //break;
//     }
//     c++;
//     i = write_file(path,recvbuf);
//     if(i < 0)
//     {
//         puts("创建文件失败");
//         return -1;
//     } 
    
// }
// void send_buf(int connfd)
// {
//     memset(recvbuf,0,1024);
//     //send(connfd,"请输入你要下载的文件",strlen("请输入你要下载的文件"),0);
//     //printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
//     recv(connfd,recvbuf,1024,0);
//     printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
//     char path[100]={0};
//     sprintf(path,"%s/%s",FTP_ROOT_DIR,recvbuf);
//     readfile(path,connfd);
    
// }
char **s = NULL;
int main(int argc,char *argv[])
{
    // char sendbuf[1024] = {0};
    // char recvbuf[1024] = {0};
    //创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sockfd)
	{
		perror("socket error");
		return -1;
	}
    //绑定套接字
    struct sockaddr_in sAddr;//定义一个以太网的地址
    sAddr.sin_family        = AF_INET;//选择协议
    sAddr.sin_port          = htons(atoi(argv[2]));//选择端口
    sAddr.sin_addr.s_addr   = inet_addr(argv[1]);//选择ip地址(点分十进制显示)

    int ret = bind(sockfd,(struct sockaddr*)&sAddr,sizeof(struct sockaddr));
    if(ret == -1)
    {
        perror("bind error");
        return -1;
    }
    //监听
    ret = listen(sockfd,10);
    if(ret == -1)
    {
        perror("listen error");
        return -1;
    }
    //接受连接
    struct sockaddr_in raddr;//客户端的ip地址
    socklen_t raddrlen = sizeof(raddr);
    int connfd  = accept(sockfd,(struct sockaddr*)&raddr,&raddrlen); 
    if(connfd == -1 )
    {
        perror("accept error");
        return -1;
    }   
    //接收信息
    ret = recv(connfd,recvbuf,1024,0);
    printf("%s\n",recvbuf);
    if(ret == -1)
    {
        perror("recv error");
        
    }
    //解析请求
    //执行请求中的命令
    // if(!strcmp(recvbuf,"1024"))
    // {
    //     printf("recv ok!");
    //     s = dir(FTP_ROOT_DIR);
    //     int i;
    //     for(i = 0;i<100;i++)
    //     {
    //         if(s[i] == NULL)
    //         {
    //             break;
    //         }
    //         strcat(sendbuf,s[i]);
    //     }
    //     send(connfd,sendbuf,strlen(sendbuf),0);
    // }
    // if(!strcmp(recvbuf,"1025"))
    // {
    //     send_buf(connfd);
    // }
    if(!strcmp(recvbuf,"1026"))
    {
        memset(recvbuf,0,1024);
        recv(connfd,recvbuf,1024,0);
        printf("%s\n",recvbuf);
         memset(recvbuf,0,1024);
        recv(connfd,recvbuf,1024,0);
        printf("%s\n",recvbuf);
         memset(recvbuf,0,1024);
        recv(connfd,recvbuf,1024,0);
        printf("%s\n",recvbuf);
         memset(recvbuf,0,1024);
        recv(connfd,recvbuf,1024,0);
        printf("%s\n",recvbuf);
        
    }
    //结束
    close(sockfd);
    close(connfd);
}