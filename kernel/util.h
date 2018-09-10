#pragma once

#define NORETURN __attribute__((noreturn))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

#define STATIC_ASSERT(x) \
        extern void __dummy(int [!!(x) - 1])

#define assert(x) \
	if (!(x)) { failed_assert(#x, __FILE__, __LINE__); }

#define NORETURN __attribute__((noreturn))

void failed_assert(const char *cond, const char *file, int line) NORETURN;

void kprint(const char *msg, ...);

void panic(const char *msg, ...) NORETURN;

static inline unsigned long align(unsigned long v, unsigned mask) {
	return (v + mask) & ~mask;
}

static inline long min(long a, long b) {
	return a < b ? a : b;
}
