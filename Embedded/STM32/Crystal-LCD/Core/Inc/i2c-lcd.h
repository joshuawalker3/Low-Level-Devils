#ifndef I2C_LCD_H
#define I2C_LCD_H

#include "main.h"

#ifndef _DELAY
	#ifdef CMSIS_OS_H_
		#define _DELAY(os_mode, x) \
			if (os_mode == NO_RTOS) { \
				HAL_Delay(x); \
			} \
			else { \
				osDelay(x); \
			}
	#else
		#define _DELAY(os_mode, x) HAL_Delay(x)
	#endif
#endif

#define _GET_LOWER_NIBBLE(x) (x << 4)

#define ROW_01 0x00
#define ROW_02 0x40

#define COL_01 0x00
#define COL_02 0x01
#define COL_03 0x02
#define COL_04 0x03
#define COL_05 0x04
#define COL_06 0x05
#define COL_07 0x06
#define COL_08 0x07
#define COL_09 0x08
#define COL_10 0x09
#define COL_11 0x0A
#define COL_12 0x0B
#define COL_13 0x0C
#define COL_14 0x0D
#define COL_15 0x0E
#define COL_16 0x0F

//commands to clear display and return home
#define CLEAR_DISPLAY 0x01
#define RET_HOME 0x02

//Entry mode set and options
#define ENTRY_MODE_SET 0x04
#define CURS_INCR 0x02
#define CURS_DECR 0x00
#define SCREEN_SHIFT_EN 0x01
#define SCREEN_SHIFT_DIS 0x00

//Display control
#define DISP_CTRL 0x08
#define DISP_ON 0x04
#define DISP_OFF 0x00
#define CURS_ON 0x02
#define CURS_OFF 0x00
#define CURS_BLINK 0x01
#define CURS_SOLID 0x00

//Cursor and Display Shift
#define CURS_DISP_SHIFT 0x10
#define SHIFT_DISP 0x08
#define SHIFT_CURS 0x00
#define SHIFT_RIGHT 0x04
#define SHIFT_LEFT 0x00

//Function Set
#define FUNCTION_SET 0x20
#define BIT_MODE_8 0x10
#define BIT_MODE_4 0x00
#define LINES_2 0x08
#define LINES_1 0x00
#define FONT_5x11 0x04
#define FONT_5x8 0x00

//Setting DDRAM and CGRAM Address
#define CGRAM_SET 0x40
#define DDRAM_SET 0x80

//Custom Character cgram addresses
#define CUSTOM_CHAR_MEM_01 0x00
#define CUSTOM_CHAR_MEM_02 0x08
#define CUSTOM_CHAR_MEM_03 0x10
#define CUSTOM_CHAR_MEM_04 0x18
#define CUSTOM_CHAR_MEM_05 0x20
#define CUSTOM_CHAR_MEM_06 0x28
#define CUSTOM_CHAR_MEM_07 0x30
#define CUSTOM_CHAR_MEM_08 0x38

//Custom character DDRAM addresses

//bytes for LCD pin control and byte transmission
#define BIT_COMP 0xF0
#define LIGHT_HI 0x08
#define LIGHT_LO 0x00
#define EN_HI 0x04
#define EN_LO 0x00
#define RW_HI 0x02
#define RW_LO 0x00
#define RS_HI 0x01
#define RS_LO 0x00
#define PACKET_SIZE 4
#define MAX_TIMEOUT 100

//Custom character DDRAM addresses
extern const char CUSTOM_CHAR_01;
extern const char CUSTOM_CHAR_02;
extern const char CUSTOM_CHAR_03;
extern const char CUSTOM_CHAR_04;
extern const char CUSTOM_CHAR_05;
extern const char CUSTOM_CHAR_06;
extern const char CUSTOM_CHAR_07;
extern const char CUSTOM_CHAR_08;

#ifndef OS_MODE_H
	#define OS_MODE_H

	typedef enum {
		NO_RTOS,
		RTOS_MODE
	} Os_Mode;
#endif

typedef enum {
	WRITE_STRING,
	WRITE_INT,
	WRITE_FLOAT,
	WRITE_CUSTOM,
	CREATE_CHAR
} Write_Type;

typedef struct {
	I2C_HandleTypeDef* hi2c;
	uint16_t addr;
	Os_Mode mode;
} Lcd_HandleTypeDef;



HAL_StatusTypeDef lcd_open(Lcd_HandleTypeDef* lcd, I2C_HandleTypeDef* hi2c, uint16_t addr, Os_Mode mode);

HAL_StatusTypeDef lcd_init(Lcd_HandleTypeDef* lcd);

HAL_StatusTypeDef lcd_write(Lcd_HandleTypeDef* lcd, void* data, Write_Type type);

HAL_StatusTypeDef lcd_ioctrl(Lcd_HandleTypeDef* lcd, char cmd);


#endif
