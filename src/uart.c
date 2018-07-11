#include "utils.h"
#include "uart.h"
#include "peripherials/uart.h"
#include "peripherials/gpio.h"

char uart_recv(void)
{
    while (get32(UART_FR) & UART_FR_RXFE)
        ;

    return (get32(UART_DR) & UART_DR_DATA);
}

void uart_send(char c)
{
    while (get32(UART_FR) & UART_FR_TXFF)
        ;

    put32(UART_DR, c);
}

void uart_send_string(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; ++i)
        uart_send((char)str[i]);
}

void uart_init(void)
{
    unsigned int selector;

    selector = get32(GPFSEL1);
    selector &= ~(GPIO_CLEAN << GPIO_14);   // clean gpio14
    selector |= (GPIO_ALT0 << GPIO_14);     // set alt0 for gpio14
    selector &= ~(GPIO_CLEAN << GPIO_15);   // clean gpio15
    selector |= (GPIO_ALT0 << GPIO_15);     // set alt0 for gpio15
    put32(GPFSEL1, selector);

    put32(GPPUD, 0);
    delay(150);
    selector = ((1 << 14) | (1 << 15));
    put32(GPPUDCLK0, selector);
    delay(150);
    put32(GPPUDCLK0, 0);

    put32(UART_CR, 0);      // disable uart
    put32(UART_ICR, 0x7FF); // clear interrupts
    put32(UART_LCRH, 0);    // disable FIFO
    // IBRD = floor(UART_FREQ / (16 * BAUD_RATE))
    // IBRD = floor(3MHz / (16 * 115200)) = floor(1.628) = 1
    put32(UART_IBRD, 1);
    // FBRD = floor(remainder * 64 + 0.5)
    // FBRD = floor(.628 * 64 + 0.5) = floor(40.692) = 40
    put32(UART_FBRD, 40);
    put32(UART_LCRH, UART_WLEN_8BIT | (1 << 4)); // 8bit word
    put32(UART_CR, UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE); // enable uart
}
