
#include <stddef.h>

#include <kernel/util.h>
#include <string.h>

#define APPS_X(X) \
	X(shell) \
	X(echo) \


#define DECLARE(X) extern int X(int, char *[]);
APPS_X(DECLARE)
#undef DECLARE

typedef int (*main_t)(int, char *[]);
static const struct {
	const char *name;
	main_t fn;
} app_list[] = {
#define ELEM(X) { # X, X },
	APPS_X(ELEM)
#undef ELEM
};

int monomain(char *argv[]) {
	int argc = 0;
	for (char **a = argv; *a != NULL; ++a) {
		++argc;
	}

	if (!argc) {
		return -1;
	}

	main_t tgt = NULL;
	for (int i = 0; i < ARRAY_SIZE(app_list); ++i) {
		if (!strcmp(argv[0], app_list[i].name)) {
			tgt = app_list[i].fn;
			break;
		}
	}

	if (!tgt) {
		return 1;
	}

	return tgt(argc, argv);
}
