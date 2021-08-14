#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MYPORT 8080
#define BACKLOG 10

char buffer[1024];
char *content;


void *myThreadFun(void *vargp){
    int flag = 1;
    int sockfd;
    int new_fd;
    int sin_size;
    struct sockaddr_in my_addr;
    struct sockaddr_in cli_addr;
    int nb_recv;
    
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Erreur de création de la socket\n");
        exit (EXIT_FAILURE);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero) , 8);

    /* Association du socket avec le port de communication */
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) == -1)
    {
        exit(EXIT_FAILURE);
    }
    if ( (bind(sockfd, (const struct sockaddr *)&my_addr, sizeof(my_addr))) == -1)
    {
        perror("Ne peut effectuer un bind de l’adresse locale (nommage de la socket)");
        exit (EXIT_FAILURE);
    }      
        listen(sockfd, BACKLOG);
        sin_size = sizeof(struct sockaddr_in);
        new_fd = accept(sockfd,(struct sockaddr *) &cli_addr, &sin_size);   
    do{          
        //memset(buffer, 0, sizeof (buffer));
        nb_recv = recv(new_fd, buffer, sizeof(buffer), 0);
        if(nb_recv>0)
        {
            content = buffer; // Didn't find end of header, write out everything
            printf("%s\n",content);  
        }   
        nb_recv = -1;   
    }while(1);
    close(sockfd);
    return 0;
}
