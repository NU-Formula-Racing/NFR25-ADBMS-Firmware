#include "adbms_update_values.h"
#include "adBMS_Application.h"
#include "adbms_mainboard.h"

void ADBMS_UpdateValues() {
    // get voltages from ADBMS;
    // get temp from ADBMS;
    // run open wire check -> have to look into
    // calculate the SOE;  // ignore for now

    // update STM32 Pin values;
        // reads: shutdown_contactors, IMD_Status, Current_ADC, 6822_State
        // writes: BMS_Status, GPIO_LEDs
}