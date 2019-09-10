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
//#include "readir.h"
//#include "protocol.h"
#define FTP_ROOT_DIR "./TCP_SERVER.c"
char sendbuf[1024] = {0};
char recvbuf[1024] = {0};

char *readfile(char * path)
{
	FILE * opf = fopen(path,"r");
    FILE * opf2 = fopen("./test1.txt","w+");
	struct stat st;
    int a,b,c;
	stat(path,&st);
	if(NULL == opf)
	{
		perror("open file error");
	}
    if(NULL == opf2)
    {
        perror("open file error");
    }
    a = st.st_size/1024;
    if((st.st_size%1024 )!= 0)
    {
        a++;
    }
    unsigned char sendfile[5][1024] = {0} ;
    int i[a];
    unsigned char  cmd[4];
    c = 0;
    while(c<a)
    {
        // printf("%d\n",__LINE__);
        // sprintf(sendfile[c],"%s",cmd);
        
        i[c] = fread(sendfile[c],1,1020,opf);  
        sendfile[c][1020] = c;
        sendfile[c][1021] = a;
        sendfile[c][1022] = ((i[c] )& 255);
        sendfile[c][1023] = (i[c] >>8 )& 255;
        //printf("%d\n",i[c]);
        if(i<0)
        {
            perror("readfile error");
        }
        //printf("%d %d\n",__LINE__,sendfile[c][1020]);
        c++;
    }
    c = 0;
    while(c<a)
    {
        printf("%d %d\n",__LINE__,sendfile[c][1020]);
        printf("%d %d\n",__LINE__,sendfile[c][1021]);
        printf("%d %d\n",__LINE__,(sendfile[c][1022]|(sendfile[c][1023]<<8)));
        printf("\n");
        if(i[c]<1020)
        {
            fwrite(sendfile[c],1,i[c],opf2);  
        }
        else
        {
            fwrite(sendfile[c],1,1020,opf2);  
        }
        //fwrite(sendfile[c],1,1024,opf2);  
        c++;
    }
	//return buf;
    fclose(opf);
    fclose(opf2);
}

int main()
{
    readfile(FTP_ROOT_DIR);
    // unsigned int a =1024;
    // unsigned char b = 0,c = 0;
    // b = a & 255;
    // c = (a >>8) & 255;
    // printf("%d %d\n",b,c);
    // int d = c<<8|b;
    // printf("%d\n",d);
}