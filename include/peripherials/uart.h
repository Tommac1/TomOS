#ifndef _P_UART_H
#define _P_UART_H

#define BAUD_RATE       (115200)
#define UART_CLOCK_FREQ (3000000)

#define UART_BASE       (0x3F201000)

#define UART_DR         (UART_BASE + 0x0)
#define UART_RSRECR     (UART_BASE + 0x4)
#define UART_FR         (UART_BASE + 0x18)
#define UART_ILPR       (UART_BASE + 0x20)	
#define UART_IBRD	    (UART_BASE + 0x24)
#define UART_FBRD    	(UART_BASE + 0x28)
#define UART_LCRH   	(UART_BASE + 0x2C)
#define UART_CR	        (UART_BASE + 0x30)
#define UART_IFLS    	(UART_BASE + 0x34)
#define UART_IMSC       (UART_BASE + 0x38)
#define UART_RIS        (UART_BASE + 0x3C)
#define UART_MIS        (UART_BASE + 0x40)
#define UART_ICR        (UART_BASE + 0x44)
#define UART_DMACR      (UART_BASE + 0x48)
#define UART_ITCR       (UART_BASE + 0x80)
#define UART_ITIP       (UART_BASE + 0x84)
#define UART_ITOP       (UART_BASE + 0x88)
#define UART_TDR        (UART_BASE + 0x8C)

#define UART_CR_UARTEN  (0x01)
#define UART_CR_TXE     (0x01 << 8)
#define UART_CR_RXE     (0x01 << 9)
#define UART_DR_DATA    (0xFF)
#define UART_FR_BUSY    (0x1 << 3)
#define UART_FR_RXFE    (0x1 << 4)
#define UART_FR_TXFF    (0x1 << 5)
#define UART_LCRH_WLEN_8BIT  (0x3 << 5)
#define UART_LCRH_FEN   (0x1 << 4)


#endif /* _P_UART_H */ 
