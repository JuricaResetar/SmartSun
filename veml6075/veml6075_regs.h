/*
* veml6075 lib
* Made by Jurica Resetar
* ResetarJurica@gmail.com
*
* All rights reserved
*
*/


#ifndef __VEML6075_REGS_H__
#define __VEML6075_REGS_H__

/* Registers define */
#define VEML6075_CONF_REG               (0x00)
#define VEML6075_UVA_DATA_REG           (0x07)
#define VEML6075_UVB_DATA_REG           (0x09)
#define VEML6075_UVCOMP1_DATA_REG       (0x0A)
#define VEML6075_UVCOMP2_DATA_REG       (0x0B)
#define VEML6075_ID_REG                 (0x0C)
/* Register value define : CONF */
#define VEML6075_CONF_SD                (0x01)
#define VEML6075_CONF_UV_AF_AUTO        (0x00)
#define VEML6075_CONF_UV_AF_FORCE       (0x02)
#define VEML6075_CONF_UV_TRIG_NO        (0x00)
#define VEML6075_CONF_UV_TRIG_ONCE      (0x04)
#define VEML6075_CONF_HD                (0x08)
#define VEML6075_CONF_UV_IT_MASK        (0x70)
#define VEML6075_CONF_UV_IT_50MS        (0x00)
#define VEML6075_CONF_UV_IT_100MS       (0x10)
#define VEML6075_CONF_UV_IT_200MS       (0x20)
#define VEML6075_CONF_UV_IT_400MS       (0x30)
#define VEML6075_CONF_UV_IT_800MS       (0x40)
#define VEML6075_CONF_DEFAULT           (VEML6075_CONF_UV_AF_AUTO | \
                                         VEML6075_CONF_UV_TRIG_NO | \
                                         VEML6075_CONF_UV_IT_100MS)

#endif  // __VEML6075_REGS_H__
