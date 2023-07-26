#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  int status;

  while (1) {
    printf("#cisfun$ ");
    getline(&line, &len, stdin);
    
    // Check if the user entered "exit"
    if (strcmp(line, "exit") == 0) {
      break;
    }

    // Check if the command exists
    pid_t pid = fork();
    if (pid == 0) {
      execvp(line, NULL);
      perror("execvp");
      exit(1);
    } else {
      waitpid(pid, &status, 0);
    }
  }

  return 0;
}
