#pragma once

#include <stdarg.h>
#include <stddef.h>

int rprintf(const char *format, ...);

int snprintf(char *buf, size_t size, const char *format, ...);

int vsnprintf(char *str, size_t size, const char *format, va_list ap);
