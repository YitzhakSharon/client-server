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

int main(int argc, char *argv[])
{
  int socket_fd,fsize;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
   // struct { char head; char body; char tail; } msgbuf;
 char  msgbuf []="my name is yitzhak, what is your name?";
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // creat socket with a IPv4, the type of the socket  ,and TCP protocol 
  memset((char *) &dest,0, sizeof(dest)); /* They say you must do this */ // reset the mmemory
  hostptr = gethostbyname(argv[1]); // the name of the host for get the IP

  dest.sin_family = (short) AF_INET; // we use with IPv4
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);// copy the name of the host
  dest.sin_port = htons((u_short)0x3333);// convert the  number of seleced port to byte/ 

 //msgbuf.head = '<'; //
 // msgbuf.body = htonl(getpid()); /* IMPORTANT! */
 // msgbuf.body ='g';
 // msgbuf.tail = '>';
  sendto(socket_fd,&msgbuf,100,0,(struct sockaddr *)&dest,sizeof(dest));// send data
  char msg []="i am sharon";
  fsize=sizeof(dest);
    recvfrom(socket_fd,&msg,100,0,(struct sockaddr *)&dest,&fsize); // getting data
    //printsin( &dest, "recv_udp: ", "Packet from:");
    printf("Got data ::%s",msg); 
    fflush(stdout);

  return 0;
}