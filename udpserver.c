//Programme for UDP server

#include<stdio.h>
#include<string.h>
#include <sys/types.h>     
#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<fcntl.h>
#define PORT_NUM 1500  //port number on which message will recieve and send
int main()
{
	int sock;      //variable for socket descriptor(server)
	int len;       //variable for initialize structure length
	char out_buf[100],in_buf[100];   //variable for input and output message initialize

	struct sockaddr_in server,client;
	
	sock=socket(AF_INET,SOCK_DGRAM,0);       //socket descripter for server(using ipv4)
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT_NUM);         //host to network short byte word
	server.sin_addr.s_addr=htonl(INADDR_ANY);//host to network long byte order
	len=sizeof(struct sockaddr_in);          //storing length of structure (define below)
	bind(sock,(struct sockaddr*)&server,len);//binding the socket with port num and ip

	printf("server is waiting.....\n");        //server goes to listen mode(explicitely define in tcp server)

	recvfrom(sock,in_buf,sizeof(in_buf),0,(struct sockaddr *)&client,&len);//recieve byte by byte stream from client 
	                                                                       //at 'in_buf' through server socket 
	printf("request accepted.................\n");
	printf("recieve from client...message:=%s\n",in_buf);    //display message recieve from client
	strcpy(out_buf,"HI mr.client I have got your message"); //storing string at 'out_buf'
	sendto(sock,out_buf,(strlen(out_buf)+1),0,(struct sockaddr *)&client,len);//stream send to client through socket
										  //(here length is increase by 1 because to assign null											//explicitely at the end of the stream 'out_buf')
	close(sock);	
}
