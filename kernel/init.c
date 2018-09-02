
#include <stddef.h>

#include "hal/dbg.h"

void kernel_init(const char* args) {
}

void kernel_start(void) {
	char *argv[] = { "shell", NULL };
	extern int monomain(char *argv[]);
	monomain(argv);
	hal_halt();
	while (1);
}
