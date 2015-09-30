/*TCP server*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

//Globally declaration of the structure for DVD stock


typedef struct {

	 int item_num[50];
	 char *title[50];
	 int quantity[50];
	} DVD;

int main(int argc,char *argv[])								//main function
{
	int sock,newsock,port,out,in,quant;						//variable and "message" buffer declaration for storing input/output data
	char message[256],message2[256];
	struct sockaddr_in server_addr,client_addr;
	
	static DVD dvd;												//entries to the DVD stock
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

if(argc<2)															//Error checking for Port number
	{
		printf("Also provide the Port number \n");
		exit(1);
	}


sock=socket(AF_INET,SOCK_STREAM,0);							//socket creation and checking its creation

if(sock<0)
	{
		perror("Failure of Socket Creation\n");
		
	}

bzero((char *) &server_addr,sizeof(server_addr));		//clearing space for server address
port = atoi(argv[1]);

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(port);
server_addr.sin_addr.s_addr = INADDR_ANY;

if(bind(sock,(struct sockaddr *) &server_addr,sizeof(server_addr))<0)	//socket binding
	{
		perror("Error in Binding\n");
	}

if(listen(sock,5)==0)											//checking of listening state of the socket
	{
		printf("Server is Listening on %d....\n",port);
	}


while(1)																//infinite while loop to keep the server running all the time
{
addr_size = sizeof(client_addr);
newsock = accept(sock,(struct sockaddr *) &client_addr,&addr_size); //accepts connection after getting request from the client

if (newsock<0)
	{
		perror("Could not accept from the socket\n");
	}
bzero(message,256);																	//clearing message buffer for reading data from client

out = read(newsock,message,255);													//read from the client

int cmp = strcmp(message,"list\n");

if(cmp  == 0)																			//displaying the list of all the movies available
{
	
	printf("List of the available movies:\n");
	printf("Item_num\t\tTitle\t\tQuantity\n");
	printf("------------------------\n");
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);
	out=write(newsock,"Item_num\t\tTitle\t\tQuantity\n------------------------------------------------\n1001\t\t Home Alone \t\t 80\n1002\t\t Terminator \t\t 50\n1003\t\t Interstellar \t\t 110\n",500);
}
else if(strcmp(message,"1001\n") == 0){										//compare the order value with 1001
	in = read(newsock,message2,256);
	quant = atoi(message2);
	if(dvd.quantity[0] >= quant){
       dvd.quantity[0] = dvd.quantity[0] - quant;
       out=write(newsock,"Server : Done! Thank you for the order\n",100);
	}
	else{
		out=write(newsock,"Server : Sorry! You entered more quantity than available!\n",100);
	}
	
	printf("List of the available movies:\n");	printf("item_num\t\tTitle\t\tQuantity\n");
	printf("------------------------\n");
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);




}
else if(strcmp(message,"1002\n") == 0){
in = read(newsock,message2,256);
	quant = atoi(message2);
	if(dvd.quantity[1] >= quant){
       dvd.quantity[1] = dvd.quantity[1] - quant;
       out=write(newsock,"Server : Done! Thank you for the order\n",100);
	}
	else{
		out=write(newsock,"Server : Sorry! You entered more quantity than available!\n",100);
	}
	printf("List of the available movies:\n");
	printf("Item_num\t\tTitle\t\tQuantity\n");
	printf("\n");
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);

}
else if(strcmp(message,"1003\n") == 0){
	in = read(newsock,message2,256);
	quant = atoi(message2);
	if(dvd.quantity[2] >= quant){
       dvd.quantity[2] = dvd.quantity[2] - quant;
       out=write(newsock,"Server : Done! Thank you for the order\n",100);
	}
	else{
		out=write(newsock,"Server : Sorry! You entered more quantity than available!\n",100);
	}
	printf("List of the available movies:\n");
	printf("Item_num\t\tTitle\t\tQuantity\n");
	printf("------------------------\n");
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[0],dvd.title[0],dvd.quantity[0]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[1],dvd.title[1],dvd.quantity[1]);
	printf("%d\t\t%s\t\t%d\n",dvd.item_num[2],dvd.title[2],dvd.quantity[2]);

}

//
if (out<0)
	{
		perror("Could not read the from socket \n");
	}

	
out=write(newsock,"Server : List is Printed on the socket!\n",100);

if(out<0)
	{
		perror("Could not write to socket\n");
	}
}

close(newsock);													//closing of the sockets
close(sock);

return 0;

}






