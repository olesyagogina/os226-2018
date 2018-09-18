
#include <stddef.h>

#include "init.h"
#include "hal/dbg.h"
#include "ksys.h"

struct kernel_globals kernel_globals;

void kernel_init(void *rootfs_cpio, void *mem, size_t sz, const char* args) {
	kernel_globals.rootfs_cpio = rootfs_cpio;
	kernel_globals.mem = mem;
	kernel_globals.memsz = sz;
	kernel_globals.countstack = 0;
}

void kernel_start(void) {
	char *argv[] = { "shell", NULL };
	if (run_first(argv)) {
		panic("first process failed");
	}
	panic("first process exited");
}
