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

int main()
{
    int CreateSocket = 0,n = 0,i = 0;
    char dataReceived[1024];
    struct sockaddr_in ipOfServer;
    char ip_addr[17];
    
    printf("Geben Sie die IP Adresse, des Targets ein:");
    scanf("%s",ip_addr);


    memset(dataReceived, '0' ,sizeof(dataReceived));

    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }

    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(1);
    ipOfServer.sin_addr.s_addr = inet_addr(ip_addr);
    
    for(i = 0;i < 102400;i++){
        ipOfServer.sin_port = htons(i);
        int connect_Result = connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
        if(connect_Result<0)
        {
            //printf("Port %d, closed\n",i);
        }else{
            printf("Port %d, open\n",i);
            shutdown(CreateSocket ,2);
            
            if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
            {
                printf("Socket not created \n");
                return 1;
            }
        }
    }

    return 0;
}
