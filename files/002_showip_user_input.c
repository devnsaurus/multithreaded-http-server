// applying logic of 001_showip.c 
// the program will prompt user to enter a website
// then return its IP

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>  
#include <arpa/inet.h>
#include <netinet/in.h>
char* string_input(){
    char* website;
    char tempBuffer[1024]={};
    //printf("\nbefore entering name\nsizeof(tempBuffer)= %ld",sizeof(tempBuffer));
    //printf("\nstrlen(tempBuffer) = %ld",strlen(tempBuffer));


    printf("\nEnter website : ");
    


    if (fgets(tempBuffer,sizeof(tempBuffer),stdin) !=NULL)
    {
        website = (char*)malloc(strlen(tempBuffer)+1);
        //printf("\n after entering name:");
        //printf("\nsizeof(tempBuffer)= %ld",sizeof(tempBuffer));
        //printf("\nstrlen(tempBuffer) = %ld",strlen(tempBuffer));
        
        strcpy(website,tempBuffer);
        website[strlen(tempBuffer)-1]='\0';
        return website;
    }
}


int main(){
    char *site=string_input();
    printf("\n The website you entered: %s\n",site);
    
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // Either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; //SOCK_DGRAM if you wanna use datagram instead of tcp

    if ((status = getaddrinfo(site, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n", site);

    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
    }
    freeaddrinfo(res); // free the linked list


    free(site);


}