#pragma once

#include "util.h"

void kernel_init(const char* args);

void kernel_start(void) NORETURN;
