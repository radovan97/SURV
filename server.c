#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void doprocessing(int sock)
{
// lokalne promenljive
  int n,check;
  float result;
  char buffer[256];
  char sendBuff[256];
  char tempstr[256];
  char sendRes[50];
  char *first, *second;
  first = (char *)malloc(20 * sizeof(char));
  second = (char *)malloc(20 * sizeof(char));

  bzero(buffer, 256);
  int done = 0, k;

  while (!done)
  {
    n = read(sock, buffer, 256);
    buffer[n] = 0; // terminiraj string primljen od klijenta

    if ((strcmp(buffer,"quit") == 0) || (strcmp(buffer,"exit") == 0))
    {
      done = 1;
      printf("Client closed connection..\n");
    }
    else
    {
      if(strchr(buffer,'+') != NULL) // Proveri da li se u stringu nalazi `+`
      {
        first = strtok (buffer, "+");
        second = strtok (NULL, "\n");
        result = atof(first) + atof(second);
        sprintf(sendRes, "%.4g", result); // Konverzija float u string
        k = send(sock, sendRes, 50, 0);

        if(k==-1)
        {
            printf("Error in sending");
            exit(1);
        }
      }else if(strchr(buffer,'-') != NULL)
      {
        first = strtok (buffer, "-");
        second = strtok (NULL, "\n");
        result = atof(first) - atof(second);
        sprintf(sendRes, "%.4g", result);
        k = send(sock, sendRes, 50, 0);

        if(k==-1)
        {
            printf("Error in sending");
            exit(1);
        }
      }else if(strchr(buffer,'*') != NULL)
      {
        first = strtok (buffer, "*");
        second = strtok (NULL, "\n");
        result = atof(first) * atof(second);
        sprintf(sendRes, "%.4g", result);
        k = send(sock, sendRes, 50, 0);

        if(k==-1)
        {
            printf("Error in sending");
            exit(1);
        }

      }else if(strchr(buffer,'/') != NULL)
      {
        first = strtok (buffer, "/");
        second = strtok (NULL, "\n");
        result = atof(first) / atof(second);
        sprintf(sendRes, "%.4g", result);
        k = send(sock, sendRes, 50, 0);

        if(k==-1)
        {
            printf("Error in sending");
            exit(1);
        }
      }else
      {
        printf("Greska. Nepravilan unos.\n");
      }
    }
  }
    free(first);
    free(second);
    close(sock);
}

int main( int argc, char *argv[] )
{
  int sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("ERROR opening socket");
    exit(1);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = 5001;
  serv_addr.sin_family = AF_INET; //mora biti AF_INET
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
  {
    perror("ERROR on binding");
    exit(1);
  }

  printf("Server started.. waiting for clients ...\n");
  listen(sockfd,5); //maksimalno 5 klijenata moze da koristi moje usluge
  clilen = sizeof(cli_addr);

  while (1)
  {
    /*ovde ce cekati sve dok ne stigne zahtev za konekcijom od prvog klijenta*/
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    printf("Client connected...\n");

    if (newsockfd < 0)
    {
      perror("ERROR on accept");
      exit(1);
    }
    /* Kreiraj child proces sa ciljem da mozes istovremeno da
    komuniciras sa vise klijenata */
    int pid = fork();
    if (pid < 0)
    {
      perror("ERROR on fork");
      exit(1);
    }

    if (pid == 0)
    {
      close(sockfd);
      doprocessing(newsockfd);
      exit(0);
    }
    else
    {
      close(newsockfd);
    }
  } /* end of while */

}
