#ifndef UART_H
#define UART_H

int open_uart(char *dev);
void set_uart_configure(int fd, int speed,int data_bits, int stop_bits, char parity);


#endif
