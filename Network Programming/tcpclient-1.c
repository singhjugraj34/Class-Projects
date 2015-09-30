/*TCP client*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>


int main(int argc, char *argv[])				//main function
{
	int sock,port,out,cmp,in,quant;				//variable and "message" message declaration for storing input/output data
	char message[256];
	char message1[256],message2[256];
	struct sockaddr_in server;
	struct hostent *ip;

if(argc<3)
	{
		perror("Please enter ip address and port no\n");//Error checking for Port number and IP address
		exit(0);
	}

port = atoi(argv[2]);						//store the port# to port variable

sock = socket(AF_INET,SOCK_STREAM,0);				//socket creation and checking its creation
if (sock<0)
	{
		perror("Failure of Socket Creation\n");
	}
	
ip = gethostbyname(argv[1]);				//store Ip address in the ip variable by using gethostbyname method

if(ip==NULL)
	{
		perror("NO such host available\n");		//check for the ip address validation
		exit(0);
	}

bzero((char *) &server, sizeof(server));			//clear memory for server address


server.sin_family = AF_INET;
server.sin_port=htons(port);
bcopy((char *) ip->h_addr, (char *) &server.sin_addr.s_addr,ip->h_length);

if(connect(sock,(struct sockaddr *) &server, sizeof(server))<0)		//check for the connection success
	{
		perror("Error in Connection\n");
		exit(0);
	}

printf("Enter your preference: \n 1. list \n 2. order \n ");		//displaying the choices on the socket

bzero(message,256);
fgets(message,255,stdin);

cmp = strcmp(message,"list\n");					//compare the input by user with the "list"


if(cmp == 0)
{
	out = write(sock,message,strlen(message));				//write to the socket the list of the available stock
}
else
{
	printf("Your order No: \n 1. 1001 \n 2. 1002 \n 3. 1003 \n");
	fgets(message1,255,stdin);
	out = write(sock,message1,strlen(message1));	
	printf("Enter the quantity: ");
	fgets(message2,255,stdin);
	in = write(sock,message2,strlen(message2));
}


if (out<0)
	{
		perror("Could not send the data to socket\n");		//check the success of sending the data to the socket
	}
bzero(message,256);

out = read(sock,message,256);
if (out<0)
	{
		perror("Could not receive the data from the socket\n");		//check the success of receiving the data to the socket
	}
printf("%s\n",message);

close(sock);									//closing of the socket

return 0;

}

