#include "adbms_update_values.h"

void ADBMS_UpdateValues(adbms_ *adbms)
{
    adBmsWakeupIc(adbms->system.TOTAL_IC);
    // get voltages from ADBMS
    adBmsReadData(adbms->system.TOTAL_IC, adbms->system.IC, RDCVALL, Cell, NONE);
    // get temp from ADBMS

    // run open wire check -> have to look into

    // calculate the SOC;  // ignore for now
}

void ADBMS_CalculateValues(adbms_ *adbms)
{
    // calculate the total, max, and min voltage
    adbms->total_v = 0;
    adbms->max_v = 0;
    adbms->min_v = 5;
    for (int i = 0; i < adbms->system.TOTAL_IC; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            adbms->total_v += adbms->system.IC[i].cell.c_codes[j];
            if (adbms->system.IC[i].cell.c_codes[j] > adbms->max_v)
            {
                adbms->max_v = adbms->system.IC[i].cell.c_codes[j];
            }
            if (adbms->system.IC[i].cell.c_codes[j] < adbms->min_v)
            {
                adbms->min_v = adbms->system.IC[i].cell.c_codes[j];
            }
        }
    }

    // calculate the avg voltage
    adbms->avg_v = adbms->total_v / (adbms->system.TOTAL_IC * 16);

    // calculate the total, max, and min temp
    // calculate the avg temp
}

cell ADBMS_Initialize(uint8_t ic_count)
{
    cell system;
    system.TOTAL_IC = ic_count;
    system.IC = malloc(ic_count * sizeof(cell_asic));
    for (uint8_t cic = 0; cic < ic_count; cic++)
    {
        /* Init config A */
        system.IC[cic].tx_cfga.refon = PWR_UP;
        system.IC[cic].tx_cfga.gpo = 0X3FF;
        system.IC[cic].tx_cfgb.vov = SetOverVoltageThreshold(OV_THRESHOLD);
        system.IC[cic].tx_cfgb.vuv = SetUnderVoltageThreshold(UV_THRESHOLD);
    }
    adBmsWakeupIc(ic_count);
    adBmsWriteData(ic_count, &system.IC[0], WRCFGA, Config, A);
    adBmsWriteData(ic_count, &system.IC[0], WRCFGB, Config, B);
}

void ADBMS_delete(adbms_ *adbms)
{
    free(adbms->system.IC);
}