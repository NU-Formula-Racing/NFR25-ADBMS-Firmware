#include "adBms_Application.h"
#include "adbms_update_values.h"
#include "fsm.h"

fsm_t *g_fsm;

typedef struct fsm_context
{
    // something something
    int stamina;
} fsm_context_t;
// placeholder

void adbms_mainboard_setup();
void adbms_mainboard_loop();