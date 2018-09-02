#pragma once

#include "../kernel/hal/dbg.h" // XXX
#include <string.h>

static inline void dbg_out_c(const char *s) {
	dbg_out(s, strlen(s));
}

