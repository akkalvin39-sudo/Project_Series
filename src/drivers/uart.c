#include "drivers/uart.h"
#include "common/defines.h"
#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#define BRCLK (SMCLK)
#define UART_BAUD_RATE (115200u)

static void uart_configure(void)
{
    // Reset module
    UCA0CTL1 &= UCSWRST;

    // Use default (data word length 8 bits, 1 stop bit, no parity bit)
    UCA0CTL0 = 0;

    // Set SMCLK as clock source
    UCA0CTL1 |= UCSSEL_2;

    // Clear reset to release the module for operation
    UCA0CTL1 &= ~UCSWRST;
}

static bool initialized = false;
void uart_init(void)
{
    if (initialized) return;
    uart_configure();
    initialized = true;
}

// mpaland/printf needs this to be named _putchar
void _putchar(char c)
{
    // Some terminals expect carriage return before line-feed
    if (c == '\n') {
        _putchar('\r');
    }

    UCA0TXBUF = c;
    while (!(IFG2 & UCA0TXIFG)) { }
}

void uart_init_assert(void)
{
    uart_configure();
}

void uart_trace_assert(const char *string)
{
    int i = 0;
    while (string[i] != '\0') {
        _putchar(string[i]);
        i++;
    }
}
