#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define PORT_A 8123
#define PORT_B 8125
#define PORT_C 8124

int main(int argc, char *argv[])
{
  int socket_fd,fsize;
  struct sockaddr_in s_in ,dest, from;
  struct hostent *hostptr;
   // struct { char head; char body; char tail; } msgbuf;
 char msgbuf [100];
 char msg [100];
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // creat socket with a IPv4, the type of the socket  ,and TCP protocol 
    
  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */
  s_in.sin_family = (short)AF_INET;// typy of the IPv4
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);   // convert the ip to Network Byte Order 
  s_in.sin_port = htons(PORT_A); // convert the port to Network Byte Order  


  
  memset((char *) &dest,0, sizeof(dest)); /* They say you must do this */ // reset the mmemory
  hostptr = gethostbyname(argv[1]); // the name of the host for get the IP
  dest.sin_family = (short) AF_INET; // we use with IPv4
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);// copy the name of the host
  dest.sin_port = htons(PORT_B);// convert the  number of seleced port to byte/ 


  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));// conect the socket with the Ip and the port

 while(1){
   printf("please enter the messege\n");
  fgets(msgbuf,100,stdin);
        if(strcmp(msgbuf,"exit\n")==0){
      break;
    }

  sendto(socket_fd,&msgbuf,100,0,(struct sockaddr *)&dest,sizeof(dest));// send data

  fsize=sizeof(from);
   recvfrom(socket_fd,&msg,100,0,(struct sockaddr *)&from,&fsize); // getting data
    //printsin( &dest, "recv_udp: ", "Packet from:");
    printf("Got data :: %s",msg); 
    fflush(stdout);
 }
  return 0;
}