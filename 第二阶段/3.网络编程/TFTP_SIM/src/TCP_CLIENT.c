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
// #include "protocol.h"
#define FTP_ROOT_DIR ".."
char recvbuf[1024] = {0};
char sendbuf[1024] = {0};

/* int readfile(char * path,int sockfd)
{
    FILE * opf = fopen(path,"r");
	struct stat st;
    int a,b,c;
	stat(path,&st);
	if(NULL == opf)
	{
		perror("open file error");
	}
    a = st.st_size/1024;
    if((st.st_size%1024 )!= 0)
    {
        a++;
    }
    char sendfile[1024] ;
    int i[a],t;
    c = 0;
    while(c<a)
    {
        memset(sendfile,0,1024);
        i[c] = fread(sendfile,1,1020,opf);  
        sendfile[1020] = c;
        sendfile[1021] = a;
        sendfile[1022] = ((i[c] )& 255);
        sendfile[1023] = (i[c] >>8 )& 255;
        //printf("%d\n",i[c]);  
        if(i[c]<0)
        {
            perror("readfile error");
        }
        memset(recvbuf,0,1024);
        strcpy(sendfile,"1234567891223646464656\n");
        t = send(sockfd,sendfile,1024,0);
        puts(sendfile);
        puts("_____________________________________________");
        if(t<0)
        {
            perror("send file error");
            return -1;
        }
        c++;
    }
	//return buf;
    fclose(opf);
    return 0;
}
void send_buf(int connfd)
{
    memset(recvbuf,0,1024);
    sleep(1);
    //printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
    char s[100] = {0};
    scanf("%s",s);
    send(connfd,s,50,0);
    printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
    char path[100]={0};
    sprintf(path,"%s/%s",FTP_ROOT_DIR,s);
    puts(path);
    readfile(path,connfd);
    
}
int write_file(char *pathname,char * data)
{
    printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
    FILE *fd =fopen(pathname,"w+");
    if(fd == NULL)
    {
        perror("open file error");
        return -1;
    }
    int num = data[1021],i,ret;
    ret = fwrite(data,1,(data[1022]|(data[1023]<<8)),fd);
    if (ret <0)
    {
        perror("write error");
    }
    fclose(fd);
    return 0;
}
int recv_buf(int sockfd)
{
    memset(recvbuf,0,1024);
    puts("请输入你想要下载的文件");
    char path[100]={0},
         rev[50] = {0};
    scanf("%s",rev);
    printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
    send(sockfd,rev,strlen(rev),0);
    sprintf(path,"%s/%s",FTP_ROOT_DIR,rev);
    int c = 0,i = 0;
    while(1)
    {
        i = recv(sockfd,recvbuf,1024,0);
        puts(recvbuf);
        if(i < 0 )
        {
            perror("recv error!");
            return -1;
        }
        if(c > recvbuf[1021])
        {
            break;
        }
        c++;
        printf("%d %d %d\n",recvbuf[1020],recvbuf[1021],i);
        //printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
        i = write_file(path,recvbuf);
        if(i < 0)
        {
            puts("创建文件失败");
            return -1;
        } 
        memset(recvbuf,0,1024);
    }
} */
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
    //接受连接
    struct sockaddr_in raddr;//客户端的ip地址
    socklen_t sAddrlen = sizeof(sAddr);
    int connfd  = connect(sockfd,(struct sockaddr*)&sAddr,sAddrlen); 
    if(connfd == -1 )
    {
        perror("connect error");
        return -1;
    }   
    
    char sp[50] = {0};
    puts("请输入你想要执行的指令：");
    scanf("%s",sp);
    // if(!strcmp(sp,"ls"))
    // {
    //     strcpy(sendbuf,"1024");
    //     send(sockfd,sendbuf,4,0);
    //     int ret =recv(sockfd,recvbuf,1024,0);
    //     if(ret == -1)
    //     {
    //         perror("recv error");
    //     }
    //     puts(recvbuf);
    // }

    // if(!strcmp(sp,"get"))
    // {
    //     memset(sendbuf,0,1024);
    //     strcpy(sendbuf,"1025");
        
    //     int ret = send(sockfd,sendbuf,4,0);
    //     if(ret == -1)
    //     {
    //         perror("recv error");
    //     }
    //     recv_buf(sockfd);
    // }
    if(!strcmp(sp,"put"))
    {
        memset(sendbuf,0,1024);
        strcpy(sendbuf,"1026");
        printf("line = %d function = %s\n",__LINE__,__FUNCTION__);
        puts(sendbuf);
        int ret = send(sockfd,sendbuf,4,0);
        if(ret == -1)
        {
            perror("recv error");
        }
        // send_buf(sockfd);
        sleep(1);
        memset(sendbuf,0,1024);
        strcpy(sendbuf,"1234567891223646464656\n");
        send(sockfd,sendbuf,1024,0);
        send(sockfd,sendbuf,1024,0);
        send(sockfd,sendbuf,1024,0);
        send(sockfd,sendbuf,1024,0);
        puts(sendbuf);
        puts("_____________________________________________");
    }
    //结束
    close(sockfd);
    close(connfd);
}