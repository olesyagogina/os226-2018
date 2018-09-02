
#include "dbgc.h"

int echo(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		/*rprintf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');*/
		dbg_out_c(argv[i]);
		dbg_out_c(i == argc - 1 ? "\n" : " ");
	}
	return 0;
}
