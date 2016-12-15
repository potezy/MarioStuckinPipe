#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>



int server_handshake(int * from_client){
  char buffer[100];
  mkfifo("wkp" , 0644);
  printf("making wkp \n");
  int fd = open("wkp", O_RDONLY);
  printf("waiting for client connection\n");
  read(fd, &buffer, sizeof(buffer));
  printf("received message from client: %s\n", buffer);
  unlink("wkp");
  int cfd = open(buffer, O_WRONLY);
  write(cfd , "hello" , 6);
}

int client_handshake(int * to_client){
    mkfifo("private", 0644);
    printf("making private \n");
    int fd = open("private", O_RDONLY);
    printf("connecting to wkp \n");
    int sfd = open("wkp", O_WRONLY);
    write(sfd, "private", 7); //client sends private pipe name to wkp
    print
}

