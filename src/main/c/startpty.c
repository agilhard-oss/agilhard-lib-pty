
#include <pty.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int startpty(int *fdbuf, const struct termios *tios, const struct winsize *ws, const char *cmd, const char *directory, char * const args[]) {
  int fd;
  int rc;
  if ( (rc = forkpty(fdbuf, NULL, tios, ws)) < 0 ) {
    return -1;
  }
  if (rc == 0) { /* child */
    // tput reset
    printf(">[?3l[?4l[?5l[?7h[?8h");

    setenv("TERM","vt100",1);
    setenv("LANG","en_US.utf8",1);
    if ( directory ) {
	chdir(directory);
    }
    execv(cmd, args);
    _exit(-1);
  }
  return rc;
}


int waitForPid(int pid) {
	int i;
	waitpid(pid, &i, WUNTRACED);
	return WEXITSTATUS(i);
}

