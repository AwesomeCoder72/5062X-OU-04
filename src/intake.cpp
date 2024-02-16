#include "intake.hpp"
#include "main.h"

void spin_intake_auto(bool intaking, int velocity) {
  if (intaking) {
    Intake.move_relative(100000, velocity);
  } else if (!intaking) {
    Intake.move_relative(-100000, velocity);
  }
}

void stop_intake_auto() {
  Intake.move_velocity(0);
}

int intake_spinning = 0;

void spin_intake_driver(int intakeButtonValue, int outtakeButtonValue) {

  if (((intakeButtonValue == 1) && (outtakeButtonValue == 1)) || 
      ((intakeButtonValue == 0) && (outtakeButtonValue == 0)))  {
        Intake.move_voltage(0);
      } else if (intakeButtonValue == 1) {
        Intake.move_voltage(12000);
      } else if (outtakeButtonValue == 1) {
        Intake.move_voltage(-12000);
      }
}