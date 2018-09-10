#pragma once

struct context;
struct context_call_save;

extern void ctx_call_setup(struct context *ctx, void(*tramp)(unsigned long *), struct context_call_save *save);

extern void ctx_push(struct context *ctx, unsigned long val);

extern void ctx_call_end(struct context *ctx, struct context_call_save *save);
