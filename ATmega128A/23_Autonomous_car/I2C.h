void init_I2C(unsigned int baud);
void I2C_start(void);
void I2C_transmit(uint8_t data);
void I2C_write_byte(uint8_t address, uint8_t data);
void I2C_stop(void);
uint8_t I2C_receive_ACK(void);
uint8_t I2C_receive_NACK(void);
