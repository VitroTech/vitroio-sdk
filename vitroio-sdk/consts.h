#ifndef VITROIO_SDK_CONSTS_H
#define VITROIO_SDK_CONSTS_H

/**
 * @file consts.h
 *
 * @brief The file contains constants of vitro-shard-sdk for user usage.
 */

/**
 * @def VITROIO_CONSTS_ENVIRONMENT_REQUIRED_FLASH_SIZE
 * @brief Defines required flash memory size in bytes for storing environment
 * variables.
 */
#define VITROIO_CONSTS_ENVIRONMENT_REQUIRED_FLASH_SIZE 0x28

#define VITROIO_REGION_A_FLASH_OFFSET       0x10800
#define VITROIO_REGION_B_FLASH_OFFSET       0x88000
// Sectors sizes may differ for other targets
#define VITROIO_REGION_FLASH_SECTORS        239

#define VITROIO_ENVIRONMENT_FLASH_OFFSET    0x10000
#define VITROIO_ENVIRONMENT_FLASH_SECTORS   1 // 1*2048=2048 (0x800)

#define DEBUG    0

/**
 * Variables listed below contains Shard V2 pinout adjusted to its design.
 * Names are compatible with schematics. When you create your own application
 * include const.h header file and use defined names rather than pin names
 * directly.
 */

#define UART_DEBUG_TX   PC_12
#define UART_DEBUG_RX   PD_2

#define UART_USER_TX    PA_0
#define UART_USER_RX    PA_1

#define UART_RS232_TX   PA_2
#define UART_RS232_RX   PA_3

#define UART_RS485_DE   PB_1
#define UART_RS485_TX   PB_10
#define UART_RS485_RX   PB_11

#define CAN_RX          PB_8
#define CAN_TX          PB_9

#define I2C1_SDA        PB_7
#define I2C1_SCL        PB_6

#define I2C3_SDA        PC_1
#define I2C3_SCL        PC_0

#define SPI1_NSS        PA_4
#define SPI1_SCK        PA_5
#define SPI1_MISO       PA_6
#define SPI1_MOSI       PA_7

#define USB_OTG_FS_DP   PA_12
#define USB_OTG_FS_DM   PA_11
#define USB_OTG_FS_VBUS PA_9
#define USB_OTG_PPWR    PC_6
#define USB_OTG_PRDY    PB_13
#define USB_OTG_OVRCR   PB_12

#define ADC1_IN1        PC_0
#define ADC1_IN2        PC_1
#define ADC1_IN5        PA_0
#define ADC1_IN6        PA_1
#define ADC1_IN9        PA_4
#define ADC1_IN10       PA_5
#define ADC1_IN11       PA_6
#define ADC1_IN12       PA_7

#define GPIO_PC10       PC_10
#define GPIO_PC11       PC_11

#define HARD_3V3_EN_N_PC3   PC_3

#endif // VITROIO_SDK_CONSTS_H
