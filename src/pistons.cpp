#include  "pistons.hpp"
#include "main.h"

bool intake_actuated_value = false;

void actuate_intake(bool down_value) {
  IntakeActuator.set_value(down_value);
  intake_actuated_value = down_value;
}

bool wings_actuated_value = false;

void actuate_wings(bool out_value) {
  WingsActuator.set_value(out_value);
  wings_actuated_value = out_value;
}

void piston_control_driver(int intakeButton, int wingButton) {
    
}