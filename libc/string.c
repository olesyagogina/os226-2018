
#include <stddef.h>
#include <string.h>

static inline __attribute__((noreturn)) void IMPL_ME() {
	extern void hal_halt(void);
	hal_halt();
	while(1);
}

int strcmp(const char *s1, const char *s2) {
	IMPL_ME();
}

size_t strlen(const char *s) {
	IMPL_ME();
}

char *strchr(const char *s, int c) {
	IMPL_ME();
}

size_t strspn(const char *str, const char *accept) {
	IMPL_ME();
}

size_t strcspn(const char *str, const char *reject) {
	IMPL_ME();
}

char *strtok_r(char *str, const char *delim, char **saveptr) {
	IMPL_ME();
}
