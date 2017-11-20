#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int READ = 0;
  int WRITE = 1;
  
  int fds[2];
  pipe(fds);
  
  int fds2[2];
  pipe(fds2);

  int forky = fork();
  
  if (forky) {
    close(fds[READ]);
    int org = 1020;
    printf("[parent] sending: %d\n", org);
    write(fds[WRITE], &org, 4);
  }
  else {
    close(fds[WRITE]);
    int new;
    read(fds[READ], &new, 4);
    printf("[child] doing maths on: %d\n", new);
    new = new / 10;
    
    close(fds2[READ]);
    write(fds2[WRITE], &new, 4);
  }
  
  if (forky){
    close(fds2[WRITE]);
    int new;
    read(fds2[READ], &new, 4);
    printf("[parent] received: %d\n", new);
  }
}
