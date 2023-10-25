#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main()
{
    int CreateSocket = 0,n = 0,i = 0, port_end = 0, delay = 0;
    char dataReceived[1024];
    struct sockaddr_in ipOfServer;
    char ip_addr[20];
    
    fd_set fdset;
    struct timeval tv;
    
    printf("Geben Sie die IP Adresse, des Targets ein:");
    scanf("%s",ip_addr);


    memset(dataReceived, '0' ,sizeof(dataReceived));
        
    printf("Sock successfully created\n");

    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(1);
    ipOfServer.sin_addr.s_addr = inet_addr(ip_addr);
    
    printf("Server successfully initialized\n");
    
    printf("Enter the last Port you want to scan:");
    scanf("%d",&port_end);
    
    printf("Enter the time delay in nano seconds:");
    scanf("%d",&delay);
    
    for(i = 1;i < port_end;i++){
	if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
	{
	    printf("Socket not created \n");
	    return 1;
	}
	
	fcntl(CreateSocket, F_SETFL, O_NONBLOCK);
	
        ipOfServer.sin_port = htons(i);
        int connect_Result = connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
	
	FD_ZERO(&fdset);
	FD_SET(CreateSocket, &fdset);
	tv.tv_sec = 0;            
	tv.tv_usec = 20000;
	
        if (select(CreateSocket + 1, NULL, &fdset, NULL, &tv) == 1)
	{
	    int so_error;
	    socklen_t len = sizeof so_error;

	    getsockopt(CreateSocket, SOL_SOCKET, SO_ERROR, &so_error, &len);

	    if (so_error == 0) {
		printf("Port %d is open\n", i);
	    }
	}

	close(CreateSocket);
    }

    return 0;
}


