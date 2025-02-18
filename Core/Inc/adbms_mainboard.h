#include "adBms_Application.h"
#include "adbms_update_values.h"
#include "fsm.h"
#include "stm32f4xx_hal.h"

fsm_t *g_fsm;

typedef struct fsm_context
{
    // something something
    bool fault_;
} fsm_context_t;
// placeholder

bool undervoltage_fault_ = false;
bool overvoltage_fault_ = false;
bool undertemperature_fault_ = false;
bool overtemperature_fault_ = false;
bool overcurrent_fault_ = false;
bool external_kill_fault_ = false;
bool timeout_fault_ = false;


void adbms_mainboard_setup();
void adbms_mainboard_loop();