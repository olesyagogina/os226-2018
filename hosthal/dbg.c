#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#include "hal/dbg.h"

void dbg_out(const char *msg, int len) {
	fwrite(msg, len, 1, stdout);
	fflush(stdout);
}

int dbg_in(char *inp, int len) {
	int r = read(STDIN_FILENO, inp, len);
	return r;
}

void hal_halt(void) {
	exit(0);
}
