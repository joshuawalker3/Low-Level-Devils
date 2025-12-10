# LCD1602A STM32 Driver

## Overview
This driver was designed for a LCD1602A LCD that is connected to a STM32 microcontroller as a peripheral. Since the vendor HAL was used for implementation, this driver should be able to be used with any STM32 microcontrtoller. This driver can be used both with and without and RTOS with no changes to the code.

Description of how to use the commands are found in the manual [here](https://www.vishay.com/docs/37481/lcd016n002mttiet.pdf).

## Adding Driver to Project
Add i2c-lcd.h and i2c-lcd.c to the projects Inc and Src directories respectively.

## How To Use This Driver
After the desired I2C bus has been initialized, perform the following operations:

- Initialize the LCD handle with lcd_open
- Initialize the LCD using lcd_init
- Write data to the LCD using lcd_write
- Send commands to the LCD using lcd_ioctrl
- Free memory allocated for the LCD handle using lcd_close when operations are completed

## Driver Defines

### Macros
_DELAY(os_mode, x) 
- Delays x microseconds. Uses either HAL_Delay or osDelay based upon os_mode.

_GET_LOWER_NIBBLE(x) 
- Bit shifts x left 4 times 

### Rows
ROW_01\
ROW_02

### Columns 
COL_01\
COL_02\
COL_03\
COL_04\
COL_05\
COL_06\
COL_07\
COL_08\
COL_09\
COL_10\
COL_11\
COL_12\
COL_13\
COL_14\
COL_15\
COL_16

### LCD Commands
#### General
CLEAR_DISPLAY\
RET_HOME
#### Entry Mode Initialization and Options
ENTRY_MODE_SET\
CURS_INCR\
CURS_DECR\
SCREEN_SHIFT_EN\
SCREEN_SHIFT_DIS
#### Display Initialization and Options
DISP_CTRL\
DISP_ON\
DISP_OFF\
CURS_ON\
CURS_OFF\
CURS_BLINK\
CURS_SOLID
#### Cursor and Display Shift Modes
CURS_DISP_SHIFT\
SHIFT_DISP\
SHIFT_CURS\
SHIFT_RIGHT\
SHIFT_LEFT 
#### LCD Function Initialization and Options
FUNCTION_SET\
BIT_MODE_8\
BIT_MODE_4\
LINES_2\
LINES_1\
FONT_5x11\
FONT_5x8 
#### Set CGRAM and DDRAM Address
CGRAM_SET\
DDRAM_SET

### CGRAM Addresses 
CUSTOM_CHAR_MEM_01\
CUSTOM_CHAR_MEM_02\
CUSTOM_CHAR_MEM_03\
CUSTOM_CHAR_MEM_04\
CUSTOM_CHAR_MEM_05\
CUSTOM_CHAR_MEM_06\
CUSTOM_CHAR_MEM_07\
CUSTOM_CHAR_MEM_08

### Custom Character DDRAM Addresses
CUSTOM_CHAR_01\
CUSTOM_CHAR_02\
CUSTOM_CHAR_03\
CUSTOM_CHAR_04\
CUSTOM_CHAR_05\
CUSTOM_CHAR_06\
CUSTOM_CHAR_07\
CUSTOM_CHAR_08

## Enums
### Os_Mode
- NO_RTOS
- RTOS_MODE

### Write_Type
- WRITE_STRING
- WRITE_INT
- WRITE_FLOAT
- WRITE_CUSTOM
- CREATE_CHAR

## Structs
### Lcd_HandleTypeDef
#### Members
- I2C_HandleTypeDef* hi2c
- uint16_t addr
- Os_Mode mode

## Functions
### Function Name
HAL_StatusTypeDef lcd_open(Lcd_HandleTypeDef* lcd, I2C_HandleTypeDef* hi2c, uint16_t addr, Os_Mode mode)
### Function Description
Initializes the LCD handle
### Parameters
- Lcd_HandleTypeDef* lcd
    - Struct representing the LCD
- I2C_HandleTypeDef* hi2c
    -  handle to module that contains the I2C configuration
- uint16_t addr
    - 7 or 10 bit address
- Os_Mode mode
    - Mode that the LCD will be used in. Must be updated programmatically if conditions change
### Return
- HAL_OK on success, HAL_ERROR otherwise

### Function Name
HAL_StatusTypeDef lcd_init(Lcd_HandleTypeDef* lcd)
### Function Description
Initializes the LCD hardware
### Parameters
- Lcd_HandleTypeDef* lcd
    -  Pointer to the handle for the LCD
### Return
- Status of transmissions

### Function Name
HAL_StatusTypeDef lcd_write(Lcd_HandleTypeDef* lcd, void* data, Write_Type type)
### Function Description
Writes data to LCD to display
### Parameters
- Lcd_HandleTypeDef* lcd
    -  Pointer to the handle for the LCD
- void* data
    - pointer to data to be sent
- Write_Type type
    - Type of data to write to LCD
### Return
- Status of transmissions

### Function Name
HAL_StatusTypeDef lcd_ioctrl(Lcd_HandleTypeDef* lcd, char cmd)
### Function Description
Sends command to LCD
### Parameters
- Lcd_HandleTypeDef* lcd
    -  Pointer to the handle for the LCD
- char cmd
    - 8-bit command to be sent
### Return
- Status of transmissions

### Function Name
HAL_StatusTypeDef lcd_close(Lcd_HandleTypeDef* lcd)
### Function Description
Closes LCD stream and frees allocated memory
### Parameters
- Lcd_HandleTypeDef* lcd
    -  Pointer to the handle for the LCD
### Return
- Status upon completion of operation