#pragma once
#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"

extern pros::ADIDigitalOut IntakeActuator;
extern pros::ADIDigitalOut WingsActuator;

extern bool intake_actuated_value;
extern bool wings_actuated_value;


void actuate_intake(bool down_value);
void actuate_wings(bool out_value);