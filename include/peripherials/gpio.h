#ifndef _P_GPIO_H
#define _P_GPIO_H

#include "peripherials/base.h"

#define GPFSEL1		(PBASE + 0x00200004)
#define GPSET0 		(PBASE + 0x0020001C)
#define GPCLR0		(PBASE + 0x00200028)
#define GPPUD		(PBASE + 0x00200094)
#define GPPUDCLK0	(PBASE + 0x00200098)

#define GPIO_14     (0xC)
#define GPIO_15     (0xF)

#define GPIO_IN     (0x00)
#define GPIO_OUT    (0x01)
#define GPIO_ALT0   (0x04)
#define GPIO_ALT1   (0x05)
#define GPIO_ALT2   (0x06)
#define GPIO_ALT3   (0x07)
#define GPIO_ALT4   (0x03)
#define GPIO_ALT5   (0x02)

#define GPIO_CLEAN  (0x07)

#endif /* _P_GPIO_H */
