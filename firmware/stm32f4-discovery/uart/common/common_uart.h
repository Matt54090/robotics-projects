#ifndef COMMON_UART_H
#define COMMON_UART_H

typedef enum {
    STATUS_BUSY = -2,
    STATUS_ERROR,
    STATUS_SUCCESS,
    STATUS_IDLE = 0,
    STATUS_READY
} status_e;

#endif /* COMMON_UART_H */
