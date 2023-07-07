#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void check (int res, const char *msg) {
  if (res) {
    perror(msg);
    exit(1);
  }
}

int main (int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [devicename]\n", argv[0]);
    exit(2);
  }
  const char *base = "/tmp/netns/ns/";
  char *devname = argv[1];
  char buf[65];
  if (strlen(devname) > sizeof(buf) - strlen(base) - 1) {
    fputs("Device name too long\n", stderr);
    exit(2);
  }
  strcpy(buf, base);
  strcat(buf, devname);

  int fd = open(buf, O_RDONLY|O_CREAT|O_EXCL, 0);
  check(fd < 0, "open");
  check(close(fd), "close");
  check(unshare(CLONE_NEWNET), "unshare");
  check(mount("/proc/self/ns/net", buf, "nsfs", MS_BIND, NULL), "mount");
  int ret;
  ret = system("ip link set lo up");
  if (ret) return ret;
  ret = system("ipserv &");
  if (ret) return ret;
}
