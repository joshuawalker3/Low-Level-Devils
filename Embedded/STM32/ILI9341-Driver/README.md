# ILI9341 STM32 Driver

## Overview
This driver was designed for a ILI9341 display that is connected to a STM32 microcontroller as a peripheral. Since the vendor HAL was used for implementation, this driver should be able to be used with any STM32 microcontrtoller. This driver can be used both with and without and RTOS with no changes to the code.

Description of how to use the commands are found in the manual [here](https://www.digikey.com/htmldatasheets/production/1640716/0/0/1/ili9341-datasheet.html).

## Adding Driver to Project
- To core/Inc add:
    - ILI9341.h
    - font.h
- To core/Src add:
    - ILI9341.c
    - font.c

## How To Use This Driver
After the desired SPI bus has been initialized, perform the following operations:

- Initialize the display with ili9341_init
- Use whatever write operation is needed to display data to the display

## Driver Defines

### Macros
_DELAY(os_mode, x) 
- Delays x microseconds. Uses either HAL_Delay or osDelay based upon os_mode.

### Display Commands
SOFTWARE_RESET <br>
PWR_CTL_1 <br>
PWR_CTL_2 <br>
VCOM_CTL_1 <br>
VCOM_CTL_2 <br>
MEM_ACC_CTL <br>
PIXEL_FMT_SET <br>
FRAME_CTL <br>
DISP_FUNC_CTL <br>
GAMMA_SET <br>
POS_GAMMA_CORR <br>
NEG_GAMMA_CORR <br>
EXIT_SLEEP <br>
COL_ADDR_SET <br>
PAGE_ADDR_SET <br>
MEM_WRITE <br>
SCREEN_ON <br>
SCREEN_OFF <br>

### Display Defaults
ILI9341_MADCTL_MX  <br>
ILI9341_MADCTL_BGR <br>
ILI9341_WIDTH  <br>
ILI9341_HEIGHT <br>
ILI9341_ROTATION <br>
ILI9341_MAX_DELAY <br>
ILI9341_MAX_BUFF_SIZE <br>

## Enums
### Os_Mode
- NO_RTOS
- RTOS_MODE

### Screen_Status
- SCREEN_OFF
- SCREEN_ON

## Structs
### Ili9341_HandleTypeDef
#### Members
- `SPI_HandleTypeDef*` hspi
- `uint16_t` cs_pin
- `uint16_t` dc_pin
- `uint16_t` screen_reset_pin
- `GPIO_TypeDef*` cs_gpio_port
- `GPIO_TypeDef*` dc_gpio_port
- `GPIO_TypeDef*` screen_reset_gpio_port
- `Os_Mode` mode

### Ili9341_AreaTypeDef
#### Members
- `uint16_t` x_pos
- `uint16_t` y_pos
- `uint16_t` width
- `uint16_t` height
- `uint16_t*` buffer

### Ili9341_CharacterTypeDef
#### Members
- `Ili9341_AreaTypeDef*` area;
- `uint16_t` pri_color;
- `uint16_t` bkgd_color;
- `uint16_t*` pixels;

## Functions
### Function Name
`HAL_StatusTypeDef` ili9341_init(Ili9341_HandleTypeDef* ili9341)
#### Function Description
Initializes the display
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
#### Return
- HAL_OK on success, other HALStatusTypeDef on failure

### Function Name
`void` ili9341_reset(Ili9341_HandleTypeDef* ili9341)
#### Function Description
Performs software reset on display
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
#### Return
- None

### Function Name
`void` ili9341_select(Ili9341_HandleTypeDef* ili9341)
#### Function Description
Pulls CS pin low for display
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
#### Return
- None

### Function Name
`void` ili9341_unselect(Ili9341_HandleTypeDef* ili9341)
#### Function Description
Pulls CS pin high for display
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
#### Return
- None

### Function Name
`HAL_StatusTypeDef` ili9341_write_cmd(Ili9341_HandleTypeDef* ili9341, uint8_t cmd)
#### Function Description
Writes command to display
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
- `uint8_t` cmd
    - Command to be sent 
#### Return
- HAL Status upon completion of operation

### Function Name
`HAL_StatusTypeDef` write_data(Ili9341_HandleTypeDef* ili9341, uint8_t* data, size_t data_size)
#### Function Description
Writes data to display
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
- `uint8_t*` data
    - pointer to data to be sent
- `size_t` data_size
    - size in bytes of data to be sent
#### Return
- HAL Status upon completion of operation

### Function Name
`HAL_StatusTypeDef` ili9341_set_address_window(Ili9341_HandleTypeDef* ili9341, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
#### Function Description
Sets the addressing window in display RAM
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
- `uint16_t` x0
    - starting page (row)
- `uint16_t` y0
    - starting column
- `uint16_t` x1
    - ending page (row)
- `uint16_t` y1
    - ending column
#### Return
- HAL Status upon completion of operation

### Function Name
`HAL_StatusTypeDef` ili9341_draw_pixel(Ili9341_HandleTypeDef* ili9341, uint16_t x, uint16_t y, uint16_t color)
#### Function Description
Draws a single pixel
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
- `uint16_t` x
    - x coordinate
- `uint16_t` y
    - y coordinate
- `uint16_t` color
    - RGB565 color to draw
#### Return
- HAL Status upon completion of operation

### Function Name
`HAL_StatusTypeDef` ili9341_draw_area(Ili9341_HandleTypeDef* ili9341, Ili9341_AreaTypeDef* area)
#### Function Description
Draws an area on the display
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
- `Ili9341_AreaTypeDef*` area
    - An area to draw 
#### Return
- HAL Status upon completion of operation

### Function Name
`HAL_StatusTypeDef` ili9341_draw_character(Ili9341_HandleTypeDef* ili9341, Ili9341_CharacterTypeDef* character, uint16_t scale)
#### Function Description
Draws a scaled character to the screen
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
- `Ili9341_CharacterTypeDef*` character
    - The character to draw
- `uint16_t` scale
    - The scale to use. For example, a scale of 1 would draw a characte of 5x8 font size
#### Return
- HAL Status upon completion of operation

### Function Name
`HAL_StatusTypeDef` ili9341_screen_control(Ili9341_HandleTypeDef* ili9341, Screen_Status status)
#### Function Description
Update screen status
#### Parameters
- `Ili9341_HandleTypeDef*` ili9341
    - The struct representing the display
- `Screen_Status` status
    - Requested status
#### Return
- HAL Status upon completion of operation
