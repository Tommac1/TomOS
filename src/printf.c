#include "printf.h"

static int process_specifier(va_list *ap, char spec);
static void itoa(int d, char *str, int base);
static int printstr(const char *str);

static printf_out print_func;
static int inited = 0;

int printf(const char *fmt, ...)
{
    va_list ap;
	int it = 0;
    int ret = 0;

    if (inited == 1) {
        va_start(ap, fmt);
        while (fmt[it] != '\0') {
            if (fmt[it] == '%') {
                ret += process_specifier(&ap, fmt[it + 1]);
                it++; // pass the arg specifier
            }
            else {
                print_func(fmt[it]);
                ret++;
            }
            it++;
        }

        va_end(ap);
    }

    return ret;
}

void printf_init(printf_out putcf)
{
    print_func = putcf;
    inited = 1;
}

static int process_specifier(va_list *ap, char spec)
{
    char str[32] = { 0 };
    int temp = 0;
    int ret = 0;
    int base = 0;

	switch(spec) {
	case 'd': case 'D':
        base = 10;
		break;
    case 'x': case 'X':
        base = 16;
        break;
	default:

		break;
	}

    temp = va_arg(*ap, int);
    itoa(temp, str, base);
    ret = printstr(str);

    return ret;
}

static void itoa(int d, char *str, int base)
{
    int temp = 1;
    int i = 0;
    int is_negative = 0;

    if (d < 0) {
        d = -d;
        str[i++] = '-';
        is_negative = 1;
    }

    while (d != 0) {
        temp = (d % base);

        if (base == 10) {
            str[i++] = temp + '0';
        }
        else { 
            if (temp < 10)
                str[i++] = temp + '0';
            else 
                str[i++] = temp + 55;
        }
        d /= base;
    }

    if (i == 0)
        str[i++] = '0';
    else
        temp = is_negative; // pass the dash (-)

    if (base == 16) {
        str[i++] = 'x';
        str[i++] = '0';
    }

    str[i] = '\0';

    strrvs(str + temp);
}

static int printstr(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        print_func(str[i++]);

    return i;
}

void strrvs(char *str)
{
    int begin = 0;
    int end = strlen(str);

    while (begin < end) {
        str[begin] = str[begin] ^ str[end];
        str[end] = str[end] ^ str[begin];
        str[begin] = str[begin] ^ str[end];
        begin++; end--;
    }

}

int strlen(char *str)
{
    int ret = 0;
    while (str[ret++] != '\0')
        ;

    // get back to last character
    // post increment + back from zero nul
    ret -= 2;

    return ret;
}
