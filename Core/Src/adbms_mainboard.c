#include "adbms_mainboard.h"
#include "adbms_can.h"
#define FSM_IMPL
adbms_ adbms;


#define Contactor_N_ctrl_pin GPIO_PIN_8
#define Contactor_P_ctrl_pin GPIO_PIN_9
#define Contactor_Pre_ctrl_pin GPIO_PIN_10


void adbms_mainbaord_setup()
{
    // initialize the contactors;
    // initialize ad chip;

    // initialize CAN
    HAL_CAN_Start(&hcan1);

    // Enable notifications (interrupts) for CAN, uses FIFO scheduling to receive msgs
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

    // add the CAN to the timer group with a different timer (one for drive, one for data)
    // initialize Charger; // do later

    // FMS Init

    adbms.system = ADBMS_Initialize(1);
    //fsm_context_t context = {0};
    g_fsm = FSM_CREATE(&context);
    FSMAddStates();
    FSMAddTransitions();

    // initialize the timer group with adbms_mainboard_loop
}

// Loop that gets ticked
void adbms_mainboard_loop()
{
    // feed watchdog;
    UpdateValues();
    CheckFaults();
    fsm_run();
}

void initialize_can_headers() {
    // SOE header initialization
    TxHeaderSOE_.StdId = 0x173;
    TxHeaderSOE_.IDE = CAN_ID_STD;
    TxHeaderSOE_.RTR = CAN_RTR_DATA;
    TxHeaderSOE_.DLC = 8; // we're sending 8 bytes of data for SOE
}

void add_can_messages() {
    
}

void add_soe_can_data() {
    
}

void UpdateValues()
{
    // ADBMS values
    ADBMS_UpdateValues();
    ADBMS_CalculateValues();
    // update STM32 Pin values;
    // reads: shutdown_contactors, IMD_Status, Current_ADC, 6822_State
    // writes: BMS_Status, GPIO_LEDs
}

// CAN Loops - Do later
void data_can_loop()
{
    // Send out
    // voltages: pack voltage, max cell voltage, min cell voltage, avg cell voltage
    // temp: max temp, avg temp
    // misc: BMS_state, IMD_state
}
void drive_can_loop()
{
    // send out everything
}

void CheckFaults()
{
    // check overvoltage fault;  --> has register for it
    // check undervoltage fault;   --> has register for it
    // check overcurrent fault;
    // check overtemperature fault;
    // check undertemperature fault;
    // check external kill fault;
    // check timeout fault; (watchdog not fed)
    
    ((fsm_context_t *)context)->fault_ = CheckADInternalFault() || external_kill_fault_ || timeout_fault_;
    // raise fault flag if any fault is true;
}

// FSM Functions //

// On_Enters
void idle_on_enter(fsm_t *fsm, void *context)
{
    printf("entering idle...\n");

    // open contactors;
    HAL_GPIO_WritePin(GPIOA, Contactor_N_ctrl_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Contactor_P_ctrl_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Contactor_Pre_ctrl_pin, GPIO_PIN_RESET);

    // send idle msg;
}
void precharge_on_enter(fsm_t *fsm, void *context)
{
    printf("entering precharge...\n");

    // turn on P contactor
    HAL_GPIO_WritePin(GPIOA, Contactor_P_ctrl_pin, GPIO_PIN_SET);
    // turn on Pre contactor;
    HAL_GPIO_WritePin(GPIOA, Contactor_Pre_ctrl_pin, GPIO_PIN_SET);
}
void active_on_enter(fsm_t *fsm, void *context)
{
    printf("entering active...\n");
    // turn on N contactor;
    HAL_GPIO_WritePin(GPIOA, Contactor_N_ctrl_pin, GPIO_PIN_SET);
    // delay(0.1 sec);
    HAL_Delay(100);
    // turn off Pre contactor;
     HAL_GPIO_WritePin(GPIOA, Contactor_Pre_ctrl_pin, GPIO_PIN_SET);
    // send active msg;

}
void charge_on_enter(fsm_t *fsm, void *context)
{
    printf("entering charge...\n");
    // send initial/start msg to charger;
}
void fault_on_enter(fsm_t *fsm, void *context)
{
    printf("entering fault...\n");
    // open (turn off) all contactors;
    HAL_GPIO_WritePin(GPIOA, Contactor_N_ctrl_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Contactor_P_ctrl_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Contactor_Pre_ctrl_pin, GPIO_PIN_RESET);
    // send fault msg;
}

