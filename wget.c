
#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <arpa/inet.h>     
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>

int main(int args,char *argv[])
{
    char *url1;
    char s[1024];
    char buffer[1024];
    char p[7];
    char reading;
    struct sockaddr_in* dest;
    struct sockaddr_in me;
    struct addrinfo* res;
    int count;
    int port,socket_fd;
    char* hostaddr;

    bzero(s,1024);
    url1=argv[1];
    char *url;


    url=strchr(url1,'/');
    url=strchr(url,url[2]);

    if(strchr(url,':')==NULL)
    {
        port=80;
        for(count=0;url[count]!='/';count++)
            {
                s[count]=url[count];
            }
    }
    else
    {
        for(count=0;url[count]!=':';count++)
        {
            s[count]=url[count]; 
        }
        url=strchr(url,':');
        url=strchr(url,url[1]);
        for(count=0;url[count]!='/';count++)
        {
            p[count]=url[count]; 
        }
         port=atoi(p);
    }
    
    memset((char *)&dest,0,sizeof(dest));
    memset((char *)&dest,0,sizeof(me));

    socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd<0)
    {
        printf("error opening socket");
    }

    if (0 != getaddrinfo(s, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", s);
    exit(1);
    }
    dest = (struct sockaddr_in*)res->ai_addr;
    hostaddr = inet_ntoa(dest->sin_addr);

    me.sin_family=AF_INET;
    me.sin_addr.s_addr=inet_addr(hostaddr);
    me.sin_port=htons(port);
    

 if (connect(socket_fd, (struct sockaddr *)&me, sizeof(me)) < 0)
     {
         printf("error in building");
     }
     bzero(buffer,strlen(buffer));
    sprintf(buffer,"GET %s HTTP/1.0\nHOST: %s\n\n", url1,s);


     send(socket_fd,buffer, strlen(buffer),0);
     
     while(read(socket_fd , &reading,1)!=0)
     {
      printf("%s",&reading);
     }
     printf("\n");
     close(socket_fd);
     printf("end program\n");
    return 0;
}

