#include "utils.h"
#include "peripherials/mini_uart.h"
#include "peripherials/gpio.h"

void uart_send(char c)
{
    while (1)
        if (get32(AUX_MU_LSR_REG) & 0x20)
            break;

    put32(AUX_MU_IO_REG, c);
}

unsigned int uart_recv(void)
{
    while (1)
        if (get32(AUX_MU_LSR_REG) & 0x01)
            break;

    return (get32(AUX_MU_IO_REG) & 0xFF);
}

void uart_send_string(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; ++i)
        uart_send((char)str[i]);
}

void uart_init(void)
{
    unsigned int baud_rate;
    unsigned int selector;

    selector = get32(GPFSEL1);
    selector &= ~(7 << 12);     // Clean gpio14
    selector |= (2 << 12);      // Set alt5 for gpio14
    selector &= ~(7 << 15);     // Clean gpio15
    selector |= (2 << 15);      // Set alt5 for gpio15
    put32(GPFSEL1, selector);

    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    put32(GPPUDCLK0, 0);

    put32(AUX_ENABLES, 1);      // Enable mini uart (this also enables access to its registers)
    put32(AUX_MU_CNTL_REG, 0);  // Disable auto flow control and disable receiver and transmitter
    put32(AUX_MU_IER_REG, 0);   // Disable receive and transmitt interrupts
    put32(AUX_MU_LCR_REG, 3);   // Enable 8 bit mode
    put32(AUX_MU_MCR_REG, 0);   // Set RTC line to be always high

    // baudrate = system_clock_freq / (8 * ( baudrate_reg + 1 ))  
    baud_rate = (int)(SYSTEM_CLOCK_FREQ / (8 * (BAUD_RATE + 1)));
    put32(AUX_MU_BAUD_REG, baud_rate); // Set baudrate to 115200

    put32(AUX_MU_CNTL_REG, 3);  // Enable transmitter and receiver
}
