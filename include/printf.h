#include <stdarg.h>
#include <unistd.h>

typedef void (*printf_out)(char);

int printf(const char *fmt, ...);
void strrvs(char *str);
int strlen(char *str);
void printf_init(printf_out putcf);

