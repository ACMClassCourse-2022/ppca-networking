#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void check (int res, const char *msg) {
  if (res) {
    perror(msg);
    exit(2);
  }
}

void swap (int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void shuffle (int *array, int length) {
  for (int i = 0; i < length; ++i) {
    swap(&array[i], &array[i + (rand() % (length - i))]);
  }
}

int main (int argc, char **argv) {
  int parallel;
  scanf("%d\n",&parallel);
  int pipefd[parallel][2][2];
  int perm[parallel];
  pid_t pid[parallel];
  for (int i = 0; i < parallel; ++i) {
    perm[i] = i;
    check(pipe(pipefd[i][0]), "pipe");
    check(pipe(pipefd[i][1]), "pipe");
    pid[i] = fork();
    check(pid[i] < 0, "fork");
    if (!pid[i]) {
      check(dup2(pipefd[i][0][0], 0) < 0, "dup2");
      check(dup2(pipefd[i][1][1], 1) < 0, "dup2");
      argv[0] = "nc";
      check(execvp("nc", argv), "execvp");
    }
  }
  while (1) {
    shuffle(perm, parallel);
    char cmd[10];
    int res = scanf("%8s", cmd);
    if (!res || res == EOF) {
      for (int i = 0; i < parallel; ++i) {
        check(kill(pid[i], SIGTERM), "kill");
      }
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
      for (int i = 0; i < parallel; ++i) {
        write(pipefd[perm[i]][0][1], buf, len);
      }
    } else if (!strcmp(cmd, "recv")) {
      int len;
      scanf("%d", &len);
      uint8_t *buf = malloc(len);
      check(!buf, "malloc");
      for (int i = 0; i < len; ++i) {
        int c;
        scanf("%d", &c);
        buf[i] = c;
      }
      for (int i = 0; i < parallel; ++i) {
        for (int j = 0; j < len; ++j) {
          uint8_t c;
          int len = read(pipefd[perm[i]][1][0], &c, 1);
          if (!len) {
            printf("read ended prematurely\n");
            return 1;
          }
          if (c != buf[j]) {
            printf("wrong value received at %d; expected %d, got %d\n", j, buf[j], c);
            return 1;
          }
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
