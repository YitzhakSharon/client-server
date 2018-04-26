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
#include <stdlib.h>

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
 srand( time( NULL ) );
  int socket_fd, fsize;
  struct sockaddr_in  s_in, from, destC, destA;
    struct hostent *hostptr;
  //struct { char head; u_long  body; char tail;} msg;
  char msg [100];
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);// open a socket

  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */
  s_in.sin_family = (short)AF_INET;// typy of the IPv4
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);   // convert the ip to Network Byte Order 
  s_in.sin_port = htons(PORT_B); // convert the port to Network Byte Order  
            printf("port sin %d\n",s_in.sin_port);

  // send data to client
  memset((char *) &destA,0, sizeof(destA)); /* They say you must do this */ // reset the mmemory
  hostptr = gethostbyname(argv[1]); // the name of the host for get the IP
  destA.sin_family = (short) AF_INET; // we use with IPv4
  memcpy(hostptr->h_addr, (char *)&destA.sin_addr,hostptr->h_length);// copy the name of the host
  destA.sin_port = htons(PORT_A);// convert the  number of seleced port to byte/ 

// send data to server
   memset((char *) &destC,0, sizeof(destC)); /* They say you must do this */ // reset the mmemory
  hostptr = gethostbyname(argv[1]); // the name of the host for get the IP
  destC.sin_family = (short) AF_INET; // we use with IPv4
  memcpy(hostptr->h_addr, (char *)&destC.sin_addr,hostptr->h_length);// copy the name of the host
  destC.sin_port = htons(PORT_C);// convert the  number of seleced port to byte/ 

 // printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout);

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));// conect the socket with the Ip and the port
  printf("please choose number between 0 to 1\n");
      double x;
    scanf("%lf",&x);

      fflush(stdout);

  while(1) {
              fsize = sizeof(from);
           recvfrom(socket_fd,&msg,100,0,(struct sockaddr *)&from,&fsize);
            printf("Got data  ::%s\n",msg); 
              printf("port destA %d\n",destA.sin_port);
              printf("port from %d\n",from.sin_port);
            printf("port destC %d\n",destC.sin_port);
            printf("port sin %d\n",s_in.sin_port);

if(from.sin_port==destC.sin_port){
                sendto(socket_fd,&msg,100,0,(struct sockaddr *)&destA,sizeof(destA)); // send infromation
                printf("send to the client");
   }
else{
      double random= (double)rand()/((double)RAND_MAX);
      if(x>random){
      printf(" the random number : %lf\n",random);
          printf("send data to srever\n");
          sendto(socket_fd,&msg,100,0,(struct sockaddr *)&destC,sizeof(destC)); // send infromation
        }
}
              fflush(stdout);



  }
  
  return 0;
}