// On_Updates
void idle_on_update(fsm_t *fsm, void *context) {}
void precharge_on_update(fsm_t *fsm, void *context)
{
    // get inverter voltage;
}
void active_on_update(fsm_t *fsm, void *context) {}
void charge_on_update(fsm_t *fsm, void *context)
{
    /*
    do actual implementation later
    send current request to charger;
    if(charger responding && current flowing){
        // CellBalance();
    }
    if(charged to full){
        stop charging;
    }
    */
}
void fault_on_update(fsm_t *fsm, void *context) {}

// On_Exits
void idle_on_exit(fsm_t *fsm, void *context) { printf("exiting idle..."); }
void precharge_on_exit(fsm_t *fsm, void *context) { printf("exiting precharge..."); }
void active_on_exit(fsm_t *fsm, void *context) { printf("exiting active..."); }
void charge_on_exit(fsm_t *fsm, void *context) { printf("exiting charge..."); }
void fault_on_exit(fsm_t *fsm, void *context) { printf("exiting fault..."); }

// Predicates

// Transition to idle
bool transition_active_to_idle(fsm_t *fsm, void *context)
{
    if (/*ECU or charger requests idle*/true)
        return true;
    return false;
}
bool transition_fault_to_idle(fsm_t *fsm, void *context)
{
    if (!((fsm_context_t *)context)->fault_)
        return true;
    return false;
}

// Transition to precharge
bool transition_idle_to_precharge(fsm_t *fsm, void *context)
{
    if (/*ECU / Charger signals precharge transition*/true)
        return true;
    return false;
}

// Transition to active
bool transition_precharge_to_active(fsm_t *fsm, void *context)
{
    if (/*ECU signals active transition*/true)
        return true;
    return false;
}

bool transition_charge_to_active(fsm_t *fsm, void *context)
{
    if (/*charge bit unset*/true)
        return true;
    return false;
}

// Transition to charge
bool transition_active_to_charge(fsm_t *fsm, void *context)
{
    if (/*charge pin is high*/true)
        return true;
    return false;
}

// Transition to fault
bool transition_to_fault(fsm_t *fsm, void *context)
{
    if (((fsm_context_t *)context)->fault_)
        return true;
    return false;
}

// Add FSM states
void FSMAddStates()
{
    fsm_add_state(g_fsm, (fsm_state_t){.name = "Idle",
                                     .on_enter = idle_on_enter,
                                     .on_update = idle_on_update,
                                     .on_exit = idle_on_exit});

    fsm_add_state(g_fsm, (fsm_state_t){.name = "Precharge",
                                     .on_enter = precharge_on_enter,
                                     .on_update = precharge_on_update,
                                     .on_exit = precharge_on_exit});

    fsm_add_state(g_fsm, (fsm_state_t){.name = "Active",
                                     .on_enter = active_on_enter,
                                     .on_update = active_on_update,
                                     .on_exit = active_on_exit});

    fsm_add_state(g_fsm, (fsm_state_t){.name = "Charge",
                                     .on_enter = charge_on_enter,
                                     .on_update = charge_on_update,
                                     .on_exit = charge_on_exit});

    fsm_add_state(g_fsm, (fsm_state_t){.name = "Fault",
                                     .on_enter = fault_on_enter,
                                     .on_update = fault_on_update,
                                     .on_exit = fault_on_exit});
}

// Add transitions to the FSM states
void FSMAddTransitions()
{
    fsm_add_transition(g_fsm, "Idle", "Precharge", FSM_PREDICATE_GROUP(transition_idle_to_precharge));
    fsm_add_transition(g_fsm, "Idle", "Fault", FSM_PREDICATE_GROUP(transition_to_fault));
    fsm_add_transition(g_fsm, "Precharge", "Active", FSM_PREDICATE_GROUP(transition_precharge_to_active));
    fsm_add_transition(g_fsm, "Precharge", "Fault", FSM_PREDICATE_GROUP(transition_to_fault));
    fsm_add_transition(g_fsm, "Active", "Charge", FSM_PREDICATE_GROUP(transition_active_to_charge));
    fsm_add_transition(g_fsm, "Active", "Idle", FSM_PREDICATE_GROUP(transition_active_to_idle));
    fsm_add_transition(g_fsm, "Active", "Fault", FSM_PREDICATE_GROUP(transition_to_fault));
    fsm_add_transition(g_fsm, "Charge", "Active", FSM_PREDICATE_GROUP(transition_charge_to_active));
    fsm_add_transition(g_fsm, "Charge", "Fault", FSM_PREDICATE_GROUP(transition_to_fault));
    fsm_add_transition(g_fsm, "Fault", "Idle", FSM_PREDICATE_GROUP(transition_fault_to_idle));
}
