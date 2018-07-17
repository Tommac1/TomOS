#include "uart.h"
#include "utils.h"

static volatile int UART_READY = 0;

void kernel_main(unsigned int procid)
{
    if (procid == 0) {
        // only 1st core initializes uart
        uart_init();
        UART_READY = 1;
    }

    while (UART_READY == 0)
        ; // wait till uart ready

    // + 1 on delay because 1st core goes into endless loop
    // while multiplying delay time by 0 (1st core)
    delay((procid * 10000) + 1);

    uart_send_string("Hello, from processor ");
    uart_send(procid + '0');
    uart_send_string("\r\n");

    if (procid == 0) {
        // 1st core responses on uart, rest are waiting
        while (1) {
            uart_send(uart_recv());
        }
    }
    else {
        while(1)
            ;
    }
}
