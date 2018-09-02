
#include <stddef.h>
#include <string.h>

#include "dbgc.h"

int shell(int argc, char *argv[]) {
	while (1) {
		dbg_out_c("> ");
		char buffer[256];
		int bytes = dbg_in(buffer, sizeof(buffer));
		if (!bytes) {
			break;
		}

		if (bytes < sizeof(buffer)) {
			buffer[bytes] = '\0';
		}

		const char *comsep = "\n;";
		char *stcmd;
		char *cmd = strtok_r(buffer, comsep, &stcmd);
		while (cmd) {
			const char *argsep = " ";
			char *starg;
			char *arg = strtok_r(cmd, argsep, &starg);
			char *argv[256];
			int argc = 0;
			while (arg) {
				argv[argc++] = arg;
				arg = strtok_r(NULL, argsep, &starg);
			}
			argv[argc] = NULL;

			if (!argc) {
				break;
			}

			int monomain(char *argv[]);
			monomain(argv);

			cmd = strtok_r(NULL, comsep, &stcmd);
		}
	}

	dbg_out_c("\n");
	return 0;
}

