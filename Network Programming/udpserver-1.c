/*UDP server*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct {														//Globally declaration of the structure for DVD stock

	 int item_num[50];
	 char *title[50];
	 int quantity[50];
	} DVD;

int main(int argc, char *argv[])									//main function
{
	int sock,length,fromlen,out,i,j,err=0,in,quant;			//variable and "message" message declaration for storing input/output data
	char message[256],message2[256];
	struct sockaddr_in server,from;
	static DVD dvd;														//entries to the DVD stock
	//entries to the DVD stock
	dvd.item_num[0]=1001;
	dvd.item_num[1]=1002;
	dvd.item_num[2]=1003;
	dvd.title[0]="Home Alone";
	dvd.title[1]="Terminator";
	dvd.title[2]="Interstellar";
	dvd.quantity[0]=80;
	dvd.quantity[1]=50;
	dvd.quantity[2]=110;
	
	socklen_t addr_size;

	if (argc < 2)															//Error checking for Port quant
	{	
		printf ("Also provide the Port number \n");
		exit(0);
	}
	sock = socket(AF_INET,SOCK_DGRAM , 0);							//create the socket		

	if (sock < 0)															//error checking for the socket creation
	{
		printf("Failure of Socket Creation\n");
	}

	length = sizeof(server);
	bzero(&server,length);
	server.sin_family = AF_INET; 
        server.sin_addr.s_addr = INADDR_ANY; 
        server.sin_port= htons(atoi(argv[1])); 


	
	if(bind(sock, ( struct sockaddr *) &server, length) < 0)			//socket binding
	{
		printf( "Error in Binding" );
	}

        while(1)																	//infinite while loop to keep the server running all the time
	{
	fromlen = sizeof (struct sockaddr_in);
	bzero(message,256);															//clearing message message for reading data from client
	
	out = recvfrom ( sock ,message,256,0,(struct sockaddr *)&from ,&fromlen);
	if (out<0)
		{
			printf("data not received\n");
		}
	for(i=0;i<out;i++)
		printf("%c",message[i]);
	int cmp = strcmp(message,"list\n");

		if(cmp  == 0)																	//displaying the list of all the movies available
		{
	
			printf("Here is List for you:\n");
			printf("item_num\t\tTitle\t\tQuantity\n");
			printf("------------------------\n");
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);
			out = sendto(sock,"Item_num\t\tTitle\t\tQuantity\n------------------------------------------------\n1001\t\t Home Alone \t\t 80\n1002\t\t Terminator \t\t 50\n1003\t\t Interstellar \t\t 110\n",200,0,(struct sockaddr *)&from, fromlen);
		}
		else if(strcmp(message,"1001\n") == 0)								//compare the order value with 1001
		{
			in = recvfrom ( sock ,message2,256,0,(struct sockaddr *)&from ,&fromlen);
	                quant = atoi(message2);
			if(dvd.quantity[0] >= quant)
			{
		       		dvd.quantity[0] = dvd.quantity[0] - quant;
		       		out = sendto(sock,"\nServer : Done! Thank you for the order\n",50,0,(struct sockaddr *)&from, fromlen);
			}
			else
			{
				out = sendto(sock,"\nServer : Sorry! You entered more quantity than available!\n",50,0,(struct sockaddr *)&from, fromlen);
	                   		

			}

			printf("List of the available movies:\n");
			printf("Item_num\t\tTitle\t\tQuantity\n");
			printf("------------------------\n");
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);
		}

		else if(strcmp(message,"1002\n") == 0)										//compare the order value with 1002
		{
			in = recvfrom ( sock ,message2,256,0,(struct sockaddr *)&from ,&fromlen);
			quant = atoi(message2);
			if(dvd.quantity[1] >= quant)
			{
			       dvd.quantity[1] = dvd.quantity[1] - quant;
			       out = sendto(sock,"Server : Done! Thank you for the order\n",50,0,(struct sockaddr *)&from, fromlen);
			}
			else
			{
				out = sendto(sock,"Server : Sorry! You entered more quantity than available!\n",50,0,(struct sockaddr *)&from, fromlen);
			}
			printf("List of the available movies:\n");
			printf("Item_num\t\tTitle\t\tQuantity\n");
			printf("------------------------\n");
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);

		}
		else if(strcmp(message,"1003\n") == 0)													//compare the order value with 1003
		{
			in = recvfrom ( sock ,message2,256,0,(struct sockaddr *)&from ,&fromlen);
			quant = atoi(message2);
			if(dvd.quantity[2] >= quant)
			{
			       dvd.quantity[2] = dvd.quantity[2] - quant;
			       out = sendto(sock,"\nServer : Done! Thank you for the order\n",50,0,(struct sockaddr *)&from, fromlen);
			}
			else
			{
				out = sendto(sock,"\nServer : Sorry! You entered more quantity than available!\n",50,0,(struct sockaddr *)&from, fromlen);
			}
			printf("List of the available movies:\n");
			printf("Item_num\t\tTitle\t\tQuantity\n");
			printf("------------------------\n");
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
			printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);

		}


		if (out<0)
		{
			perror("Could not read the from socket\n");
		}

		 out = sendto(sock,"\nServer : List is Printed on the socket!\n",50,0,(struct sockaddr *)&from, fromlen);

		if(out<0)
		{
			perror("Could not write to socket\n");
		}
}

close(sock);								//closing of the socket

return 0;

	
}

