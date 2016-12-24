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

char req[5],ack[5], typ[5];

int main()
{
int cont,create_socket,new_socket,addrlen,fd;
int bufsize = 1024;

char *buffer = malloc(bufsize);
char datats[256];
struct sockaddr_in address;

/*ASKING USER TO ENTER DATA*/

printf("Enter the type of data\n f:file\n d:data\n");
gets(typ);
printf("Enter the data to be sent: \n");
gets(datats);

/*WHENEVER SENDER GETS THE DATA IT MAKES REQ LINE 1*/

req[5]='1';
if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
    printf("The sender has data and request for receiver\n");
printf("The req is made high =1\n");

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(10000);

if(req[5]=='1')

/* BINDING SOCKET TO TRANSFER THE DATA*/

if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
    printf("Waitinging for Acknowledgement\n");
  listen(create_socket,3);
  addrlen = sizeof(struct sockaddr_in);
  new_socket = accept(create_socket,(struct sockaddr *)&address,&addrlen);
  
/*SENSE THE ACK IS MADE HIGH*/

recv(new_socket,ack, 255,0);
if (new_socket > 0)
{
if(ack[5]=='1')
     printf("The receiver  %s is Connected...\n",
             inet_ntoa(address.sin_addr));
}
send(new_socket,typ,sizeof(typ),0);

/*SEND THE DATA TO RECEIVER*/

if(typ[5]=='f')
{
if ((fd=open(datats, O_RDONLY))<0)
    {perror("File Open Failed"); exit(0);}
while((cont=read(fd, buffer, bufsize))>0) {
     send(new_socket,buffer,cont,0);
  }
}
else
{
send(new_socket,datats,sizeof(datats),0);
}
sleep(5);

  printf("Data transfer Completed\n");

  close(new_socket);

/* AFTER TRANSMISSION MAKE REQ LINE LOW*/

printf("Req line is made 0\n");
return close(create_socket);
}
