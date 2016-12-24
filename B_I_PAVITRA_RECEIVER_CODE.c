#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <string.h>
#include<arpa/inet.h>

char req[5],ack[5],typ[5];

int main(int argc,char *argv[])
{
int create_socket;
int bufsize = 1024;
int cont;
char *buffer = malloc(bufsize);
char datats[256];
struct sockaddr_in address;

/* CREATES THE SOCKET OF INTERNET FAMILY AND WITH TCP AS THE PROTOCOL*/

if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
    printf("The Receiver is ready\n");
printf("The ack is made high =1\n");

/* RAISE THE ACK LINE TO INDICATE RECEIVER IS READY*/

ack[5]='1';
  address.sin_family = AF_INET;
  address.sin_port = htons(10000);
  inet_pton(AF_INET,argv[1],&address.sin_addr);

/*CONNECT TO THE SENDER */

if (connect(create_socket,(struct sockaddr *) &address,
sizeof(address)) == 0)
    printf("The connection was accepted with the sender %s...\n",
            argv[1]);
  send(create_socket, ack, sizeof(ack), 0);
  printf("Connection established...... Receiving ….....\n\n");

/*RECEIVE THE CONTENT*/

recv(create_socket, typ, sizeof(typ), 0);
if(typ[5]=='f')
{
  printf("The contents of file are...\n\n");
while((cont=recv(create_socket, buffer, bufsize, 0))>0) {
    write(1, buffer, cont);
  }
}
else
{
recv(create_socket, datats, sizeof(datats), 0);
printf("The data received is: \n");
puts(datats);
}
printf("The data received successfully\n");
sleep(3);

/*AFTER SUCCESSFUL TRANSMISSION ACK IS MADE 0*/

printf("The ack is made 0 \n");
return close(create_socket);
}
