/*

ADBMS State Machine Pseudocode
By: Albert Luo

*/



/*

BMS Class:

public:
    command_signal  // gets CAN signals and communicates with ECU
    current_state  // current state of the BMS
    fault  // is bms currently faulted or not
    adbms  // adbms library that retrieves AD data 


functions:
    Tick()
    CalculateSOE()
    UpdateValues()
    CheckFaults()

    enter func:
        idle_on_enter
        precharge_on_enter
        active_on_enter
        charge_on_enter
        fault_on_enter

    update func:
        idle_on_update
        precharge_on_update
        active_on_update
        charge_on_update
        fault_on_update

    exit func:
        idle_on_exit
        precharge_on_exit
        active_on_exit
        charge_on_exit
        fault_on_exit

    predicate func:
        ->idle:
            active
            fault
        
        ->precharge:
            idle
        
        ->active:
            precharge
            charge

        ->charge:
            active

        ->fault:
            idle
            precharge
            active
            charge
            


void Initialize() {
    initialize the contactors;
    initialize ad chip;
    initialize CAN; // do later
    initialize Charger; // do later

    // FMS Init
    FSMAddStates();
    FSMAddTransitions();
    fsm_set_state("idle");
}

void Tick() {
    feed watchdog;
    UpdateValues();
    CheckFaults();
    fsm_run();
}

void UpdateValues() {
    get voltages from ADBMS;
    get temp from ADBMS;
    calculate the SOE;  // ignore for now

    update STM32 Pin values;
}


void CheckFaults() {
    check overvoltage fault;
    check undervoltage fault;
    check overcurrent fault;
    check overtemperature fault;
    check undertemperature fault;
    check external kill fault;
    check timeout fault; (watchdog not fed)

    raise fault flag if any fault is true;
}

void idle_on_enter() { 
    printf("entering idle..."); 
    open contactors;
    send idle msg;
}
void precharge_on_enter() { 
    printf("entering precharge..."); 
    turn on P contactor
    turn on Pre contactor;
}
void active_on_enter() { 
    printf("entering active..."); 
    turn on N contactor;
    delay(0.1 sec)
    turn off Pre contactor;
    send active msg;
}
void charge_on_enter() { 
    printf("entering charge...");
    initial talk to charger; 
}
void fault_on_enter() { 
    printf("entering fault..."); 
    open contactors;
    send fault msg;
}


void idle_on_update() {}
void precharge_on_update() { get inverter voltage; }
void active_on_update() {}
void charge_on_update() {
    // do actual implementation later
    if(charger responding && current flowing){
        ProcessCellBalancing();
    }
    if(charged to full){
        stop charging;
    }
}
void fault_on_update() {}


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


void FSMAddStates() {
    fsm_add_state("idle");
    fsm_add_state("precharge");
    fsm_add_state("active");
    fsm_add_state("charge");
    fsm_add_state("fault");
}

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


*/


// CAN MSG NOTES
// have it report external vs interal fault
