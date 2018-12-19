#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>


/* definisanje globalnih promenljivih */
int main(int argc, char *argv[])
{
  int sockfd = 0;
  struct sockaddr_in serv_addr;
  int done, k;
  char * line = NULL;
  size_t len = 0;
  int nread;
  char buf[100];
  /* klijentska aplikacija se poziva sa ./ime_aplikacija ip_adresa_servera */
  if(argc != 2)
  {
    printf("\n Usage: %s <ip of server> \n",argv[0]);
    return 1;
  }
  /* kreiraj socket za komunikaciju sa serverom */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Error : Could not create socket \n");
    return 1;
  }
  memset(&serv_addr, 0, sizeof(serv_addr));
  /* kao i podatke neophodne za komunikaciju sa serverom */
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5001);
  /* inet_pton konvertuje ip adresu iz stringa u format
  neophodan za serv_addr strukturu */

  if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
  {
    printf("\n inet_pton error occured\n");
    return 1;
  }
  /* povezi se sa serverom definisanim preko ip adrese i porta */
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\n Error : Connect Failed \n");
    return 1;
  }
  printf("Connected to server... Send message to server, or type 'quit' or 'exit' to exit\n");
  printf("Upisi izraz za proracun: (npr `2+3`)\n");
  /* udji u petlju u kojoj ces slati poruke serveru sve dok ne posaljes “quit” */
  done = 0;
  while (!done)
  {
    printf("\n[C] >> ");
    nread=getline(&line, &len, stdin);
    //ignore '\n'
    nread--;
    line[nread] = '\0';
    if ((strcmp(line,"quit") == 0) || (strcmp(line,"exit") == 0))
    {
      done = 1;
      printf("Closing connection with the server..\n");
    }
    /* posalji poruku serveru */
    write (sockfd, line, strlen(line));

    // primi poruku od servera
    k=recv(sockfd, buf, 50,0);
    if(k==-1)
    {
        printf("Error in receiving");
        exit(1);
    }

     printf("[S] >> %s\n",buf);
  }

  close(sockfd);
  return 0;

}
