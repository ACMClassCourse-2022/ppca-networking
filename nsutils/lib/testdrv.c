#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void check (int res, const char *msg) {
  if (res) {
    perror(msg);
    exit(1);
  }
}

int main (int argc, char **argv) {
  int pipefd[2][2];
  check(pipe(pipefd[0]), "pipe");
  check(pipe(pipefd[1]), "pipe");
  pid_t pid = fork();
  check(pid < 0, "fork");
  if (!pid) {
    check(dup2(pipefd[0][0], 0) < 0, "dup2");
    check(dup2(pipefd[1][1], 1) < 0, "dup2");
    argv[0] = "nc";
    check(execvp("nc", argv), "execvp");
  }
  while (1) {
    char cmd[10];
    int res = scanf("%8s", cmd);
    if (!res || res == EOF) {
      return 0;
    } else if (!strcmp(cmd, "send")) {
      int len;
      scanf("%d", &len);
      uint8_t *buf = malloc(len);
      check(!buf, "malloc");
      for (int i = 0; i < len; ++i) {
        int v;
        scanf("%d", &v);
        buf[i] = v;
      }
      write(pipefd[0][1], buf, len);
    } else if (!strcmp(cmd, "recv")) {
      int len;
      scanf("%d", &len);
      uint8_t *buf = malloc(len);
      check(!buf, "malloc");
      for (int i = 0; i < len; ++i) {
        int len = read(pipefd[1][0], &buf[i], 1);
        if (!len) {
          printf("read ended prematurely\n");
          return 1;
        }
      }
      for (int i = 0; i < len; ++i) {
        int c;
        scanf("%d", &c);
        if (c != buf[i]) {
          printf("wrong value received at %d; expected %d, got %d\n", i, c, buf[i]);
          return 1;
        }
      }
    } else if (!strcmp(cmd, "sleep")) {
      int time;
      scanf("%d", &time);
      usleep(time);
    } else {
      printf("Unknown command %s\n", cmd);
      return 2;
    }
  }
}
