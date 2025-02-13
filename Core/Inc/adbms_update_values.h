#include "adBms6830CmdList.h"
#include "adBms6830GenericType.h"

const float OV_THRESHOLD = 4.2; /* Volt */
const float UV_THRESHOLD = 3.0; /* Volt */
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