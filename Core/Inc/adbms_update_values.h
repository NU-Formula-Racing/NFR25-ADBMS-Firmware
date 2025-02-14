#include "adBms6830CmdList.h"
#include "adBms6830GenericType.h"

const float OV_THRESHOLD = 4.2;  /* Volt */
const float UV_THRESHOLD = 3.0;  /* Volt */
const int OWC_Threshold = 2000;  /* Cell Open wire threshold(mili volt) */
const int OWA_Threshold = 50000; /* Aux Open wire threshold(mili volt) */
OW_C_S CELL_OPEN_WIRE_DETECTION = OW_ON_ALL_CH;
OW_AUX AUX_OPEN_WIRE_DETECTION = AUX_OW_ON;
CH AUX_CH_TO_CONVERT = AUX_ALL;
PUP OPEN_WIRE_CURRENT_SOURCE = PUP_UP;
typedef struct
{
    uint8_t TOTAL_IC;
    cell_asic *IC;
} cell;

typedef struct
{
    cell system;
    float total_v;
    float max_v;
    float min_v;
    float avg_v;

    float total_temp;
    float max_temp;
    float min_temp;
    float avg_temp;
} adbms_;

cell ADBMS_Initialize(uint8_t ic_count);

void ADBMS_UpdateValues(adbms_ *adbms);
void ADBMS_CalculateValues(adbms_ *adbms);
void ADBMS_delete(adbms_ *adbms);