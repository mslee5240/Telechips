#define COMMAND_CLEAR_DISPLAY	0X01

#define COMMAND_DISPLAY_ON_OFF_BIT	2
#define COMMAND_CURSOR_ON_OFF_BIT	1
#define COMMAND_BLINK_ON_OFF_BIT	0

#define START 0x08
#define SLA_W (0x27<<1)    // I2C LCD 주소 0x27 , <<1 이유는 write모드 유지
#define SLA_R (0x27<<1 | 0x01)       // I2C LCD 주소 0x27 , Read모드 유지
//I2C LCD주소는 0x27 인데, <<1로 하는 이유는 wirite 모드를 유지하기 위함.
// 마지막 bit : write bit로 만들기 위함?

void I2C_LCD_init(void);
void I2C_LCD_write_data(uint8_t data);
void I2C_LCD_write_command(uint8_t command);
void I2C_LCD_clear(void);
void I2C_LCD_write_string(char *string);
void I2C_LCD_goto_XY(uint8_t row, uint8_t col);
void I2C_LCD_write_string_XY(uint8_t row, uint8_t col, char *string);

void I2C_LCD_Test();