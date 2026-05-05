/*
 * emu_tc_programming.cpp
 *
 *  Created on: Oct 26, 2024
 *      Author: Oscar Rodriguez Polo
 */

/****************************************************************************
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 *
 ****************************************************************************/

#include <public/emu_hw_timecode_drv_v1.h>
#include <public/emu_sc_channel_drv_v1.h>
#include <public/emu_gss_v1.h>

#define OBT_START_FT_ST05_12 (OBT_AFTER_POWER_ON )

#define FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080

#define FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090
#define FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100

#ifdef FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080

#define FT_0080_TIME_step0 (OBT_START_FT_ST05_12 + 3)
#define FT_0080_TIME_step1 (OBT_START_FT_ST05_12 + 5)
#define FT_0080_TIME_step2 (OBT_START_FT_ST05_12 + 7)
#define FT_0080_TIME_step3 (OBT_START_FT_ST05_12 + 18)
#define FT_0080_TIME_step4 (OBT_START_FT_ST05_12 + 40)
#define FT_0080_TIME_step5 (OBT_START_FT_ST05_12 + 60)

EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_0(FT_0080_TIME_step0,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 0, Set PID 15 to 10 (within limits)",
		15, 10);

EmuGSS_TCProgram12_5_Limit_UINT8 prog_FT_0080_step_1(FT_0080_TIME_step1,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 1, Config PMODID 0 for monitoring PID 15 with limits [1,20], interval 1, repetition 2, EvLowLimit=0x40001, EvHighLimit=0x40002",
		0, 15, 1, 2, 1, 0x4001, 20, 0x4002);

EmuGSS_TCProgram12_1 prog_FT_0080_step_2(FT_0080_TIME_step2,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 2, Enable Monitoring PMODID 0",
		0);

EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_3(FT_0080_TIME_step3,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 3, Update PID 15 to 99",
		15, 99);

EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_4(FT_0080_TIME_step4,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 4, Update PID 15 to 5",
		15, 5);

EmuGSS_TCProgram20_3_uint8 prog_FT_0080_step_5(FT_0080_TIME_step5,
		"FT_UAH_ASW_ICU_SERVS_5_12_Limits_Monitoring_0080 step 5, Update PID 15 to 0",
		15, 0);

#endif

EmuGSS_TCProgram20_3_uint8 prog_FT_0090_step_0(OBT_START_FT_ST05_12 + 0,
		"FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090 step 0, Set PID 15 to 10 (within limits)",
		15, 10);

// Paso 1: Configurar la monitorización (igual que el 0080)
EmuGSS_TCProgram12_5_Limit_UINT8  prog_FT_0090_step_1(OBT_START_FT_ST05_12 + 5,
		"FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090 step 1, Config PMODID 0 for monitoring PID 15 with limits [1,20], interval 1, repetition 2, EvLowLimit=0x4001, EvHighLimit=0x4002",
		0, 15, 1, 2, 1, 0x4001, 20, 0x4002);

// Paso 2: Habilitar la monitorización
EmuGSS_TCProgram12_1 prog_FT_0090_step_2(OBT_START_FT_ST05_12 + 7,
		"FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090 step 2, Enable Monitoring PMODID 0",
		0);

// Novedad del Test 0090: Deshabilitar el reporte del evento de límite alto (0x4002)
EmuGSS_TCProgram5_6 prog_FT_0090_disable_ev(OBT_START_FT_ST05_12 + 12,
		"FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090, Disable Event 0x4002",
		0x4002);

// Paso 3: Forzar el límite alto. El monitor lo detectará, pero NO generará TM[5,4]
EmuGSS_TCProgram20_3_uint8 prog_FT_0090_step_3(OBT_START_FT_ST05_12 + 18,
		"FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090 step 3, Update PID 15 to 99",
		15, 99);

// Paso 4: Devolver el parámetro a su rango normal
EmuGSS_TCProgram20_3_uint8 prog_FT_0090_step_4(OBT_START_FT_ST05_12 + 40,
		"FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090 step 4, Update PID 15 to 5",
		15, 5);

// Paso 5: Forzar el límite bajo. Como el evento 0x4001 SÍ está habilitado, este SÍ generará TM[5,4]
EmuGSS_TCProgram20_3_uint8 prog_FT_0090_step_5(OBT_START_FT_ST05_12 + 60,
		"FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090 step 5, Update PID 15 to 0",
		15, 0);

#ifdef FT_UAH_ASW_ICU_SERVS_5_12_EvDisabled_0090

#define FT_0090_TIME_step0 (OBT_START_FT_ST05_12 + 3)
#define FT_0090_TIME_step1 (OBT_START_FT_ST05_12 + 5)
#define FT_0090_TIME_step2 (OBT_START_FT_ST05_12 + 7)
#define FT_0090_TIME_step3 (OBT_START_FT_ST05_12 + 12)
#define FT_0090_TIME_step4 (OBT_START_FT_ST05_12 + 18)
#define FT_0090_TIME_step5 (OBT_START_FT_ST05_12 + 40)
#define FT_0090_TIME_step6 (OBT_START_FT_ST05_12 + 60)


#endif

EmuGSS_TCProgram20_3_uint8 prog_FT_0100_step_0(OBT_START_FT_ST05_12 + 0,
		"FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100 step 0, Set PID 16 to Expected Value 0x03",
		16, 0x03);

// Paso 1: Configurar la monitorización (CheckType = Expected Value)
// Params: time, brief, PMONID(1), PID(16), interval(1), rep(2), mask(0x0F), expected(0x03), EvID(0x4003)
EmuGSS_TCProgram12_5_Value_UINT8 prog_FT_0100_step_1(OBT_START_FT_ST05_12 + 5,
		"FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100 step 1, Config PMODID 1 for PID 16, mask 0x0F, exp 0x03",
		1, 16, 1, 2, 0x0F, 0x03, 0x4003);

// Paso 2: Habilitar la monitorización del PMONID 1
EmuGSS_TCProgram12_1 prog_FT_0100_step_2(OBT_START_FT_ST05_12 + 7,
		"FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100 step 2, Enable Monitoring PMODID 1",
		1);

// Paso 3: Alterar el valor a 0x02. Al no coincidir con el expected value, saltará el evento 0x4003.
EmuGSS_TCProgram20_3_uint8 prog_FT_0100_step_3(OBT_START_FT_ST05_12 + 15,
		"FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100 step 3, Update PID 16 to unexpected value 0x02",
		16, 0x02);

// Paso 4: Restaurar el valor a 0x03 para verificar la transición de vuelta a la normalidad en TM[12,12]
EmuGSS_TCProgram20_3_uint8 prog_FT_0100_step_4(OBT_START_FT_ST05_12 + 30,
		"FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100 step 4, Restore PID 16 to 0x03",
		16, 0x03);

#ifdef FT_UAH_ASW_ICU_SERVS_5_12_MonMaskedValue_0100


#endif

