#include "drivers/i2c.h"
#include "common/defines.h"
#include <msp430.h>
#include <stdbool.h>

#define DEFAULT_SLAVE_ADDRESS (0x29)

i2c_result_e i2c_write(const uint8_t *addr, uint8_t addr_size, const uint8_t *data,
                       uint8_t data_size)
{
    (void)addr;
    (void)addr_size;
    (void)data;
    (void)data_size;
    return I2C_RESULT_OK;
}

i2c_result_e i2c_read(const uint8_t *addr, uint8_t addr_size, uint8_t *data, uint8_t data_size)
{
    (void)addr;
    (void)addr_size;
    (void)data;
    (void)data_size;
    return I2C_RESULT_OK;
}

i2c_result_e i2c_read_addr8_data8(uint8_t addr, uint8_t *data)
{
    return i2c_read(&addr, 1, data, 1);
}

i2c_result_e i2c_read_addr8_data16(uint8_t addr, uint16_t *data)
{
    return i2c_read(&addr, 1, (uint8_t *)data, 2);
}

i2c_result_e i2c_read_addr8_data32(uint8_t addr, uint32_t *data)
{
    return i2c_read(&addr, 1, (uint8_t *)data, 4);
}

i2c_result_e i2c_write_addr8_data8(uint8_t addr, uint8_t data)
{
    return i2c_write(&addr, 1, &data, 1);
}

void i2c_set_slave_address(uint8_t addr)
{
    UCB0I2CSA = addr;
}

static bool initialized = false;
void i2c_init(void)
{
    if (initialized) return;

    // Must set reset while configuring
    UCB0CTL1 |= UCSWRST;
    // Single master, synchronous mode, I2C mode
    UCB0CTL0 = UCMST + UCSYNC + UCMODE_3;
    // SMCLK
    UCB0CTL1 |= UCSSEL_2;
    // SMCLK/160 ~= 100 kHz
    UCB0BR0 = 160;
    UCB0BR1 = 0;
    // Clear reset
    UCB0CTL1 &= ~UCSWRST;
    i2c_set_slave_address(DEFAULT_SLAVE_ADDRESS);

    initialized = true;
}
