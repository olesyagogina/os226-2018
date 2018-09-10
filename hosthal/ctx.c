#define _GNU_SOURCE

#include <stddef.h>

#include "hal/context.h"
#include "hal_context.h"
#include "util.h"

#include <ucontext.h>
#include <string.h>

STATIC_ASSERT(sizeof(ucontext_t) <= HOST_UCTX_SZ);

extern void tramptramp(void);

static ucontext_t *h2uctx(struct context *hctx) {
	return (ucontext_t *) &hctx->host_uctx;
}

void ctx_push(struct context *ctx, unsigned long val) {
	greg_t *regs = h2uctx(ctx)->uc_mcontext.gregs;
	regs[REG_RSP] -= sizeof(unsigned long);
	*(unsigned long *) regs[REG_RSP] = val;
}

void ctx_call_setup(struct context *ctx, void(*tramp)(unsigned long *), struct context_call_save *save) {
	greg_t *regs = h2uctx(ctx)->uc_mcontext.gregs;

	ctx_push(ctx, regs[REG_RIP]);
	regs[REG_RIP] = (greg_t) tramptramp;

	save->spbeforearg = (unsigned long) regs[REG_RSP];
	save->calltraget = (unsigned long) tramp;
}

void ctx_call_end(struct context *ctx, struct context_call_save *save) {
	ctx_push(ctx, save->spbeforearg);
	ctx_push(ctx, save->calltraget);
}
