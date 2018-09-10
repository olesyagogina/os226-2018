#pragma once

#define HOST_UCTX_SZ 0x10000
struct context {
	char host_uctx[HOST_UCTX_SZ];
};

struct context_call_save {
	unsigned long calltraget;
	unsigned long spbeforearg;
};
