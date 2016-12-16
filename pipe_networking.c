#include "pipe_networking.h"

int server_handshake(int * from_client){
  char buffer[100];
  mkfifo("wkp" , 0644);
  printf("[SERVER]: making wkp \n");
  int fd = open("wkp", O_RDONLY);
  printf("[SERVER]: waiting for client connection\n");
  read(fd, &buffer, sizeof(buffer));
  printf("[SERVER]: received message from client: %s\n", buffer);
  unlink("wkp");
  int cfd = open(buffer, O_WRONLY);
  write(cfd , "hello" , 6);
}

int client_handshake(int * to_client){
  char buffer[100];
  mkfifo("private", 0644);
  printf("[CLIENT]: making private \n");
  int fd = open("private", O_RDONLY);
  printf("[CLIENT]: connecting to wkp \n");
  int sfd = open("wkp", O_WRONLY);
  write(sfd, "private", 7); //client sends private pipe name to wkp
  read(fd , &buffer, sizeof(buffer));
  printf("[CLIENT]: received message from server: %s\n", buffer);
  unlink("private");
  write(sfd , "potato" , 7);
}

void main(){
}

