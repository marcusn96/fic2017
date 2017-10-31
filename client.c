#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


void move(char *c){

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[256];
    
    /* if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    } */
    
    portno = 20232;              //portno = atoi(argv[2]);   // Port-ul
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
        error("ERROR opening socket");
        
    server = gethostbyname("193.226.12.217");          //server = gethostbyname(argv[1]);   //adresa IP a serverului
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
         
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
           
    //printf("Please enter the message: ");  //comanda pt miscare
    
    bzero(buffer,256);
    strcpy(buffer,c);
    //fgets(buffer,255,stdin);
    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
         
    bzero(buffer,256);
    
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
         
    printf("%s\n",buffer);
    close(sockfd);
    }

void comanda(char *aux){
    int i;
    char *tmp;
    
    for(i=0;i<strlen(aux);i++){
      if(aux[i]=='102' || aux[i]=='115' || aux[i]=='98' || aux[i]=='108' || aux[i]=='114'){  //strchr("fslrb",aux[i]);
          sprintf(tmp,"%c",aux[i]);
          move(tmp);
          sleep(1);
        }
    }
}



int main(int argc, char *argv[])
{
    comanda("fls");
    move("s");
    return 0;
}
