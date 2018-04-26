#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define PORT_A 8123
#define PORT_C 8124
#define PORT_B 8125

void printsin(struct sockaddr_in *sin, char *pname, char* msg){
char *ip= inet_ntoa(sin->sin_addr); // https://linux.die.net/man/3/inet_ntoa
puts(pname); 
printf("%s",msg);
printf(" ip= %s  port= %d",ip,sin->sin_port);
}

int main(int argc, char *argv[])
{
  int socket_fd, fsize;
  struct sockaddr_in  s_in, from, dest;
    struct hostent *hostptr;

  //struct { char head; u_long  body; char tail;} msg;
  char msg [100];
  
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);// open a socket
  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */

  s_in.sin_family = (short)AF_INET;// typy of the IPv4
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);   // convert the ip to Network Byte Order 
  s_in.sin_port = htons(PORT_C); // convert the port to Network Byte Order  

  memset((char *) &dest,0, sizeof(dest)); /* They say you must do this */ // reset the mmemory
  hostptr = gethostbyname(argv[1]); // the name of the host for get the IP
  dest.sin_family = (short) AF_INET; // we use with IPv4
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);// copy the name of the host
  dest.sin_port = htons(PORT_B);// convert the  number of seleced port to byte/ 

  //printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));// conect the socket with the Ip and the port

  while(1) {
    printf("hhh");
    fsize = sizeof(from);
    recvfrom(socket_fd,&msg,100,0,(struct sockaddr *)&from,&fsize); // Getting information 
   // printsin( &from, "recv_udp: ", "Packet from:");
  printf("Got data :%s\n",msg); 
   printf("please enter the messege\n");
    char back[100] ;
    fgets(back,100,stdin);
      if(strcmp(back,"exit\n")==0){
      break;
    }

    sendto(socket_fd,&back,100,0,(struct sockaddr *)&from,sizeof(from)); // send infromation

    fflush(stdout);
  }
  
  return 0;
}
