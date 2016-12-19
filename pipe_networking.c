#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pipe_networking.h"

int server_handshake(int * from_client){
  char  buffer[100];
  mkfifo("wkp" , 0644);
  printf("[SERVER]: making wkp \n");
  printf("[SERVER]: waiting for client connection\n");
  int fd = open("wkp", O_RDONLY);
  read(fd, buffer, sizeof(buffer));
  printf("[SERVER]: received message from client: %s\n", buffer);
  int cfd = open(buffer , O_WRONLY);
  write(cfd , "hello" , 6);
  remove("wkp");
  return cfd;
}

int client_handshake(int * to_client){
  char  buffer[6];
  mkfifo("private", 0644);
  printf("[CLIENT]: Connecting to wkp\n");
  int sfd = open("wkp", O_WRONLY);
  write(sfd, "private" , 8);
  int fd = open("private" , O_RDONLY);
  printf("[CLIENT]: made private pipe\n");
  printf("[CLIENT]: buffer: %lu\n" , sizeof("hello"));
  read(fd , buffer, sizeof(buffer));
  printf("buffer: %s\n ", buffer);
  printf("[CLIENT]: received message from server: %s\n", buffer);
  remove("private");
  return fd;
}


