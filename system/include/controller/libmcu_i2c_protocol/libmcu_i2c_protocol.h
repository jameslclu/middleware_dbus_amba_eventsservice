#ifndef _LIB_MCU_I2C_PROTOCOL_H_
#define _LIB_MCU_I2C_PROTOCOL_H_

#include <sys/types.h>
#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define LIB_MCU_I2C_PROTOCOL_VERSION    "v1"

#define CMD_OFF             0
#define CMD_ON              1
#define CMD_READ            1
#define CMD_WRITE           2

typedef enum {
    CMD_IDX_SIGN        = 0x00,
    CMD_IDX_CMD         = 0x01,
    CMD_IDX_DATA0       = 0x02,
    CMD_IDX_DATA1       = 0x03,
    CMD_IDX_DATA2       = 0x04,
    CMD_IDX_DATA3       = 0x05,
    CMD_IDX_DATA4       = 0x06,
    CMD_IDX_DATA5       = 0x07,
    CMD_IDX_DATA6       = 0x08,
    CMD_IDX_DATA7       = 0x09,
} kMCD_IDX;

typedef enum {
    CMD_CONNECT_TEST    = 0x01,
    CMD_HEATER_PWM      = 0x02,
    CMD_SIREN_CTL       = 0x03,
    CMD_FW_VERSION      = 0x04,
    CMD_TEMP_LED_CTL    = 0x05,
    CMD_CHARGER_REG     = 0x08,
    CMD_TEMPERATURE     = 0x49,
    CMD_GSENSOR_DATA    = 0x4C,
} kMCU_CMD;

typedef struct {
    unsigned char cmd;
    unsigned char len;
} cmd_table_t;

typedef struct {
    unsigned char data[3];
} fw_version_t;

int MCU_CMD_Init(void);
int MCU_CMD_DeInit(void);
int MCU_CMD_Library_Ver(char *szVersion);

int MCU_CMD_Connect_Test(void);
int MCU_CMD_Set_Heater_PWM(const uint8_t enable, const uint8_t u8Duty);
int MCU_CMD_Set_Siren_OnOff(const uint8_t u8OnOff);
int MCU_CMD_Get_Firmware_Version(fw_version_t *isp_ver, fw_version_t *aprom_ver);
int MCU_CMD_Set_Temp_LED_OnOff(const uint8_t u8OnOff);
int MCU_CMD_Get_Charger_Cell(uint8_t *BatteryCellCharger);
int MCU_CMD_Set_Charger_Reg(const uint8_t REG, const uint16_t u16Value);
int MCU_CMD_Get_Charger_Reg(const uint8_t REG, uint16_t *u16Value);
int MCU_CMD_Get_Temperature(char *temp);
int MCU_CMD_Get_GSensor_Data(uint8_t g_sensor[], uint8_t *data_len);

#ifdef  __cplusplus
}
#endif

#endif

