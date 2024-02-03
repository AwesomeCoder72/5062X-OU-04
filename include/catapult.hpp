#pragma once
#include "main.h"
#include "pros/motors.hpp"

/*
    DEFINES CATAPULT FUNCTIONS
*/

extern pros::Motor Catapult;

void spin_cata_driver(int shootButtonValue, int velocity);
void spin_cata_auto(int velocity);

void stop_cata_auto();