/*UDP client*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netdb.h>

void error( char *msg)
{
	perror(msg);
	exit(1);
}
int main(int argc, char *argv[])												//main function
{
	int sock,length,out,err=0,in;
	char message[256],message2[256],message1[256];
	struct sockaddr_in server,from;
	
	struct hostent *ip;
	if (argc != 3) 
	{	
		printf(" Please enter ip address and port no\n ");
		exit(1);
	}
	sock = socket(AF_INET,SOCK_DGRAM , 0);									//socket creation and checking its creation
	if (sock < 0)
		{
			error("Failure of Socket Creation");
		}
	server.sin_family = AF_INET;
	ip =gethostbyname(argv[1]);												//store Ip address in the ip variable by using gethostbyname method
	if(ip==NULL)
	{
		perror("NO such host available\n");		//check for the ip address validation
		exit(0);
	}
	bcopy((char *)ip->h_addr, (char *)&server.sin_addr,ip->h_length);
	server.sin_port = htons(atoi(argv[2]));
	length = sizeof(struct sockaddr_in);

	printf("Enter your request: \n 1. list \n 2. order \n ");

	bzero(message,256);															//clear memory for server address
	fgets(message,255,stdin);

	int cmp = strcmp(message,"list\n");										//compare the input by user with the "list"


	if(cmp == 0)
	{
		out = sendto(sock,message,strlen(message),0,(struct sockaddr_in *)&server,length);
	}
	else
	{
		printf("Your order No: \n 1. 1001 \n 2. 1002 \n 3. 1003 \n");
		fgets(message1,255,stdin);
	
		out = sendto(sock,message1,strlen(message1),0,(struct sockaddr_in *)&server,length);
		printf("Enter the quantity: ");
		fgets(message2,255,stdin);
		out = sendto(sock,message2,strlen(message2),0,(struct sockaddr_in *)&server,length);
	}


	if (out<0)
	{
		perror("Could not send the data to socket\n");									//check the success of sending the data to the socket
	}
	bzero(message,256);

	out = recvfrom ( sock ,message,256,0,(struct sockaddr_in *) &server , &length);
	if (out<0)
	{
		perror("Could not receive the data from the socket\n");								//check the success of receiving the data to the socket
	}
	printf("%s\n",message);

close(sock);																						//closing of the socket

return 0;
		

}
