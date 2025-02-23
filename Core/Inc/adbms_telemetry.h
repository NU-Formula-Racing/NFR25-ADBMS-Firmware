#include "can_interface.h"
#include "virtualTimer.h"

typedef enum {
    kIdle = 0,
    kPrecharge = 1,
    kActive = 2,
    kCharging = 3,
    kFault = 4,
} BMSState;


ICAN &hp_can_bus_; // hp is drive
ICAN &lp_can_bus_; // lp is data
ICAN &vb_can_bus_; // vb is charger

VirtualTimerGroup &timer_group_;
IBMS &bms_;


// BMS SOE
MakeUnsignedCANSignal(float, 0, 12, 0.1, 0) max_discharge_signal_;
MakeUnsignedCANSignal(float, 12, 12, 0.1, 0) max_regen_signal_;
MakeUnsignedCANSignal(float, 24, 16, 0.01, 0) battery_voltage_signal_;
MakeUnsignedCANSignal(float, 40, 8, 1, -40) battery_temperature_signal_;
MakeUnsignedCANSignal(float, 48, 16, 0.01, 0) battery_current_signal_;

CANTXMessage<5> hp_soe_message_ {
    hp_can_bus_,
    0x173,
    false,
    8,
    10,
    timer_group_,
    max_discharge_signal_,
    max_regen_signal_,
    battery_voltage_signal_,
    battery_temperature_signal_,
    battery_current_signal_ 
};


// BMS faults
MakeUnsignedCANSignal(bool, 0, 1, 1, 0) fault_summary_signal_;
MakeUnsignedCANSignal(bool, 1, 1, 1, 0) undervoltage_fault_signal_;
MakeUnsignedCANSignal(bool, 2, 1, 1, 0) overvoltage_fault_signal_;
MakeUnsignedCANSignal(bool, 3, 1, 1, 0) undertemperature_fault_signal_;
MakeUnsignedCANSignal(bool, 4, 1, 1, 0) overtemperature_fault_signal_;
MakeUnsignedCANSignal(bool, 5, 1, 1, 0) overcurrent_fault_signal_;
MakeUnsignedCANSignal(bool, 6, 1, 1, 0) external_kill_fault_signal_;
MakeUnsignedCANSignal(bool, 7, 1, 1, 0) open_wire_fault_signal_;

CANTXMessage<8> hp_fault_message_ {
    hp_can_bus_,
    0x174,
    false,
    
}


// BMS status
MakeUnsignedCANSignal(BMSState, 0, 8, 1, 0) bms_state_signal_;
MakeUnsignedCANSignal(BMSState, 0, 8, 1, 0) imd_state_signal_;
MakeUnsignedCANSignal(float, 16, 8, 1, -40) max_cell_temp_signal_;
MakeUnsignedCANSignal(float, 24, 8, 1, -40) min_cell_temp_signal_;
MakeUnsignedCANSignal(float, 32, 8, 0.012, 2) max_cell_voltage_signal_;
MakeUnsignedCANSignal(float, 40, 8, 0.012, 2) min_cell_voltage_signal_;
MakeUnsignedCANSignal(float, 48, 8, 0.5, 0) bms_soc_signal_;