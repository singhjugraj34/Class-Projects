TCP Server and Client
---------------------


Initially socket is created for TCP server. TCP server binds IP address 

and port number to the socket by using ‘bind’ command. Server then 

listens the connection from the client by using ‘listen’ command. When 

client starts connecting to the server for requesting the data, server 

accepts the connection by using ‘accept’ command. There are condition 
checking on the basis of output of all the socket, bind, connect, accept, 
read and write methods to check whether the method worked properly or not.
Now server is ready for read and write the data in the socket. 

When client connects to the server, server will send the data, depending 
upon the preference of the client as it inputs. Client also can now read 
and write the data from and to the server.

Compilation steps:

1) Server is compiled by gcc tcpserver.c –o tcpserver 

2) Server is executed by ./tcpserver. Once socket is created, server 

will listen for the client to connect.

3) Client is compiled by gcc tcpclient.c –o tcpclient

4) Client is connected to the server after execution by ./tcpclient

5) As the client consoles for CDs, Server will display 1) List and 2) 

order

6) If client selects ‘List’, Server will send the message- Here is your list.

7) If client selects ‘order’, server will ask to enter Item number – 1001, 1002, 1003 

and then Quantity. 

8) Server will give the DVDs to the client as per the client’s request and 

will display the message ‘Done! Thank you for the order’.

9) If server does not contain any CDs, it will display the message as-

‘Sorry! You entered more quantity than available!’ 

10) Thus, server will maintain connectivity throughout the process.


UDP server and UDP client
-------------------------

UDP is a connectionless process. Initially UDP server will create a 

socket by using ‘socket’ sys call. UDP will also bind IP address and port 

number to the socket by using ‘socket’ sys call. Once server is connected 

it will start sending and receiving data through ‘recvfrom’ and ‘sendto’ 

sys call.

Similarly, UDP client will create a socket and also the binding to the ip 
address by using bind method. After that it starts sending and 
receiving data through ‘recvfrom’ and ‘sendto’ sys call. At last, UDP 
client will close the socket. 

Compilation steps:

1) Server is compiled by gcc udpserver.c –o udpserver 

2) Server is executed by ./udpserver. Once socket is created, server 

will listen for the client to connect.

3) Client is compiled by gcc udpclient.c –o udpclient

4) Client is connected to the server after execution by ./udpclient

5) As the client consoles for CDs, Server will display 1) List and 2) order

6) If client selects ‘List’, Server will send the message- Here is your list.

7) If client selects ‘order’, server will ask to enter Item number – 1001, 1002, 1003 and then Quantity. 

8) Server will give the CDs to the client as per the client’s request and 

will display the message ‘Done! Thank you for the order’.

9) If server does not contain any DVDs, it will display the message as-

‘Sorry! You entered more quantity than available!’ 

10) Thus, server will maintain connectivity throughout the process.
