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

void calculate_baud_rate()
{
    unsigned int ibrd;
    unsigned int fbrd;
    unsigned int temp;

    // IBRD = floor(UART_FREQ / (16 * BAUD_RATE))
    // FBRD = floor(remainder * 64 + 0.5)

    ibrd = ((100 * UART_CLOCK_FREQ) / (16 * BAUD_RATE));
    for (temp = 0; temp <= ibrd; temp += 100)
        ; // find the highest 100x lower that ibrd
    temp -= 100;

    fbrd = (((ibrd - temp) * 64) + 50);

    // resolution = 100
    put32(UART_IBRD, ibrd / 100);
    put32(UART_FBRD, fbrd / 100);
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
    calculate_baud_rate();  // ibrd and fbrd calculation
    put32(UART_ICR, 0x7FF); // clear interrupts
    put32(UART_LCRH, UART_LCRH_WLEN_8BIT | UART_LCRH_FEN); // enable FIFO and 8bit word
    put32(UART_CR, UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE); // enable uart
}

