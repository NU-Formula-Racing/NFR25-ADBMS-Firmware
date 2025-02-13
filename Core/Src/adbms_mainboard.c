#include "adbms_mainboard.h"
#include "adBMS_Application.h"
#include "adbms_update_values.h"

void adbms_mainbaord_setup(){
    // initialize the contactors;
    // initialize ad chip;
    // initialize CAN; // do later 
        // add the CAN to the timer group with a different timer (one for drive, one for data)
    // initialize Charger; // do later

    // FMS Init
    //FSMAddStates();
    //FSMAddTransitions();
    //fsm_set_state("idle");

    // initialize the timer group with adbms_mainboard_loop

}

// Loop that gets ticked
void adbms_mainboard_loop(){
    // feed watchdog;
    UpdateValues();
    CheckFaults();
    fsm_run();
}

void UpdateValues(){
    // ADBMS values
    ADBMS_UpdateValues();

    // update STM32 Pin values;
        // reads: shutdown_contactors, IMD_Status, Current_ADC, 6822_State
        // writes: BMS_Status, GPIO_LEDs
}

// CAN Loops - Do later
void data_can_loop(){
    // Send out 
        // voltages: pack voltage, max cell voltage, min cell voltage, avg cell voltage
        // temp: max temp, avg temp
        // misc: BMS_state, IMD_state
}
void drive_can_loop(){
    // send out everything
}


void CheckFaults() {
    // check overvoltage fault;
    // check undervoltage fault;
    // check overcurrent fault;
    // check overtemperature fault;
    // check undertemperature fault;
    // check external kill fault;
    // check timeout fault; (watchdog not fed)

    // raise fault flag if any fault is true;
}

// FSM Functions //

// On_Enters
void idle_on_enter() { 
    printf("entering idle..."); 
    // open contactors;
    // send idle msg;
}
void precharge_on_enter() { 
    printf("entering precharge..."); 
    // turn on P contactor
    // turn on Pre contactor;
}
void active_on_enter() { 
    printf("entering active..."); 
    // turn on N contactor;
    // delay(0.1 sec);
    // turn off Pre contactor;
    // send active msg;
}
void charge_on_enter() { 
    printf("entering charge...");
    // send initial/start msg to charger; 
}
void fault_on_enter() { 
    printf("entering fault..."); 
    // open (turn off) all contactors;
    // send fault msg;
}


// On_Updates
void idle_on_update() {}
void precharge_on_update() { 
    //get inverter voltage; 
}
void active_on_update() {}
void charge_on_update() {
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
void fault_on_update() {}


// On_Exits
void idle_on_exit() { printf("exiting idle..."); }
void precharge_on_exit() { printf("exiting precharge..."); }
void active_on_exit() { printf("exiting active..."); }
void charge_on_exit() { printf("exiting charge..."); }
void fault_on_exit() { printf("exiting fault..."); }



// Predicates


// Transition to idle
bool transition_active_to_idle() {
    if (ECU or charger requests idle) return true;
    return false;
}
bool transition_fault_to_idle() {
    if (fault flag is cleared) return true;
    return false;
}

// Transition to precharge
bool transition_idle_to_precharge() {
    if (ECU/Charger signals precharge transition) return true;
    return false;
}

// Transition to active
bool transition_precharge_to_active() {
    if (ECU signals active transition) return true;
    return false;
}

bool transition_charge_to_active() {
    if (charge bit unset) return true;
    return false;
}

// Transition to charge
bool transition_active_to_charge(){
    if (charge pin is high) return true;
    return false;
}

//Transition to fault
bool transition_to_fault() {
    if(fault flag is raised) return true;
    return false;
} 

// Add FSM states
void FSMAddStates() {
    fsm_add_state("idle");
    fsm_add_state("precharge");
    fsm_add_state("active");
    fsm_add_state("charge");
    fsm_add_state("fault");
}

// Add transitions to the FSM states
void FSMAddTransitions() {
    fsm_add_transition("idle", "precharge", transition_idle_to_precharge);
    fsm_add_transition("idle", "fault", transition_to_fault);
    fsm_add_transition("precharge", "active", transition_precharge_to_active);
    fsm_add_transition("precharge", "fault", transition_to_fault);
    fsm_add_transition("active", "charge", transition_active_to_charge);
    fsm_add_transition("active", "idle", transition_active_to_idle);
    fsm_add_transition("active", "fault", transition_to_fault);
    fsm_add_transition("charge", "active", transition_charge_to_active);
    fsm_add_transition("charge", "fault", transition_to_fault);
    fsm_add_transition("fault", "idle", transition_fault_to_idle);
}

