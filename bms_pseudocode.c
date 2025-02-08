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
        drive_on_enter
        charge_on_enter
        fault_on_enter

    update func:
        idle_on_update
        precharge_on_update
        drive_on_update
        charge_on_update
        fault_on_update

    exit func:
        idle_on_exit
        precharge_on_exit
        drive_on_exit
        charge_on_exit
        fault_on_exit

    predicate func:
        ->idle:
            drive
            fault
        
        ->precharge:
            idle
        
        ->drive:
            precharge
            charge

        ->charge:
            drive

        ->fault:
            idle
            precharge
            drive
            charge
            



Functions for BMS Class:
    void Initialize() {
        initialize the contactors;
        initialize ad chip;
        initialize CAN;
    }

    void idle_on_enter() { 
        printf("entering idle..."); 
        open contactors;
    }
    void precharge_on_enter() { 
        printf("entering precharge..."); 
        turn on precharge contactors;
        start precharging;
        start prechargetimer;
    }
    void drive_on_enter() { 
        printf("entering drive..."); 
        turn on contactors;
    }
    void charge_on_enter() { 
        printf("entering charge..."); 
        if(no faults || chargers connected){
            ProcessCellBalancing();
        }
    }
    void fault_on_enter() { 
        printf("entering fault..."); 
        open contactors;
    }


    void idle_on_update() {}
    void precharge_on_update() { prechargetimer.tick(); }
    void drive_on_update() {}
    void charge_on_update() {
        if(charged to full){
            stop charging;
        }
    }
    void fault_on_update() {}


    void idle_on_exit() { printf("exiting idle..."); }
    void precharge_on_exit() { 
        printf("exiting precharge..."); 
        disable precharge contactors;
    }
    void drive_on_exit() { printf("exiting drive..."); }
    void charge_on_exit() { printf("exiting charge..."); }
    void fault_on_exit() { printf("exiting fault..."); }


    // Predicates

    // Transition to idle
    bool transition_drive_to_idle() {
        if (charge requests idle) return true;
        return false;
    }
    bool transition_fault_to_idle() {
        if (fault flag is cleared) return true;
        return false;
    }

    // Transition to precharge
    bool transition_idle_to_precharge() {
        if (ECU signals precharge transition) return true;
        return false;
    }

    // Transition to drive
    bool transition_precharge_to_drive() {
        if (ECU signals drive transition) return true;
        return false;
    }

    bool transition_charge_to_drive() {
        if (charge bit unset) return true;
        return false;
    }

    //Transition to fault
    bool transition_to_fault() {
        if(fault flag is raised) return true;
        return false;
    } 


    void AddStates() {
        fsm_add_state("idle");
        fsm_add_state("precharge");
        fsm_add_state("drive");
        fsm_add_state("charge");
        fsm_add_state("fault");
    }

    void AddTransitions() {
        fsm_add_transition("idle", "precharge", transition_idle_to_precharge);
        fsm_add_transition("idle", "fault", transition_to_fault);
        fsm_add_transition("precharge", "drive", transition_precharge_to_drive);
        fsm_add_transition("precharge", "fault", transition_to_fault);
        fsm_add_transition("drive", "charge", transition_drive_to_charge);
        fsm_add_transition("drive", "idle", transition_drive_to_idle);
        fsm_add_transition("drive", "fault", transition_to_fault);
        fsm_add_transition("charge", "drive", transition_charge_to_drive);
        fsm_add_transition("charge", "fault", transition_to_fault);
        fsm_add_transition("fault", "idle", transition_fault_to_idle);
    }

    void Init() {
        AddStates();
        AddTransitions();
        fsm_set_state("idle");
    }

    void CheckFaults() {
        check overvoltage fault;
        check undervoltage fault;
        check overcurrent fault;
        check overtemperature fault;
        check undertemperature fault;
        check external kill fault;

        raise fault flag if any fault is true;
    }

    void UpdateValues() {
        get current from ADBMS;
        get voltages from ADBMS;
        calculate the SOE;
    }

    void Tick() {
        feed watchdog;
        UpdateValues();
        CheckFaults();
        fsm_run();
    }


*/
