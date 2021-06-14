#include <netinet/in.h>
#include <unistd.h>

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
    do{
        new_fd = accept(sockfd,(struct sockaddr *) &cli_addr, &sin_size);

        nb_recv = recv(new_fd, buffer, sizeof(buffer), 0);
        if(nb_recv>0)
        {
            content = strstr(buffer, "POST /");
            if (content != NULL) {
                content += 6; // Offset by 4 bytes to start of content

            }
            else{
                content = buffer; // Didn't find end of header, write out everything

            }
            char *positionEntree2 = NULL;
            positionEntree2 = strchr(content, ' ');
            if (positionEntree2 != NULL) {
                *positionEntree2 = '\0'; // On remplace ce caractère par \0
            }
            printf("%s\n",content);

        }
    }while(1);

    close(sockfd);
    return 0;
}
