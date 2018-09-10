#define _GNU_SOURCE

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "syscall.h"
#include "exn.h"

#include "hostexn.h"

static bool syscall_hnd(int exn, struct context *c, void *arg) {
	ucontext_t *uc = (ucontext_t *) c;
	greg_t *regs = uc->uc_mcontext.gregs;

	if (0x81cd != *(uint16_t *) regs[REG_RIP]) {
		return false;
	}
	regs[REG_RIP] += 2;

	unsigned long ret = syscall_do(c, regs[REG_RAX],
			regs[REG_RBX], regs[REG_RCX],
			regs[REG_RDX], regs[REG_RSI],
			(void *) regs[REG_RDI]);
	regs[REG_RAX] = ret;
	return true;
}

static void sighnd(int sig, siginfo_t *info, void *ctx) {
	exn_do(sig, (struct context *) ctx);
}

int exn_init(void) {
       int res;

       if ((res = exn_set_hnd(SIGSEGV, syscall_hnd, NULL))) {
	       return res;
       }

       struct sigaction act = {
               .sa_sigaction = sighnd,
               .sa_flags = SA_RESTART,
       };
       sigemptyset(&act.sa_mask);
       for (int i = 1; i < 32; ++i) {
               if (i == SIGKILL || i == SIGSTOP) {
                       continue;
               }
               if (-1 == sigaction(i, &act, NULL)) {
                       perror("irq init failed");
                       return -1;
               }
       }

       return 0;
}
